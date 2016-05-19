#ifndef DIAGDSMI_H
#define DIAGDSMI_H
/*===========================================================================

                                  D I A G D S M I . H

  GENERAL DESCRIPTION
  Declares sizes for diag dsm items.

Copyright (c) 2009-2015 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================
                            EDIT HISTORY FOR FILE
                                      
  $Header: //components/rel/core.adsp/2.6.1/services/diag/platform/adsp/src/diagdsmi.h#2 $

when        who    what, where, why
--------    ---    ---------------------------------------------------------- 
04/03/15    sa     Updated the SIO TX DSM pool watermark levels to
                   support max size of a chained packet.
04/10/14    sr     Support for peripheral buffering mode   
04/01/14    rs      Added support for build mask centralization. 
07/23/13    rh     Increased extra DSM padding on TX pool to guarantee we 
                   have enough items to handle our larger max packet size 
08/02/13    rh     Added flow control limits for control channel 
02/05/13    rh     Added DSM Control Items Size and Number
11/01/10    JV      Defined DSMI_DIAG_SIO_TX_ITEM_MANY_MARK and DSMI_DIAG_SIO_TX_ITEM_FEW_MARK,
                    used for flow-control
10/06/09    JV      Mainlined FEATURE_DSM_DIAG_ITEMS.
09/17/09    JV     Changed location of file. Separate file per platform. On the
                   audio Q6, we use only 2 DSM pools. SIO_RX pool to receive
				   requests from the ARM9 and SIO_TX pool to send traffic to the
				   master.
04/15/09    mad    Reduced SIO_TX count on slave processors
04/03/09    mad    Created from diagdsm.c
===========================================================================*/



/*---------------------------------------------------------------------------
  Size, Count, Few, many and do not exceed counts for DIAG items SIO RX
  (Receive diag pkts from USB on master. 
  Receive diag pkts forwarded via SMD on slave.)
---------------------------------------------------------------------------*/
#if !defined DSMI_DIAG_SIO_RX_ITEM_SIZ
#define DSMI_DIAG_SIO_RX_ITEM_SIZ                 2048
#endif

#if !defined DSMI_DIAG_SIO_RX_ITEM_CNT
#define DSMI_DIAG_SIO_RX_ITEM_CNT                 5
#endif

#define DSMI_DIAG_SIO_RX_ITEM_DONT_EXCEED         3 /* we have 3 re-tries for a packet */
#define DSMI_DIAG_SIO_RX_ITEM_FEW_MARK            (1)
#define DSMI_DIAG_SIO_RX_ITEM_MANY_MARK           (4)

/*---------------------------------------------------------------------------
  Size, Count Number for DIAG items CTRL TX/RX
---------------------------------------------------------------------------*/
/* the DSM Items size and number for the control Channel */
//TODO: Analysis to get a optimal size for the items and the count


#if !defined DSMI_DIAG_SIO_CTRL_RX_ITEM_SIZ
#define DSMI_DIAG_SIO_CTRL_RX_ITEM_SIZ                 512
#endif
  
#if !defined DSMI_DIAG_SIO_CTRL_RX_ITEM_CNT
#define DSMI_DIAG_SIO_CTRL_RX_ITEM_CNT                 40
#endif

#if !defined DSMI_DIAG_SIO_CTRL_TX_ITEM_SIZ
#define DSMI_DIAG_SIO_CTRL_TX_ITEM_SIZ                 512
#endif
  
#if !defined DSMI_DIAG_SIO_CTRL_TX_ITEM_CNT
#define DSMI_DIAG_SIO_CTRL_TX_ITEM_CNT                 10
#endif

#define DSMI_DIAG_SIO_CTRL_RX_ITEM_DONT_EXCEED         10
#define DSMI_DIAG_SIO_CTRL_RX_ITEM_FEW_MARK            ((DSMI_DIAG_SIO_CTRL_RX_ITEM_CNT) - 10) /* This many used to start sending again */
#define DSMI_DIAG_SIO_CTRL_RX_ITEM_MANY_MARK           ((DSMI_DIAG_SIO_CTRL_RX_ITEM_CNT) - 5)  /* This many used when we stop sending */
  
#define DSMI_DIAG_SIO_CTRL_TX_ITEM_DONT_EXCEED         10
#define DSMI_DIAG_SIO_CTRL_TX_ITEM_FEW_MARK            ((DSMI_DIAG_SIO_CTRL_TX_ITEM_CNT) - 8) /* This many used to start sending again */
#define DSMI_DIAG_SIO_CTRL_TX_ITEM_MANY_MARK           ((DSMI_DIAG_SIO_CTRL_TX_ITEM_CNT) - 4)  /* This many used when we stop sending */

  
/*---------------------------------------------------------------------------
  Size, Count, Few, many and do not exceed counts for DIAG items SIO TX
  (Transmit to USB on master
  Transmit via SMD on slave)
---------------------------------------------------------------------------*/
#if !defined DSMI_DIAG_SIO_TX_ITEM_SIZ
#define DSMI_DIAG_SIO_TX_ITEM_SIZ                 4096
#endif

#if !defined DSMI_DIAG_SIO_TX_ITEM_CNT
#define DSMI_DIAG_SIO_TX_ITEM_CNT                 14 /* Making the count less on slave processor, since master should have enough DSM items to handle sum of all slave traffic */
#endif

#define DSMI_DIAG_SIO_TX_ITEM_FEW_MARK            8
#define DSMI_DIAG_SIO_TX_ITEM_MANY_MARK           11

  /* Number of items we want consumed before triggering flow control */
  #define DSMI_DIAG_SIO_TX_ITEM_BUFFERED_MANY_MARK           ((DSMI_DIAG_SIO_TX_ITEM_CNT) - 8)
  /* Number of items we want outstanding before restoring flow */
  #define DSMI_DIAG_SIO_TX_ITEM_BUFFERED_FEW_MARK            ((DSMI_DIAG_SIO_TX_ITEM_BUFFERED_MANY_MARK) - 7)
  
#if !defined DSMI_DIAG_SIO_TX_ITEM_BUFFERED_MANY_DRAIN_MARK
  #define DSMI_DIAG_SIO_TX_ITEM_BUFFERED_MANY_DRAIN_MARK     ((DSMI_DIAG_SIO_TX_ITEM_CNT) - 15)
#endif

#if !defined DSMI_DIAG_SIO_TX_ITEM_BUFFERED_FEW_DRAIN_MARK
  #define DSMI_DIAG_SIO_TX_ITEM_BUFFERED_FEW_DRAIN_MARK      (5)
#endif

/* Buffering Mode parameters */
#if defined(DIAG_MP_MASTER)
  #define DSMI_DIAG_BUFFERED_MANY_FLOW_MARK               DSMI_DIAG_SMD_TX_ITEM_BUFFERED_MANY_MARK
  #define DSMI_DIAG_BUFFERED_FEW_FLOW_MARK                DSMI_DIAG_SMD_TX_ITEM_BUFFERED_FEW_MARK
  #define DSMI_DIAG_BUFFERED_MANY_DRAIN_MARK              DSMI_DIAG_SMD_TX_ITEM_BUFFERED_MANY_DRAIN_MARK
  #define DSMI_DIAG_BUFFERED_FEW_DRAIN_MARK               DSMI_DIAG_SMD_TX_ITEM_BUFFERED_FEW_DRAIN_MARK
  
  #define DIAG_BUFFERED_DSM_CNT_TO_BYTES( cnt )			  (cnt * DSMI_DIAG_SIO_TX_ITEM_SIZ)
  #define DIAG_DEFAULT_BUFFERED_DSM_TOT_COUNT             (DSMI_DIAG_SIO_TX_ITEM_CNT)
  #define DIAG_DEFAULT_BUFFERED_DSM_ITEM_SIZE              DSMI_DIAG_SIO_TX_ITEM_SIZ
#else
  /* For flow control (Count of DSMs used) */
  #define DSMI_DIAG_BUFFERED_MANY_FLOW_MARK               DSMI_DIAG_SIO_TX_ITEM_BUFFERED_MANY_MARK
  #define DSMI_DIAG_BUFFERED_FEW_FLOW_MARK                DSMI_DIAG_SIO_TX_ITEM_BUFFERED_FEW_MARK
  /* For buffering mode draining (Count of DSMs used) */
  #define DSMI_DIAG_BUFFERED_MANY_DRAIN_MARK              DSMI_DIAG_SIO_TX_ITEM_BUFFERED_MANY_DRAIN_MARK
  #define DSMI_DIAG_BUFFERED_FEW_DRAIN_MARK               DSMI_DIAG_SIO_TX_ITEM_BUFFERED_FEW_DRAIN_MARK
  
  #define DIAG_BUFFERED_DSM_CNT_TO_BYTES( cnt )			  (cnt * DSMI_DIAG_SIO_TX_ITEM_SIZ)
  #define DIAG_DEFAULT_BUFFERED_DSM_TOT_COUNT             (DSMI_DIAG_SIO_TX_ITEM_CNT)
  #define DIAG_DEFAULT_BUFFERED_DSM_ITEM_SIZE              DSMI_DIAG_SIO_TX_ITEM_SIZ
  
  #define DIAG_BUFFERED_MANY_FLOW_PER_MARK       (90) /* % of buffer full when we disable flow */
  #define DIAG_BUFFERED_FEW_FLOW_PER_MARK        (70) /* % of buffer full when we resume flow */
  #define DIAG_BUFFERED_MANY_DRAIN_PER_MARK      (75) /* % of buffer full when we start to drain or wrap */
  #define DIAG_BUFFERED_FEW_DRAIN_PER_MARK       (20) /* % of buffer full when we stop draining */
#endif


#endif /* DIAGDSMI_H */

