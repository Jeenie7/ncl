/*
 *      $Id: LogLinPlot.h,v 1.2 1993-12-22 00:56:01 dbrown Exp $
 */
/************************************************************************
*									*
*			     Copyright (C)  1992			*
*	     University Corporation for Atmospheric Research		*
*			     All Rights Reserved			*
*									*
************************************************************************/
/*
 *	File:		LogLinPlot.h
 *
 *	Author:		David Brown
 *			National Center for Atmospheric Research
 *			PO 3000, Boulder, Colorado
 *
 *	Date:		Tue Nov 16 15:18:58 MST 1993
 *
 *	Description:	Public header for LogLinPlot class.
 */

#ifndef _NLogLinPlot_h
#define _NLogLinPlot_h

#include <ncarg/hlu/Overlay.h>

/*
 * LogLinPlot instance resources
 */

/*
 * LogLinPlot class resources
 */

typedef struct _LogLinPlotLayerClassRec	*LogLinPlotLayerClass;
typedef struct _LogLinPlotLayerRec	*LogLinPlotLayer;

extern LayerClass logLinPlotLayerClass;

#endif /*_NLogLinPlot_h */
