/*
 *  $Id: s_gqcf.c,v 1.2 2000-07-12 17:06:10 haley Exp $
 */
/************************************************************************
*                                                                       *
*                Copyright (C)  2000                                    *
*        University Corporation for Atmospheric Research                *
*                All Rights Reserved                                    *
*                                                                       *
* This file is free software; you can redistribute it and/or modify     *
* it under the terms of the GNU Lesser General Public License as        *
* published by the Free Software Foundation; either version 2.1 of the  *
* License, or (at your option) any later version.                       *
*                                                                       *
* This software is distributed in the hope that it will be useful, but  *
* WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
* Lesser General Public License for more details.                       *
*                                                                       *
* You should have received a copy of the GNU Lesser General Public      *
* License along with this software; if not, write to the Free Software  *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307   *
* USA.                                                                  *
*                                                                       *
************************************************************************/

/*
 *  Inquire colour facilities  
 */

#include <ncarg/gks.h>

void ginq_colr_facs
#ifdef NeedFuncProto
(
    Gint       ws_type,    /* workstation type      */
    Gint       *err_ind,   /* OUT error indicator   */
    Gcolr_facs *colr_facs  /* OUT colour facilities */
)
#else
( ws_type, err_ind, colr_facs )
    Gint       ws_type;
    Gint       *err_ind;
    Gcolr_facs *colr_facs;
#endif
{
    NGCALLF(gqcf,GQCF)(&ws_type,err_ind,&colr_facs->num_colrs,
                       &colr_facs->colr_avail,&colr_facs->num_pred_inds);
}
