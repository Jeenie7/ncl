/*
 *      $Id: ncgmstat.c,v 1.4 2000-07-12 18:13:46 haley Exp $
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
 *	File:		ncgmstat.c
 *
 *	Author:		John Clyne
 *			National Center for Atmospheric Research
 *			PO 3000, Boulder, Colorado
 *
 *	Date:		Wed Apr 8 12:52:58 MDT 1992
 *
 *	Description:	Get status of a CGM.
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ncarg/cgm_tools.h>
#include <ncarg/c.h>



/*
 * 	command line options
 */
static	struct	{
	boolean		do_frame_count;
	boolean		do_version;
	boolean		do_help;
	} opt;

static  OptDescRec      set_options[] = {
	{"count", 0, NULL, "Report number of frames in file and exit"},
	{"Version", 0, NULL, "Print version and exit"},
	{"help", 0, NULL, "Print this message and exit"},
	{NULL},
};

static	Option get_options[] = {
	{"count", NCARGCvtToBoolean, (Voidptr) &opt.do_frame_count, 
						sizeof(opt.do_frame_count)
	},
	{"Version", NCARGCvtToBoolean, (Voidptr) &opt.do_version, 
							sizeof(opt.do_version)
	},
	{"help", NCARGCvtToBoolean, (Voidptr) &opt.do_help, 
							sizeof(opt.do_help)
	},
	{NULL
	}
};

static	char	*progName;
static	int		oD;
	
static	void	Usage(msg) 
	char	*msg;
{
	char	*opts = "[-format <format>] [-V|c|h] <metafile>";

	if (msg) {
		fprintf(stderr, "%s: %s\n", progName, msg);
	}
	fprintf(stderr, "Usage: %s %s\n", progName, opts);
	PrintOptionHelp(oD, stderr);
	exit(1);
}


main(argc, argv)
	int	argc;
	char	*argv[];
{
	Directory	*dir;
	Cgm_fd		cgm_fd;

	progName = (progName = strrchr(argv[0],'/')) ? ++progName : *argv;


	oD = OpenOptionTbl();
	if (ParseOptionTable(oD, &argc, argv, set_options) < 0) {
		fprintf(
			stderr, "%s : Error parsing options : %s\n", 
			progName, ErrGetMsg()
		);
		exit(1);
	}

	/*
	 * load the options into opt
	 */
	if (GetOptions(oD, get_options) < 0) {
		fprintf(
			stderr, "%s : Error getting options : %s\n", 
			progName, ErrGetMsg()
		);
		Usage(NULL);
	}


	if (opt.do_version) {
		PrintVersion(progName);
		exit(0);
	}
	if (opt.do_help) {
		Usage(NULL);
	}

	if (argc != 2) {
		Usage(NULL);
	}

	if ((cgm_fd = CGM_open(argv[1], 1440, "r")) == -1) {
		perror(argv[1]);
		exit(2);
	}

	if ((dir = CGM_directory(cgm_fd, NULL)) == (Directory *) NULL) {
		perror(argv[1]);
		exit(2);
	}

	if (opt.do_frame_count) {
		fprintf(stdout, "%d\n", CGM_NUM_FRAMES(dir));
	}
	else {
		CGM_printDirectory(dir);
	}

	CGM_freeDirectory(dir);
	(void) CGM_close(cgm_fd);

	exit(0);
}

