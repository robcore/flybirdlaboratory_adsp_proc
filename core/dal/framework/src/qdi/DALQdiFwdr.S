/*======================================================================

                DALQdiFwdr.S

GENERAL DESCRIPTION
		  QDI DAL FORWARDING FUNCTIONS in USER-PD
			
EXTERNAL FUNCTIONS
        qurt_qdi_get_dal_fwd_vtable

INITIALIZATION AND SEQUENCING REQUIREMENTS
   None.

      Copyright (c) 2014
                    by QUALCOMM Technologies Incorporated.  All Rights Reserved.

=======================================================================*/

/*======================================================================

                        EDIT HISTORY FOR MODULE

 This section contains comments describing changes made to the module.
 Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.adsp/2.6.1/dal/framework/src/qdi/DALQdiFwdr.S#1 $
$DateTime: 2014/10/16 12:45:40 $

when       who     what, where, why
--------   ---     -----------------------------------------------------
06/08/12   aa      Updated for QDI2.0.
06/01/12   aa      Tuned for DAL, Bug fix and added comments for release.
04/03/12   jack    Initial Version
=======================================================================*/
#include "qurt_qdi_constants.h"

/*
 A DAL forwarding object in user pd's looks like this:
 DalDeviceHandle
     dwDalHandleId == used for identify if the handle is abstraction
                      for remote object via QDI call.
     pVtbl         == points at qurt_qdi_dal_fwd_vtable, which dal 
                      driver methods jump into for any DDI calls
     pClientCtxt   == points at the word where the QDI handle is stored
                      (can be the immediately following word)
     dwQdiHandle   == QDI handle associated with this forwarding object
*/

	.equ QDI_DAL_FWD, 128          /* 0-128 method id reserved for QDI FW */

//	.altmacro

/*
 MACRO vtentry generate assembly output with as many as elements(dal_fwd_x)
 defined in macro definition.(0,99). Its a recursive calls that expands 
 for a vtable containing function pointers until (HI-LO) is greater then 0
 .word dal_fwd_0
 .word dal_fwd_1
 .word dal_fwd_2
 .
 .
 .
 .word dal_fwd_99
*/
/*
	.macro vtentry LO, HI
	.word dal_fwd_\LO
	.if \HI-\LO
	vtentry %(\LO+1),\HI
	.endif
	.endm
*/
/*
 MACRO vtforward generate assembly output with as many as elements(dal_fwd_x)
 definition in macro definition.(0,99). Its a recursive calls that expands 
 until (HI-LO) is greater for function definitions.
 dal_fwd_0 {}
 dal_fwd_1 {}
 dal_fwd_2 {}
 .
 .
 .
 dal_fwd_99 {}
     
*/
	.macro vtforward LO, HI
dal_fwd_\LO:
	{
	r1 = memw(r0+#8)                /* R1 := DalDeviceHandle->pClientCtxt */
	r2 = #(QDI_DAL_FWD+\LO)         /* R2 := method number for forwarding */
   r7:6 = combine(r2,r1)           /* save user args R2, R1 in R7, R6 */
	jump dal_fwd_generic
	}
	.if \HI-\LO
	vtforward %(\LO+1),\HI
	.endif
	.endm

/*
 qurt_qdi_dal_fwd_vtable contains a macro vtentry which a pre-processor
 unwraps with function table of dal forwarders.
 .word dal_fwd_0
 .word dal_fwd_1
 .word dal_fwd_2
 .
 .
 .
 .word dal_fwd_99
*/
	.section .rodata
	.p2align 5
qurt_qdi_dal_fwd_vtable:
//	vtentry 0,99
	.word dal_fwd_0
	.word dal_fwd_1
	.word dal_fwd_2
	.word dal_fwd_3
	.word dal_fwd_4
	.word dal_fwd_5
	.word dal_fwd_6
	.word dal_fwd_7
	.word dal_fwd_8
	.word dal_fwd_9
	.word dal_fwd_10
	.word dal_fwd_11
	.word dal_fwd_12
	.word dal_fwd_13
	.word dal_fwd_14
	.word dal_fwd_15
	.word dal_fwd_16
	.word dal_fwd_17
	.word dal_fwd_18
	.word dal_fwd_19
	.word dal_fwd_20
	.word dal_fwd_21
	.word dal_fwd_22
	.word dal_fwd_23
	.word dal_fwd_24
	.word dal_fwd_25
	.word dal_fwd_26
	.word dal_fwd_27
	.word dal_fwd_28
	.word dal_fwd_29
	.word dal_fwd_30
	.word dal_fwd_31
	.word dal_fwd_32
	.word dal_fwd_33
	.word dal_fwd_34
	.word dal_fwd_35
	.word dal_fwd_36
	.word dal_fwd_37
	.word dal_fwd_38
	.word dal_fwd_39
	.word dal_fwd_40
	.word dal_fwd_41
	.word dal_fwd_42
	.word dal_fwd_43
	.word dal_fwd_44
	.word dal_fwd_45
	.word dal_fwd_46
	.word dal_fwd_47
	.word dal_fwd_48
	.word dal_fwd_49
	.word dal_fwd_50
	.word dal_fwd_51
	.word dal_fwd_52
	.word dal_fwd_53
	.word dal_fwd_54
	.word dal_fwd_55
	.word dal_fwd_56
	.word dal_fwd_57
	.word dal_fwd_58
	.word dal_fwd_59
	.word dal_fwd_60
	.word dal_fwd_61
	.word dal_fwd_62
	.word dal_fwd_63
	.word dal_fwd_64
	.word dal_fwd_65
	.word dal_fwd_66
	.word dal_fwd_67
	.word dal_fwd_68
	.word dal_fwd_69
	.word dal_fwd_70
	.word dal_fwd_71
	.word dal_fwd_72
	.word dal_fwd_73
	.word dal_fwd_74
	.word dal_fwd_75
	.word dal_fwd_76
	.word dal_fwd_77
	.word dal_fwd_78
	.word dal_fwd_79
	.word dal_fwd_80
	.word dal_fwd_81
	.word dal_fwd_82
	.word dal_fwd_83
	.word dal_fwd_84
	.word dal_fwd_85
	.word dal_fwd_86
	.word dal_fwd_87
	.word dal_fwd_88
	.word dal_fwd_89
	.word dal_fwd_90
	.word dal_fwd_91
	.word dal_fwd_92
	.word dal_fwd_93
	.word dal_fwd_94
	.word dal_fwd_95
	.word dal_fwd_96
	.word dal_fwd_97
	.word dal_fwd_98
	.word dal_fwd_99

/*
 Pre-Proccessor expands vtforward with macro defintion as defined above
 from 2-99. dal_fwd_1 and dal_fwd_2 explicitly defined.
 dal_fwd_2 {}
 dal_fwd_3 {}
 dal_fwd_4 {}
 .
 .
 .
 dal_fwd_99 {}
*/
	.text
	.p2align 5
//	vtforward 2,99
dal_fwd_2:
{
  r1 = memw(r0+#8)
  r2 = #130
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_3:
{
  r1 = memw(r0+#8)
  r2 = #131
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_4:
{
  r1 = memw(r0+#8)
  r2 = #132
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_5:
{
  r1 = memw(r0+#8)
  r2 = #133
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_6:
{
  r1 = memw(r0+#8)
  r2 = #134
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_7:
{
  r1 = memw(r0+#8)
  r2 = #135
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_8:
{
  r1 = memw(r0+#8)
  r2 = #136
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_9:
{
  r1 = memw(r0+#8)
  r2 = #137
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_10:
{
  r1 = memw(r0+#8)
  r2 = #138
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_11:
{
  r1 = memw(r0+#8)
  r2 = #139
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_12:
{
  r1 = memw(r0+#8)
  r2 = #140
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_13:
{
  r1 = memw(r0+#8)
  r2 = #141
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_14:
{
  r1 = memw(r0+#8)
  r2 = #142
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_15:
{
  r1 = memw(r0+#8)
  r2 = #143
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_16:
{
  r1 = memw(r0+#8)
  r2 = #144
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_17:
{
  r1 = memw(r0+#8)
  r2 = #145
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_18:
{
  r1 = memw(r0+#8)
  r2 = #146
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_19:
{
  r1 = memw(r0+#8)
  r2 = #147
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_20:
{
  r1 = memw(r0+#8)
  r2 = #148
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_21:
{
  r1 = memw(r0+#8)
  r2 = #149
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_22:
{
  r1 = memw(r0+#8)
  r2 = #150
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_23:
{
  r1 = memw(r0+#8)
  r2 = #151
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_24:
{
  r1 = memw(r0+#8)
  r2 = #152
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_25:
{
  r1 = memw(r0+#8)
  r2 = #153
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_26:
{
  r1 = memw(r0+#8)
  r2 = #154
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_27:
{
  r1 = memw(r0+#8)
  r2 = #155
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_28:
{
  r1 = memw(r0+#8)
  r2 = #156
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_29:
{
  r1 = memw(r0+#8)
  r2 = #157
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_30:
{
  r1 = memw(r0+#8)
  r2 = #158
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_31:
{
  r1 = memw(r0+#8)
  r2 = #159
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_32:
{
  r1 = memw(r0+#8)
  r2 = #160
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_33:
{
  r1 = memw(r0+#8)
  r2 = #161
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_34:
{
  r1 = memw(r0+#8)
  r2 = #162
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_35:
{
  r1 = memw(r0+#8)
  r2 = #163
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_36:
{
  r1 = memw(r0+#8)
  r2 = #164
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_37:
{
  r1 = memw(r0+#8)
  r2 = #165
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_38:
{
  r1 = memw(r0+#8)
  r2 = #166
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_39:
{
  r1 = memw(r0+#8)
  r2 = #167
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_40:
{
  r1 = memw(r0+#8)
  r2 = #168
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_41:
{
  r1 = memw(r0+#8)
  r2 = #169
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_42:
{
  r1 = memw(r0+#8)
  r2 = #170
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_43:
{
  r1 = memw(r0+#8)
  r2 = #171
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_44:
{
  r1 = memw(r0+#8)
  r2 = #172
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_45:
{
  r1 = memw(r0+#8)
  r2 = #173
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_46:
{
  r1 = memw(r0+#8)
  r2 = #174
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_47:
{
  r1 = memw(r0+#8)
  r2 = #175
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_48:
{
  r1 = memw(r0+#8)
  r2 = #176
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_49:
{
  r1 = memw(r0+#8)
  r2 = #177
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_50:
{
  r1 = memw(r0+#8)
  r2 = #178
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_51:
{
  r1 = memw(r0+#8)
  r2 = #179
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_52:
{
  r1 = memw(r0+#8)
  r2 = #180
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_53:
{
  r1 = memw(r0+#8)
  r2 = #181
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_54:
{
  r1 = memw(r0+#8)
  r2 = #182
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_55:
{
  r1 = memw(r0+#8)
  r2 = #183
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_56:
{
  r1 = memw(r0+#8)
  r2 = #184
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_57:
{
  r1 = memw(r0+#8)
  r2 = #185
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_58:
{
  r1 = memw(r0+#8)
  r2 = #186
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_59:
{
  r1 = memw(r0+#8)
  r2 = #187
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_60:
{
  r1 = memw(r0+#8)
  r2 = #188
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_61:
{
  r1 = memw(r0+#8)
  r2 = #189
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_62:
{
  r1 = memw(r0+#8)
  r2 = #190
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_63:
{
  r1 = memw(r0+#8)
  r2 = #191
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_64:
{
  r1 = memw(r0+#8)
  r2 = #192
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_65:
{
  r1 = memw(r0+#8)
  r2 = #193
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_66:
{
  r1 = memw(r0+#8)
  r2 = #194
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_67:
{
  r1 = memw(r0+#8)
  r2 = #195
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_68:
{
  r1 = memw(r0+#8)
  r2 = #196
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_69:
{
  r1 = memw(r0+#8)
  r2 = #197
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_70:
{
  r1 = memw(r0+#8)
  r2 = #198
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_71:
{
  r1 = memw(r0+#8)
  r2 = #199
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_72:
{
  r1 = memw(r0+#8)
  r2 = #200
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_73:
{
  r1 = memw(r0+#8)
  r2 = #201
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_74:
{
  r1 = memw(r0+#8)
  r2 = #202
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_75:
{
  r1 = memw(r0+#8)
  r2 = #203
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_76:
{
  r1 = memw(r0+#8)
  r2 = #204
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_77:
{
  r1 = memw(r0+#8)
  r2 = #205
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_78:
{
  r1 = memw(r0+#8)
  r2 = #206
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_79:
{
  r1 = memw(r0+#8)
  r2 = #207
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_80:
{
  r1 = memw(r0+#8)
  r2 = #208
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_81:
{
  r1 = memw(r0+#8)
  r2 = #209
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_82:
{
  r1 = memw(r0+#8)
  r2 = #210
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_83:
{
  r1 = memw(r0+#8)
  r2 = #211
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_84:
{
  r1 = memw(r0+#8)
  r2 = #212
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_85:
{
  r1 = memw(r0+#8)
  r2 = #213
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_86:
{
  r1 = memw(r0+#8)
  r2 = #214
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_87:
{
  r1 = memw(r0+#8)
  r2 = #215
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_88:
{
  r1 = memw(r0+#8)
  r2 = #216
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_89:
{
  r1 = memw(r0+#8)
  r2 = #217
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_90:
{
  r1 = memw(r0+#8)
  r2 = #218
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_91:
{
  r1 = memw(r0+#8)
  r2 = #219
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_92:
{
  r1 = memw(r0+#8)
  r2 = #220
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_93:
{
  r1 = memw(r0+#8)
  r2 = #221
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_94:
{
  r1 = memw(r0+#8)
  r2 = #222
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_95:
{
  r1 = memw(r0+#8)
  r2 = #223
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_96:
{
  r1 = memw(r0+#8)
  r2 = #224
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_97:
{
  r1 = memw(r0+#8)
  r2 = #225
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_98:
{
  r1 = memw(r0+#8)
  r2 = #226
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}

dal_fwd_99:
{
  r1 = memw(r0+#8)
  r2 = #227
  r7:6 = combine(r2,r1)
  jump dal_fwd_generic
}
 


/*
 dal_fwd_generic : Loads the qdi handle in r0 and invoke qurt_qdi_handle_invoke
 to trap in qurtos.
*/   

dal_fwd_generic:
	{
   C1:0 = R7:6                      /* Cl:0 specify the LC0/SA0 pair, expect first source register to be of higher index */
	r1 = memw(r1)                    /* Load QDI handle from address in r1 */                                      
   r0 = #QDI_HANDLE_LOCAL_CLIENT    /* R0 := QDI handle for denote its a local qdi client */
	jump ##qurt_qdi_qhi12            /* Go invoke the QDI handle, will explicitly pass all 12 args */
	}

/* 
 We do not support forwarding the first/second entry (Attach/Detach), 
 using forwarder so return -1 unconditionally.  They are handled via 
 DALFWK. 
*/

dal_fwd_0:
dal_fwd_1:

	{
	r0 = #-1
	jumpr r31
	}

/*
 void *qurt_qdi_get_dal_fwd_vtable(void);
 Returns a pointer to the DAL QDI forwarding vtable which is appropriate for 
 use to initialize the pVtbl field of a DAL QDI forwarding object.
*/

	.globl qurt_qdi_get_dal_fwd_vtable
qurt_qdi_get_dal_fwd_vtable:
	{
	r0 = ##qurt_qdi_dal_fwd_vtable
	jumpr r31
	}
