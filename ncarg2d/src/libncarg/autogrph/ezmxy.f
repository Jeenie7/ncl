C
C $Id: ezmxy.f,v 1.4 1996-04-18 17:46:23 kennison Exp $
C
      SUBROUTINE EZMXY (XDRA,YDRA,IDXY,MANY,NPTS,LABG)
C
      REAL XDRA(*),YDRA(*)
C
      CHARACTER*(*) LABG
C
C The routine EZMXY draws many curves, each of them defined by points of
C the form (XDRA(I,J),YDRA(I,J)) or (XDRA(J,I),YDRA(J,I)) or, possibly,
C (XDRA(I),YDRA(I,J)) or (XDRA(I),YDRA(J,I)), for I = 1, 2, ... NPTS and
C for J = 1, 2, ... MANY.  (YDRA is actually dimensioned IDXY by * .)
C
      CALL AGGETI ('SET .',ISET)
      CALL AGGETI ('FRAM.',IFRA)
      CALL AGGETI ('DASH/SELE.',IDSH)
C
      CALL AGEZSU (4,XDRA,YDRA,IDXY,MANY,NPTS,LABG,IIVX,IIEX,IIVY,IIEY)
      CALL AGBACK
C
      IF (ISET.LT.0) GO TO 102
C
           DO 101 I=1,MANY
           INXD=1+(I-1)*IIVX
           INYD=1+(I-1)*IIVY
           KDSH=ISIGN(I,IDSH)
           CALL AGCURV (XDRA(INXD),IIEX,YDRA(INYD),IIEY,NPTS,KDSH)
  101      CONTINUE
C
  102 IF (IFRA.EQ.1) CALL FRAME
C
      RETURN
C
      END
