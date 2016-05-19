/*============================================================================
  @file modem_scn.c

  The modem_scn algorithm source file 

  Copyright (c) 2010-2013 QUALCOMM Technologies Incorporated.
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

#include "modem_scn.h"
#include "fixed_point.h"

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
int32_t modem_scn_sam_mem_req(const modem_scn_config_s *config_data)
{
  return (sizeof(modem_scn_state_s));
}

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
  void *mem)
{
  modem_scn_state_s *algo;

  algo = (modem_scn_state_s*)mem;
  algo->config = *config_data;   // structure copy
  algo->last_scn = MODEM_SCN_UNKNOWN;
  algo->first_time = true;

  return algo;
}

/*=========================================================================
  FUNCTION: modem_scn_update_results
  ========================================================================*/
/*!
  @brief Updates the output structure 

  @param[i] quat_algo: Pointer to algorithm state data
  @param[i] input: Pointer to algorithm input data
    @param[o] output: Pointer to algorithm output data

  @return none
*/
/*=======================================================================*/
void modem_scn_update_results(modem_scn_state_s *algo, 
                              const modem_scn_input_s *input, 
                              modem_scn_output_s *output)
{
   int32_t scn = input->sample > algo->config.thresh ? MODEM_SCN_OCCLUDED : 
		                                                  MODEM_SCN_FREE_SPACE;

   if(algo->last_scn != scn)
	{
	 output->scn = scn;
	 output->timestamp = input->timestamp;
		output->do_report = true;

      /* Change output data struct to be sent, restart timer*/
		algo->ts_start_period = input->timestamp;
		algo->last_scn = output->scn;
	}
  return;
}


/*=========================================================================
  FUNCTION:  modem_scn_sam_update
  =======================================================================*/
/*!
  @brief Execute the algorithm, update the output with given input

  @param[i] algo: Pointer to algorithm state memory
  @param[i] input: Pointer to algorithm input data
  @param[o] output: Pointer to algorithm output data

  @return none
*/
/*=======================================================================*/
void modem_scn_sam_update(modem_scn_state_s *algo, 
                          const modem_scn_input_s *input, 
                          modem_scn_output_s *output)
{
	uint32_t t_diff;

  /* first time running the algo, always report */
  if (algo->first_time == true)
  {
    algo->first_time = false;
    modem_scn_update_results(algo, input, output);
    return;
  }

	/* else wait for the quiet period */
	if(input->timestamp >= algo->ts_start_period)
	{
		t_diff = input->timestamp - algo->ts_start_period;
	}
	else
	{
		/* rollover */
		t_diff = ((UINT32_MAX - algo->ts_start_period) + input->timestamp);
	}

	if(t_diff < algo->config.quiet_period)
	{
		return;
	}

	/* Now we can update results */
  modem_scn_update_results(algo, input, output);
}
