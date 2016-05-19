#include "dlw.h"
#include "platform_libs.h"
#include "DALSysTypes.h"
#include "DALSysCmn.h"
#include "DALSysInt.h"

// initialization dependency
PL_DEP(dlw)

void* gpDevCfgDLOpenhandle = NULL;
extern DALProps* gpDALPROP_PropsShObjInfo;
extern DALSYSEventHandle hgMultiEvent[2];

DALResult DEVCFG_LOADER(void)
{  
   if(!gpDevCfgDLOpenhandle)
   {   
      gpDevCfgDLOpenhandle = dlw_Open("DevCfg_guestos.so", DLW_RTLD_NOW);
      if(!gpDevCfgDLOpenhandle)
      {
         DALSYS_LOG_FATAL_EVENT("pDevCfgDLhandle error: %s", dlw_Error());
         return DAL_ERROR;
      }
      gpDALPROP_PropsShObjInfo = dlw_Sym(gpDevCfgDLOpenhandle, "DALPROP_PropsInfo");
      if(!gpDALPROP_PropsShObjInfo)
      {
         DALSYS_LOG_FATAL_EVENT("DALPROP_PropsShObjInfo error: %s", dlw_Error());
         return DAL_ERROR;
      }
   }

   return DAL_SUCCESS;
}

static int DEVCFG_LOADER_INIT(void)
{  

   /* Since dlopen is done at boot time, make sure platform is intialized with right order */
   int nErr = 0;    

   nErr = PL_INIT(dlw);
   if(nErr) 
   {
      return nErr;
   }
      
   if (DAL_SUCCESS !=DALSYS_EventCtrl(hgMultiEvent[0], DALSYS_EVENT_CTRL_TRIGGER))
   {
      DALSYS_LOG_ERROR_EVENT("Failed to signal dlopen complete");
      return DAL_ERROR;
   }
         
   return nErr;  
}
 
DALResult DEVCFG_DELOADER(void)
{  
   
   return DAL_SUCCESS;
}   

static void DEVCFG_LOADER_DEINIT(void)
{
   dlw_Close(gpDevCfgDLOpenhandle);
   PL_DEINIT(dlw);
}

//add env.PLRegister("mycode") to your scons file
PL_DEFINE(DevCfgDyn, DEVCFG_LOADER_INIT, DEVCFG_LOADER_DEINIT);

