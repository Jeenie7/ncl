C
C	$Id: stex03.f,v 1.7 1993-04-09 23:46:13 dbrown Exp $
C
      PROGRAM STEX03
C
C Example STEX03 draws a uniform southwesterly field on ten
C different EZMAP projections. A streamline representation overlays
C a rendering using vectors. Polar input mode is employed: all members
C of the U array, representing magnitude, are set to 1.0, while the
C V array contains the directional component, -135.0 degrees.
C
C All projections use the maximum possible extent of the globe, except
C except for frame 3, a Lambert Conical projection, for which a full
C globe projection is impossible.
C  
      PARAMETER (M=25, N=25)
      DIMENSION A(M,N),B(M,N),WRK(M*N*2)
C
C     Open GKS, open workstation, activate workstation.
C
      CALL GOPKS (6,ISZ)
      CALL GOPWK (1, 2, 1)
      CALL GACWK (1)
C
C     Generate the polar input mode component arrays.
C
      DO 2 I=1,M
         DO 1 J=1,N
            A(I,J) = 1.0
            B(I,J) = -135.0
 1       CONTINUE
 2    CONTINUE
C
C Set up a GKS color table
C
      CALL DFCLRS
C
C Do 10 different EZMAP projections, with Vectors and Streamlines
C superimposed
C
      DO 1000 I=1,10,1 
C
C Draw the map projections
C
         IF (I .EQ. 3) THEN
            CALL SUPMAP (3,0.,80.,70.,90.,80.,0.,0.,2,20,4,0,IERS)
         ELSE
            CALL SUPMAP (I,0.,0.,0.,0.,0.,0.,0.,1,20,2,0,IERS)
         END IF
C
C Set the Vectors coordinate parameters appropriately for a full
C globe polar input mode dataset projected using EZMAP
C
         CALL VVSETI('MAP -- Mapping Flag', 1)
         CALL VVSETI('SET -- Set Call Flag', 0)
         CALL VVSETR('XC1 -- Lower X Bound', -180.0)
         CALL VVSETR('XCM -- Upper X Bound', 180.0)
         CALL VVSETR('YC1 -- Lower Y Bound', -90.0)
         CALL VVSETR('YCN -- Upper Y Bound', 90.0)
         CALL VVSETI('PLR -- Vector Polar Flag', 1)
C
C Set the Streamlines coordinate parameters appropriately for a full
C globe polar input mode dataset projected using EZMAP
C
         CALL STSETI('MAP -- Mapping Flag', 1)
         CALL STSETI('SET -- Set Call Flag', 0)
         CALL STSETR('XC1 -- Lower X Bound', -180.0)
         CALL STSETR('XCM -- Upper X Bound', 180.0)
         CALL STSETR('YC1 -- Lower Y Bound', -90.0)
         CALL STSETR('YCN -- Upper Y Bound', 90.0)
         CALL STSETI('PLR -- Vector Polar Flag', 1)
C
C Draw the Vectors in one color
C
         CALL GSPLCI(3)
         CALL VVINIT(A,M,B,M,IDM,IDM,M,N,IDM,IDM,IDM,IDM)
         CALL VVECTR(A,B,IDM,IDM,IDM,IDM,IDM)
C
C Draw the Streamlines in another color
C
         CALL GSPLCI(7)
         CALL STINIT(A,M,B,M,IDM,IDM,M,N,WRK,2*M*N)
         CALL STREAM(A,B,IDM,IDM,IDM,WRK)
C
C Reset the color to the default color index and advance the frame.
C
         CALL GSPLCI(1)
         CALL FRAME
C
 1000 CONTINUE
C
C     Deactivate and close workstation, close GKS.
C
      CALL GDAWK (1)
      CALL GCLWK (1)
      CALL GCLKS
C
      STOP
      END
C
C ==============================================================
C
      SUBROUTINE DFCLRS
C
C Define a set of RGB color triples for colors 0 through 15.
C
      PARAMETER (NCLRS=16)
      DIMENSION RGBV(3,NCLRS)
C
C Define the RGB color triples needed below.
C
      DATA RGBV / 
     +     0.00 , 0.00 , 0.00 ,
     +     1.00 , 1.00 , 1.00 ,
     +     0.70 , 0.70 , 0.70 ,
     +     0.75 , 0.50 , 1.00 ,
     +     0.50 , 0.00 , 1.00 ,
     +     0.00 , 0.00 , 1.00 ,
     +     0.00 , 0.50 , 1.00 ,
     +     0.00 , 1.00 , 1.00 ,
     +     0.00 , 1.00 , 0.60 ,
     +     0.00 , 1.00 , 0.00 ,
     +     0.70 , 1.00 , 0.00 ,
     +     1.00 , 1.00 , 0.00 ,
     +     1.00 , 0.75 , 0.00 ,
     +     1.00 , 0.38 , 0.38 ,
     +     1.00 , 0.00 , 0.38 ,
     +     1.00 , 0.00 , 0.00 /
C
C Define 16 different color indices, for indices 0 through 15.  The
C color corresponding to index 0 is black and the color corresponding
C to index 1 is white.
C
      DO 101 I=1,NCLRS
         CALL GSCR (1,I-1,RGBV(1,I),RGBV(2,I),RGBV(3,I))
 101  CONTINUE
C
C Done.
C
        RETURN
C
      END
C
