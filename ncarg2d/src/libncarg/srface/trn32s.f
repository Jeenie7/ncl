C
C $Id: trn32s.f,v 1.5 2006-03-10 14:46:00 kennison Exp $
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
      SUBROUTINE TRN32S (X,Y,Z,XT,YT,ZT,IFLAG)
C
C THIS ROUTINE IMPLEMENTS THE 3-SPACE TO 2-SPACE TRANSFOR-
C MATION BY KUBER, SZABO AND GIULIERI, THE PERSPECTIVE
C REPRESENTATION OF FUNCTIONS OF TWO VARIABLES. J. ACM 15,
C 2, 193-204,1968.
C IFLAG=0 ARGUMENTS
C X,Y,Z    ARE THE 3-SPACE COORDINATES OF THE INTERSECTION
C          OF THE LINE OF SIGHT AND THE IMAGE PLANE.  THIS
C          POINT CAN BE THOUGHT OF AS THE POINT LOOKED AT.
C XT,YT,ZT ARE THE 3-SPACE COORDINATES OF THE EYE POSITION.
C
C IFLAG=1 ARGUMENTS
C X,Y,Z    ARE THE 3-SPACE COORDINATES OF A POINT TO BE
C          TRANSFORMED.
C XT,YT    THE RESULTS OF THE 3-SPACE TO 2-SPACE TRANSFOR-
C          MATION.
C          USE INT(XT) AND INT(YT) IN GPL CALLS.
C ZT       NOT USED.
C IF LL (IN COMMON) =0 XT AND YT ARE IN THE SAME SCALE AS X, Y, AND Z.
C
      COMMON /PWRZ1S/ XXMIN      ,XXMAX      ,YYMIN      ,YYMAX      ,
     1                ZZMIN      ,ZZMAX      ,DELCRT     ,EYEX       ,
     2                EYEY       ,EYEZ
      COMMON /SRFBLK/ LIMU(1024) ,LIML(1024) ,CL(41)     ,NCL        ,
     1                LL         ,FACT       ,IROT       ,NDRZ       ,
     2                NUPPER     ,NRSWT      ,BIGD       ,UMIN       ,
     3                UMAX       ,VMIN       ,VMAX       ,RZERO      ,
     4                IOFFP      ,NSPVAL     ,SPVAL      ,BIGEST
      DIMENSION       NLU(7)     ,NRU(7)     ,NBV(7)     ,NTV(7)
C
C SAVE INSERTED BY BEN DOMENICO 9/8/85 BECAUSE OF ASSUMPTION THAT
C   JUMP, JUMP2, AND JUMP3 ARE PRESERVED BETWEEN CALLS.
C   THERE MAY BE OTHER SUCH ASSUMPTIONS AS WELL.
C
      SAVE
C
C PICTURE CORNER COORDINATES FOR LL=1
C
      DATA NLU(1),NRU(1),NBV(1),NTV(1)/  10,1014,  10,1014/
C
C PICTURE CORNER COORDINATES FOR LL=2
C
      DATA NLU(2),NRU(2),NBV(2),NTV(2)/  10, 924,  50, 964/
C
C PICTURE CORNER COORDINATES FOR LL=3
C
      DATA NLU(3),NRU(3),NBV(3),NTV(3)/ 100,1014,  50, 964/
C
C PICTURE CORNER COORDINATES FOR LL=4
C
      DATA NLU(4),NRU(4),NBV(4),NTV(4)/  10,1014,  10,1014/
C
C PICTURE CORNER COORDINATES FOR LL=5
C
      DATA NLU(5),NRU(5),NBV(5),NTV(5)/  10,1014,  10,1014/
C
C PICTURE CORNER COORDINATES FOR LL=6
C
      DATA NLU(6),NRU(6),NBV(6),NTV(6)/  10, 512, 256, 758/
C
C PICTURE CORNER COORDINATES FOR LL=7
C
      DATA NLU(7),NRU(7),NBV(7),NTV(7)/ 512,1014, 256, 758/
C
C STORE THE PARAMETERS OF THE SET32 CALL FOR USE WHEN
C TRN32 IS CALLED.
C
      IF (IFLAG)  40, 10, 40
   10 CONTINUE
      JUMP3 = 1
      IF (IOFFP .EQ. 1) JUMP3 = 2
      AX = X
      AY = Y
      AZ = Z
      EX = XT
      EY = YT
      EZ = ZT
C
C AS MUCH COMPUTATION AS POSSIBLE IS DONE DURING EXECUTION
C THIS ROUTINE WHEN IFLAG=0 BECAUSE CALLS IN THAT MODE ARE INFREQUENT.
C
      DX = AX-EX
      DY = AY-EY
      DZ = AZ-EZ
      D = SQRT(DX*DX+DY*DY+DZ*DZ)
      COSAL = DX/D
      COSBE = DY/D
      COSGA = DZ/D
      SINGA = SQRT(1.-COSGA*COSGA)
      JUMP2 = 1
      IF (LL .EQ. 0) GO TO  20
      JUMP2 = 2
      DELCRT = NRU(LL)-NLU(LL)
      U0 = UMIN
      V0 = VMIN
      U1 = NLU(LL)
      V1 = NBV(LL)
      U2 = NRU(LL)-NLU(LL)
      V2 = NTV(LL)-NBV(LL)
      U3 = U2/(UMAX-UMIN)
      V3 = V2/(VMAX-VMIN)
      U4 = NRU(LL)
      V4 = NTV(LL)
      IF (NRSWT .EQ. 0) GO TO  20
      U0 = -BIGD
      V0 = -BIGD
      U3 = U2/(2.*BIGD)
      V3 = V2/(2.*BIGD)
C
C THE 3-SPACE POINT LOOKED AT IS TRANSFORMED INTO (0,0) OF
C THE 2-SPACE.  THE 3-SPACE Z AXIS IS TRANSFORMED INTO THE
C 2-SPACE Y AXIS.  IF THE LINE OF SIGHT IS CLOSE TO PARALLEL
C TO THE 3-SPACE Z AXIS, THE 3-SPACE Y AXIS IS CHOSEN (IN-
C STEAD OF THE 3-SPACE Z AXIS) TO BE TRANSFORMED INTO THE
C 2-SPACE Y AXIS.
C
   20 IF (SINGA .LT. 0.0001) GO TO  30
      R = 1./SINGA
      JUMP = 1
      RETURN
   30 SINBE = SQRT(1.-COSBE*COSBE)
      R = 1./SINBE
      JUMP = 2
      RETURN
   40 CONTINUE
      XX = X
      YY = Y
      ZZ = Z
      GO TO ( 60, 50) , JUMP3
   50 IF (ZZ .EQ. SPVAL) GO TO 110
   60 Q = D/((XX-EX)*COSAL+(YY-EY)*COSBE+(ZZ-EZ)*COSGA)
      GO TO (70,80), JUMP
   70 XX = ((EX+Q*(XX-EX)-AX)*COSBE-(EY+Q*(YY-EY)-AY)*COSAL)*R
      YY = (EZ+Q*(ZZ-EZ)-AZ)*R
      GO TO 90
   80 XX = ((EZ+Q*(ZZ-EZ)-AZ)*COSAL-(EX+Q*(XX-EX)-AX)*COSGA)*R
      YY = (EY+Q*(YY-EY)-AY)*R
   90 GO TO (120,100), JUMP2
  100 XX = MIN(U4,MAX(U1,U1+U3*(FACT*XX-U0)))
      YY = MIN(V4,MAX(V1,V1+V3*(FACT*YY-V0)))
      GO TO 120
  110 XX = NSPVAL
      YY = NSPVAL
C
  120 XT = XX
      YT = YY
      RETURN
      END
