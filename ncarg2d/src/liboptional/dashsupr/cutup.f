C
C	$Id: cutup.f,v 1.5 2006-03-16 17:55:02 kennison Exp $
C                                                                      
C                Copyright (C)  2000
C        University Corporation for Atmospheric Research
C                All Rights Reserved
C
C This file is free software; you can redistribute it and/or modify
C it under the terms of the GNU General Public License as published
C by the Free Software Foundation; either version 2 of the License, or
C (at your option) any later version.
C
C This software is distributed in the hope that it will be useful, but
C WITHOUT ANY WARRANTY; without even the implied warranty of
C MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
C General Public License for more details.
C
C You should have received a copy of the GNU General Public License
C along with this software; if not, write to the Free Software
C Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
C USA.
C
      SUBROUTINE CUTUP (MX1,MY1,MX2,MY2)
C
C THE CONNECTION LINES BETWEEN POINTS PROCESSED WITH DASHSUPR ARE
C SMOOTHED AND THEREFORE MOST LINE SEGMENTS WILL BE VERY SHORT.
C IN CASE ONLY 2 POINTS ARE BEING PROCESSED NO SMOOTHING WILL BE DONE
C AND VERY LONG LINE SEGMENTS CAN OCCUR.
C SUCH LONG LINES ARE DIVIDED UP INTO SHORT SEGMENTS IN THE ROUTINE
C CUTUP, BECAUSE THE ALGORITHM FOR THE REMOVAL OF CROWDED LINES RELIES
C ON SHORT LINE SEGMENTS.
C
      COMMON/INTPR/IPAU,FPART,TENSN,NP,SMALL,L1,ADDLR,ADDTB,MLLINE,
     1    ICLOSE
      SAVE
C
C FOR BETTER ACCURACY CHOOSE LONGER COORDINATE AS BASIS FOR ITERATION.
C
      DX = MX2-MX1
      DY = MY2-MY1
      IF (ABS(DX)-ABS(DY)) 60,50,10
C
C DX IS LONGER THAN DY.
C
   10 SLOPE = DY/DX
      IF (DX .LT. 0.) GO TO 30
C
      CALL CFVLD (1,MX1,MY1)
      DO 20 MX=MX1,MX2,MLLINE
         MY = INT(REAL(MY1)+REAL(MX-MX1)*SLOPE+.5)
         CALL CFVLD (2,MX,MY)
   20 CONTINUE
      CALL CFVLD (1,MX2,MY2)
      GOTO 100
C
   30 CONTINUE
      CALL CFVLD (1,MX2,MY2)
      DO 40 MX=MX2,MX1,MLLINE
         MY = INT(REAL(MY2)+REAL(MX-MX2)*SLOPE+.5)
         CALL CFVLD (2,MX,MY)
   40 CONTINUE
      CALL CFVLD (2,MX1,MY1)
      GOTO 100
C
C DX AND DY HAVE SAME LENGTH.
C
   50 IF (DX .NE. 0.) GO TO 10
      CALL CFVLD (2,MX2,MY2)
      RETURN
C
C DY IS LONGER THAN DX.
C
   60 SLOPE = DX/DY
      IF (DY .LT. 0.) GO TO 80
C
      CALL CFVLD (1,MX1,MY1)
      DO 70 MY=MY1,MY2,MLLINE
         MX = INT(REAL(MX1)+REAL(MY-MY1)*SLOPE+.5)
         CALL CFVLD (2,MX,MY)
   70 CONTINUE
      CALL CFVLD (2,MX2,MY2)
      GOTO 100
C
   80 CONTINUE
C
      CALL CFVLD (1,MX2,MY2)
      DO 90 MY=MY2,MY1,MLLINE
         MX = INT(REAL(MX2)+REAL(MY-MY2)*SLOPE+.5)
         CALL CFVLD (2,MX,MY)
   90 CONTINUE
      CALL CFVLD (2,MX1,MY1)
C
  100 CONTINUE
C
      RETURN
      END
