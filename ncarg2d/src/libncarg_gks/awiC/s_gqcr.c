/*
 *	$Id: s_gqcr.c,v 1.2 2000-07-12 17:06:11 haley Exp $
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
 * Inquire colour representation  
 */

#include <ncarg/gks.h>

void ginq_colr_rep
#ifdef NeedFuncProto
(
    Gint       ws_id,     /* workstation identifier     */
    Gint       colr_ind,  /* colour index               */
    Ginq_type  type,      /* type of returned values    */
    Gint       *err_ind,  /* OUT error indicator        */
    Gcolr_rep  *colr_rep  /* OUT colour representation  */
)
#else
( ws_id, colr_ind, type, err_ind, colr_rep )
    Gint       ws_id;
    Gint       colr_ind;
    Ginq_type  type;
    Gint       *err_ind;
    Gcolr_rep  *colr_rep;
#endif
{
    NGCALLF(gqcr,GQCR)(&ws_id,&colr_ind,&type,err_ind,
                       &colr_rep->rgb.red,
                       &colr_rep->rgb.green,
                       &colr_rep->rgb.blue);
}
