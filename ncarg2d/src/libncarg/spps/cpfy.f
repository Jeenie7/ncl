C
C $Id: cpfy.f,v 1.2 1993-12-12 20:55:03 kennison Exp $
C
      FUNCTION CPFY (IY)
C
C Given a Y coordinate IY in the plotter system, CPFY(IY) is a Y
C coordinate in the fractional system.
C
      COMMON /IUTLCM/ LL,MI,MX,MY,IU(96)
      SAVE /IUTLCM/
      CPFY=FLOAT(IY-1)/(2.**MY-1.)
      RETURN
      END
