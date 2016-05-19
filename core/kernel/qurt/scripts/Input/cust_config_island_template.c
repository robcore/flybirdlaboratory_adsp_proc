#if KERNELSEP
#define KSEP(a,b) a
#else
#define KSEP(a,b) b
#endif

#ifdef CONFIG_SECTIONS
#define SECTION(s, a) __attribute__((section(s "." a)))
#else
#define SECTION(s, a)
#endif

#define CONFIG_DEFAULT                                            /* Expands to nothing, but can be a macro argument */
#ifdef GEN_CONFIG_HEADER
#define IDIM(x)
#define CONFIG_SEC_VAR(c,s,t,n,i)    extern typeof(t)       n
#define CONFIG_RW_VAR(c,t,n,i)       extern typeof(t)       n
#define CONFIG_RO_VAR(c,t,n,i)       extern typeof(t) const n
#define CONFIG_RW_SPACE(c,s,t,n,a,i) extern typeof(t)       n
#define CONFIG_ZI_SPACE(c,s,t,n,a)   extern typeof(t)       n
#else
#define IDIM(x) x
#define CONFIG_SEC_VAR(c,s,t,n,i)    typeof(t)       n   s = i    /* This (section config vars) will be deprecated soon */
#define CONFIG_RW_VAR(c,t,n,i)       typeof(t)       n     = i    /* This (R/W config vars) will be deprecated soon */
#define CONFIG_RO_VAR(c,t,n,i)       typeof(t) const n     = i    /* Preferred way to declare information variables */
#define CONFIG_RW_SPACE(c,s,t,n,a,i) typeof(t)       n a s = i    /* Declare an initialized space-providing variable */
#define CONFIG_ZI_SPACE(c,s,t,n,a)   typeof(t)       n a s        /* Declare an un-initialized space-providing variable */
#endif

#define CACHEALIGNED __attribute__((aligned(32)))
#define DIVUP(number,divisor) (((number)/(divisor))+(((number)%(divisor))>0))  /* Divide, rounding up */
#define ROUNDUP(number,divisor) (DIVUP((number),(divisor))*(divisor))          /* Round up to multiple */
#define ARRAY_INIT(size) [0 ... (size)-1]
#define ALIGNED_SPACE(size) typeof(struct { unsigned char a[size] __attribute__((aligned(size))); })   /* Suitable for simple declaration of aligned space */
#define THREAD_CONTEXT typeof(struct { unsigned char a[THREAD_CONTEXT_TOTALSIZE] CACHEALIGNED; })      /* Suitable for declaring a thread context */

CONFIG_RW_VAR("Bit mask to start HW threads, 0x3f to start all HW threads",
              unsigned int,
              QURTK_hthread_startup,
              HTHREADMASK);

CONFIG_RW_VAR("Priority for main thread",
              unsigned int,
              qurtos_main_priority,
              QURTKMAINPRIORITY);
CONFIG_RW_VAR("Bitmask for main thread",
              unsigned int,
              qurtos_main_bitmask,
              QURTKMAINBITMASK);

#if QURTOSSTACKSIZE != 0
#define ACTUALQURTOSSTACKSIZE (QURTOSSTACKSIZE)
#elif defined(CONFIG_MP)
#define ACTUALQURTOSSTACKSIZE (0x7C0)
#else
#define ACTUALQURTOSSTACKSIZE (0x1C0)
#endif

CONFIG_RO_VAR("Stack size for guest-OS stack associated with each user thread",
              unsigned int,
              qurtos_stack_size,
              ROUNDUP(ACTUALQURTOSSTACKSIZE, 32));

struct objcache_config {
   short memory_blocks;
   short virt_regions;
   short phys_regions;
   short user_processes;
   short user_threads;
   short qurtos_threads;
   short shmem_regions;
};
#define OBJCACHE_DEFAULT (-1)
#define OBJCACHEINIT { \
   OBJCACHECONFIG \
}

CONFIG_RO_VAR("Object cache starting configuration",
              struct objcache_config,
              qurtos_objcache_config,
              OBJCACHEINIT);

CONFIG_RO_VAR("Priority for reaper thread",
              unsigned int,
              qurtos_reaper_priority,
              QURTOS_REAPER_PRIORITY);
CONFIG_RO_VAR("Tcb partition for reaper thread",
              unsigned int,
              qurtos_reaper_tcb_partition,
              QURTOS_REAPER_TCB_PARTITION);
CONFIG_RO_VAR("Stack size for reaper thread",
              unsigned int,
              qurtos_reaper_stack_size,
              QURTOSREAPERSTACKSIZE);

CONFIG_RW_VAR("Qurt PIMUTEX priority",
              unsigned int,
              QURTK_max_pi_prio,
              MAXPIMUTEXPRIO);

CONFIG_RO_VAR("Set to non-zero to cause qurtos to have a separate virtual pool for shared memory",
              unsigned int,
              qurtos_split_virt_pool,
              SPLITVIRTPOOL);

CONFIG_RW_SPACE("Stack space for main thread",
                __attribute__((section(".data.user.config"))),
                unsigned char [],
                qurtos_app_stack,
                CACHEALIGNED,
                {ARRAY_INIT(ROUNDUP(MAINSTACKSIZE,8)) = 0xF8});

CONFIG_RW_VAR("Stack size for main thread",
              unsigned int,
              qurtos_main_stack_size,
              sizeof(qurtos_app_stack));

CONFIG_RW_VAR("How many bytes at the beginning of each thread stack should be filled with F8F8F8F8 watermark?",
              unsigned int,
              qurt_osam_stack_fill_count,
              OSAMSTACKFILLCOUNT);

enum config_heap_type {
   QURTOS_CONFIG_HEAP_STATIC,   /* Statically allocated */
   QURTOS_CONFIG_HEAP_DYNAMIC,  /* Dynamically allocated */
   QURTOS_CONFIG_HEAP_ASLR,     /* Dynamically allocated at random address */
   QURTOS_CONFIG_HEAP_APPREGION /* Not allocated by QuRT -- left up to application */
};

struct config_heap_info {
   enum config_heap_type type;
   void *vaddr;
   unsigned size;
};

#if QURTOSAPPHEAPTYPE == 0
#if !defined(GEN_CONFIG_HEADER)
static unsigned char qurtos_app_heap[ROUNDUP(HEAPSIZE,4)] CACHEALIGNED __attribute__((section(".bss.user.config")));
#endif
#define QURTOSAPPHEAPINIT { QURTOS_CONFIG_HEAP_STATIC, qurtos_app_heap, sizeof(qurtos_app_heap) }
#elif QURTOSAPPHEAPTYPE == 1
#define QURTOSAPPHEAPINIT { QURTOS_CONFIG_HEAP_DYNAMIC, 0, ROUNDUP(HEAPSIZE,0x1000) }
#elif QURTOSAPPHEAPTYPE == 2
#define QURTOSAPPHEAPINIT { QURTOS_CONFIG_HEAP_ASLR, 0, ROUNDUP(HEAPSIZE,0x1000) }
#elif QURTOSAPPHEAPTYPE == 3
#define QURTOSAPPHEAPINIT { QURTOS_CONFIG_HEAP_APPREGION, 0, ROUNDUP(HEAPSIZE,0x1000) }
#endif

CONFIG_RO_VAR("Number of QDI handles permitted in guest-OS",
              unsigned int,
              qurtos_qdi_handle_count,
              QURTOSQDIHANDLES);

CONFIG_RW_VAR("Guest-OS application heap configuration",
              struct config_heap_info,
              qurtos_app_heap_cfg,
              QURTOSAPPHEAPINIT);

CONFIG_RW_VAR("Timetest port number",
              unsigned int,
              QURTK_timetest_port,
              TIMETESTPORT);

CONFIG_SEC_VAR("The address of IMEM that contains the flag for initializing ISDB",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_isdb_flag_imem_addr,
               ISDBIMEMADDR);

CONFIG_SEC_VAR("The address of memory-map ETM & ETB config registers",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_etm_cfg_base,
               ETMCFGBASEADDR);

CONFIG_RW_VAR("Interrupts that wake up the processor during TCXO shutdown; Most significant bit is INT 0",
              unsigned int,
              QURTK_tcxo_intmask,
              TCXOINTMASK);

CONFIG_SEC_VAR("flag to enable DMT scheduling",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_dmt_enabled,
               DMT_ENABLED);

CONFIG_SEC_VAR("flag to enable bus resources sharing",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_BQ_shared,
               BQ_SHARED);

CONFIG_RW_SPACE("Space for TCM dump",
                __attribute__((section(".data.user.config"))),
                unsigned char [],
                qurt_tcm_dump,
                CACHEALIGNED,
                {ARRAY_INIT(ROUNDUP(TCMSIZE,8)) = 0xFF});
CONFIG_RW_VAR("Size for TCM dump",
              unsigned int,
              qurt_tcm_dump_size,
              sizeof(qurt_tcm_dump));

/****************************************************************************
 * Default SSR (Supervisor Status Register) settings                        *
 * Read Q6 Architecture system-level Specification before change            *
 * Incorrect setting of any bit will cause runtime system failure           *
 * bit 0 is LSB                                                             *
 * bit 16:  the privilege mode the SW thread will be running                *
 *          1->user mode (default); 0->supervisor mode                      *
 * bit 22:  BadVa selector.                                                 * 
 *          1->BadVA1; 0->BadVA0 (default)                                  *
 * bit 23:  enable/disable reading PCYCLE register                          *
 *          1->enabled (default); 0->disabled                               *
 * bit 24:  enable/disable reading PMU                                      *
 *          1->enabled (default); 0->disabled                               *
 *                                                                          * 
 *  Default SSR bits from MSB:  0000,0001,1000,0111, 0000,0000,0000,0000    *
 ****************************************************************************/

CONFIG_RW_VAR("Default SSR value",
              unsigned int,
              QURTK_ssr_default,
              0x01870000
#if defined(CONFIG_MP)
              | 0x00080000      /* Enable guest OS mode initially */
#endif //defined(CONFIG_MP)
              );


/****************************************************************************
 * Default CCR (Cache Control Register) settings                            *
 *                                                                          *
 *   bits 0-1, 3-4, 6-7 are cache CP bits, and set to 0 to use CCCC attr    *
 *                                                                          *
 *   bit 16:  HFI for L1 I cache hardware prefetch                          *
 *          1->honor the USR[HFI] settings(default); 0->disabled            *
 *   bit 17:  HFD for L1 D cache hardware prefetch                               *
 *          1->honor the USR[HFD] settings(default); 0->disabled            *
 *   bit 18:  HFI-L2 for L2 I cache hardware prefetch                       *
 *          1->honor the USR[HFIL2] settings(default); 0->disabled          *
 *   bit 19:  HFD-L2 for L2 D cache hardware prefetch                       *
 *          1->honor the USR[HFDL2] settings(default); 0->disabled          *
 *   bit 20:  SFD for  DCFECTCH/L2FETCH                                     *
 *          1->enalble DCFETCH/L2FETCH based on CCCC and partition(default) *
 *          0->disable DCFETCH and L2FETCH                                  *
 *                                                                          * 
 *  Default CCR bits from MSB:  0000,0000,0001,0101, 0000,0000,0000,0000    *
 ****************************************************************************/
 
CONFIG_SEC_VAR("Default CCR value",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_config_ccr_default,
               CACHEATTR);

/****************************************************************************
 * Default USR Cache Prefetch settings                                      *
 *                                                                          *
 *   bit 14-13: HFD.  Two bits for L1 data cache prefetching.               *
 *          00: No prefetching  (default)                                   *
 *          01: Prefetch Loads with post-updating address mode when         *
 *          execution is within a hardware loop.                            *
 *          Prefetch up to 4 cache lines.                                   *
 *          10: Prefetch any hardware-detected striding Load when           *
 *          execution is within a hardware loop.                            *
 *          Prefetch up to 4 cache lines.                                   *
 *          11: Prefetch any hardware-detected striding Load.               *
 *          Prefetch up to 4 cache lines.                                   *
 *   bit 16-15: HFI.  Two bits for L1 instruction cache prefetching.        *
 *          00: No prefetching                                              *
 *          01: prefetching of at most 1 additional cache line (default)    *
 *          10: prefetching of at most 2 additional cache lines             *
 *   bit 17:  This bit is reserved.                      *
 *   bit l9-18: HFI-L2. Two bits for L2 prefetching for instructions.       *
 *          00 = Disable L2 instruction prefetching for this thread.        *
 *          01 = Enable L2 instruction prefetching of 1 line.               *
 *          10 = Enable L2 instruction prefetching of 2 lines (default).    *
 *          11 = Enable L2 instruction prefetching of 4 lines.              *
 *                                                                          * 
 *  Default USR bits from MSB:  0000,0000,0000,0101, 0000,0000,0000,0000    *
 ****************************************************************************/
 
CONFIG_SEC_VAR("Default USR value",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_config_usr_default,
               USRATTR);



/****************************************************************************
 * Configure L2 cache size                                                  *
 *                                                                          *
 * Dependent Features:                                                      *
 *      N/A                                                                 *
 *                                                                          *
 * NOTES:                                                                   *
 *      The value in this variable doesn't have the exact size number       *
 *      in Kilobytes. Instead, this variable has the value that is          *
 *      assigned to register - SYSCFG:L2CFG. Please refer to Hexagon        *
 *      Architecture system-level specification for more information        *
 *      about system register SYSCFG and L2 cache size configuration.       *
 *      The valid L2 cache size is 0KB, 64KB, 128KB, 256KB, 512kB(V4M).     *
 *      The default size is set by Qurt to 128KB.                           *
 *      - 0 (sets 0KB L2 cache size)                                        *
 *      - 1 (sets 64KB L2 cache size)                                       *
 *      - 2 (sets 128KB L2 cache size)                                      *
 *      - 3 (sets 256KB L2 cache size)                                      *
 *      - 4 (sets 512KB L2 cache size)                                      *
 *      - 100 (sets entire L2/TCM area as L2 cache)                         *
 ****************************************************************************/
#define kb_0   0 
#define kb_64  1
#define kb_128 2
#define kb_256 3
#define kb_512 4
#define kb_full 100

CONFIG_SEC_VAR("L2 cache size configuration",
               __attribute__((section(".data"))),
               unsigned char,
               QURTK_l2cache_size,
               L2SIZE);

/****************************************************************************
 * L2 cache non-write-allocate setting                                      *
 *                                                                          *
 * Dependent Features:                                                      *
 *      N/A                                                                 *
 *                                                                          *
 * NOTES:                                                                   *
 *      The L2 cache NWA is set to false by default if no input from XML.   *
 ****************************************************************************/
 
#define ENABLED     1
#define DISABLED    0
CONFIG_SEC_VAR("L2 cache non-write-allocate configuration",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_l2cache_nwa,
               L2CACHENWA);


/****************************************************************************
 * L2 cache write-back setting                                              *
 *                                                                          *
 * Dependent Features:                                                      *
 *      N/A                                                                 *
 *                                                                          *
 * NOTES:                                                                   *
 *      The L2 cache write-back support is only available on V3+ target.    *
 *      By default, L2 cache is write-through.                              *
 ****************************************************************************/
 
#define ENABLED     1
#define DISABLED    0
CONFIG_SEC_VAR("L2 cache write-back configuration",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_l2cache_wb,
               L2CACHEWB);

/****************************************************************************
 * L1 cache size setting                                                    *
 *                                                                          *
 * Dependent Features:                                                      *
 *      N/A                                                                 *
 *                                                                          *
 * NOTES:                                                                   *
 *      Enabling Half Icache or Dcache is only available on V3+ target.     *
 *      By default, Full I/D cache is used.                                 *
 ****************************************************************************/
 
CONFIG_SEC_VAR("L1 cache size setting",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_HI_cache,
               DISABLED);
CONFIG_SEC_VAR("L1 cache size setting",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_HD_cache,
               DISABLED);

/****************************************************************************
 * L1 cache partition settings                                              *
 *                                                                          *
 * Dependent Features:                                                      *
 *      N/A                                                                 *
 *                                                                          *
 * NOTES:                                                                   *
 *      The L1 data and instruction caches can be independently             *
 *      partitioned into two regions, a main partition and an auxiliary     *
 *      partition. The partitions are controlled by the ICPART and          *
 *      DCPART RW-bits in SYSCFG register. The feature is only              *
 *      available on v3+ targets.                                           *
 *                                                                          *
 *      The actual size of each cache partition also depends on the L1      *
 *      cache size setting. The following values are allowed for            *
 *      QURTK_DC_partition and QURTK_IC_partition:                        *
 *      - 0 (L1 cache is shared by all threads)                             *
 *      - 1 (L1 cache is split into two equal parts. Both main and          *
 *          auxiliary sections use 1/2 the cache)                           *
 *      - 2 (L1 cache is split into two parts. The main section is 3/4      *
 *          of the capacity, while the auxiliary section uses 1/4)          *
 *      - 3 (reserved)                                                      *
 ****************************************************************************/
#define full          0
#define half          1
#define three_quarter 2
#define resv          3

CONFIG_SEC_VAR("L1 data cache partition",
               __attribute__((section(".data"))),
               unsigned char,
               QURTK_DC_partition,
               L1DP);

CONFIG_SEC_VAR("L1 instruction cache partition",
               __attribute__((section(".data"))),
               unsigned char,
               QURTK_IC_partition,
               L1IP);


/****************************************************************************
 * L2 cache partition settings                                              *
 *                                                                          *
 * NOTES:                                                                   *
 *      L2 cache is partitioined into two regions, a main partition and     *
 *      an auxiliary. This are controlled by the L2PART in SYSCFG           *
 *      This feature is only available on v4+ targets.                      *
 *                                                                          *
 *      - 0 (L2 cache is fully shared)                                      *
 *      - 1 (L2 cache is split into two equal parts. Both main and          *
 *          auxiliary sections use 1/2 the cache)                           *
 *      - 2 (L2 cache is split into two parts. The main section is 3/4      *
 *          of the capacity, while the auxiliary section uses 1/4)          *
 *      - 3 (L2 cache is split into two parts. The main section is 7/8      *
 *          of the capacity, while the auxiliary section uses 1/8)          *
 ****************************************************************************/

// reuse the definitions on the above from 0 to 2, and add definition for 7/8
#define seven_eighths    3

CONFIG_SEC_VAR("L2 cache partition",
               __attribute__((section(".data"))),
               unsigned char,
               QURTK_L2_partition,
               L2CP);


/****************************************************************************
 * Chicken bit settings (for HW bug workaround)                             *
 *                                                                          *
 * Dependent Features:                                                      *
 *      CONFIG_CHICKEN_BITS                                                 *
 *                                                                          *
 * NOTES:                                                                   *
 ****************************************************************************/
/* Chicken bit settings */

CONFIG_SEC_VAR("",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_chicken_bits_rgdr,
               QURTKCHICKENBITSRGDR);
CONFIG_SEC_VAR("",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_chicken_bits_chicken,
               QURTKCHICKENBITSCHICKEN);

CONFIG_SEC_VAR("",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_chicken_bits_rgdr_2nd,
               QURTKCHICKENBITS2NDRGDR);
CONFIG_SEC_VAR("",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_chicken_bits_chicken_2nd,
               QURTKCHICKENBITS2NDCHICKEN);

CONFIG_SEC_VAR("",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_chicken_bits_rgdr_3rd,
               QURTKCHICKENBITS3RDRGDR);
CONFIG_SEC_VAR("",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_chicken_bits_chicken_3rd,
               QURTKCHICKENBITS3RDCHICKEN);

#define SUPP_RGDR_INIT {QURTKSUPRGDR}
CONFIG_RW_VAR("Supplement rgdr bits",
              unsigned int [16],
              QURTK_supplement_rgdr,
              SUPP_RGDR_INIT);

#define SUPP_RGDRREV_INIT {QURTKSUPREVRGDR}
CONFIG_RW_VAR("Supplement rgdr revid",
              unsigned int [16],
              QURTK_supplement_rgdr_revid,
              SUPP_RGDRREV_INIT);

#define SUPP_CHICKEN_INIT {QURTKSUPCHICKEN}
CONFIG_RW_VAR("Supplement chicken bits",
              unsigned int [16],
              QURTK_supplement_chicken,
              SUPP_CHICKEN_INIT);

#define SUPP_CHICKENREV_INIT {QURTKSUPREVCHICKEN}
CONFIG_RW_VAR("Supplement chicken revid",
              unsigned int [16],
              QURTK_supplement_chicken_revid,
              SUPP_CHICKENREV_INIT);

CONFIG_SEC_VAR("",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_supplement_rgdr_num,
               QURTKSUPNORGDR);

CONFIG_SEC_VAR("",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_supplement_chicken_num,
               QURTKSUPNOCHICKEN);

/****************************************************************************
 * Qurt Timer or Qtimer definitions                                        *
 *                                                                          *
 * Dependent Features:                                                      *
 *      CONFIG_QTIMERS                                                      *
 *                                                                          *
 * NOTES:                                                                   *
 *      Refer to your target HW reference manual for configuration          *
 *      of RGPT timer. Make sure the timer base address is one of           *
 *      the physical memory pools. Interrupt number does not conflict       *
 *      with RTOS reserved interrupts (check sched_config.h).               *
 ****************************************************************************/
CONFIG_RO_VAR("",
              unsigned int,
              QDSP6_QURT_TIMER_BASE,
              QDSP6QTIMERBASE);
CONFIG_RO_VAR("",
              unsigned int,
              QURT_timer_intno,
              TIMERINTNO);
CONFIG_RO_VAR("//254",
              unsigned int,
              QURT_timerIST_priority,
              TIMERISTPRIORITY);
CONFIG_RO_VAR("",
              unsigned int,
              QURT_timerIST_tcb_partition,
              TIMERISTTCBPARTITION);


/****************************************************************************
 * Qurt Memory Pool Configuration                                          *
 *                                                                          *
 * Dependent Features:                                                      *
 *      CONFIG_DYNAMIC_MEMORY                                               *
 *                                                                          *
 * NOTES:                                                                   *
 *      QURT can have unlimited number of pools and each pool have a name  *
 *      and it can have up to 16 ranges. No gaps are allowed in ranges, e.g *
 *      if RANGE 2 is not defined in a pool the following range definitions,*
 *      e.g RANGE 3, RANGE 4 etc., are ignored                              *
 ****************************************************************************/
#if defined(CONFIG_DYNAMIC_MEMORY) || defined(GEN_CONFIG_HEADER)
struct phys_mem_pool_config{
    char name[32];
    struct range {
        unsigned int start;
        unsigned int size;
    } ranges[16];
};

#define POOLSTART(name) {name, {
#define POOLREGION(addr,size) {addr, size},
#define POOLEND {0}}},
#define POOL_CONFIGS_INIT { PHYSPOOLS {""}}      /* Last physpool marked by empty name */
CONFIG_RW_VAR("Memory pool config information",
              struct phys_mem_pool_config [],
              pool_configs,
              POOL_CONFIGS_INIT);
#endif /* QURT_DYNAMIC_MEMORY */

CONFIG_SEC_VAR("Number of entries to be locked in TLB",
               __attribute__((section(".data"))),
               unsigned int,
               QURTK_tlblock_entries,
               TLBLOCKNUM);

CONFIG_RW_VAR("",
              unsigned int,
              config_tlb_first_replaceable,
              TLBFIRSTREPL);

CONFIG_RO_VAR("TLB debug level (0 for no debugging)",
              unsigned int,
              QURTK_tlb_debug_level,
              TLBDEBUGLEVEL);

#if TLBDEBUGLEVEL || defined(GEN_CONFIG_HEADER)

CONFIG_ZI_SPACE("TLB debug space",
                CONFIG_DEFAULT,
                ALIGNED_SPACE(32) [IDIM(4096)],
                QURTK_tlb_debug_space __attribute__((weak)),
                CONFIG_DEFAULT);

#endif

/*
 * Configure static mappings array to add device memory mappings or shared
 * memory mapping
 *
 * vpn:         virtual page number
 * ppn:         physical page number
 * perm:        permission
 * cached_attr: cacheability
 * pgsize:      page size
 * others:      un-used
 *
 * Note: vpn and ppn has to be number of 4KB
 *
 * Note: please contact Qualcomm Technologies Inc. to verify the change.
 *       Incorrect change will crash the build in run time!
 */

#define R    1
#define W    2
#define RW   3
#define WR   3
#define X    4
#define RX   5
#define XR   5
#define WX   6
#define XW   6
#define RWX  7
#define XWR  7

#define MAIN  0
#define AUX   1

#define MEMORY_MAP(glob, asid, vpn, umode, busattr, perm, cache_attr, pgsize, cache_part, ppn) \
   ( ((unsigned long long)((1 << 31) | (glob << 30) | (busattr << 27) | (asid << 20)|vpn) << 32 ) \
   | ( ((perm << 29) & 0xe0000000) | ((umode & 1) << 28) | (cache_attr << 24) | (ppn << 1) | pgsize))

#define MMAP_TABLE_INIT { MEMORY_MAPS 0 }
CONFIG_RW_VAR("Empty1 0x008000- 0x070000 size = 0x068000 (416k)",
              unsigned long long [],
              qurtos_mmap_table __attribute__((weak)),
              MMAP_TABLE_INIT);

#define VIRT_RESERVE_INIT { VIRT_RESERVE_RANGES -1 }
CONFIG_RO_VAR("Reserved virtual address ranges",
              int [],
              qurtos_virt_reserved,
              VIRT_RESERVE_INIT);

#define PHYS_ISLAND_INIT { PHYS_ISLAND_RANGES -1 }
CONFIG_RO_VAR("Physical island address ranges",
              int [],
              QURTK_phys_island,
              PHYS_ISLAND_INIT);

/****************************************************************************
 * Qurt L1 interrupt Configuration                                         *
 *                                                                          *
 * Dependent Features:                                                      *
 *      N/A                                                                 *
 *                                                                          *
 * NOTES:                                                                   *
 *      Use QURTK_IEL to configure interrupt is                            *
 *      - level triggered (bit value = 0)                                   *
 *      - edge triggered (bit value = 1)                                    *
 *      Use QURTK_IAHL to configure interrupt is                           *
 *      - Active high (or rising edge) (bit value = 1)                      *
 *      - Active low (or falling edge) (bit value = 0)                      *
 *      interrupt 0 is at MSB.                                              *
 ****************************************************************************/
 
CONFIG_RW_VAR("0xffffffff",
              unsigned int,
              QURTK_IEL,
              0xffffffff);

/* 1 - Active High, 0 - Active Low. All bits are 1. Rising edge or active high */
CONFIG_RW_VAR("0xffffffff",
              unsigned int,
              QURTK_IAHL,
              0xffffffff);

/****************************************************************************
 * Qurt L2 interrupt Configuration                                         *
 *                                                                          *
 * Dependent Features:                                                      *
 *      CONFIG_L2_INTERRUPT_ENABLED                                         *
 *                                                                          *
 * NOTES:                                                                   *
 *      Qurt kernel currently support up to 1024 L2VIC interrupts           *
 ****************************************************************************/
            
/* QURTK_l2_type[N] defines second level interrupt types, in which each bit
 * sets up the type of a L2 interrupt 
 */
#define L2TYPE_INIT {QURTKSIRCTYPE}
CONFIG_RW_VAR("interrupt 0 -> QURTK_l2_type[0]"
              "define L2 interrupt 0's type in LSB of QURTK_l2_type[N]"
              "0->level triggered; 1->edge triggered",
              unsigned int [32],
              QURTK_l2_type,
              L2TYPE_INIT);

/* Interrupt Privilege Control */
CONFIG_RW_VAR("disabled=0, enabled=1",
              unsigned int,
              QURTK_int_privilege,
              INTPRIV);

CONFIG_RW_VAR("Maximum number of programs",
              unsigned int,
              QURTK_max_programs,
              MAXPROGRAMS);

#define L2ENABLE_INIT {QURTKL2VICENABLE}
CONFIG_RW_VAR("disable=0, enable=1",
              unsigned int [], 
              QURTK_l2_enable,
              L2ENABLE_INIT);

#define ISR_INIT {ISRDATA}
CONFIG_RW_VAR("isr_int_no | isr_cb_no",
              unsigned short [], 
              QURTK_isr_data,
              ISR_INIT);
            
/* Program Name length, set to the same value of QURT_PROCESS_ATTR_NAME_MAXLEN */
#define PROGRAM_NAME_LEN 64
#define PROGRAM_NAMES {QURTKPROGNAMES}
CONFIG_RO_VAR("Program names",
              char [][PROGRAM_NAME_LEN],
              QURTK_program_names,
              PROGRAM_NAMES);

CONFIG_ZI_SPACE("",
              SECTION(".data", "QURTK.INTERRUPT"),
              ALIGNED_SPACE(16) [IDIM(MAXPROGRAMS)],
              QURTK_interrupt_pd_table,
              CONFIG_DEFAULT);


/* Define stack memory for fast interrupt callback */
// TBD: FASTINT_STACKSIZE will become a xml item in next step

CONFIG_ZI_SPACE("",
                SECTION(".data", "QURT.FASTINT"),
                ALIGNED_SPACE(32) [IDIM(QURT_CONFIG_MAX_HTHREADS*DIVUP(FASTINTSTACKSIZE,32))],
                qurt_fastint_stack,
                CONFIG_DEFAULT);
CONFIG_SEC_VAR("",
               SECTION(".data", "QURTK.INTERRUPT"),
               unsigned int,
               qurt_fastint_stack_size,
               sizeof(qurt_fastint_stack)/QURT_CONFIG_MAX_HTHREADS);

CONFIG_SEC_VAR("",
               SECTION(".data", "QURTK.INTERRUPT"),
               unsigned int,
               QURTK_int_max,
               MAXINT);
CONFIG_RW_VAR("",
              unsigned int,
              qdsp6ss_base_addr,
              QDSP6SSBASE);
CONFIG_ZI_SPACE("",
                SECTION(".data", "QURTK.INTERRUPT"),
                ALIGNED_SPACE(16) [IDIM(MAXINT+1)],
                QURTK_l2_interrupt_table,
                CONFIG_DEFAULT);


CONFIG_RW_VAR("",
              unsigned int,
              QURTK_int_elem_size,
              sizeof(QURTK_l2_interrupt_table[0]));
CONFIG_RW_VAR("",
              int,
              QURTK_CONTEXT_SIZE,
              THREAD_CONTEXT_TOTALSIZE);

#if defined(CONFIG_DYNAMIC_MEMORY) || defined(GEN_CONFIG_HEADER)
CONFIG_ZI_SPACE("",
                CONFIG_DEFAULT,
                ALIGNED_SPACE(0x1000) [IDIM(DIVUP(PAGETABLESIZE,0x1000))],
                QURTK_page_tables,
                CONFIG_DEFAULT);
CONFIG_RO_VAR("",
              unsigned int,
              QURTK_page_table_count,
              sizeof(QURTK_page_tables)/sizeof(QURTK_page_tables[0]));

CONFIG_RW_SPACE("",
                KSEP(__attribute__((section(".data.user.config"))),CONFIG_DEFAULT),
                unsigned char [],
                qurtos_heap,
                CACHEALIGNED,
                {ARRAY_INIT(ROUNDUP(KERNELHEAPSIZE,4)) = 0xFF});
CONFIG_RW_VAR("",
              unsigned int,
              QURTOS_HEAP_SIZE,
              sizeof(qurtos_heap));
#endif /* CONFIG_DYNAMIC_MEMORY */

/* Threads */
CONFIG_RW_VAR("",
              int,
              QURTK_config_MAX_THREADS,
              MAXTHREADS);
CONFIG_RW_VAR("",
              int,
              QURTK_MAX_THREADS_IN_TCM,
              MAXTHREADSINTCM);
CONFIG_ZI_SPACE("Each id has two words",
                SECTION(".data", "QURTK.CONTEXTS"),
                unsigned long long [IDIM(MAXTHREADS)],
                QURTK_thread_objs,
                CONFIG_DEFAULT);
/* Regular TCB storage */
CONFIG_ZI_SPACE("Regular TCB storage",
                SECTION(".data", "QURTK.CONTEXTS"),
                THREAD_CONTEXT [IDIM(MAXTHREADS - MAXTHREADSINTCM)],
                QURTK_thread_contexts,
                CONFIG_DEFAULT);
CONFIG_ZI_SPACE("TCM TCB storage",
                SECTION(".data", "QURTK.CONTEXTS.TCM"),
                THREAD_CONTEXT [IDIM(MAXTHREADSINTCM)],
                QURTK_thread_contexts_tcm,
                CONFIG_DEFAULT);

/* Futexes */
CONFIG_RW_SPACE("Futex space",
                SECTION(".data", "QURTK.FUTEX"),
                ALIGNED_SPACE(16) [IDIM(MAXTHREADS)],
                QURTK_futex_objs,
                CONFIG_DEFAULT,
                {{{0}}});

				
/* Debug Buffer*/
CONFIG_RW_VAR("",
              unsigned int,
              QURTK_config_debug_buffer_size,
              DEBUGBUFSIZE);
	             
CONFIG_ZI_SPACE("Array for Debug Buffer",
                CONFIG_DEFAULT,
                unsigned char [IDIM(DEBUGBUFSIZE)],
                QURTK_debug_buf,
                CONFIG_DEFAULT);   				
				
				
/* Trace buffer */
#if defined(CONFIG_TRACEBUFFER) || defined(GEN_CONFIG_HEADER)
typedef struct
{
   unsigned int   tbuf_size __attribute__((aligned(8)));
   unsigned int   tbuf_mask;
}
QURTK_trace_mask_t;
#define TRACE_INIT(a,b) { .tbuf_size=(a), .tbuf_mask=(b) }

CONFIG_RW_VAR("",
              unsigned int,
              QURTK_trace_buffer_size,
              ROUNDUP(TRACESIZE,8));
CONFIG_SEC_VAR("",
               SECTION(".data", "QURTK.SCHEDULER"),
               QURTK_trace_mask_t,
               QURTK_config_trace_mask,
               TRACE_INIT(ROUNDUP(TRACESIZE,8), QURTKDEFAULTTRACEMASK));
#if !defined(CONFIG_DYNAMIC_MEMORY) || defined(GEN_CONFIG_HEADER)
CONFIG_ZI_SPACE("",
                SECTION(".data", "QURTK.TRACEBUFFER"),
                unsigned long long [IDIM(QURT_CONFIG_MAX_HTHREADS*DIVUP(TRACESIZE,8))],
                QURTK_trace_memory,
                CONFIG_DEFAULT);
#endif //CONFIG_DYNAMIC_MEMORY


#endif
