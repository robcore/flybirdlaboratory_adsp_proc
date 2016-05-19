/*
 * HALclkInitASM.S
 * This file contains the implementation for setting up PLL, Q6 clock of LPASS
 *                   Edit History

   $Header: //components/rel/core.adsp/2.6.1/systemdrivers/hal/clk/hw/msm8994/src/HALclkInitASM.S#1 $

     #when       who                  what, where, why
    --------   -------------       ----------------------------------------------
    06/15/13   dcf                 Created file based on 8974.
 *
 */

 #include "HALclkHWIOASM.h"


/////////////////////////////////////////////////////////////////////////////////
//
//       Additional definitions and bit masks not defined in HWIO inc files.
// 
/////////////////////////////////////////////////////////////////////////////////


#define LPAAUDIO_PLL_USER_CTL_CLEAR (HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ALPHA_EN_BMSK | \
                                     HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PRE_DIV_RATIO_BMSK | \
                                     HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_BMSK)


#define LPAAUDIO_PLL_MODE_ACTIVE HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK


// Q6SS Core clock configuration values.

#define Q6CORE_PLL_SRC_SEL    0x1
#define Q6SS_CORE_CLK_M_VAL   0x0
#define Q6SS_CORE_CLK_N_VAL   0x0
#define Q6SS_CORE_CLK_D_VAL   0x0
#define Q6SS_CORE_CLK_DIV     0x1
#define Q6SS_GFMUX_SRC_SEL    0x0

// AHB Select LPAPLL_PRIUS with divider 10 to give 61.44 MHz.
#define AHB_SRC_SEL           0x5
#define AHB_DIV_SEL           0x5

/////////////////////////////////////////////////////////////////////////////////
//
//                        Data declarations start here.
// 
/////////////////////////////////////////////////////////////////////////////////

   //PLL L, and ALPHA VAL REG values
   .equ Q6SS_PLL_L_VAL,                   0x2E  //  46 for 441.6 MHz
   .equ Q6SS_PLL_ALPHA_VAL,               0x00  //  00 for 441.6 MHz
   .equ Q6SS_PLL_ALPHA_U_VAL,             0x00
   .equ Q6AHB_DIV_VAL,                     r13
   .equ Q6AHB_SRC_VAL,                     0x5
   
   
   //PLL L, and ALPHA VAL REG values
   .equ PLL0_L_VAL,                   0x20  //  32 for 614.4 MHz
   .equ PLL0_ALPHA_VAL,               0x00  //  00 for 614.4 MHz
   .equ PLL0_ALPHA_U_VAL,             0x00

    //AHB MND settings for 140MHZ, from PLL=491 MHZ
    .equ AHB_M,                        0x00   // No M Required
    .equ AHB_N,                        0x00   // No N Required
    .equ AHB_D,                        0x00   // No D Required

    // PLL Configuration values.
    .equ Q6SS_PLL_USER_CTL_VCO_VAL,                2
    .equ Q6SS_PLL_USER_CTL_POSTDIV_VAL,            1
    .equ Q6SS_PLL_USER_CTL_ALPHA_VAL,              1
    .equ Q6SS_PLL_USER_CTL_LV_MAIN_VAL,            1
    .equ Q6SS_PLL_MODE_BIAS_COUNT_VAL,           0x1
    .equ Q6SS_PLL_MODE_LOCK_COUNT_VAL,           0x0
	
    // PLL Configuration values.
    .equ PLL_USER_CTL_VCO_VAL,                     2
    .equ PLL_USER_CTL_POSTDIV_VAL,                 0
    .equ PLL_USER_CTL_ALPHA_VAL,                   0
    .equ PLL_USER_CTL_LV_MAIN_VAL,                 1
    .equ PLL_MODE_BIAS_COUNT_VAL,                0x1
    .equ PLL_MODE_LOCK_COUNT_VAL,                0x0

    .equ CPU_SPEED,                           0x10    // XO 19.2MHZ (rounded to 20 MHz), 3 HW threads, 6.4 MHZ per HW thread


/////////////////////////////////////////////////////////////////////////////////
//
//                 Macros Start Here.
// 
/////////////////////////////////////////////////////////////////////////////////


    //
    // MACRO:  WRITE_REGISTER
    //
    // DESCRIPTION:
    //   This macro writes an unmasked value to a register.  Any contents will
    //   be overwritten in the proccess.  r6 and r7 may be clobbered.
    //

    .macro write_register  val
        {
            r6 = \val
            r7 = r0
        }
        memw(r0) = r6
        barrier
    .endm


    //
    // MACRO:  CLEAR_BITS
    //
    // DESCRIPTION:
    //   This macro clears one ore more bits in a register.  r4, r5, r6, and r7
    //   may be clobbered when running this macro.
    //

    .macro clear_bits val_mask
        {
            r7 = r0
            r5.h = #hi(\val_mask)
        }
        {
            r5.l = #lo(\val_mask)
        }
        {
            r4 = memw(r0)
            r5 = not(r5)
        }
        r4 = and(r4, r5)    // clear the mask bits
        {
            memw(r0) = r4  //write the reg value
        }
        barrier
    .endm


    //
    // MACRO:  SET_BITS
    //
    // DESCRIPTION:
    //   This macro sets one or more bits in a register.  r4, r5 and r7 will be 
    //   clobbered when using this macro.
    //

    .macro set_bits val_mask
        {
            r7 = r0
            r5.h = #hi(\val_mask)
        }
        {
            r5.l = #lo(\val_mask)
            dcinva(r7)
        }
        {
            r4 = memw(r0)
            r6 = not(r5)
        }
        r4 = and(r4, r6)    // clear the fields
        r4 = or(r4,r5)      // set the value

        {
            memw(r0) = r4  //write the reg value
        }
        barrier
    .endm


/////////////////////////////////////////////////////////////////////////////////
//
//         Executable code starts here.
// 
/////////////////////////////////////////////////////////////////////////////////



//---------------------------------------------------------------------------------
// FUNCTION: __HEXAGON_BSP_INIT
//
// DESCRIPTION:
//   This is the main API for this file.  This function will check the status of the
//   main LPASS PLL and configure it if it is not running.  Otherwise, it will just
//   add a HW vote on behalf of the LPASS processor.
//
//   The QDSP6 and AHB clocks will then be initialized if not already set up.  The 
//   purpose of this is to ensure the QDSP6 clock and AHB are running at maximum
//   frequency under SVS voltage.
//
// ASSUMPTIONS:
//   There is no stack available when this is called, so only device registers can be
//   accessed.
//----------------------------------------------------------------------------------
#if defined(SIM)
  // No initialization.
#else
   .section .start    
   .falign
   .global __hexagon_bsp_init
   .type  __hexagon_bsp_init, @function

__hexagon_bsp_init:
#ifdef CLOCK_8974_RUMI

#else

   // Fill in generic values which are the same for most targets.
   {
     r10 = #Q6SS_PLL_L_VAL
     r11 = #Q6SS_PLL_ALPHA_VAL
     r12 = #Q6SS_PLL_ALPHA_U_VAL
   }

check_q6_pll:
   // Check if the PLL is enabled or not.
   r0.h = #hi(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR)
   r0.l = #lo(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR)
   r1 = memw(r0)                             // Read the contents of the PLL_MODE register.
   r2.h = #hi(LPAAUDIO_PLL_MODE_ACTIVE)
   r2.l = #lo(LPAAUDIO_PLL_MODE_ACTIVE)
   r3 = and(r1, r2)
   {
     p0 = cmp.eq(r2,r3)
     if (p0.new) jump:t vote_for_q6_pll         // If the PLL is already set up go to PLL voting.
   }

   // Assume now that the PLL has not been set up yet. r0 contains LPAAUDIO_PLL_MODE address.
   // Disable FSM Mode.
   clear_bits HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK

                      // Program the L, M, and N values.
   r0.h = #hi(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR)
   r0.l = #lo(HWIO_LPASS_QDSP6SS_PLL_L_VAL_ADDR)
   write_register r10

   r0.h = #hi(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR)
   r0.l = #lo(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_ADDR)
   write_register r11

   r0.h = #hi(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR)
   r0.l = #lo(HWIO_LPASS_QDSP6SS_PLL_ALPHA_VAL_U_ADDR)
   write_register r12

                       // Get the Configuration value and clear out fields we will configure.
   r0.h = #hi(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR)
   r0.l = #lo(HWIO_LPASS_QDSP6SS_PLL_USER_CTL_ADDR)
   clear_bits LPAAUDIO_PLL_USER_CTL_CLEAR

  // r0.h = #hi(HWIO_LPASS_QDSP6SS_PLL_CLK_DIV_ADDR)
  // r0.l = #lo(HWIO_LPASS_QDSP6SS_PLL_CLK_DIV_ADDR)
  // clear_bits HWIO_LPASS_QDSP6SS_PLL_CLK_DIV_CLK_AUX2_DIV_BMSK
   
   // Add the VCO
   r5.h = #hi(Q6SS_PLL_USER_CTL_VCO_VAL<<HWIO_LPASS_QDSP6SS_PLL_USER_CTL_VCO_SEL_SHFT)
   r5.l = #lo(Q6SS_PLL_USER_CTL_VCO_VAL<<HWIO_LPASS_QDSP6SS_PLL_USER_CTL_VCO_SEL_SHFT)
   r4 = or(r4, r5)

   // Add the post-div value
   r5.h = #hi(Q6SS_PLL_USER_CTL_POSTDIV_VAL<<HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_SHFT)
   r5.l = #lo(Q6SS_PLL_USER_CTL_POSTDIV_VAL<<HWIO_LPASS_QDSP6SS_PLL_USER_CTL_POST_DIV_RATIO_SHFT)
   r4 = or(r4, r5)

   // Enable MAIN_OUT_ENA bit
   r5.h = #hi(Q6SS_PLL_USER_CTL_LV_MAIN_VAL<<HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT)
   r5.l = #lo(Q6SS_PLL_USER_CTL_LV_MAIN_VAL<<HWIO_LPASS_QDSP6SS_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT)
   r4 = or(r4, r5)

   // Program the config register.
   write_register r4

   // Clear out and program the FSM portion of the mode register.
   r0.h = #hi(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR)
   r0.l = #lo(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR)

   // Put the FSM in reset mode.
   set_bits HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK

   r1 = memw(r0)

   {
     r2.h = #hi(HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_BMSK)
     r3.h = #hi(HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_BMSK)
   }
   {
     r2.l = #lo(HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_BMSK)
     r3.l = #lo(HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_BMSK)
   }
   r2 = or(r2, r3)
   r2 = not(r2)
   r1 = and(r1, r2)
   {
     r2.h = #hi(PLL_MODE_BIAS_COUNT_VAL<<HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_SHFT)
     r3.h = #hi(PLL_MODE_LOCK_COUNT_VAL<<HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_SHFT)
   }
   {
     r2.l = #lo(PLL_MODE_BIAS_COUNT_VAL<<HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_BIAS_COUNT_SHFT)
     r3.l = #lo(PLL_MODE_LOCK_COUNT_VAL<<HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_LOCK_COUNT_SHFT)
   }
   r2 = or(r2, r3)
   r1 = or(r1, r2)
   write_register r1

enable_q6_pll:
   set_bits HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK
   clear_bits HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK
   barrier

vote_for_q6_pll:
   // Vote for LPAAUDIO PLL on (HW vote)
   r0.h = #hi(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR)
   r0.l = #lo(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR)
   set_bits HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_QDSP6SS_PLL_BMSK

   // Wait for PLL active here.
   r0.h = #hi(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR)
   r0.l = #lo(HWIO_LPASS_QDSP6SS_PLL_MODE_ADDR)
   r2.l = #lo(HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_BMSK)
   r2.h = #hi(HWIO_LPASS_QDSP6SS_PLL_MODE_PLL_ACTIVE_FLAG_BMSK)
q6_pll_vote_loop:
   r1 = memw(r0)
   r3 = and(r1, r2)
   {
     p0 = cmp.eq(r2,r3)
     if (!p0.new) jump:t q6_pll_vote_loop              // If the PLL is already set up go to PLL voting.
   }

   // Program the Strap ACC value.
   r0.h = #hi(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR)
   r0.l = #lo(HWIO_LPASS_QDSP6SS_STRAP_ACC_ADDR)

   r1.h = #hi(0x00000020)
   r1.l = #lo(0x00000020)
   memw(r0) = r1
   barrier

   // Set up the QDSP6 now.
check_qdsp6:
   r0.h = #hi(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR)
   r0.l = #lo(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_ADDR)
   r1 = memw(r0)

   // Clear out the source selection and divider values.
   {
     r2.h = #hi(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_BMSK)
     r3.h = #hi(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_BMSK)
   }
   {
     r2.l = #lo(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_BMSK)
     r3.l = #lo(HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_BMSK)
   }
   r2 = or(r2, r3)
   r2 = not(r2)
   r1 = and(r1, r2)

   // Add the new values.
   {
     r2.h = #hi(Q6CORE_PLL_SRC_SEL<<HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SHFT)
     r3.h = #hi(Q6SS_CORE_CLK_DIV<<HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_SHFT)
   }
   {
     r2.l = #lo(Q6CORE_PLL_SRC_SEL<<HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_SEL_SHFT)
     r3.l = #lo(Q6SS_CORE_CLK_DIV<<HWIO_LPASS_QDSP6SS_CORE_CFG_RCGR_SRC_DIV_SHFT)
   }
   r2 = or(r2, r3)
   r1 = or(r1, r2)
   memw(r0) = r1
   barrier

   // Ensure Q6 is on.
   r0.h = #hi(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR)
   r0.l = #lo(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_ADDR)
   r1 = memw(r0)
   
   // Trigger the update
   r2.h = #hi(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_BMSK)
   r2.l = #lo(HWIO_LPASS_QDSP6SS_CORE_CMD_RCGR_UPDATE_BMSK)
   r1 = or(r1, r2)
   memw(r0) = r1
   barrier

q6_cmd_update:
   r1 = memw(r0)
   r3 = and(r1, r2)
   {
     p0 = cmp.eq(r3, r2)
     if (p0.new) jump:t q6_cmd_update
   }   

   // Program the GFMUX config register.
   r0.h = #hi(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR)
   r0.l = #lo(HWIO_LPASS_QDSP6SS_GFMUX_CTL_ADDR)
   r1 = memw(r0)

   r2.h = #hi(HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_BMSK)
   r2.l = #lo(HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_BMSK)
   r2 = not(r2)
   r1 = and(r1, r2)
   {
     r2.h = #hi(Q6SS_GFMUX_SRC_SEL<<HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_SHFT)
     r3.h = #hi(HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_BMSK)
     r4.h = #hi(HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_BMSK)
   }
   {
     r2.l = #lo(Q6SS_GFMUX_SRC_SEL<<HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_SRC_SEL_SHFT)
     r3.l = #lo(HWIO_LPASS_QDSP6SS_GFMUX_CTL_SRC_SWITCH_CLK_OVR_BMSK)
     r4.l = #lo(HWIO_LPASS_QDSP6SS_GFMUX_CTL_CLK_ENA_BMSK)
   }
   r3 = or(r3, r4)
   r2 = or(r2, r3)
   r1 = or(r1, r2)

   memw(r0) = r1
   barrier

      
    // place the AHB divider value in R13 for 491.52 derived AHB.
   r13 = #AHB_DIV_SEL

   // Fill in generic values which are the same for most targets.
   {
     r10 = #PLL0_L_VAL
     r11 = #PLL0_ALPHA_VAL
     r12 = #PLL0_ALPHA_U_VAL
   }

check_pll:
   // Check if the PLL is enabled or not.
   r0.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_ADDR)
   r0.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_ADDR)
   r1 = memw(r0)                             // Read the contents of the PLL_MODE register.
   r2.h = #hi(LPAAUDIO_PLL_MODE_ACTIVE)
   r2.l = #lo(LPAAUDIO_PLL_MODE_ACTIVE)
   r3 = and(r1, r2)
   {
     p0 = cmp.eq(r2,r3)
     if (p0.new) jump:t vote_for_pll         // If the PLL is already set up go to PLL voting.
   }

   // Assume now that the PLL has not been set up yet. r0 contains LPAAUDIO_PLL_MODE address.
   // Disable FSM Mode.
   clear_bits HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK

                      // Program the L, M, and N values.
   r0.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_ADDR)
   r0.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_L_VAL_ADDR)
   write_register r10

   r0.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_ADDR)
   r0.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_ADDR)
   write_register r11

   r0.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_ADDR)
   r0.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_ALPHA_VAL_U_ADDR)
   write_register r12

                       // Get the Configuration value and clear out fields we will configure.
   r0.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_ADDR)
   r0.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_ADDR)
   clear_bits LPAAUDIO_PLL_USER_CTL_CLEAR
   
   // Add the VCO
   r5.h = #hi(PLL_USER_CTL_VCO_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_VCO_SEL_SHFT)
   r5.l = #lo(PLL_USER_CTL_VCO_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_VCO_SEL_SHFT)
   r4 = or(r4, r5)

   // Add the post-div value
   r5.h = #hi(PLL_USER_CTL_POSTDIV_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_POST_DIV_RATIO_SHFT)
   r5.l = #lo(PLL_USER_CTL_POSTDIV_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_POST_DIV_RATIO_SHFT)
   r4 = or(r4, r5)

   // Enable ALPHA
   r5.h = #hi(PLL_USER_CTL_ALPHA_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_ALPHA_EN_SHFT)
   r5.l = #lo(PLL_USER_CTL_ALPHA_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_ALPHA_EN_SHFT)
   r4 = or(r4, r5)
   
   // Enable MAIN_OUT_ENA bit
   r5.h = #hi(PLL_USER_CTL_LV_MAIN_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT)
   r5.l = #lo(PLL_USER_CTL_LV_MAIN_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_MAIN_SHFT)
   r4 = or(r4, r5)
   
   r5.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK)
   r5.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_AUX_BMSK)
   r4 = or(r4, r5)

   r5.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK)
   r5.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_AUX2_BMSK)
   r4 = or(r4, r5)

   r5.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK)
   r5.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_PLLOUT_LV_EARLY_BMSK)
   r4 = or(r4, r5)

   // Program the config register.
   write_register r4


   r0.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_ADDR)
   r0.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_USER_CTL_U_ADDR)
   set_bits 0x4


   // Clear out and program the FSM portion of the mode register.
   r0.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_ADDR)
   r0.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_ADDR)

   // Put the FSM in reset mode.
   set_bits HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK

   r1 = memw(r0)

   {
     r2.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_BIAS_COUNT_BMSK)
     r3.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_LOCK_COUNT_BMSK)
   }
   {
     r2.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_BIAS_COUNT_BMSK)
     r3.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_LOCK_COUNT_BMSK)
   }
   r2 = or(r2, r3)
   r2 = not(r2)
   r1 = and(r1, r2)
   {
     r2.h = #hi(PLL_MODE_BIAS_COUNT_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_BIAS_COUNT_SHFT)
     r3.h = #hi(PLL_MODE_LOCK_COUNT_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_LOCK_COUNT_SHFT)
   }
   {
     r2.l = #lo(PLL_MODE_BIAS_COUNT_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_BIAS_COUNT_SHFT)
     r3.l = #lo(PLL_MODE_LOCK_COUNT_VAL<<HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_LOCK_COUNT_SHFT)
   }
   r2 = or(r2, r3)
   r1 = or(r1, r2)
   write_register r1

enable_pll:
   set_bits HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_VOTE_FSM_ENA_BMSK
   clear_bits HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_VOTE_FSM_RESET_BMSK
   barrier

vote_for_pll:
   // Vote for LPAAUDIO PLL on (HW vote)
   r0.h = #hi(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR)
   r0.l = #lo(HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_ADDR)
   set_bits HWIO_LPASS_LPA_PLL_VOTE_LPASSQ6_LPAAUDIO_PRIUS_PLL_BMSK

   // Wait for PLL active here.
   r0.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_ADDR)
   r0.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_ADDR)
   r2.l = #lo(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_ACTIVE_FLAG_BMSK)
   r2.h = #hi(HWIO_LPASS_LPAAUDIO_PRIUS_PLL_MODE_PLL_ACTIVE_FLAG_BMSK)
pll_vote_loop:
   r1 = memw(r0)
   r3 = and(r1, r2)
   {
     p0 = cmp.eq(r2,r3)
     if (!p0.new) jump:t pll_vote_loop              // If the PLL is already set up go to PLL voting.
   }  
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   // Initialize the AHB bus.
config_ahb:

   r0.h = #hi(HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR)
   r0.l = #lo(HWIO_LPASS_AHBFABRIC_CFG_RCGR_ADDR)
   r1 = memw(r0)

   // Clear out the source selection and divider values.
   {
     r2.h = #hi(HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_SEL_BMSK)
     r3.h = #hi(HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_DIV_BMSK)
   }
   {
     r2.l = #lo(HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_SEL_BMSK)
     r3.l = #lo(HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_DIV_BMSK)
   }
   r2 = or(r2, r3)
   r2 = not(r2)
   r1 = and(r1, r2)

   // Add the new values.
   {
     r2.h = #hi(Q6AHB_SRC_VAL << HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_SEL_SHFT)
     r3.h = #hi(HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_DIV_SHFT)
   }
   {
     r2.l = #lo(Q6AHB_SRC_VAL << HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_SEL_SHFT)
     r3.l = #lo(HWIO_LPASS_AHBFABRIC_CFG_RCGR_SRC_DIV_SHFT)
   }
   r4 = lsl(r13, r3)
   r2 = or(r2, r4)
   r1 = or(r1, r2)
   memw(r0) = r1
   barrier

   // Program the MN/D values for the max frequency supported at low voltage.
   r0.h = #hi(HWIO_LPASS_AHBFABRIC_M_ADDR)
   r0.l = #lo(HWIO_LPASS_AHBFABRIC_M_ADDR)
   write_register #AHB_M

   r0.h = #hi(HWIO_LPASS_AHBFABRIC_N_ADDR)
   r0.l = #lo(HWIO_LPASS_AHBFABRIC_N_ADDR)
   write_register #AHB_N

   r0.h = #hi(HWIO_LPASS_AHBFABRIC_D_ADDR)
   r0.l = #lo(HWIO_LPASS_AHBFABRIC_D_ADDR)
   write_register #AHB_D

   r0.h = #hi(HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR)
   r0.l = #lo(HWIO_LPASS_AHBFABRIC_CMD_RCGR_ADDR)
   r1 = memw(r0)
   r2.h = #hi(HWIO_LPASS_AHBFABRIC_CMD_RCGR_UPDATE_BMSK)
   r2.l = #lo(HWIO_LPASS_AHBFABRIC_CMD_RCGR_UPDATE_BMSK)
   r1 = or(r1, r2)
   memw(r0) = r1
   barrier

end_init:
   Jumpr r31
#endif
.size __hexagon_bsp_init, .-__hexagon_bsp_init
#endif // SIM
