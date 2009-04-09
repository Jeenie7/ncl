/*
 *      $Id: userAddProto.c,v 1.6 2009-04-01 21:19:36 huangwei Exp $
 */
/************************************************************************
*                                                                   *
*            Copyright (C)  2009                                    *
*       University Corporation for Atmospheric Research             *
*           All Rights Reserved                                     *
*                                                                   *
************************************************************************/
/*
 *    File:		userAddProto.c
 *
 *    Author:		Wei Huang
 *    		National Center for Atmospheric Research
 *    		PO 3000, Boulder, Colorado
 *
 *    Date:		Fri March 20 11:24:07 MDT 2009
 *
 *    Description:	
 */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <ncarg/hlu/hlu.h>
#include <ncarg/hlu/NresDB.h>
#include "defs.h"
#include "NclBuiltIns.h"
#include "MathFuncs.h"
#include "HLUFunctions.h"

extern NhlErrorTypes _Nclstr_fields_count(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_get_field(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_get_cols(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_substitute_str(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_is_blank(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_left_strip(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_right_strip(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_strip(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_squeeze(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_index_of_substr(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_upper(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_lower(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_switch(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_capital(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_concat(
#if NhlNeedProto
void
#endif
);

extern NhlErrorTypes _Nclstr_join(
#if NhlNeedProto
void
#endif
);

void NclAddUserBuiltInFuncs
#if     NhlNeedProto
(void)
#else
()
#endif
{
    void *args;
    int dimsizes[NCL_MAX_DIMENSIONS];
    int nargs = 0;

    nargs = 0;
    args = NewArgs(2);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    dimsizes[0] = 1;
    SetArgTemplate(args, nargs, "string", 1, dimsizes); nargs++;
    NclRegisterFunc(_Nclstr_fields_count, args, "str_fields_count", nargs);

    nargs = 0;
    args = NewArgs(3);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    dimsizes[0] = 1;
    SetArgTemplate(args, nargs, "numeric", 1, dimsizes); nargs++;
    dimsizes[0] = 1;
    SetArgTemplate(args, nargs, "string", 1, dimsizes); nargs++;
    NclRegisterFunc(_Nclstr_get_field, args, "str_get_field", nargs);
    
    nargs = 0;
    args = NewArgs(3);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    dimsizes[0] = 1;
    SetArgTemplate(args, nargs, "numeric", 1, dimsizes); nargs++;
    dimsizes[0] = 1;
    SetArgTemplate(args, nargs, "numeric", 1, dimsizes); nargs++;
    NclRegisterFunc(_Nclstr_get_cols, args, "str_get_cols", nargs);
    
    nargs = 0;
    args = NewArgs(3);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    dimsizes[0] = 1;
    SetArgTemplate(args, nargs, "string", 1, dimsizes); nargs++;
    dimsizes[0] = 1;
    SetArgTemplate(args, nargs, "string", 1, dimsizes); nargs++;
    NclRegisterFunc(_Nclstr_substitute_str, args, "str_substitute_str", nargs);
    NclRegisterFunc(_Nclstr_substitute_str, args, "str_sub_str", nargs);

    nargs = 0;
    args = NewArgs(1);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    NclRegisterFunc(_Nclstr_is_blank, args, "str_is_blank", nargs);

    nargs = 0;
    args = NewArgs(1);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    NclRegisterFunc(_Nclstr_left_strip, args, "str_left_strip", nargs);

    nargs = 0;
    args = NewArgs(1);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    NclRegisterFunc(_Nclstr_right_strip, args, "str_right_strip", nargs);

    nargs = 0;
    args = NewArgs(1);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    NclRegisterFunc(_Nclstr_strip, args, "str_strip", nargs);

    nargs = 0;
    args = NewArgs(1);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    NclRegisterFunc(_Nclstr_squeeze, args, "str_squeeze", nargs);

    nargs = 0;
    args = NewArgs(1);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    NclRegisterFunc(_Nclstr_upper, args, "str_upper", nargs);

    nargs = 0;
    args = NewArgs(1);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    NclRegisterFunc(_Nclstr_lower, args, "str_lower", nargs);

    nargs = 0;
    args = NewArgs(1);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    NclRegisterFunc(_Nclstr_switch, args, "str_switch", nargs);

    nargs = 0;
    args = NewArgs(1);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    NclRegisterFunc(_Nclstr_capital, args, "str_capital", nargs);

    nargs = 0;
    args = NewArgs(3);
    dimsizes[0] = 1;
    SetArgTemplate(args, nargs, "string", 1, dimsizes); nargs++;
    SetArgTemplate(args, nargs, "string", 1, dimsizes); nargs++;
    SetArgTemplate(args, nargs, "numeric", 1, dimsizes); nargs++;
    NclRegisterFunc(_Nclstr_index_of_substr, args, "str_index_of_substr", nargs);

    nargs = 0;
    args = NewArgs(1);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    NclRegisterFunc(_Nclstr_concat, args, "str_concat", nargs);

    nargs = 0;
    args = NewArgs(2);
    SetArgTemplate(args, nargs, "string", 0, NclANY); nargs++;
    dimsizes[0] = 1;
    SetArgTemplate(args, nargs, "string", 1, dimsizes); nargs++;
    NclRegisterFunc(_Nclstr_join, args, "str_join", nargs);

  /*
   */

    return;
}

#ifdef __cplusplus
}
#endif
