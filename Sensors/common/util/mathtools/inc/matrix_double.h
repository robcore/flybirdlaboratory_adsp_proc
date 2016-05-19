/*============================================================================
  @file accel_cal.c

  Gyroscope calibration algorithm source file 

  Copyright (c) 2010-2011 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
============================================================================*/

/* $Header: //components/rel/ssc.adsp/2.6.1/common/util/mathtools/inc/matrix_double.h#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. 

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2012-06-09  ks   initial version  

============================================================================*/

#define MATRIX_MAX_ROW (6)
#define MATRIX_MAX_COL (6)

// O = M
void matrix_double_copy(double M[MATRIX_MAX_ROW][MATRIX_MAX_COL],
                   int Mrows, int Mcols,
                   double O[MATRIX_MAX_ROW][MATRIX_MAX_COL]);

// O = M * N
void matrix_double_multiply(double M[MATRIX_MAX_ROW][MATRIX_MAX_COL],
                       int Mrows, int Mcols,
                       double N[MATRIX_MAX_ROW][MATRIX_MAX_COL],
                       int Nrows, int Ncols,
                       double O[MATRIX_MAX_ROW][MATRIX_MAX_COL]);

// O = M + N
void matrix_double_add(double M[MATRIX_MAX_ROW][MATRIX_MAX_COL],
                  int Mrows, int Mcols,
                  double N[MATRIX_MAX_ROW][MATRIX_MAX_COL],
                  int Nrows, int Ncols,
                  double O[MATRIX_MAX_ROW][MATRIX_MAX_COL]);

// O = M'
void matrix_double_transpose(double M[MATRIX_MAX_ROW][MATRIX_MAX_COL],
                        int Mrows, int Mcols,
                        double O[MATRIX_MAX_ROW][MATRIX_MAX_COL]);

// O = -M
void matrix_double_negate(double M[MATRIX_MAX_ROW][MATRIX_MAX_COL],
                     int Mrows, int Mcols,
                     double O[MATRIX_MAX_ROW][MATRIX_MAX_COL]);

// O = I ( Identity )
void matrix_double_identity(double O[MATRIX_MAX_ROW][MATRIX_MAX_COL],
                       int Orows, int Ocols);

// O = Zero Matrix
void matrix_double_zero(double O[MATRIX_MAX_ROW][MATRIX_MAX_COL],
                       int Orows, int Ocols);

