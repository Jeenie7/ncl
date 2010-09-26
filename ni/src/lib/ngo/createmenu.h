/*
 *      $Id: createmenu.h,v 1.3 2000-03-21 02:35:33 dbrown Exp $
 */
/************************************************************************
*									*
*			     Copyright (C)  1996			*
*	     University Corporation for Atmospheric Research		*
*			     All Rights Reserved			*
*									*
************************************************************************/
/*
 *	File:		createmenu.h
 *
 *	Author:		David I. Brown
 *			National Center for Atmospheric Research
 *			PO 3000, Boulder, Colorado
 *
 *	Date:		Mon Sep 15 13:49:25 MDT 1997
 *
 *	Description:	
 */
#ifndef	_NG_CREATEMENU_H
#define	_NG_CREATEMENU_H

#include <ncarg/ngo/go.h>
#include <ncarg/ngo/browse.h>

/*
 * Public api
 */
        
typedef struct _NgCreateMenuRec
{
        Widget		data_mbutton;
        Widget		wks_mbutton;
        Widget		plot_mbutton;
        Widget		anno_mbutton;
        Widget		other_mbutton;
        Widget		var_mbutton;
        Widget		file_mbutton;
} NgCreateMenu;

NgCreateMenu *
NgCreateCreateMenu(
        int		goid,
        Widget		parent
        );

NhlErrorTypes
NgUpdateCreateMenu
(
        NgCreateMenu		*create_menu
        );
        
void
NgDestroyCreateMenu
(
        NgCreateMenu		*create_menu
        );
        

#endif	/* _NG_CREATEMENU_H */