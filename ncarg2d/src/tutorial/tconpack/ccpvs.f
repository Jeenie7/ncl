
      PROGRAM CCPVS
C
C Define the error file, the Fortran unit number, the workstation type,
C and the workstation ID to be used in calls to GKS routines.
C
C     PARAMETER (IERRF=6, LUNIT=2, IWTYPE=1,  IWKID=1)   ! NCGM
C     PARAMETER (IERRF=6, LUNIT=2, IWTYPE=8,  IWKID=1)   ! X Windows
C     PARAMETER (IERRF=6, LUNIT=2, IWTYPE=11, IWKID=1)   ! PDF
C     PARAMETER (IERRF=6, LUNIT=2, IWTYPE=20, IWKID=1)   ! PostScript
C
      PARAMETER (IERRF=6, LUNIT=2, IWTYPE=1,  IWKID=1)
C
C Declare required data arrays and workspace arrays.
C
      PARAMETER(LMAP=100000,LWRK=1000)
      REAL ZDAT(23,14),RWRK(LWRK),XCRA(LWRK),YCRA(LWRK)
      INTEGER IWRK(LWRK),IAMA(LMAP), IAREA(2),IGRP(2)
C
C Declare the routine which will color the areas.
C
      EXTERNAL FILL
C
C Open GKS.
C
      CALL GOPKS (IERRF, ISZDM)
      CALL GOPWK (IWKID, LUNIT, IWTYPE)
      CALL GACWK (IWKID)
C
C Turn off the clipping indicator.
C
      CALL GSCLIP (0)
C
C Force solid fill.
C
      CALL GSFAIS (1)
C
C Define color indices.
C
      CALL COLOR(IWKID)
C
C Generate an array of test data.
C
      CALL GENDAT (ZDAT,23,23,14,20,20,-136.148,451.834)
C
C Tell CONPACK to use 12 contour lines, splitting the range into 13
C equal bands, one for each of the 13 colors available.
C
      CALL CPSETI ('CLS - CONTOUR LEVEL SELECTOR',-12)
C
C Tell Conpack that we want 3 vertical strips
C
      CALL CPSETI ('NVS - NUMBER OF VERTICAL STRIPS',3)
C
C Initialize the drawing of the contour plot.
C
      CALL CPRECT (ZDAT,23,23,14,RWRK,LWRK,IWRK,LWRK)
C
C Initialize the area map and put the contour lines into it.
C
      CALL ARINAM (IAMA,LMAP)
      CALL CPCLAM (ZDAT,RWRK,IWRK,IAMA)
C
C Color the map.
C
      CALL ARSCAM (IAMA,XCRA,YCRA,LWRK,IAREA,IGRP,2,FILL)
C
C Put black contour lines over the colored map.
C
      CALL GSPLCI (0)
      CALL CPCLDR (ZDAT,RWRK,IWRK)
      CALL GSPLCI (1)
C
C Advance the frame.
C
      CALL FRAME
C
C Close GKS.
C
      CALL GDAWK (IWKID)
      CALL GCLWK (IWKID)
      CALL GCLKS
C
C Done.
C
      STOP
C
      END
      SUBROUTINE FILL (XCRA,YCRA,NCRA,IAREA,IGRP,NGRPS)
C
      REAL XCRA(NCRA),YCRA(NCRA)
      INTEGER IAREA(NGRPS),IGRP(NGRPS)
C
C Get area identifiers for contour levels and vertical strips.
C
      IFILL=0
      DO 101 I=1,NGRPS
         IF (IGRP(I).EQ.3) IFILL=IAREA(I)
 101  CONTINUE
C
C Find the average X value of the X coordinates defining the area
C
      XSUM=0.
      DO 102 I=1,NCRA
         XSUM=XSUM+XCRA(I)
 102  CONTINUE
      XAVG=XSUM/REAL(NCRA)
C
C Fill vertical strip 1.
C
      IF (IFILL.GT.0.AND.XAVG.LT..35) THEN
         CALL GSFACI (IFILL+2)
         CALL GFA (NCRA-1,XCRA,YCRA)
C
C Fill vertical strip 2
C
      ELSE IF (IFILL.GT.0.AND.XAVG.GE..35.AND.XAVG.LE..65) THEN
         CALL GSFACI (IFILL+15)
         CALL GFA (NCRA-1,XCRA,YCRA)
C
C Fill vertical strip 3
C
      ELSE IF (IFILL.GT.0.AND.XAVG.GT..65) THEN
         CALL GSFACI (IFILL+28)
         CALL GFA (NCRA-1,XCRA,YCRA)
      END IF
C
C Done.
C
      RETURN
C
      END

      SUBROUTINE GENDAT (DATA,IDIM,M,N,MLOW,MHGH,DLOW,DHGH)
C
C This is a routine to generate test data for two-dimensional graphics
C routines.  Given an array "DATA", dimensioned "IDIM x 1", it fills
C the sub-array ((DATA(I,J),I=1,M),J=1,N) with a two-dimensional field
C of data having approximately "MLOW" lows and "MHGH" highs, a minimum
C value of exactly "DLOW" and a maximum value of exactly "DHGH".
C
C "MLOW" and "MHGH" are each forced to be greater than or equal to 1
C and less than or equal to 25.
C
C The function used is a sum of exponentials.
C
      DIMENSION DATA(IDIM,1),CCNT(3,50)
C
      FOVM=9./REAL(M)
      FOVN=9./REAL(N)
C
      NLOW=MAX(1,MIN(25,MLOW))
      NHGH=MAX(1,MIN(25,MHGH))
      NCNT=NLOW+NHGH
C
      DO 101 K=1,NCNT
         CCNT(1,K)=1.+(REAL(M)-1.)*FRAN()
         CCNT(2,K)=1.+(REAL(N)-1.)*FRAN()
         IF (K.LE.NLOW) THEN
            CCNT(3,K)=-1.
         ELSE
            CCNT(3,K)=+1.
         END IF
 101  CONTINUE
C
      DMIN=+1.E36
      DMAX=-1.E36
      DO 104 J=1,N
         DO 103 I=1,M
            DATA(I,J)=.5*(DLOW+DHGH)
            DO 102 K=1,NCNT
               TEMP=-((FOVM*(REAL(I)-CCNT(1,K)))**2+
     +              (FOVN*(REAL(J)-CCNT(2,K)))**2)
               IF (TEMP.GE.-20.) DATA(I,J)=DATA(I,J)+
     +              .5*(DHGH-DLOW)*CCNT(3,K)*EXP(TEMP)
 102        CONTINUE
            DMIN=MIN(DMIN,DATA(I,J))
            DMAX=MAX(DMAX,DATA(I,J))
 103     CONTINUE
 104  CONTINUE
C
      DO 106 J=1,N
         DO 105 I=1,M
            DATA(I,J)=(DATA(I,J)-DMIN)/(DMAX-DMIN)*(DHGH-DLOW)+DLOW
 105     CONTINUE
 106  CONTINUE
C
      RETURN
C
      END

      FUNCTION FRAN ()
      DIMENSION RSEQ (100)
      SAVE ISEQ
      DATA RSEQ / .749,.973,.666,.804,.081,.483,.919,.903,.951,.960 ,
     +     .039,.269,.270,.756,.222,.478,.621,.063,.550,.798 ,
     +     .027,.569,.149,.697,.451,.738,.508,.041,.266,.249 ,
     +     .019,.191,.266,.625,.492,.940,.508,.406,.972,.311 ,
     +     .757,.378,.299,.536,.619,.844,.342,.295,.447,.499 ,
     +     .688,.193,.225,.520,.954,.749,.997,.693,.217,.273 ,
     +     .961,.948,.902,.104,.495,.257,.524,.100,.492,.347 ,
     +     .981,.019,.225,.806,.678,.710,.235,.600,.994,.758 ,
     +     .682,.373,.009,.469,.203,.730,.588,.603,.213,.495 ,
     +     .884,.032,.185,.127,.010,.180,.689,.354,.372,.429 /
      DATA ISEQ / 0 /
      ISEQ=MOD(ISEQ,100)+1
      FRAN=RSEQ(ISEQ)
      RETURN
      END
      SUBROUTINE COLOR(IWKID)
C
C Background color
C Black
C
      CALL GSCR(IWKID,0,0.,0.,0.)
C
C Foreground colors
C White
C
      CALL GSCR(IWKID, 1, 1.0, 1.0, 1.0)
C
C Aqua
C
      CALL GSCR(IWKID, 2, 0.0, 0.9, 1.0)
C
C Red1
C
      CALL GSCR(IWKID, 3, 0.9, 0.25, 0.0)
C
C OrangeRed1
C
      CALL GSCR(IWKID, 4, 1.0, 0.0, 0.2)
C
C Orange1
C
      CALL GSCR(IWKID, 5, 1.0, 0.65, 0.0)
C
C Yellow1
C
      CALL GSCR(IWKID, 6, 1.0, 1.0, 0.0)
C
C GreenYellow1
C
      CALL GSCR(IWKID, 7, 0.7, 1.0, 0.2)
C
C Chartreuse1
C
      CALL GSCR(IWKID, 8, 0.5, 1.0, 0.0)
C
C Celeste1
C
      CALL GSCR(IWKID, 9, 0.2, 1.0, 0.5)
C
C Green1
C
      CALL GSCR(IWKID, 10, 0.2, 0.8, 0.2)
C
C DeepSkyBlue1
C
      CALL GSCR(IWKID, 11, 0.0, 0.75, 1.0)
C
C RoyalBlue1
C
      CALL GSCR(IWKID, 12, 0.25, 0.45, 0.95)
C
C SlateBlue1
C
      CALL GSCR(IWKID, 13, 0.4, 0.35, 0.8)
C
C DarkViolet1
C
      CALL GSCR(IWKID, 14, 0.6, 0.0, 0.8)
C
C Orchid1
C
      CALL GSCR(IWKID, 15, 0.85, 0.45, 0.8)
C
C Red2
C
      CALL GSCR(IWKID, 16, 0.77, 0.21, 0.0)
C
C OrangeRed2
C
      CALL GSCR(IWKID, 17, 0.85, 0.0, 0.17)
C
C Orange2
C
      CALL GSCR(IWKID, 18, 0.85, 0.55, 0.0)
C
C Yellow2
C
      CALL GSCR(IWKID, 19, 0.85, 0.85, 0.0)
C
C GreenYellow2
C
      CALL GSCR(IWKID, 20, 0.6, 0.85, 0.17)
C
C Chartreuse2
C
      CALL GSCR(IWKID, 21, 0.43, 0.85, 0.0)
C
C Celeste2
C
      CALL GSCR(IWKID, 22, 0.17, 0.85, 0.43)
C
C Green2
C
      CALL GSCR(IWKID, 23, 0.17, 0.68, 0.17)
C
C DeepSkyBlue2
C
      CALL GSCR(IWKID, 24, 0.0, 0.64, 0.85)
C
C RoyalBlue2
C
      CALL GSCR(IWKID, 25, 0.21, 0.38, 0.81)
C
C SlateBlue2
C
      CALL GSCR(IWKID, 26, 0.32, 0.3, 0.68)
C
C DarkViolet2
C
      CALL GSCR(IWKID, 27, 0.51, 0.0, 0.68)
C
C Orchid2
C
      CALL GSCR(IWKID, 28, 0.72, 0.38, 0.68)
C
C Red3
C
      CALL GSCR(IWKID, 29, 0.63, 0.18, 0.0)
C
C OrangeRed3
C
      CALL GSCR(IWKID, 30, 0.7, 0.0, 0.14)
C
C Orange3
C
      CALL GSCR(IWKID, 31, 0.6, 0.39, 0.0)
C
C Yellow3
C
      CALL GSCR(IWKID, 32, 0.7, 0.7, 0.0)
C
C GreenYellow3
C
      CALL GSCR(IWKID, 33, 0.49, 0.7, 0.14)
C
C Chartreuse3
C
      CALL GSCR(IWKID, 34, 0.35, 0.7, 0.0)
C
C Celeste3
C
      CALL GSCR(IWKID, 35, 0.14, 0.7, 0.35)
C
C Green3
C
      CALL GSCR(IWKID, 36, 0.14, 0.56, 0.14)
C
C DeepSkyBlue3
C
      CALL GSCR(IWKID, 37, 0.0, 0.53, 0.7)
C
C RoyalBlue3
C
      CALL GSCR(IWKID, 38, 0.18, 0.32, 0.67)
C
C SlateBlue3
C
      CALL GSCR(IWKID, 39, 0.28, 0.25, 0.56)
C
C DarkViolet3
C
      CALL GSCR(IWKID, 40, 0.42, 0.0, 0.56)
C
C Orchid3
C
      CALL GSCR(IWKID, 41, 0.6, 0.32, 0.56)
C
C Lavender
C
      CALL GSCR(IWKID, 42, 0.8, 0.8, 1.0)
C
C Gray
C
      CALL GSCR(IWKID, 43, 0.7, 0.7, 0.7)
C
C Done.
C
      RETURN
C
      END
