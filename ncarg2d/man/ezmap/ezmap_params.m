.TH Ezmap_params 3NCARG "March 1993" UNIX "NCAR GRAPHICS"
.na
.nh
.SH NAME
Ezmap_params - This document briefly describes all Ezmap
internal parameters.
.SH DESCRIPTION 
Ezmap has a large group of internal parameters, each of which affects the
behavior of one or more of the Ezmap routines. The current values of the
internal parameters may be retrieved using the routines MAPGTC, MAPGTI,
MAPGTL, and MAPGTR. The values of most of the internal parameters may be
reset using the routines MAPSTC, MAPSTI, MAPSTL, and MAPSTR; some of the
parameters are intended for retrieval only and may not be given new
values in this way. 
.sp
Parameter descriptions, in alphabetical order, of all Ezmap 
internal parameters follow. Each description begins with a line
giving the parameter name and the intrinsic FORTRAN type of the
parameter.   
.IP "\&'AR' - Character" 
For retrieval only. The value of the map 
limits specifier JLTS from the last 
call to MAPSET. The default value is 'MA'.
.IP "\&'Cn' - Integer" 
The character "n" is a digit between 1 and 7. Each 'Cn', if zero
or greater, specifies the color index of some part
of the map. The user must do the calls to GKS
routines to define the color indices. All default
values are -1s, indicating no change in color index
from one part of the map to another.
.IP "\&'C1' - Integer"
Color index for perimeter. See 'Cn', above.
.IP "\&'C2' - Integer"
Color index for grid. See 'Cn', above.
.IP "\&'C3' - Integer"
Color index for labels. See 'Cn', above.
.IP "\&'C4' - Integer"
Color index for limb lines. See 'Cn', above.
.IP "\&'C5' - Integer"
Color index for continent outlines. See 'Cn', above.
.IP "\&'C6' - Integer"
Color index for U.S. state outlines. See 'Cn',
above.
.IP "\&'C7' - Integer"
Color index for outlines of countries of the world.
See 'Cn', above.
.IP "\&'DA' - Integer"
Dashed-line pattern for the grids. A 16-bit
quantity. The default is 21845 (octal 52525 or
binary 0101010101010101).
.IP "\&'DD' - Integer or Real"
Distance between dots along a dotted line drawn by
MAPIT. The default value is 12 (out of 4096; see
\&'RE', below).
.IP "\&'DL' - Integer or Logical"
If true (non-zero), user calls to MAPIT draw dotted
lines. The default is false (zero); lines drawn by
MAPIT are solid or dashed, depending on the current
state of the Dashline package. 'DL' may be reset by a
user version of MAPUSR to change the way in which the
perimeter, the grid, the limb lines, and the
outlines are drawn.
.IP "\&'DO' - Integer or Logical"
If true (non-zero), outlines are dotted. The default
is false (zero); outlines are solid.
.IP "\&'EL' - Integer or Logical"
If true (non-zero), only that part of the map which
falls inside an ellipse inscribed within the normal
rectangular perimeter is drawn. This is particularly
appropriate for use with azimuthal projections and
angular limits specifying a square, in which case
the ellipse becomes a circle, but it will work for
any map. The default value is false (zero).
.IP "\&'ER' - Integer"
For retrieval only. The current value of the error
flag. Initially, the value is zero (no error).
.IP "\&'GD' - Real"
The distance between points used to draw the grid,
in degrees. The default value is 1.; user values
must fall between 0.001 and 10.0.
.IP "\&'GR' - Integer or Real"
The desired grid spacing. A zero suppresses the
grid. The default is 10 degrees.
.IP "\&'G1' - Integer"
The group identifier to be used by MAPBLA when
putting into the area map the group of edges that
define the division of the plotter frame into the
projected images of geographic entities.
.IP "\&'G2' - Integer"
The group identifier to be used by MAPBLA when
putting into the area map the group of edges that
define the division of the plotter frame into
vertical strips.
.IP "\&'IN' - Integer or Logical"
For retrieval only. Initialization flag. If true
(non-zero), it says that Ezmap is in need of
initialization (by a CALL MAPINT). The default value
is true (non-zero).
.IP "\&'LA' - Integer or Logical"
If true (non-zero), label the meridians and the
poles. The default is true (non-zero).
.IP "\&'LS' - Integer"
Controls label size. A character width, to be used
in a call to PWRIT. The default value is 1, which
gives a character width of 12 plotter units.
.IP "\&'MV' - Integer or Real"
Minimum vector length for MAPIT. A point closer to
the previous point than this is omitted. The default
value is 4 (out of 4096; see 'RE', below).
.IP "\&'OU' - Character"
Says which set of outline data to use. The possible
values are 'NO', for no outlines, 'CO', for
continental outlines, 'US', for U.S. state outlines,
\&'PS', for continental outlines plus international
outlines plus U.S. outlines, and 'PO', for
continental outlines plus international outlines.
Default is 'CO'.
.IP "\&'PE' - Integer or Logical"
If true (non-zero), draw the perimeter. The default
is true (non-zero).
.IP "\&'PN' - Integer or Real" 
For retrieval only. The value of PLON from the last
call to MAPROJ. The default value is zero.
.IP "\&'PR' - Character"
For retrieval only. The value of the projection
specifier JPRJ from the last call to MAPROJ. The
default value is 'CE'.
.IP "\&'PT' - Integer or Real" 
For retrieval only. The value of PLAT from the last
call to MAPROJ. The default value is zero.
.IP "\&'Pn' - Integer or Real"
For retrieval only. The character "n" is a digit from 1 to 8,
inclusive. Retrieves values from the call to MAPSET.
P1 through P4 specify PLM1(1), PLM2(1), PLM3(1), and
PLM4(1), while P5 through P8 specify PLM1(2),
PLM2(2), PLM3(2), and PLM4(2). Default values are
all zero.
.IP "\&'RE' - Integer or Real"
The width of the target plotter, in plotter units.
The default value is 4096.
.IP "\&'RO' - Integer or Real"
For retrieval only. The value of ROTA from the last
call to MAPROJ. The default value is zero.
.IP "\&'SA' - Integer or Real"
If 'SA' is greater than 1., a satellite-view
projection replaces the orthographic. The value is
the distance of the satellite from the center of the
earth, in multiples of the earth's radius. The
default value is zero. See also 'S1' and 'S2',
below.
.IP "\&'S1', 'S2' - Integer or Real"
Used only when 'SA' is greater than 1. Both are
angles, in degrees. 'S1' measures the angle between
the line to the center of the earth and the line of
sight (to which the projection plane is
perpendicular). If 'S1' is zero, the projection
shows the earth as seen by a satellite looking
straight down; call this the "basic view". If 'S1'
is non-zero, 'S2' measures the angle from the
positive u axis of the basic view to the line OP,
where O is the origin of the basic view and P is the
projection of the desired line of sight on the basic
view. 'S2' is positive if measured counter-clockwise.
.IP "\&'SR' - Real"
A search radius, in degrees, used by MAPINT in
finding the latitude/longitude range of a map. The
default value is 1.; user values must lie between
0.001 and 10.0. Should not be changed except by advice
of a consultant.
.IP "\&'VS' - Integer"
The vertical-stripping parameter, which determines
whether MAPBLA puts into the area map edge group
\&'G2', defining a set of vertical strips. A negative
or zero value of 'VS' prevents MAPBLA from doing
this. A value greater than zero requests that it be
done and specifies the number of vertical strips to
be created. The default value of 'VS' is 1.
.IP "\&'XL', 'XR', 'YB', and 'YT' - Real"
For retrieval only. The parameters XLOW, XROW, YBOW,
and YTOW from the last call to MAPPOS. Defaults are
0.05, 0.95, 0.05, and 0.95, respectively.
.SH SEE ALSO
Online:
mapgtc,  
mapgti,  
mapgtl,  
mapgtr,  
mappos,   
maproj,  
maprst,  
mapsav,  
mapset,  
mapstc,  
mapsti,  
mapstl,  
mapstr,  
mpgetc,
mpgeti,  
mpgetl,
mpgetr,  
mprset,
mpsetc,  
mpseti,  
mpsetl,  
mpsetr,  
.sp
Hardcopy:
NCAR Graphics Contouring and Mapping Tutorial
.SH COPYRIGHT
Copyright (C) 1987-1996
.br
University Corporation for Atmospheric Research
.br
The use of this Software is governed by a License Agreement.
