C
C $Id: mapgtr.f,v 1.9 1998-05-23 20:19:40 kennison Exp $
C
      SUBROUTINE MAPGTR (WHCH,RVAL)
C
      CHARACTER*(*) WHCH
C
C Declare required common blocks.  See MAPBD for descriptions of these
C common blocks and the variables in them.
C
      COMMON /MAPCM4/ INTF,JPRJ,PHIA,PHIO,ROTA,ILTS,PLA1,PLA2,PLA3,PLA4,
     +                PLB1,PLB2,PLB3,PLB4,PLTR,GRID,IDSH,IDOT,LBLF,PRMF,
     +                ELPF,XLOW,XROW,YBOW,YTOW,IDTL,GRDR,SRCH,ILCW,GRLA,
     +                GRLO,GRPO
      LOGICAL         INTF,LBLF,PRMF,ELPF
      SAVE /MAPCM4/
C
      COMMON /MAPCMA/ DPLT,DDTS,DSCA,DPSQ,DSSQ,DBTD,DATL
      SAVE /MAPCMA/
C
      COMMON /MAPSAT/ SALT,SSMO,SRSS,ALFA,BETA,RSNA,RCSA,RSNB,RCSB
      SAVE /MAPSAT/
C
      COMMON /MAPDPS/ DSNA,DCSA,DSNB,DCSB
      DOUBLE PRECISION DSNA,DCSA,DSNB,DCSB
      SAVE /MAPDPS/
C
      IF (ICFELL('MAPGTR - UNCLEARED PRIOR ERROR',1).NE.0) RETURN
C
      IF      (WHCH(1:2).EQ.'DD'.OR.WHCH(1:2).EQ.'dd') THEN
        RVAL=DDTS
      ELSE IF (WHCH(1:2).EQ.'GD'.OR.WHCH(1:2).EQ.'gd') THEN
        RVAL=GRDR
      ELSE IF (WHCH(1:2).EQ.'GN'.OR.WHCH(1:2).EQ.'gn') THEN
        RVAL=GRLO
      ELSE IF (WHCH(1:2).EQ.'GP'.OR.WHCH(1:2).EQ.'gp') THEN
        RVAL=GRPO
      ELSE IF (WHCH(1:2).EQ.'GR'.OR.WHCH(1:2).EQ.'gr') THEN
        RVAL=GRID
      ELSE IF (WHCH(1:2).EQ.'GT'.OR.WHCH(1:2).EQ.'gt') THEN
        RVAL=GRLA
      ELSE IF (WHCH(1:2).EQ.'MV'.OR.WHCH(1:2).EQ.'mv') THEN
        RVAL=DPLT
      ELSE IF (WHCH(1:2).EQ.'PN'.OR.WHCH(1:2).EQ.'pn') THEN
        RVAL=PHIO
      ELSE IF (WHCH(1:2).EQ.'PT'.OR.WHCH(1:2).EQ.'pt') THEN
        RVAL=PHIA
      ELSE IF (WHCH(1:2).EQ.'P1'.OR.WHCH(1:2).EQ.'p1') THEN
        RVAL=PLA1
      ELSE IF (WHCH(1:2).EQ.'P2'.OR.WHCH(1:2).EQ.'p2') THEN
        RVAL=PLA2
      ELSE IF (WHCH(1:2).EQ.'P3'.OR.WHCH(1:2).EQ.'p3') THEN
        RVAL=PLA3
      ELSE IF (WHCH(1:2).EQ.'P4'.OR.WHCH(1:2).EQ.'p4') THEN
        RVAL=PLA4
      ELSE IF (WHCH(1:2).EQ.'P5'.OR.WHCH(1:2).EQ.'p5') THEN
        RVAL=PLB1
      ELSE IF (WHCH(1:2).EQ.'P6'.OR.WHCH(1:2).EQ.'p6') THEN
        RVAL=PLB2
      ELSE IF (WHCH(1:2).EQ.'P7'.OR.WHCH(1:2).EQ.'p7') THEN
        RVAL=PLB3
      ELSE IF (WHCH(1:2).EQ.'P8'.OR.WHCH(1:2).EQ.'p8') THEN
        RVAL=PLB4
      ELSE IF (WHCH(1:2).EQ.'RE'.OR.WHCH(1:2).EQ.'re') THEN
        RVAL=PLTR
      ELSE IF (WHCH(1:2).EQ.'RO'.OR.WHCH(1:2).EQ.'ro') THEN
        RVAL=ROTA
      ELSE IF (WHCH(1:2).EQ.'SA'.OR.WHCH(1:2).EQ.'sa') THEN
        RVAL=SALT
      ELSE IF (WHCH(1:2).EQ.'S1'.OR.WHCH(1:2).EQ.'s1') THEN
        RVAL=ALFA
      ELSE IF (WHCH(1:2).EQ.'S2'.OR.WHCH(1:2).EQ.'s2') THEN
        RVAL=BETA
      ELSE IF (WHCH(1:2).EQ.'SR'.OR.WHCH(1:2).EQ.'sr') THEN
        RVAL=SRCH
      ELSE IF (WHCH(1:2).EQ.'XL'.OR.WHCH(1:2).EQ.'xl') THEN
        RVAL=XLOW
      ELSE IF (WHCH(1:2).EQ.'XR'.OR.WHCH(1:2).EQ.'xr') THEN
        RVAL=XROW
      ELSE IF (WHCH(1:2).EQ.'YB'.OR.WHCH(1:2).EQ.'yb') THEN
        RVAL=YBOW
      ELSE IF (WHCH(1:2).EQ.'YT'.OR.WHCH(1:2).EQ.'yt') THEN
        RVAL=YTOW
      ELSE
        GO TO 901
      END IF
C
C Done.
C
      RETURN
C
C Error exits.
C
  901 CALL MAPCEM ('MAPGTR - UNKNOWN PARAMETER NAME ',WHCH,2,1)
      RVAL=0.
      RETURN
C
      END
