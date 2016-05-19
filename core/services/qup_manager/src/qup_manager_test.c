/******************************************************************************

DESCRIPTION
  QUP MANAGER test client

Copyright (c) 2014 by Qualcomm Technologies Incorporated.  All Rights Reserved.

  EDIT HISTORY FOR MODULE

  when        who     what, where, why
  ----------  ---     -----------------------------------------------------------
  2014-06-28  dav  test code to verify  Qupmanager QMI services 

*******************************************************************************/

#define QMI_TEST
#define I2C_TEST
//#define SPI_TEST

#include "qup_manager.h"
#include <stdlib.h>
#include <comdef.h>
#include <qurt.h>
#include "msg_diag_service.h"


#include "qup_manager_v01.h"

#define DEBUG

/* Debug printf configuration */
#ifdef DEBUG
  #define DEBUG_PRINTF(fmt, arg1, arg2) \
     MSG_SPRINTF_2(MSG_SSID_TMS, MSG_LEGACY_HIGH, fmt, arg1, arg2); \
     qurt_printf(fmt, arg1, arg2);
#else
  #define DEBUG_PRINTF(fmt, arg1, arg2) {}
#endif

/* Error printf configuration */
#define ERR_PRINTF(fmt, arg1, arg2) \
   MSG_SPRINTF_2(MSG_SSID_TMS, MSG_LEGACY_HIGH, fmt, arg1, arg2); \
   qurt_printf(fmt, arg1, arg2);
#define   QUPM_QMI_CLNT_STACK_SIZE 1024 

#ifdef I2C_TEST
#include "I2cDriver.h"

int32 i2c_read_eeprom(I2cDrv_I2cBus *pI2c, uint32 offset, uint8* pRdBuff, uint32 size)
{
    I2cIoResult     ioRes;
    I2cRegSeqObj        i2c_seq_obj;
	int32 rc;

    I2c_RegObj_InitRead(&i2c_seq_obj);
    I2c_RegObj_SetOffset(&i2c_seq_obj, offset, I2cRegOffset_16Bit);
    I2c_RegObj_SetReadIoVector(&i2c_seq_obj, pRdBuff, size);

    rc = I2cDrv_BatchTransfer(pI2c, &(i2c_seq_obj.seq), &ioRes);
	return rc;
}

void i2c_write_eeprom(I2cDrv_I2cBus *pI2c, uint32 offset, uint8* pBuff, uint32 size)
{
    I2cIoResult     ioRes;
    I2cRegSeqObj        i2c_seq_obj;
	int32 rc;

    I2c_RegObj_InitWrite(&i2c_seq_obj);
    I2c_RegObj_SetOffset(&i2c_seq_obj, offset, I2cRegOffset_16Bit);
    I2c_RegObj_SetWriteIoVector(&i2c_seq_obj, pBuff, size);

    rc = I2cDrv_BatchTransfer(pI2c, &(i2c_seq_obj.seq), &ioRes);
    DEBUG_PRINTF("i2c_write_eeprom: 0x%x", rc, 0);
}

/*
 Config QUPs: \core\buses\i2c\config\i2c_[chipset]_adsp.c
*/
I2cDrv_I2cBus i2c_bus;
int i2c_driver_enable(void)
{
   DEBUG_PRINTF("I2C Driver enable...", 0, 0);
   //I2cResult i2cErrorCode = I2C_RES_SUCCESS;
   int32          i2cResult;
   uint8          store_data[10]= {1,2,3,4,5,4,3,2,1,0};
   uint8          rd_data[10]={0xA5,0x5A,0xA5,0x5A,0xA5, 0x5A,0xA5,0x5A,0xA5,0x5A};
   uint8          wr_data[10] = {1,2,3,4,5,6,7,8,9,10};
   //int32          ind;
   int32           rc;
   int i;
   int success = 1;


    i2c_bus.clntCfg.uSlaveAddr = 0x50;
    i2c_bus.clntCfg.uBusFreqKhz = 400;
    i2c_bus.clntCfg.uByteTransferTimeoutUs = 2500;


   i2cResult = I2cDrv_Open(I2CDRV_I2C_11, &i2c_bus, 0);
   //i2cResult = I2CDEV_Init(DALDEVICEID_I2C_DEVICE_11, &hI2C);
   if (I2C_RES_SUCCESS != i2cResult)
   {
      DEBUG_PRINTF("I2C Driver opened failed", 0, 0);
      return -1;     
   }

   rc = I2cDrv_Cmd(&i2c_bus, I2cDrvCmd_Vote_PnocOn, (void*) 150000);
   DEBUG_PRINTF("I2cDrv_Cmd PnocOn rc=%d", rc, 0);
   rc = I2cDrv_Cmd(&i2c_bus, I2cDrvCmd_Vote_I2cClocsOn, NULL);
   DEBUG_PRINTF("I2cDrv_Cmd ClocsOn rc=%d", rc, 0);
   

   // store the data
   rc = i2c_read_eeprom(&i2c_bus, 0x32,store_data, 10);
   DEBUG_PRINTF("i2c_read_eeprom: 0x%x", rc, 0);


     for (i = 0; i < 10; i++)
     {
        DEBUG_PRINTF("Store_data:%d", store_data[i], 0)
     }
   DEBUG_PRINTF("I2C Driver enable...complete? %d", success, 0);
   if (!success) {

     for (i = 0; i < 10; i++)
     {
        DEBUG_PRINTF("Read:%d, Write:%d", rd_data[i], wr_data[i])
     }
	 return -1;
   }
   // restore previous content
   // i2c_write_eeprom(&i2c_bus, 0x3000,store_data, 10);
   return 0;
}

int i2c_driver_disable(void)
{
    int32           rc1, rc2;
	DEBUG_PRINTF("I2C Driver disable", 0, 0);
	rc1 = I2cDrv_Cmd(&i2c_bus, I2cDrvCmd_Vote_PnocOff, (void*) 150000);
	rc2 = I2cDrv_Cmd(&i2c_bus, I2cDrvCmd_Vote_I2cClocsOff, NULL);
	I2cDrv_Close(&i2c_bus);
	DEBUG_PRINTF("I2C Driver disable...complete, rc=0x%x, 0x%x", rc1, rc2);
	return 0;
}

#elif SPI_TEST 

#include <comdef.h>
#include "SpiDriver.h"
#include "stdlib.h"
/*
   SPI_TEST involved some drivers that are not exposed to user space.
   Manually modification to the following files might be needed:
     core\buses\spi\src\config\spi_adsp_[chipset].c
     core\hwengines\bam\build\build.scons
     core\buses\api\spi\SpiDriver.h
*/
spi_config_t test_spi_config =
{
   SPI_CLK_IDLE_LOW,      // Clock polarity is IDLE_LOW
   SPI_INPUT_FIRST_MODE,  // Input bit is shifted in first
   SPI_CS_ACTIVE_LOW,     // Chip Select is LOW when the bus is idle
   SPI_CS_DEASSERT,       // De-assert Chip Select after transferring data for N clock cycles
   SPI_CLK_NORMAL,        // Clock is OFF when the bus is idle
   8                      // N = 8
};
extern void SpiInit(void);

/*
 Not all the QUPs can be used 
 Number of QUPs available: SPIPD_DEVICE_COUNT in SpiDriver.h
 Config what QUP to use: core\buses\spi\src\config\spi_[chipset].c
*/
int spi_driver_enable(void)
{
   DEBUG_PRINTF("SPI Driver enable...", 0, 0);
   int i, k;
   int success=1;
   uint32 rc;
   spi_transaction_t read_transaction_info;
   spi_transaction_t write_transaction_info;
   uint8 *rd_data = NULL;
   uint8 *wr_data = NULL;
   uint32 TransferCount = 1;
   uint32 APTTEST_SPI_MAX_BUF_SIZE = 10;

   SpiInit();
   // Allocate uncached, physically contiguous buffers
   // for the read and write data
   rd_data = (uint8 *)malloc((uint32)APTTEST_SPI_MAX_BUF_SIZE);
   if (NULL == rd_data)
   {
      //tzt_log("test_spi: Malloc for rd_data failed");
      goto cleanup;
   }
   wr_data = (uint8 *)malloc((uint32)APTTEST_SPI_MAX_BUF_SIZE);
   if (NULL == wr_data)
   {
      //tzt_log("test_spi: Malloc for wr_data failed");
      goto cleanup;
   }

   for (i = 0; i < APTTEST_SPI_MAX_BUF_SIZE; i++)
   {
      wr_data[i] = (uint8)(i + 10);
      rd_data[i] = 1;
   }

   read_transaction_info.buf_virt_addr = (void *)rd_data;
   read_transaction_info.buf_phys_addr = (void *)rd_data; //Vin: figure this out
   read_transaction_info.buf_len = APTTEST_SPI_MAX_BUF_SIZE;

   write_transaction_info.buf_virt_addr = (void *)wr_data;
   write_transaction_info.buf_phys_addr = (void *)wr_data; //Vin: figure this out
   write_transaction_info.buf_len = APTTEST_SPI_MAX_BUF_SIZE;

   rc = spi_open(SPI_DEVICE_5);
   DEBUG_PRINTF("spi_open: %x", rc, 0);

   // Perform a full duplex transfer
   for (k = 0; k < TransferCount; k++)
   {
      rc = spi_full_duplex(SPI_DEVICE_5, &test_spi_config, &write_transaction_info, &read_transaction_info);
      DEBUG_PRINTF("spi_full_duplex: %x", rc, 0);
      // Compare data written and data read back
      for (i = 0; i < APTTEST_SPI_MAX_BUF_SIZE; i++)
      {
         if (rd_data[i] != wr_data[i])
         {
			success = 0;
            break;
         }
      }
   }
   DEBUG_PRINTF("SPI Driver enable...complete? %d", success, 0);
   if (!success) {
     for (i = 0; i < APTTEST_SPI_MAX_BUF_SIZE; i++)
     {
        DEBUG_PRINTF("Read:%d, Write:%d", rd_data[i], wr_data[i])
     }
	 return -1;
   }
   return 0;
cleanup:
   if (NULL != rd_data)
   {
      free(rd_data);
   }
   if (NULL != wr_data)
   {
      free(wr_data);
   }
   return -2;
}

int spi_driver_disable(void)
{
  DEBUG_PRINTF("SPI Driver disable...", 0, 0);
  spi_close(SPI_DEVICE_5);
  DEBUG_PRINTF("SPI Driver disable...complete", 0, 0);
  return 0;
}
#else
int qup_manager_dummy_driver_enable(void)
{
  DEBUG_PRINTF("Dummy Driver Enable", 0, 0);
  return 0;
}

int qup_manager_dummy_driver_disable(void)
{
    DEBUG_PRINTF("Dummy Driver Disable", 0, 0);
  return 0;
}
#endif

void qup_manager_registration(void* unused)
{
  DEBUG_PRINTF("%s: here\n", __func__, 0);

  #ifdef I2C_TEST
    qup_manager_register_driver(5, i2c_driver_enable, i2c_driver_disable);
    qup_manager_register_driver(6, i2c_driver_enable, i2c_driver_disable);
  #elif SPI_TEST 
    qup_manager_register_driver(5, spi_driver_enable, spi_driver_disable);
    qup_manager_register_driver(6, spi_driver_enable, spi_driver_disable);
  #else
    qup_manager_register_driver(5, qup_manager_dummy_driver_enable, qup_manager_dummy_driver_disable);
    qup_manager_register_driver(6, qup_manager_dummy_driver_enable, qup_manager_dummy_driver_disable);
  #endif
}

#ifdef QMI_TEST

#include "qmi_client.h"
#include "qmi_idl_lib.h"
#include "qmi_cci_target_ext.h"
#define QMI_CLNT_WAIT_SIG       0x00010000
#define QMI_CLNT_TIMER_SIG      0x00000001

/*=========================================================================
FUNCTION qup_manager_ping_ind_cb

DESCRIPTION
  This callback function is called by the QCCI infrastructure when
  infrastructure receives an indication for this client

===========================================================================*/
void qup_manager_ping_ind_cb
(
 qmi_client_type                user_handle,  /*Opaque handle used by the infrastructure to
                                                identify different services.*/
 unsigned int                   msg_id,       /*Message ID of the indication*/
 void                           *ind_buf,     /*Buffer holding the encoded indication*/
 unsigned int                   ind_buf_len,  /*Length of the encoded indication*/
 void                           *ind_cb_data  /*Cookie value supplied by the client during registration*/
)
{
  DEBUG_PRINTF("%s: Initialization...pid is %d\n", __func__, qurt_getpid());
  switch (msg_id)
  {
    default:
      break;
  }
}

/*=========================================================================
FUNCTION qup_manager_ping_rx_cb

DESCRIPTION
  This callback function is called by the QCCI infrastructure when
  infrastructure receives an asynchronous response for this client

===========================================================================*/
static void qup_manager_ping_rx_cb
(
 qmi_client_type                user_handle,    /*Opaque handle used by the infrastructure to
                                                  identify different services.*/
 unsigned int                   msg_id,         /*Message ID of the response*/
 void                           *buf,           /*Buffer holding the decoded response*/
 unsigned int                   len,            /*Length of the decoded response*/
 void                           *resp_cb_data,  /*Cookie value supplied by the client*/
 qmi_client_error_type          transp_err      /*Error value*/
 )
{
  switch (msg_id)
  {
    case QMI_QUPM_READY_RESP_V01:
	{
      DEBUG_PRINTF("CLNT: READY RESP ", 0, 0);
	  qupm_ready_resp_msg_v01 *resp_msg = (qupm_ready_resp_msg_v01*) buf;
      DEBUG_PRINTF("Ready? %d\n", resp_msg->resp.result, 0);
	}
	break;

    case QMI_QUPM_TAKE_OWNERSHIP_RESP_V01: 
    {
      DEBUG_PRINTF("CLNT: TAKE OWNERSHIP ", 0, 0);
	  qupm_take_ownership_resp_msg_v01 *resp_msg = (qupm_take_ownership_resp_msg_v01*) buf;
      DEBUG_PRINTF("Eanbled? %d\n", resp_msg->resp.result, 0);
    }
	break;

    case QMI_QUPM_GIVE_OWNERSHIP_RESP_V01: 
    {
      DEBUG_PRINTF("CLNT: GIVE OWNERSHIP ", 0, 0);
	  qupm_give_ownership_resp_msg_v01 *resp_msg = (qupm_give_ownership_resp_msg_v01*) buf;
      DEBUG_PRINTF("Disabled? %d\n", resp_msg->resp.result, 0);
    }
	break;
    default:
	{
      DEBUG_PRINTF("Unknown Message\n", 0, 0);
	}
      break;
  }
}

/*=============================================================================
FUNCTION qup_manager_ping_msg_test

DESCRIPTION
  This function tells the service to send messages
=============================================================================*/
int qup_manager_ping_msg_test
(
 qmi_client_type *clnt,    /*Opaque handle used by the infrastructure to
                             identify different services.*/
 qmi_txn_handle *txn       /*Transaction handle*/
 )
{
  int rc = -1;

  qupm_ready_req_msg_v01 *req_msg = (qupm_ready_req_msg_v01*) 
                                         malloc(sizeof(qupm_ready_req_msg_v01));
  qupm_ready_resp_msg_v01 *resp_msg = (qupm_ready_resp_msg_v01*) 
                                         malloc(sizeof(qupm_ready_resp_msg_v01));
  req_msg->qup_id = 6;
  DEBUG_PRINTF("CLNT: READY REQ on QUP %d\n", req_msg->qup_id, 0);
  rc = qmi_client_send_msg_async(*clnt, QMI_QUPM_READY_REQ_V01, 
                             req_msg, sizeof(qupm_ready_req_msg_v01),
							 resp_msg, sizeof(qupm_ready_resp_msg_v01),
							 qup_manager_ping_rx_cb,
							 (void *) 2, txn);  
  if ( rc != 0)
    return -1;

  qupm_take_ownership_req_msg_v01 *req_msg1 = (qupm_take_ownership_req_msg_v01*) 
                                         malloc(sizeof(qupm_take_ownership_req_msg_v01));
  qupm_take_ownership_resp_msg_v01 *resp_msg1 = (qupm_take_ownership_resp_msg_v01*) 
                                         malloc(sizeof(qupm_take_ownership_resp_msg_v01));
  req_msg1->qup_id = 6;
  DEBUG_PRINTF("CLNT: TAKE OWNERSHIP REQ on QUP %d\n", req_msg1->qup_id, 0);
  rc = qmi_client_send_msg_async(*clnt, QMI_QUPM_TAKE_OWNERSHIP_REQ_V01, 
                             req_msg1, sizeof(qupm_take_ownership_req_msg_v01),
							 resp_msg1, sizeof(qupm_take_ownership_resp_msg_v01),
							 qup_manager_ping_rx_cb,
							 (void *) 2, txn);  
  if ( rc != 0)
    return -1;

  qupm_give_ownership_req_msg_v01 *req_msg2 = (qupm_give_ownership_req_msg_v01*) 
                                         malloc(sizeof(qupm_give_ownership_req_msg_v01));
  qupm_give_ownership_resp_msg_v01 *resp_msg2 = (qupm_give_ownership_resp_msg_v01*) 
                                         malloc(sizeof(qupm_give_ownership_resp_msg_v01));
  if ( !req_msg2 ){ free(req_msg2); return -1; }
  if ( !resp_msg2 ){ free(resp_msg2); return -1; }
  req_msg2->qup_id = 6;
  DEBUG_PRINTF("CLNT: GIVE OWNERSHIP REQ on QUP %d\n", req_msg2->qup_id, 0);
  rc = qmi_client_send_msg_async(*clnt, QMI_QUPM_GIVE_OWNERSHIP_REQ_V01, 
                             req_msg2, sizeof(qupm_give_ownership_req_msg_v01),
							 resp_msg2, sizeof(qupm_give_ownership_resp_msg_v01),
							 qup_manager_ping_rx_cb,
							 (void *) 2, txn);  
  if ( rc != 0)
    return -1;
  return 0;
}

void qup_manager_qmi_client_thread(void *unused)
{
  qmi_client_type clnt;
  qmi_txn_handle txn;
  qmi_client_type notifier;
  unsigned int num_services, num_entries=10, i=0, num_services_old=0;
  int rc;
  qmi_cci_os_signal_type os_params;
  qmi_service_info info[10];

  qup_manager_registration(unused);

  os_params.ext_signal = NULL;
  os_params.sig = QMI_CLNT_WAIT_SIG;
  os_params.timer_sig = QMI_CLNT_TIMER_SIG;

  qmi_idl_service_object_type qupm_service_object = qupm_get_service_object_v01();
  if (!qupm_service_object)
  {
    ERR_PRINTF("%s: Unable to get QUP Manager Service Object\n", __func__, 0);
  }

  rc = qmi_client_notifier_init(qupm_service_object, &os_params, &notifier);
  DEBUG_PRINTF("%s: qmi_client_notifier_init, rc=%d \n", __func__, rc);

  /* Check if the service is up, if not wait on a signal */
  while(1)
  {
    QMI_CCI_OS_SIGNAL_WAIT(&os_params, 0);
    QMI_CCI_OS_SIGNAL_CLEAR(&os_params);
    /* The server has come up, store the information in info variable */
    num_entries=10;
    rc = qmi_client_get_service_list( qupm_service_object, info, &num_entries, &num_services);

    if(rc != QMI_NO_ERR || num_services == num_services_old)
      continue;

    num_services_old = num_services;

    for(i = 0; i < num_services; i++)
    {
      rc = qmi_client_init(&info[i], qupm_service_object, qup_manager_ping_ind_cb, NULL, &os_params, &clnt);

      DEBUG_PRINTF("Registered test client with QUP MANAGER service: %d, rc=%d \n", i, rc);
      rc = qup_manager_ping_msg_test(&clnt, &txn);
	  if (rc)
        qmi_client_release(clnt);
    }
  }
}
#endif

void qup_manager_test_init(void)
{
  static qurt_anysignal_t    qupm_qmi_client_sig;
  static qurt_thread_attr_t  qupm_qmi_client_thread_attr;
  static qurt_thread_t       qupm_qmi_client_tcb;

  // QUP Manager Test Client
  DEBUG_PRINTF("%s: Initialization...pid is %d\n", __func__, qurt_getpid());
  static char qupm_qmi_client_stack[QUPM_QMI_CLNT_STACK_SIZE];

  qurt_anysignal_init(&qupm_qmi_client_sig);
  qurt_thread_attr_init(&qupm_qmi_client_thread_attr);
  qurt_thread_attr_set_name(&qupm_qmi_client_thread_attr, "QUPMQmiTest");
  qurt_thread_attr_set_priority(&qupm_qmi_client_thread_attr, 10);
  qurt_thread_attr_set_stack_size(&qupm_qmi_client_thread_attr, QUPM_QMI_CLNT_STACK_SIZE);
  qurt_thread_attr_set_stack_addr(&qupm_qmi_client_thread_attr, qupm_qmi_client_stack);
#ifdef QMI_TEST
  qurt_thread_create(&qupm_qmi_client_tcb, &qupm_qmi_client_thread_attr,
                     qup_manager_qmi_client_thread, NULL);
#else
  qurt_thread_create(&qupm_qmi_client_tcb, &qupm_qmi_client_thread_attr,
                     qup_manager_registration, NULL);
#endif
}
