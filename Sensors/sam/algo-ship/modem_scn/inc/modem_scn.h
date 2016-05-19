#ifndef MODEM_SCN_H
#define MODEM_SCN_H

/*============================================================================
  @file modem_scn.h

  The modem_scn algorithm header file

  Copyright (c) 2010-2012 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
============================================================================*/

/*============================================================================
  EDIT HISTORY

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. 

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2013-01-03  asj   initial version  

============================================================================*/

#include <stdint.h>
#include <stdbool.h>

#define MODEM_SCN_DEF_QUIET_PERIOD (3276) // 1/10th of a second
#define MODEM_SCN_DEF_THRESH       (0xFFFF)  

typedef struct
{
  uint32_t sample_rate;  // in Hz, Q16
  uint32_t thresh;       // Q16
  uint32_t quiet_period; // Q16 - in DSPS ticks
} modem_scn_config_s;

typedef struct
{
  int32_t sample;     // sensor sample data, Q16
  uint32_t timestamp;
} modem_scn_input_s;

typedef struct
{
  bool    do_report;     // whether samples are to be reported
  int32_t scn;           // scenario detected
  uint32_t timestamp;
} modem_scn_output_s;

typedef struct
{
  modem_scn_config_s config;
  uint32_t ts_start_period;
  int32_t last_scn;
  bool    first_time;
} modem_scn_state_s;

typedef enum
{
  MODEM_SCN_UNKNOWN,
  MODEM_SCN_OCCLUDED,
  MODEM_SCN_FREE_SPACE
}modem_scn_e;

/*=========================================================================
  FUNCTION:  modem_scn_sam_mem_req
  =======================================================================*/
/*!
    @brief Returns memory needed by the algorithm with given configuration

    @param[i] config_data: Pointer to algorithm configuration

    @return Size of state memory required, given the configuration settings
            0 if the configuration is invalid
*/
/*=======================================================================*/
int32_t modem_scn_sam_mem_req(const modem_scn_config_s *config_data);

/*=========================================================================
  FUNCTION:  modem_scn_sam_state_reset
  =======================================================================*/
/*!
    @brief Resets the algorithm instance with given configuration

    @param[i] config_data: Pointer to algorithm configuration
    @param[i] mem: Pointer to a block of allocated algorithm state memory

    @return Pointer to a valid algorithm state memory if successful
            NULL if error
*/
/*=======================================================================*/
modem_scn_state_s* modem_scn_sam_state_reset(
   const modem_scn_config_s *config_data, 
   void *mem);

/*=========================================================================
  FUNCTION:  modem_scn_sam_update
  =======================================================================*/
/*!
    @brief Execute the algorithm, update the output with given input

    @param[i] modem_scn_algo: Pointer to algorithm state memory
    @param[i] input: Pointer to algorithm input data
    @param[o] output: Pointer to algorithm output data

    @return none
*/
/*=======================================================================*/
void modem_scn_sam_update(modem_scn_state_s *modem_scn_algo, 
                          const modem_scn_input_s *input, 
                          modem_scn_output_s *output);

#endif /* MODEM_SCN_H */
