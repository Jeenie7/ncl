C
C $Id: mapiq.f,v 1.6 1998-05-23 20:19:44 kennison Exp $
C
      SUBROUTINE MAPIQ
C
C Declare required common blocks.  See MAPBD for descriptions of these
C common blocks and the variables in them.
C
      COMMON /MAPCMP/ NPTB,XPTB(50),YPTB(50)
      SAVE /MAPCMP/
C
C Check for an uncleared prior error.
C
      IF (ICFELL('MAPIQ - UNCLEARED PRIOR ERROR',1).NE.0) RETURN
C
C Flush the points buffer.
C
      IF (NPTB.GT.0) THEN
        CALL POINTS (XPTB,YPTB,NPTB,0,0)
        IF (ICFELL('MAPIQ',2).NE.0) RETURN
        NPTB=0
      END IF
C
C Flush PLOTIT's buffer, too.
C
      CALL PLOTIF (0.,0.,2)
      IF (ICFELL('MAPIQ',3).NE.0) RETURN
C
C Done.
C
      RETURN
C
      END
