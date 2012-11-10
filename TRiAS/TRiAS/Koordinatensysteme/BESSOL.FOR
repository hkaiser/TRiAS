C+
C	*****************************************************************
C	* Bessel-GK-Koordinaten zu Soldner-Koordinaten                  *
C	*****************************************************************
C	(C)
C	Dokumentationsnummer: -
C	Autor:                Major, Walter
C	Datum:                29-MÑrz-2002
C	Modulname:            *** BESSOL ***
C       aus:                      GAUSOL
C	Routinenummer:        -
C	Programmiersprache:   Fortran-77
C	Verwendete Funktionen und Unterprogramme
C	libF77      :         DINT,DBLE
C	eigene      :         KOPF,GAUGEO,GEOESO
C	Common-Bloecke:       -
C	-----------------------------------------------------------------
C	Aufruf:               BESSOL
C
C	Parameter:
C
C	Aufgabenstellung, Hintergrund:
C	Das Programm dient zur Transformation von Bessel-GK-
C	Koordinaten (3 Grad Streifen) ins Soldnerkoordinaten-
C       system mit eigenstÑndiger Wahl des Mittelmeridians (12¯, 15¯).
C	Die Koordinaten des Nullpunktes des Soldnersystems werden
C	abgefragt, ebenso die Additionskonstanten der Soldnerkoordinaten
C	- entweder durch Auswahl oder durch Eingabe.
C
C	Das Programm wird Åber Dialog gefÅhrt.
C       Koordinaten-
C	INPUT:  Name des Files mit den zu transformierenden Daten; das
C		Format der Daten ist dabei weitgehend frei; Trennzeichen
C		kînnen Leerzeichen oder Kommatas sein:
C               (INTEGER REAL REAL:  Punktnummer, Rechtswert, Hochwert,
C		bzw. Tastatureingabe
C
C	OUTPUT: Ergebnisfile 'name',
C		bzw. Terminalanzeige
C
C	ELLIPSOIDPARAMETER
C                   Bessel:   A=  6 377 397.155    m
C                             B=  6 356 078.96282  m
C
C	Fehlerbehandlung:
C	     bei gefundenen Fehlern erfolgt Ausschrift und Sprung
C	     zur Wiederholung bzw. zum Ende
C	-----------------------------------------------------------------
C-
      PROGRAM BESSOL
C
      INTEGER*4 L02,ISTR,INP,OUTP,IB0G,IB0M,IL0G,IL0M
      INTEGER*4 IRC1,GEOESO,IRC2,GAUGEO,EOKAY,SOLSYS,NRSYS
      INTEGER*4 ISOLDR,ISOLDH
      REAL*8    HAB,HBB,RM,RBB,RLB,HO,RE,HT,RT
      REAL*8    B0,B0G,B0M,B0S,L0,L0G,L0M,L0S,SOLDR,SOLDH
      CHARACTER*14 IP
      CHARACTER*20 NAME1,NAME2
C
      PARAMETER (EOKAY=0)
C
C******** Titelbild schreiben ***************************************
      CALL KOPF
C
C******** Ellipsoidparameter setzen *********************************
C   Bessel:
      HAB=6377397.155D0
      HBB=6356078.96282D0
C
C******** Anfangswerte setzen ***************************************
      RM=1.0D0
      RBB=0.0D0
      RLB=0.0D0
      ISTR=3
C
C******** Name der Eingabedatei *************************************
  12  WRITE (6,1001)
      READ (5,1010) NAME1
      IF (NAME1 .EQ. ' ') THEN
C				Handeingabe
          INP=5
      ELSE
C				Eingabe von Datei
          INP=18
          OPEN (18,FILE=NAME1,STATUS='OLD',ERR=10)
          GOTO 11
  10      WRITE (6,1002) NAME1
          GOTO 12
  11      REWIND 18
      END IF
C******* Name der Ausgabedatei **************************************
 112  WRITE (6,1006)
      READ (5,1010) NAME2
      IF (NAME2 .EQ. ' ') THEN
C				Bildschirmausgabe
          OUTP=6
      ELSE
C				Ausgabe auf Datei
          OUTP=19
          OPEN (19,FILE=NAME2,STATUS='NEW',ERR=110)
          GOTO 111
 110      WRITE (6,1007) NAME2
          GOTO 112
 111      REWIND 19
      END IF
C
C*******Abfrage des Nullpunktes des Soldnersystems*******************
117     WRITE (6,3001)
        READ (5,*,ERR=117,END=500) SOLSYS
	IF (SOLSYS .EQ. 15) THEN
C Kaltenborn
C Offsets: Rechtswert: +55078.56, Hochwert: -8247.97
C Quelle: http://www.lverma-bb.de/produkte/dienst_link/Dienst_li4.htm
		IB0G=51
		IB0M=55
		B0S=44.5335D0
		IL0G=14
		IL0M=39
		L0S=43.6659D0	
	ELSE IF (SOLSYS .EQ. 16) THEN
C Bahn I
		IB0G=53
		IB0M=06
		B0S=06.6450D0
		IL0G=14
		IL0M=42
		L0S=05.2034D0
	ELSE IF (SOLSYS .EQ. 17) THEN	  
C Greifswald
		IB0G=54
		IB0M=05
		B0S=49.1594D0
		IL0G=13
		IL0M=22
		L0S=43.7053D0
	ELSE IF (SOLSYS .EQ. 18) THEN
C M¸ggelberge (Berliner Systeme)
		IB0G=52
		IB0M=25
		B0S=07.1338D0
		IL0G=13
		IL0M=37
		L0S=37.9332D0
	ELSE IF (SOLSYS .EQ. 19) THEN
C Gˆtzer Berg
		IB0G=52
		IB0M=26
		B0S=14.1346D0
		IL0G=12
		IL0M=43
		L0S=43.7870D0
	ELSE IF (SOLSYS .EQ. 20) THEN
C Torgau
		IB0G=51
		IB0M=33
		B0S=40.9038D0
		IL0G=13
		IL0M=00
		L0S=27.3695D0
	ELSE
118       WRITE (6,2009)
          READ (5,*,ERR=118,END=500) IB0G,IB0M,B0S,IL0G,IL0M,L0S
	END IF
	B0G=DBLE(IB0G)
	B0M=DBLE(IB0M)
	L0G=DBLE(IL0G)
	L0M=DBLE(IL0M)
	B0=B0G*3600.0D0+B0M*60.0D0+B0S
	L0=L0G*3600.0D0+L0M*60.0D0+L0S
C
C*******Abfrage des Soldner-Offsets im Hoch-und Rechtswert***********
4000    WRITE (6,3010)
        READ (5,*,ERR=4000,END=500) NRSYS
C
C*******Ausgabedateikopf schreiben***********************************
        WRITE (OUTP,3002)
        WRITE (OUTP,3003) SOLSYS,IB0G,IB0M,B0S,IL0G,IL0M,L0S
        WRITE (OUTP,3004)
        IF (NRSYS .EQ. 1) THEN
          WRITE (OUTP,3020)
3020      FORMAT ('    System 18/1         50000 m        50000 m',/)
          SOLDR=50000.0D0
          SOLDH=50000.0D0
        ELSE IF (NRSYS .EQ. 2) THEN
          WRITE (OUTP,3021)
3021      FORMAT ('    System 18/2         50000 m        50000 m',/)
          SOLDR=50000.0D0
          SOLDH=50000.0D0
        ELSE IF (NRSYS .EQ. 3) THEN
          WRITE (OUTP,3022)
3022      FORMAT ('    System 18/3         70000 m        20000 m',/)
          SOLDR=70000.0D0
          SOLDH=20000.0D0
        ELSE IF (NRSYS .EQ. 88) THEN
          WRITE (OUTP,3023)
3023      FORMAT ('    System Netz 88      40000 m        10000 m',/)
          SOLDR=40000.0D0
          SOLDH=10000.0D0
        ELSE
119       WRITE (6,2014)
	  READ (5,*,ERR=119,END=500) ISOLDR,ISOLDH
          WRITE (OUTP,3015) ISOLDR,ISOLDH
          SOLDR=DBLE(ISOLDR)
          SOLDH=DBLE(ISOLDH)
        END IF
        WRITE (OUTP,3005)
C
C*******Eingabe des Mittelmeridians des G.-K.-Systems****************
c121	WRITE (6,2015)
c	READ (5,*,ERR=121,END=500) L02
C
C******* Eingabe der Werte ******************************************
  13    IF (INP .EQ. 5) WRITE (6,1003)
C
C******* Schleifeneinsprung *****************************************
  15    READ (INP,*,ERR=16,END=500) IP,RE,HO
        GOTO 17
  16    WRITE (6,2016)
        GOTO 500
  17    CONTINUE
C******* Ermittelung des Mittelmeridians ****************************
        IF ((RE.GE.4000000.0D0).AND.(RE.LT.5000000.0D0)) THEN
          L02=12
        ELSE IF ((RE.GE.5000000.0D0).AND.(RE.LT.5000000.0D0)) THEN
          L02=15
        ELSE
          WRITE (6,*) ' Koordinaten nicht im 12¯- oder 15¯-Streifen !'
          GOTO 500
        END IF
C
C******** Transformationsschritt ************************************
      IRC1=GAUGEO (HAB,HBB,ISTR,L02,RM,HO,RE,RBB,RLB)
      IF (IRC1 .NE. EOKAY) GOTO 500
C  Ermittelung des Mittelmeridians 3 Grad:
C        IF (RLB .LT. 48600.0D0) THEN
C           L02=12
C        ELSE
C           L02=15
C        END IF
      IRC2=GEOESO (HAB,HBB,B0,L0,RBB,RLB,HT,RT)
      IF (IRC2 .NE. EOKAY) GOTO 500
C ***** Soldner-Translationen aus Eingabe:
      HT=HT+SOLDH
      RT=RT+SOLDR
C
C******** Ausgabe auf OUTPUT-File ***********************************
      WRITE (OUTP,2005) IP,RE,HO,RT,HT
      IF (OUTP .EQ. 6) THEN
        GOTO 13
      ELSE
        GOTO 15
      END IF
C********* Schlu· **************************************************
 500  IF (INP .EQ. 18) CLOSE (18)
      IF (OUTP .EQ. 19) CLOSE (19)
      IF (IRC1 .NE. EOKAY) THEN 
         WRITE (6,2010)
      ELSE IF (IRC2 .NE. EOKAY) THEN
         WRITE (6,2011)
      ELSE
         WRITE (6,2012)
      END IF
C
C******** Formatangaben *********************************************
C      
 1001 FORMAT (' Name der Datei  mit den  zu trans-  ',/,
     .        '           formierenden Koordinaten ?',/,
     .        '     ENTER = Handeingabe               ') 
 1002 FORMAT (' Datei ',A20,'nicht gefunden !!!')
 1003 FORMAT (' Punktnr.   Rechtswert    Hochwert ',/)
 1006 FORMAT (' Name der Ausgabedatei ?             ',/,
     .        '     ENTER = Bildschirmausgabe         ')
 1007 FORMAT (' Datei ',A20,'bereits vorhanden !!!')
 1010 FORMAT (A20)
 1011 FORMAT (A80)
C
 2005 FORMAT (4X,A14,1X,2F12.3,X,2F12.3)
 2009 FORMAT (/,/,' Nullpunkt Soldner B0, L0 (Grad, Min. Sek.) ',
     *'eingeben: ',/)
 2010 FORMAT (/,/,' Fehler in GAUGEO ',/)
 2011 FORMAT (/,/,' Fehler in GEOESO ',/)
 2012 FORMAT (/,/,' Ende der Bearbeitung ',/)
 2014 FORMAT ( ' Soldner-Offset im Rechts- und Hochwert eingeben: ')
c 2015 FORMAT ( ' Mittelmeridian des Ausgangssystems Gau·-KrÅger: ')
 2016 FORMAT ( ' Fehler beim Koordinatenlesen !!!')
C
 3001 FORMAT ( '      Soldnersysteme: ',/,
     *'      15  Kaltenborn',/,
     *'      16  Bahn I',/,
     *'      17  Greifswald',/,
     *'      18  MÅggelsberg-Berliner Systeme-',/,
     *'      19  Gîtzer Berg',/,
     *'      20  Torgau',/,
     *'       0  anderes System',/,
     *'   ',/,
     *' Nummer des Soldnersystems eingeben:  ')
C
 3002 FORMAT (' ',
     . '   *************************************************',/,
     . '    *  K O O R D I N A T E N V E R Z E I C H N I S  *',/,
     . '    *************************************************')
 3003 FORMAT ('    Soldnernullpunkt: Nummer des Systems: ',I3,/,
     . '    Breite in Grad, Min., Sek.    LÑnge in Grad, Min., Sek.',/,
     .      14X,I3,2X,I3,2X,F8.4,11X,I3,2X,I3,2X,F8.4,/)
 3004 FORMAT ('    Soldner-Offset:',/,
     .        '                       Rechtswert     Hochwert')
 3005 FORMAT (' ',
     .'                           GK Bessel                 Soldner',/,
     .'    Punkt-Nr.          Rechts       Hoch        Rechts       ',
     .     'Hoch',/,
     .'    --------------------------------------------------------',
     .     '--------')
 3010 FORMAT ('    Auswahl der Soldner-Additionskonstanten:    ',/,
     .'    Eingabe    System                    Offset         ',/,
     .'                               Rechtswert      Hochwert ',/,
     .'       1       System 18/1      50000 m         50000 m ',/,
     .'       2       System 18/2      50000 m         50000 m ',/,
     .'       3       System 18/3      70000 m         20000 m ',/,
     .'      88       System Netz 88   40000 m         10000 m ',/,
     .'       0       anderes System',/,
     .'   ',/,
     .' Auswahlzahl eingeben:  ')
 3015 FORMAT ('    anderes System    ',I7,' m',6X,I7,' m',/)
C
      STOP
      END


      SUBROUTINE KOPF
C*********************************************************************
C     Zweck:  Erzeugung eines Titelbildes bei Programmstart
C     Autor:  Korth,  geÑndert: Major
C*********************************************************************
      INTEGER*4 I,K
      CHARACTER*80 Z1,Z2,Z3
      DO 1 I=1,80
    1 Z1(I:I)=' '
      DO 2 I=11,70
    2 Z1(I:I)=CHAR(219)
      WRITE (6,1001)
      DO 3 I=1,5
    3 WRITE (6,1000) Z1
      Z2=Z1
      Z3='                                             '
      DO 4 I=18,63
      K=I-17
    4 Z2(I:I)=Z3(K:K)
      WRITE (6,1000) Z2
      Z2(64:64)=CHAR(177)
      Z3='      Gau·-KrÅger Koordinaten (Bessel)       '
      DO 6 I=18,63
      K=I-17
    6 Z2(I:I)=Z3(K:K)
      WRITE (6,1000) Z2
C
      Z3='                   zu                        '
      DO 61 I=18,63
      K=I-17
   61 Z2(I:I)=Z3(K:K)
      WRITE (6,1000) Z2
C
      Z3='          Soldner-Koordinaten                '
      DO 62 I=18,63
      K=I-17
   62 Z2(I:I)=Z3(K:K)
      WRITE (6,1000) Z2
C
      Z3='   ________________________________________   '
      DO 7 I=18,63
      K=I-17
    7 Z2(I:I)=Z3(K:K)
      WRITE (6,1000) Z2
      Z3=' (C) LGB, Dez. 12                MÑrz 2002    '
      DO 8 I=18,63
      K=I-17
    8 Z2(I:I)=Z3(K:K)
      WRITE (6,1000) Z2
      Z3='                                              '
      DO 9 I=18,63
      K=I-17
    9 Z2(I:I)=Z3(K:K)
      WRITE (6,1000) Z2
      Z2=Z1
      DO 10 I=19,64
   10 Z2(I:I)=CHAR(177)
      WRITE (6,1000) Z2
      DO 11 I=1,5
   11 WRITE (6,1000) Z1
 1001 FORMAT (/,/,/,/,/,/,/)
 1000 FORMAT (A80)
      RETURN
      END
