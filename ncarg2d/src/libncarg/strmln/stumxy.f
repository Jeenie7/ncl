C
C       $Id: stumxy.f,v 1.5 1997-03-25 21:32:07 haley Exp $
C
C-----------------------------------------------------------------------
C
      SUBROUTINE STUMXY(XDA,YDA,XUS,YUS,IST)
C
C User modifiable routine for mapping data coordinate space to
C user space
C
C
C Input parameters:
C
C XDA,YDA - Point in data coordinate space
C
C Output parameters:
C
C XUS,YUS - Point in user coordinate space
C IST     - Status code indicating success or failure
C
C --------------------------------------------------------------------
C
C The mapping common block: made available to user mapping routines
C
      COMMON /STMAP/
     +                IMAP       ,LNLG       ,INVX       ,INVY       ,
     +                XLOV       ,XHIV       ,YLOV       ,YHIV       ,
     +                WXMN       ,WXMX       ,WYMN       ,WYMX       ,
     +                XVPL       ,XVPR       ,YVPB       ,YVPT       ,
     +                XGDS       ,YGDS       ,NXCT       ,NYCT       ,
     +                ITRT       ,FW2W       ,FH2H       ,
     +                DFMG       ,VNML       ,RBIG       ,IBIG
C
      SAVE /STMAP/
C
C Math constants
C
      PARAMETER (PDTOR  = 0.017453292519943,
     +           PRTOD  = 57.2957795130823,
     +           P1XPI  = 3.14159265358979,
     +           P2XPI  = 6.28318530717959,
     +           P1D2PI = 1.57079632679489,
     +           P5D2PI = 7.85398163397448) 
C
C -------------------------------------------------------------
C
C Identity transformation
C
      IST=0
      XUS=XDA
      YUS=YDA
C
C Done.
C
      RETURN
C
      END




