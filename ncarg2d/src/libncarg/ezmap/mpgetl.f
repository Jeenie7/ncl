C
C $Id: mpgetl.f,v 1.7 1998-05-23 20:20:07 kennison Exp $
C
      SUBROUTINE MPGETL (WHCH,LVAL)
      CHARACTER*(*) WHCH
      LOGICAL LVAL
      IF (ICFELL('MPGETL - UNCLEARED PRIOR ERROR',1).NE.0) RETURN
      CALL MAPGTL (WHCH,LVAL)
      IF (ICFELL('MPGETL',2).NE.0) RETURN
      RETURN
      END
