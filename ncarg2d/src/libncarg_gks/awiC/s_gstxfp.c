/*
 *	$Id: s_gstxfp.c,v 1.2 2000-07-12 17:06:24 haley Exp $
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
 *  Set text font and precision  
 */

#include <ncarg/gks.h>

void gset_text_font_prec
#ifdef NeedFuncProto
(
    const Gtext_font_prec *text_font_prec  /* text font and precision */
)
#else
( text_font_prec )
    Gtext_font_prec *text_font_prec;
#endif
{
    NGCALLF(gstxfp,GSTXFP)(&text_font_prec->font,&text_font_prec->prec);
}
