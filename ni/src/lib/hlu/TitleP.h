/*
 *      $Id: TitleP.h,v 1.3 1994-01-27 21:26:39 boote Exp $
 */
/************************************************************************
*									*
*			     Copyright (C)  1992			*
*	     University Corporation for Atmospheric Research		*
*			     All Rights Reserved			*
*									*
************************************************************************/
/*
 *	File:		TitleP.h
 *
 *	Author:		Ethan Alpert
 *			National Center for Atmospheric Research
 *			PO 3000, Boulder, Colorado
 *
 *	Date:		Wed Nov 18 15:53:22 MST 1992
 *
 *	Description:	
 */
#ifndef  _NTitleP_h
#define _NTitleP_h 

#include <ncarg/hlu/ViewP.h>
#include <ncarg/hlu/Title.h>
#include <ncarg/hlu/TextItem.h>

typedef struct _NhlTitleLayerPart {
/* Publically setable resource fields */
	float	delta;
	char	*main_string;
	NhlBoolean	main_on;
	NhlTitlePositions	main_side;
	NhlTitlePositions	main_position;
	int	main_just;
	NhlFont	main_font;
	float 	main_font_height;
	float 	main_font_aspect;
	float 	main_font_thickness;
	float   main_angle;
	NhlTextDirection	main_direction;
	float	main_constant_spacing;
	char 	main_func_code;
	float	main_offset_x;
	float	main_offset_y;
	NhlFontQuality	main_font_quality;
	int	use_main_attributes; /* if set only those TextItem attributes 
					blonging to the main resources will be 
					used for all the titles */
	int 	main_font_color;
	char	*x_axis_string;
	NhlBoolean	x_axis_on;
	NhlTitlePositions	x_axis_side;
	NhlTitlePositions	x_axis_position;
	int	x_axis_just;
	NhlFont	x_axis_font;
	float 	x_axis_font_height;
	float	x_axis_font_aspect;
	float	x_axis_font_thickness;
	float	x_axis_angle;
	NhlTextDirection	x_axis_direction;
	float 	x_axis_constant_spacing;
	float	x_axis_offset_x;
	float	x_axis_offset_y;
	char	x_axis_func_code;
	NhlFontQuality	x_axis_font_quality;
	int 	x_axis_font_color;

	char	*y_axis_string;
	NhlBoolean	y_axis_on;
	NhlTitlePositions	y_axis_side;
	NhlTitlePositions	y_axis_position;
	int	y_axis_just;
	NhlFont	y_axis_font;
	float	y_axis_font_height;
	float	y_axis_font_aspect;
	float	y_axis_font_thickness;
	float	y_axis_angle;
	NhlTextDirection	y_axis_direction;
	float	y_axis_constant_spacing;
	float	y_axis_offset_x;
	float	y_axis_offset_y;
	char	y_axis_func_code;
	NhlFontQuality	y_axis_font_quality;
	int 	y_axis_font_color;
/* Private internal fields */
	int	main_id;
	int	x_axis_id;
	int	y_axis_id;
	float	main_pos_x;
	float	main_pos_y;
	float	x_axis_pos_x;
	float	x_axis_pos_y;
	float	y_axis_pos_x;
	float	y_axis_pos_y;
}NhlTitleLayerPart;

typedef struct _NhlTitleLayerRec {
	NhlBaseLayerPart	base;
	NhlViewLayerPart	view;
	NhlTitleLayerPart	title;
}NhlTitleLayerRec;

typedef struct _NhlTitleLayerClassPart {
	void *foo;
}NhlTitleLayerClassPart;

typedef struct _NhlTitleLayerClassRec {
	NhlBaseLayerClassPart	base_class;
	NhlViewLayerClassPart	view_class;
	NhlTitleLayerClassPart	title_class;
}NhlTitleLayerClassRec;

typedef struct _NhlTitleLayerClassRec *NhlTitleLayerClass;
typedef struct _NhlTitleLayerRec	*NhlTitleLayer;

extern NhlTitleLayerClassRec	NhltitleLayerClassRec;
#endif /* _NTitleP_h */
