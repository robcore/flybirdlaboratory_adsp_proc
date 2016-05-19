/** vi: tw=128 ts=3 sw=3 et
@file pd_elf.c
@brief This file contains the API details for the Protection Domain Monitor, API 1.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2014 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/pd_mon/src/pd_elf.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "msg.h"
#include "pd_dump.h"

#include "pd_elf.h"
#include "pd_elf_hexagon.h"

// wrapper to help a crippled API by chunking writes in 1KB

#define CHUNKSIZE 256

static int chunk_write(int fd, char* buf_p, unsigned int buf_s)
{
   int temp_s = buf_s;
   int chunk_s = CHUNKSIZE;
   int trys = 0;
   int ret_s;

   while (0 < temp_s) // while buf still has content to write
   {
      // write a chunk via a crippled API

#if 1
      ret_s = 0;
#else
      ret_s = rfsa_write(fd, buf_p, chunk_s < temp_s ? chunk_s : temp_s);
#endif

      // adjust base address and size based on amount of chunk written

      buf_p += ret_s;
      temp_s -= ret_s;

      // bail out if we cant write this small of a chunk multiple times.
      // the maximum acceptable try count will be set to 1 when the last
      // portion of the buffer is smaller than a chunk size write. anything
      // larger than 1 should be suspect, and we bailout on 3.

      if (chunk_s > ret_s && 3 > trys)
      {
         trys++;
      }
      else
      {
         MSG_SPRINTF_1(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump chunk write error", 0);
         return 0;
      }
   }

   if (1 == trys)
   {
      // indicates that the data buffer was not a multiple of chunk size
   }

   return buf_s; // completed
}

PD_ELF_STATUS pd_elf_header_init(Elf32_Ehdr* header_p)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;

   if (NULL != header_p)
   {
      secure_memset(header_p, 0, sizeof(*header_p));

      header_p->e_ident[EI_MAG0]    = ELFMAG0;
      header_p->e_ident[EI_MAG1]    = ELFMAG1;
      header_p->e_ident[EI_MAG2]    = ELFMAG2;
      header_p->e_ident[EI_MAG3]    = ELFMAG3;
      header_p->e_ident[EI_CLASS]   = ELFCLASS32;
      header_p->e_ident[EI_DATA]    = ELFDATA2LSB;
      header_p->e_ident[EI_VERSION] = EV_CURRENT;

      header_p->e_ident[EI_OSABI]  = ELFOSABI_NONE;

      header_p->e_type             = ET_CORE;
      header_p->e_machine          = EM_HEXAGON;
      header_p->e_version          = EV_CURRENT;
      header_p->e_ehsize           = sizeof(Elf32_Ehdr);

      header_p->e_shentsize        = sizeof(Elf32_Shdr);
      header_p->e_phentsize        = sizeof(Elf32_Phdr);

      header_p->e_shstrndx         = SHN_UNDEF;

      rc = PD_ELF_STATUS_SUCCESS;
   }

   return rc;
}

static PD_ELF_STATUS pd_elf_header_write(Elf32_Ehdr* header_p, int fd)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;

   if (header_p->e_ehsize == chunk_write(fd, (void*)header_p, header_p->e_ehsize))
   {
      rc = PD_ELF_STATUS_SUCCESS;
   }

   return rc;
}

static PD_ELF_STATUS pd_elf_header_free(Elf32_Ehdr* header_p)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;

   if (NULL != header_p)
   {
      secure_memset(header_p, 0, sizeof(*header_p));

      rc = PD_ELF_STATUS_SUCCESS;
   }

   return rc;
}

static inline Elf32_Half pd_elf_prgtab_count(Elf32_Ehdr* header_p, pd_elf_prgtab_p* prgtab_p)
{
   pd_elf_prgtab_p pt_p;
   Elf32_Half count = 0;

   for (pt_p = *prgtab_p; NULL != pt_p; pt_p = pt_p->next)
   {
      count++;
   }

   return count;
}

static inline Elf32_Off pd_elf_prgtab_size(Elf32_Ehdr* header_p, pd_elf_prgtab_p* prgtab_p)
{
   pd_elf_prgtab_p pt_p;
   Elf32_Off size = 0;

   for (pt_p = *prgtab_p; NULL != pt_p; pt_p = pt_p->next)
   {
      size += pt_p->phdr.p_filesz;
   }

   return size;
}

PD_ELF_STATUS pd_elf_prgtab_alloc(Elf32_Ehdr* header_p, pd_elf_prgtab_p* prgtab_p, Elf32_Word type, char* name, Elf32_Word ntype, void* addr, Elf32_Half size)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;
   pd_elf_prgtab_p pt_p = malloc(sizeof(pd_elf_prgtab_t));

   if (NULL != pt_p)
   {
      Elf32_Word name_len = strlen(name) + 1;
      Elf32_Word name_pad = 0;

      secure_memset(pt_p, 0, sizeof(pd_elf_prgtab_t));

      pt_p->phdr.p_offset = 0;
      pt_p->phdr.p_type = type;
      pt_p->phdr.p_align = 0;

      switch (type)
      {
         case PT_LOAD:
         {
            pt_p->size = size;
            pt_p->addr = addr;
            pt_p->name = name;

            pt_p->phdr.p_vaddr = (Elf32_Addr)addr;
            pt_p->phdr.p_filesz = size;
            pt_p->phdr.p_memsz = size;
            pt_p->phdr.p_flags = PF_R + PF_W;

            pt_p->next = *prgtab_p;

            *prgtab_p = pt_p;

            rc = PD_ELF_STATUS_SUCCESS;

            break;
         }

         case PT_NOTE:
         {
            if (0 != name_len % sizeof(Elf32_Word))
            {
               name_pad = sizeof(Elf32_Word) - name_len % sizeof(Elf32_Word);
            }

            pt_p->size = sizeof(Elf32_Nhdr) + name_len + name_pad;
            pt_p->size += size;

            pt_p->addr = malloc(pt_p->size);

            if (NULL != pt_p->addr)
            {
               secure_memset(pt_p->addr, 0, pt_p->size);

               ((Elf32_Nhdr*)pt_p->addr)->n_namesz = name_len;
               ((Elf32_Nhdr*)pt_p->addr)->n_descsz = size;
               ((Elf32_Nhdr*)pt_p->addr)->n_type = ntype;

               memsmove((char*)pt_p->addr + sizeof(Elf32_Nhdr), name_len, name, name_len);

               memsmove((char*)pt_p->addr + sizeof(Elf32_Nhdr) + name_len + name_pad, size, addr, size);

               pt_p->name = name;

               pt_p->phdr.p_vaddr = 0;
               pt_p->phdr.p_filesz = pt_p->size;
               pt_p->phdr.p_memsz = 0;
               pt_p->phdr.p_flags = 0;

               pt_p->next = *prgtab_p;

               *prgtab_p = pt_p;

               rc = PD_ELF_STATUS_SUCCESS;

               break;
            }

            else
            {
               free(pt_p);
            }

            break;
         }
      }
   }

   return rc;
}

static PD_ELF_STATUS pd_elf_prgtab_prepare_offsets(Elf32_Ehdr* header_p, pd_elf_prgtab_p* prgtab_p, pd_elf_sectab_p* sectab_p)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;
   pd_elf_prgtab_p pt_p;
   Elf32_Off offset;

   header_p->e_phnum = pd_elf_prgtab_count(header_p, prgtab_p);
   header_p->e_phoff = header_p->e_ehsize;

   offset = header_p->e_phoff + header_p->e_phentsize * header_p->e_phnum;

   for (pt_p = *prgtab_p; NULL != pt_p; pt_p = pt_p->next)
   {
      if (0 != pt_p->phdr.p_filesz)
      {
         pt_p->phdr.p_offset = offset;

         offset += pt_p->phdr.p_filesz;
      }
   }

   rc = PD_ELF_STATUS_SUCCESS;

   return rc;
}

PD_ELF_STATUS pd_elf_prgtab_write(Elf32_Ehdr* header_p, pd_elf_prgtab_p* prgtab_p, int fd)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;
   pd_elf_prgtab_p pt_p;

   // Write ALL Headers

   for (pt_p = *prgtab_p; NULL != pt_p; pt_p = pt_p->next)
   {
      if (sizeof(Elf32_Phdr) == chunk_write(fd, (void*)&pt_p->phdr, sizeof(Elf32_Phdr)))
      {
         // SUCCESS
      }
      else
      {
         break; // for ()
      }
   }

   // Write ALL Sections

   for (pt_p = *prgtab_p; NULL != pt_p; pt_p = pt_p->next)
   {
      if (0 != pt_p->phdr.p_filesz)
      {
         if (pt_p->phdr.p_filesz == chunk_write(fd, (void*)pt_p->addr, pt_p->phdr.p_filesz))
         {
            // SUCCESS
         }
         else
         {
            break; // for ()
         }
      }
   }

   rc = PD_ELF_STATUS_SUCCESS;

   return rc;
}

PD_ELF_STATUS pd_elf_prgtab_free(Elf32_Ehdr* header_p, pd_elf_prgtab_p* prgtab_p)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;

   while (NULL != *prgtab_p)
   {
      pd_elf_prgtab_p pt_p = *prgtab_p;

      *prgtab_p = pt_p->next;

      switch (pt_p->phdr.p_type)
      {
         case PT_LOAD:
            break;

         case PT_NOTE:
            free(pt_p->addr);
            break;
      }

      free(pt_p);
   }

   rc = PD_ELF_STATUS_SUCCESS;

   return rc;
}

static inline Elf32_Half pd_elf_sectab_count(Elf32_Ehdr* header_p, pd_elf_sectab_p *sectab_p)
{
   pd_elf_sectab_p st_p;
   Elf32_Half count = 0;

   for (st_p = *sectab_p; NULL != st_p; st_p = st_p->next)
   {
      count++;
   }

   return count;
}

static inline Elf32_Off pd_elf_sectab_size(pd_elf_sectab_p* sectab_p)
{
   pd_elf_sectab_p st_p;
   Elf32_Off size = 0;

   for (st_p = *sectab_p; NULL != st_p; st_p = st_p->next)
   {
      size += st_p->shdr.sh_size;
   }

   return size;
}

PD_ELF_STATUS pd_elf_sectab_alloc(Elf32_Ehdr* header_p, pd_elf_sectab_p* sectab_p, Elf32_Word type, Elf32_Word link)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;
   pd_elf_sectab_p st_p = malloc(sizeof(pd_elf_sectab_t));

   if (NULL != st_p)
   {
      secure_memset(st_p, 0, sizeof(pd_elf_sectab_t));

      st_p->shdr.sh_offset = 0;
      st_p->shdr.sh_type = type;
      st_p->shdr.sh_link = link;

      st_p->next = *sectab_p;

      *sectab_p = st_p;

      rc = PD_ELF_STATUS_SUCCESS;
   }

   return rc;
}

static PD_ELF_STATUS pd_elf_sectab_prepare_offsets(Elf32_Ehdr* header_p, pd_elf_prgtab_p* prgtab_p, pd_elf_sectab_p* sectab_p)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;
   pd_elf_sectab_p st_p;
   Elf32_Off offset;

   header_p->e_shnum = pd_elf_sectab_count(header_p, sectab_p);
   header_p->e_shoff = header_p->e_phoff + header_p->e_phentsize * header_p->e_phnum + pd_elf_prgtab_size(header_p, prgtab_p);

   offset = header_p->e_shoff + header_p->e_shentsize * header_p->e_shnum;

   for (st_p = *sectab_p; NULL != st_p; st_p = st_p->next)
   {
      if (0 != st_p->shdr.sh_size)
      {
         st_p->shdr.sh_offset = offset;

         offset += st_p->shdr.sh_size;
      }
   }

   rc = PD_ELF_STATUS_SUCCESS;

   return rc;
}

static PD_ELF_STATUS pd_elf_sectab_write(Elf32_Ehdr* header_p, pd_elf_sectab_p* sectab_p, int fd)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;
   pd_elf_sectab_p st_p;

   for (st_p = *sectab_p; NULL != st_p; st_p = st_p->next)
   {
      if (sizeof(Elf32_Shdr) == chunk_write(fd, (void*)&st_p->shdr, sizeof(Elf32_Shdr)))
      {
         // SUCCESS
      }
      else
      {
         break; // for ()
      }
   }

   if (NULL == st_p)
   {
      for (st_p = *sectab_p; NULL != st_p; st_p = st_p->next)
      {
         if (0 != st_p->shdr.sh_size)
         {
            if (st_p->shdr.sh_size == chunk_write(fd, (void*)st_p->shdr.sh_addr, st_p->shdr.sh_size))
            {
               // SUCCESS
            }
            else
            {
               break; // for ()
            }
         }
      }

      if (NULL == st_p)
      {
         rc = PD_ELF_STATUS_SUCCESS;
      }
   }

   return rc;
}

static PD_ELF_STATUS pd_elf_sectab_free(Elf32_Ehdr* header_p, pd_elf_sectab_p* sectab_p)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;

   while (NULL != *sectab_p)
   {
      pd_elf_sectab_p st_p = *sectab_p;

      *sectab_p = st_p->next;

      free(st_p);
   }

   rc = PD_ELF_STATUS_SUCCESS;

   return rc;
}

PD_ELF_STATUS pd_elf_init(Elf32_Ehdr* header_p, pd_elf_prgtab_p* prgtab_p, pd_elf_sectab_p* sectab_p)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;

   if (PD_ELF_STATUS_SUCCESS == pd_elf_header_init(header_p))
   {
      rc = PD_ELF_STATUS_SUCCESS;
   }

   return rc;
}

PD_ELF_STATUS pd_elf_prepare_offsets(Elf32_Ehdr* header_p, pd_elf_prgtab_p* prgtab_p, pd_elf_sectab_p* sectab_p)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;

   if (PD_ELF_STATUS_SUCCESS == pd_elf_prgtab_prepare_offsets(header_p, prgtab_p, sectab_p) &&
       PD_ELF_STATUS_SUCCESS == pd_elf_sectab_prepare_offsets(header_p, prgtab_p, sectab_p))
   {
      rc = PD_ELF_STATUS_SUCCESS;
   }

   return rc;
}

PD_ELF_STATUS pd_elf_write(Elf32_Ehdr* header_p, pd_elf_prgtab_p* prgtab_p, pd_elf_sectab_p* sectab_p, int fd)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;

   if (PD_ELF_STATUS_SUCCESS != pd_elf_header_write(header_p, fd))
   {
      MSG_SPRINTF_1(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump write header error", 0);
      return rc;
   }

   if (PD_ELF_STATUS_SUCCESS != pd_elf_prgtab_write(header_p, prgtab_p, fd))
   {
      MSG_SPRINTF_1(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump write prgtab error", 0);
      return rc;
   }

   if (PD_ELF_STATUS_SUCCESS != pd_elf_sectab_write(header_p, sectab_p, fd))
   {
      MSG_SPRINTF_1(MSG_SSID_TMS, MSG_LEGACY_ERROR, "device dump write sectab error", 0);
      return rc;
   }

   rc = PD_ELF_STATUS_SUCCESS;
   return rc;
}

PD_ELF_STATUS pd_elf_term(Elf32_Ehdr* header_p, pd_elf_prgtab_p* prgtab_p, pd_elf_sectab_p* sectab_p)
{
   PD_ELF_STATUS rc = PD_ELF_STATUS_ERROR;

   if (PD_ELF_STATUS_SUCCESS == pd_elf_prgtab_free(header_p, prgtab_p) &&
       PD_ELF_STATUS_SUCCESS == pd_elf_sectab_free(header_p, sectab_p) &&
       PD_ELF_STATUS_SUCCESS == pd_elf_header_free(header_p))
   {
      rc = PD_ELF_STATUS_SUCCESS;
   }

   return rc;
}
