      PROGRAM FAGAXMAX
C
C  Define error file, Fortran unit number, and workstation type,
C  and workstation ID.
C
      PARAMETER (IERRF=6, LUNIT=2, IWTYPE=SED_WSTYPE, IWKID=1)
      PARAMETER (NPTS=200)
      PARAMETER (NCURVE=4)
      REAL YDRA(NPTS,NCURVE),XDRA(NPTS)

      DO 10 I=1,NPTS
          XDRA(I  )=I*0.1
          DO 10 J=1,NCURVE
              YDRA(I,J)=SIN(XDRA(I)+0.2*J)*EXP(-0.01*XDRA(I)*J**2)
  10  CONTINUE
C
C  Open GKS, open and activate a workstation.
C
      CALL GOPKS (IERRF, ISZDM)
      CALL GOPWK (IWKID, LUNIT, IWTYPE)
      CALL GACWK (IWKID)

      CALL AGSETF('Y/MINIMUM.',-1.4)
      CALL AGSETF('Y/MAXIMUM.', 1.4)
      CALL AGSETF('Y/NICE.',    0.0)

      CALL AGSETF('X/MINIMUM.', 0.0)
      CALL AGSETF('X/MAXIMUM.',25.0)
      CALL AGSETF('X/NICE.',    0.0)

      CALL EZMXY (XDRA,YDRA,NPTS,NCURVE,NPTS,'AXIS MIN/MAX$')
C
C  Deactivate and close the workstation, close GKS.
C
      CALL GDAWK (IWKID)
      CALL GCLWK (IWKID)
      CALL GCLKS

      STOP
      END
