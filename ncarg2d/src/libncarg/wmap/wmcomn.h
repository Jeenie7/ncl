C
C	$Id: wmcomn.h,v 1.10 2000-07-20 19:28:33 fred Exp $
C                                                                      
C                Copyright (C)  2000
C        University Corporation for Atmospheric Research
C                All Rights Reserved
C
C This file is free software; you can redistribute it and/or modify
C it under the terms of the GNU Lesser General Public License as
C published by the Free Software Foundation; either version 2.1 of the
C License, or (at your option) any later version.
C
C This software is distributed in the hope that it will be useful, but
C WITHOUT ANY WARRANTY; without even the implied warranty of
C MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
C Lesser General Public License for more details.
C
C You should have received a copy of the GNU Lesser General Public
C License along with this software; if not, write to the Free Software
C Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
C USA.
C
C  Size of the symbol type array.  This is a hardwired maximum.
C
      PARAMETER (ISDIM=200)
C
C  Tension factor used for spline computations.
C
      PARAMETER(TNSION=0.001)
C
C  WMCOMI contains the values for all settable INTEGER and REAL
C  parameters:
C
C    Var.    Name  Def.
C    ----    ----  -----------------------------
C    SYMWID  SWI   Default symbol width.
C    BEGDST  BEG   Distance to leave along the curve before the first
C                  symbol is drawn.
C    ENDDST  END   Distance to leave along the curve after the final 
C                   ymbol is drawn.
C    BETDST  BET   Distance to leave along the curve between symbols.
C    MAXSYM  MXS   Maximum number of symbols allowed along a front line.
C    ISTYPE  STY   An integer array indicating the sequence of symbol
C                   ypes to be drawn along a front line (1 = warm; 2 = cold; 
C                  3 = convergence).
C    IARNDX  PAI   Current array index.
C    IFRONT  FRO   Type of front (1=cold, 2=warm, 3=occluded, 4=stationary,
C                   =squall, 6=tropical, 7=convergence).
C    CRVLEN  ARC   Length of current curve.
C    ISLFLG  SLF   Flag for usage of endline slopes in interpolator.
C    SLOPE1  SL1   Supplied slope for beginning of line.
C    SLOPE2  SL2   Supplied slope for end of line.
C    SLOPEL  CS1   Slope calculated at beginning of spline curve.
C    SLOPER  CS2   Slope calculated at end of spline curve.
C    IALOFT  ALO   Flag to indicate surface/aloft.
C    RLINWD  LIN   Line width scale factor.
C    DLINWD  DWD   Line width scale factor for fronts with dashed lines.
C    IWDTYP  WTY   Controls how line widths are implemented (0=use GKS
C                  inewidth scale factor; 1=use internal subroutines)
C    SLINWD  LWD   Width of line if using the precise width linewidth 
C                  option.
C    ICOLOR  COL   GKS color index to be used for objects that have only
C                  a single color selection.
C    NPTSBZ  NBZ   Number of points used in calculating the Bezier curves 
C                   aking up the warm front symbols.
C    WSIZET  THT   Size of labels drawn with WMLABT.
C    WSIZEC  CHT   Size of labels drawn with WMLABC.
C    WSIZEW  WHT   Size of labels drawn with WMLABW.
C    WSIZES  SHT   Size of labels drawn with WMLABS.
C    WSIZER  RHT   Size of symbols in regional weather patterns.
C    ARWSIZ  ARS   Size of arrow as fraction of maximum screen height.
C    ARWLEN  ARL   Scale factor for the length of an arrow independent of
C                  its size.
C    ARWDIR  ARD   Direction of arrows, in degrees.
C    CDOTSZ  DTS   Diameter of dot used to mark cities.
C    CTYMRG  CMG   Margin to use for background of city/temp labels.
C    TMPMRG  RMG   Margin to use for background of regional temperature labels.
C    IBGCTY  CBC   Color index to use for background of city/temp labels.
C    IFGTRG  RFC   Color index to use for foreground of regional
C                  temperature labels.
C    IDOTCO  DTC   Color index for the dots that mark cities.
C    WBSHFT  WBS   Length of the shaft of a wind barb as a fraction of the
C                  maximum screen height.
C    WBFTIC  WBT   Length of a full tic on a windbarb as a percentage of 
C                  the shaft length.
C    WBDIST  WBD   Distance between tics along a windbarb as a percentage
C                  of the shaft length.
C    WBCLMR  WBR   Radius of the larger circle used to represent calm (as
C                  a percentage of the windbarb shaft length.
C    WBBANG  WBA   Angle the barbs on a windbarb make with the shaft.
C    WBXL          Left X extent of last wind barb drawn (in NDC).
C    WBXR          Right X extent of last wind barb drawn (in NDC).
C    WBYB          Bottom Y extent of last wind barb drawn (in NDC).
C    WBYT          Top Y extent of last wind barb drawn (in NDC).
C    WBBASE  WBC   Diameter of sky cover at base of wind barb as a fraction
C                  of the shaft length.
C    IWBBAS  WBF   Flag indicating whether space should be left at the base
C                  of a wind barb (=1) or not (=0, the default).
C    WBLSIZ  WBL   Size of text labels in station model display.
C    ISUNC1  SC1   Color index for center of sun symbol.
C    ISUNC2  SC2   Color index for points of sun symbol.
C    ISUNC3  SC3   Color index for outline of sun symbol.
C    ISUNC4  SC4   Color index for color of sun symbol offset.
C    ICLDC1  CC1   Color index for cloud symbol.
C    ICLDC2  CC2   Color index for outline.
C    ICLDC3  CC3   Color index for cloud symbol offset.
C    ILTNC1  LC1   Color index for lightening bolt symbol.
C    ILTNC2  LC2   Color index for lightening bolt outline.
C    ILTNC3  LC3   Color index for lightening bolt offset.
C    NUMSYO  NMS   Forces this number of symbols on a front line if > 0.
C    IWARMC  WFC   Color index for drawing warm front symbols.
C    ICOLDC  CFC   Color index for drawing cold front symbols.
C    IHIGC1  HIS   Shadow color for high symbols.
C    IHIGC2  HIB   Symbol color for high symbols.
C    IHIGC3  HIF   Character background color for high symbols.
C    IHIGC4  HIC   Color for circle perimeter around high symbols.
C    ILOWC1  LOS   Shadow color for low symbols.
C    ILOWC2  LOB   Symbol color for low symbols.
C    ILOWC3  LOF   Character background color for low symbols.
C    ILOWC4  LOC   Color for circle perimeter around low symbols.
C    IRGLC1  RC1   Color of box outline for regional weather labels.
C    IRGLC2  RC2   Color of character background color for regional labels.
C    IRGLC3  RC3   Color of shadow for regional labels.
C    IRGLC4  RC4   Color of characters for regional labels.
C    IRGLC5  RC5   Color of outlines for characters for regional labels.
C    IDOTBG  DBC   Color used for drawing background of a dot symbol.
C    IAROWC  AWC   Arrow color index.
C    IARSHC  ASC   Arrow shadow color.
C    IRLLSC  RLS   Regional temperature label shadow color index.
C    IRLOUC  ROS   Regional temperature label outline color.
C    IRLBKC  RBS   Regional temperature label background box color.
C    IAROUC  AOC   Arrow outline color.
C    ITRO1C  T1C   One color for alternate colors of tropical front. 
C    ITRO2C  T2C   Second color for alternate colors of tropical front.
C    IEZFLG  EZF   Flag for NCL to know if wmap is being used with mapping.
C
      COMMON /WMCOMI/ SYMWID, BEGDST, ENDDST, BETDST, MAXSYM, IARNDX, 
     +                IFRONT, CRVLEN, ISLFLG, SLOPE1, SLOPE2, SLOPEL,
     +                SLOPER, IALOFT, RLINWD, IWDTYP, SLINWD, ICOLOR,
     +                NPTSBZ, WSIZET, WSIZEC, WSIZEW, WSIZES, WSIZER,
     +                ARWSIZ, ARWLEN, ARWDIR, CDOTSZ, CTYMRG, TMPMRG,
     +                IBGCTY, IFGTRG, IDOTCO, WBSHFT, WBFTIC, WBDIST,
     +                WBCLMR, WBBANG, WBXL  , WBXR  , WBYB  , WBYT  ,
     +                WBBASE, IWBBAS, WBLSIZ, ISUNC1, ISUNC2, ISUNC3,
     +                ISUNC4, ICLDC1, ICLDC2, ICLDC3, ILTNC1, ILTNC2,
     +                ILTNC3, DLINWD, NUMSYO, IWARMC, ICOLDC, IHIGC1,
     +                IHIGC2, IHIGC3, ILOWC1, ILOWC2, ILOWC3, IRGLC1,
     +                IRGLC2, IRGLC3, IRGLC4, IDOTBG, IAROWC, IARSHC,
     +                IRLLSC, IRLOUC, IRLBKC, IHIGC4, IAROUC, IRGLC5,
     +                ITRO1C, ITRO2C, ILOWC4, IEZFLG,
     +                ISTYPE(ISDIM)
C
C  WMARRS contains arrray space.
C
      PARAMETER (NPTS=300,NWRK=50000)
      COMMON /WMARRS/XO(NPTS),YO(NPTS),TEMP(NPTS),S(NPTS),
     +               XS(NPTS),YS(NPTS),XOUT(NPTS),YOUT(NPTS),
     +               ALEN(NPTS),RWORK(NWRK)
      COMMON /IMARRS/IWORK(NWRK)
