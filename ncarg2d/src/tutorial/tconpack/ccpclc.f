	PROGRAM CCPCLC

        PARAMETER (K=40,N=40,LRWK=1000,LIWK=1000)
	REAL Z(K,N), RWRK(LRWK)
	INTEGER I, M, IWRK(LIWK)

	CALL GETDAT (Z, K, M, N) 

C Open GKS
	CALL OPNGKS

C Set up color table
	CALL COLOR

C Call conpack normally
	CALL CPRECT(Z,K,M,N,RWRK,LRWK,IWRK,LIWK)
CC  
	CALL CPPKCL(Z, RWRK, IWRK)
C Set line color to red if it's negative, green if it's zero, 
C and blue if it's positive.
	CALL CPGETI('NCL - NUMBER OF CONTOUR LEVELS',NCON)
	DO 11, I=1,NCON
	   CALL CPSETI('PAI - PARAMETER ARRAY INDEX',I)
	   CALL CPGETR('CLV - CONTOUR LEVEL VALUES',CVAL)
	   IF (CVAL .LT. 0.0) THEN
	      CALL CPSETI('CLC - CONTOUR LINE COLOR INDEX',1)
	   ELSE IF (CVAL .EQ. 0.0) THEN
	      CALL CPSETI('CLC - CONTOUR LINE COLOR INDEX',2)
	   ELSE
	      CALL CPSETI('CLC - CONTOUR LINE COLOR INDEX',3)
	   ENDIF
 11	CONTINUE

	CALL CPBACK(Z, RWRK, IWRK)
	CALL CPCLDR(Z,RWRK,IWRK)

C Close frame and close GKS
	CALL FRAME
	CALL CLSGKS

	STOP
	END

	SUBROUTINE GETDAT (Z, K, M, N)

	REAL Z(K,N)
	INTEGER I,J,K,M,N

	M=K
	DO 10, I=1,M
	  DO 20, J=1,N
	    Z(I,J)= 10.E-5*(-16.*REAL(I**2*J) +
     +		    34*REAL(I*J**2) - REAL(6*I) + 93.)
  20	  CONTINUE
  10	CONTINUE

	RETURN
	END

	SUBROUTINE COLOR

	CALL GSCR (1,0,1.,1.,1.)
	CALL GSCR (1,1,1.,0.,0.)
	CALL GSCR (1,2,0.,1.,0.)
	CALL GSCR (1,3,0.,0.,1.)

	RETURN
	END
