C
C $Id: mapvec.f,v 1.6 1998-05-23 20:20:04 kennison Exp $
C
      SUBROUTINE MAPVEC (XLAT,XLON)
      IF (ICFELL('MAPVEC - UNCLEARED PRIOR ERROR',1).NE.0) RETURN
      CALL MAPIT (XLAT,XLON,1)
      IF (ICFELL('MAPVEC',2).NE.0) RETURN
      RETURN
      END
