C
C	$Id: tsrfac.f,v 1.2 1993-03-05 00:12:40 haley Exp $
C
C
C OPEN GKS, OPEN WORKSTATION OF TYPE 1, ACTIVATE WORKSTATION
C
      CALL GOPKS (6,IDUM) 
      CALL GOPWK (1, 2, 1)
      CALL GACWK (1) 
C
C INVOKE DEMO DRIVER
C
      CALL TSRFAC(IERR)
C
C     DEACTIVATE AND CLOSE WORKSTATION, CLOSE GKS.
C
      CALL GDAWK (1)
      CALL GCLWK (1)
      CALL GCLKS
C
      STOP
      END
C
      SUBROUTINE TSRFAC (IERROR)
C
C PURPOSE                To provide a simple demonstration of SRFACE.
C
C USAGE                  CALL TSRFAC (IERROR)
C
C ARGUMENTS
C
C ON OUTPUT              IERROR
C                          An integer variable
C                          = 0, if the test was successful,
C                          = 1, the test was not successful.
C
C I/O                    If the test is successful, the message
C
C               SRFACE TEST EXECUTED--SEE PLOT TO CERTIFY
C
C                        is printed on unit 6.  In addition, 2
C                        frames are produced on the machine graphics
C                        device.  In order to determine if the test
C                        was successful, it is necessary to examine
C                        the plots.
C
C PRECISION              Single
C
C LANGUAGE               FORTRAN 77
C
C REQUIRED ROUTINES      SRFACE
C
C REQUIRED GKS LEVEL     0A
C
C ALGORITHM              The function
C
C                          Z(X,Y) = .25*(X + Y + 1./((X-.1)**2+Y**2+.09)
C                                   -1./((X+.1)**2+Y**2+.09)
C
C                        for X = -1. to +1. in increments of .1, and
C                            Y = -1.2 to +1.2 in increments of .1,
C                        is computed.  Then, entries EZSRFC and SURFACE
C                        are called to generate surface plots of Z.
C
C HISTORY                SURFACE was first written in April 1979 and
C                        converted to FORTRAN 77 and GKS in March 1984.
C
C XX contains the X-direction coordinate values for Z(X,Y);  YY contains
C the Y-direction coordinate values for Z(X,Y);  Z contains the function
C values;  S contains values for the line of sight for entry SRFACE;
C WORK is a work array;  ANGH contains the angle in degrees in the X-Y
C plane to the line of sight;  and ANGV contains the angle in degrees
C from the X-Y plane to the line of sight.
C
      REAL            XX(21)     ,YY(25)     ,Z(21,25)   ,S(6)       ,
     1                WORK(1096)
C
      DATA  S(1), S(2), S(3), S(4), S(5), S(6)/
     1      -8.0, -6.0,  3.0,  0.0,  0.0,  0.0/
C
      DATA  ANGH/45./, ANGV/15./
C
C Specify coordinates for plot titles.  The values CX and CY
C define the center of the title string in a 0. to 1. range.
C
      DATA CX/.5/, CY/.9/
C
C Initialize the error parameter.
C
      IERROR = 0
C
C Fill the XX and YY coordinate arrays as well as the Z function array.
C
      DO  20 I=1,21
         X = .1*FLOAT(I-11)
         XX(I) = X
         DO  10 J=1,25
            Y = .1*FLOAT(J-13)
            YY(J) = Y
            Z(I,J) = (X+Y+1./((X-.1)**2+Y**2+.09)-
     1                                      1./((X+.1)**2+Y**2+.09))*.25
   10    CONTINUE
   20 CONTINUE
C
C Select the normalization transformation 0.
C
      CALL GSELNT(0)
C
C
C     Frame 1 -- The EZSRFC entry.
C
C Add the plot title using GKS calls.
C
C Set the text alignment to center the string in horizontal and vertical
C
      CALL GSTXAL(2,3)
C
C Set the character height.
C
      CALL GSCHH(.016)
C
C Write the text.
C
      CALL GTX(CX,CY,'DEMONSTRATION PLOT FOR EZSRFC ENTRY OF SRFACE')
C
      CALL EZSRFC (Z,21,25,ANGH,ANGV,WORK)
C
C
C     Frame 2 -- The SRFACE entry.
C
C Add the plot title.
C
C Set the text alignment to center the string in horizontal and vertical
C
      CALL GSTXAL(2,3)
C
C Set the character height.
C
      CALL GSCHH(.016)
C
C Write the text.
C
      CALL GTX(CX,CY,'DEMONSTRATION PLOT FOR SRFACE ENTRY OF SRFACE')
C
      CALL SRFACE (XX,YY,Z,WORK,21,21,25,S,0.)
C
C This routine automatically generates frame advances.
C
      WRITE (6,1001)
C
      RETURN
C
 1001 FORMAT (' SRFACE TEST EXECUTED--SEE PLOT TO CERTIFY')
C
      END
