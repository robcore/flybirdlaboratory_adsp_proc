#include <comdef.h>
#include "SpiDriver.h"
#include "stdlib.h"
#include "uSleep.h"
#include "qurt_island.h"
#include "utimer.h"
spi_config_t test_spi_config =
{
   SPI_CLK_IDLE_LOW,      // Clock polarity is IDLE_LOW
   SPI_INPUT_FIRST_MODE,  // Input bit is shifted in first
   SPI_CS_ACTIVE_LOW,     // Chip Select is LOW when the bus is idle
   SPI_CS_DEASSERT,       // De-assert Chip Select after transferring data for N clock cycles
   SPI_CLK_NORMAL,        // Clock is OFF when the bus is idle
   8,                      // N = 8
   0,
   0,
   10000000,
   0,
   1
};

#define ATTRIBUTE_ISLAND_DATA __attribute__((section("RW.island")))
uint32 spi_test_started_uimage = 0;
uint32 spi_test_before_uimage = 0;
uint32 spi_test_successful_iterations = 0;
uint32 spi_test_uimage_exited = 0;
uint32 spi_error_no_uimage_fully = 0;
static uSleep_notification_cb_handle uSleep_handle;
uint32 uimage_enter_latency = 20000; 
uint32 uimage_exit_latency = 10000;
utimer_type f_type_enter;
extern void SpiInit(void);


uint8 rd_data[8]; //ATTRIBUTE_ISLAND_DATA;
uint8 wr_data[8]; //ATTRIBUTE_ISLAND_DATA;

static void test_spi_duplex_core(int data);
static void start_uimage_thread_timer(uSleep_state_notification state);

void test_spi_duplex(void)
{
   SpiInit();
   uSleep_handle = uSleep_registerNotificationCallback(uimage_enter_latency, uimage_exit_latency, start_uimage_thread_timer);
}

static void start_uimage_thread_timer(uSleep_state_notification state)
{
   if (state == USLEEP_STATE_ENTER)
   {
      utimer_def_osal(&f_type_enter, UTIMER_FUNC1_CB_TYPE, &test_spi_duplex_core, 0); 
      utimer_set_64(&f_type_enter, 500, 0, UT_USEC);
   }
   else
   {
      spi_test_uimage_exited++;
   }
}

static void test_spi_duplex_core(int data)
{
   int i, j;
   spi_transaction_t read_transaction_info;
   spi_transaction_t write_transaction_info;
   uint32 LoopCount = 10;
   uint32 APTTEST_SPI_MAX_BUF_SIZE = 8;
   uint32 temp_cnt = spi_test_uimage_exited;

   spi_test_before_uimage = 1;
   //about to enter usleep
   while (qurt_island_get_status() == 0);

   spi_test_started_uimage = 1;
   
   //in island mode.
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

   for (j = 0; j < LoopCount; j++)
   {

      spi_open(SPI_DEVICE_12);

      // Perform a full duplex transfer
      spi_full_duplex(SPI_DEVICE_12, &test_spi_config, &write_transaction_info, &read_transaction_info);
      // Compare data written and data read back
      for (i = 0; i < APTTEST_SPI_MAX_BUF_SIZE; i++)
      {
         if (rd_data[i] != wr_data[i])
         {
            // Comparison failed
            while(1000);
            break;
         }
      }
      spi_close(SPI_DEVICE_12);
   }
   if (spi_test_uimage_exited != temp_cnt)
   {
      spi_error_no_uimage_fully = 1;
      while(1);
   }
   spi_test_successful_iterations = j; 
   //tzt_log("spi_duplex: Success from 1 till %d bytes for %d loops", APTTEST_SPI_MAX_BUF_SIZE, j);

}
