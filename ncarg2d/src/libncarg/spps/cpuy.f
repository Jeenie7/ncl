C
C $Id: cpuy.f,v 1.2 1993-12-12 20:55:08 kennison Exp $
C
      FUNCTION CPUY (IY)
C
C Given a Y coordinate IY in the plotter system, CPUY(IY) is a Y
C coordinate in the user system.
C
      COMMON /IUTLCM/ LL,MI,MX,MY,IU(96)
      SAVE /IUTLCM/
      DIMENSION WD(4),VP(4)
      CALL GQCNTN (IE,NT)
      IF (IE.NE.0) THEN
        CALL SETER ('CPUY - ERROR EXIT FROM GQCNTN',1,1)
        CPUY=0.
        RETURN
      END IF
      CALL GQNT (NT,IE,WD,VP)
      IF (IE.NE.0) THEN
        CALL SETER ('CPUY - ERROR EXIT FROM GQNT',2,1)
        CPUY=0.
        RETURN
      END IF
      I=3
      IF (MI.EQ.2.OR.MI.GE.4) I=4
      CPUY=WD(I)+(FLOAT(IY-1)/(2.**MY-1.)-VP(3))/(VP(4)-VP(3))*
     +     (WD(7-I)-WD(I))
      IF (LL.EQ.2.OR.LL.GE.4) CPUY=10.**CPUY
      RETURN
      END
