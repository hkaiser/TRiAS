/* Festlegen der Routinennummern                                */
/* File: ROUTINES.H                                             */

#ifndef _ROUTINES_H
#define _ROUTINES_H

#define KA_ROUT      8000    /* erste Nummer-1 fuer ka */

#define         ACTIVATE        KA_ROUT+1
#define         COMBIN          KA_ROUT+2
#define         FIND_PAGE       KA_ROUT+3
#define         DIO_IN          KA_ROUT+4
#define         DIO_OUT         KA_ROUT+5
#define         BACK_UP         KA_ROUT+6
#define         Z_CLOSE         KA_ROUT+7
#define         Z_OPEN          KA_ROUT+8
#define         DIO_PZINIT      KA_ROUT+9
#define         FILE_CLOSE      KA_ROUT+10
#define         FILE_OPEN       KA_ROUT+11
#define         HTDMP           KA_ROUT+12
#define         HTPREP          KA_ROUT+13
#define         HTSEARCH        KA_ROUT+14
#define         HTSPLIT         KA_ROUT+15
#define         HTWINDOW        KA_ROUT+16
#define         USER_FUNC       KA_ROUT+17
#define         INITTAB         KA_ROUT+18
#define         DIO_GET         KA_ROUT+19
#define         DIO_TOUCH       KA_ROUT+20
#define         KEY_INIT        KA_ROUT+21
#define         KEY_NEXT        KA_ROUT+22
#define         KEY_PREV        KA_ROUT+23
#define         KEY_READ_ROUT   KA_ROUT+24
#define         INSERT_KEY      KA_ROUT+25
#define         DELETE_KEY      KA_ROUT+26
#define         PUTLIST         KA_ROUT+27
#define         GETLIST         KA_ROUT+28
#define         EXPAND          KA_ROUT+29
#define         PARENT          KA_ROUT+30
#define         PZFLUSH         KA_ROUT+31
#define         PZALLOC         KA_ROUT+32
#define         PZFREE          KA_ROUT+33
#define         QTDMP           KA_ROUT+34
#define         QTPREP          KA_ROUT+35
#define         QTSEARCH        KA_ROUT+36
#define         QTSPLIT         KA_ROUT+37
#define         QTWINDOW        KA_ROUT+38
#define         SHRINK          KA_ROUT+39
#define         TZAPSLT         KA_ROUT+40
#define         ZAPSLT          KA_ROUT+41
#define         ZACT_F          KA_ROUT+42
#define         ZACTIV          KA_ROUT+43
#define         ZCLOSE_F        KA_ROUT+44
#define         ZDESTR_F        KA_ROUT+45
#define         ZDESTROY        KA_ROUT+46
#define         ZDISP_F         KA_ROUT+47
#define         ZDISPOSE        KA_ROUT+48
#define         FILLNEW         KA_ROUT+49
#define         ZNEW_F          KA_ROUT+50
#define         ZFIND_F         KA_ROUT+51
#define         ZFIND           KA_ROUT+52
#define         Z1ST_F          KA_ROUT+53
#define         Z1ST            KA_ROUT+54
#define         ZINIT_F         KA_ROUT+55
#define         ZINIT           KA_ROUT+56
#define         ZLAST           KA_ROUT+57
#define         ZLAST_F         KA_ROUT+58
#define         ZNEXT           KA_ROUT+59
#define         ZNEXT_F         KA_ROUT+60
#define         ZPREV           KA_ROUT+61
#define         ZPREV_F         KA_ROUT+62
#define         ZKREAD          KA_ROUT+63
#define         ZKREAD_F        KA_ROUT+64
#define         ZREAD           KA_ROUT+65
#define         ZREAD_F         KA_ROUT+66
#define         ZOPEN_F         KA_ROUT+67
#define         ZSETP           KA_ROUT+68
#define         ZSETF           KA_ROUT+69
#define         ZWRITE          KA_ROUT+70
#define         ZWRITE_F        KA_ROUT+71
#define         DIO_INIT        KA_ROUT+72
#define         ERRINST         KA_ROUT+73
#define         DELETE_BT       KA_ROUT+74
#define         HTDEL           KA_ROUT+75
#define         KEYLOC          KA_ROUT+76
#define         LOCATE          KA_ROUT+77
#define         LOCFRST         KA_ROUT+78
#define         LOCLAST         KA_ROUT+79
#define         QTDEL           KA_ROUT+80
#define         HTINS           KA_ROUT+81
#define         INSERT_BT       KA_ROUT+82
#define         QTINS           KA_ROUT+83
#define         SETERROR        KA_ROUT+84
#define         DB_READ         KA_ROUT+85
#define         DB_WRITE        KA_ROUT+86
#define         GEN_BACKUP      KA_ROUT+87
#define         ZTOUCH          KA_ROUT+88
#define         ZRESTORE        KA_ROUT+89
#define         HTCONT          KA_ROUT+90
#define         QTCONT          KA_ROUT+91
#define		ZACCESS		KA_ROUT+92
#define		RC_GETDWENT	KA_ROUT+93
#define		RC_ENDDWENT	KA_ROUT+94
#define		RC_InstallHandler	KA_ROUT+95
#define		ERR_FUNC	KA_ROUT+96
#define 	PZREREAD	KA_ROUT+97

#define         GETHD_F         KA_ROUT+100

#define		CREATEKEYFILE	KA_ROUT+101
#define		CREATEDATAFILE	KA_ROUT+102
#define		CREATEGEOTREEFILE	KA_ROUT+103
#define		CREATETREEKEYFILE	KA_ROUT+104
#define		CREATEBACKUPFILE	KA_ROUT+105

#define 	CHKCHN		KA_ROUT+200


/* Routinencodes in FLEX.C */
#define         FLEX_INI        KA_ROUT+900
#define         FLEX_GET        KA_ROUT+901
#define         FLEX_PUT        KA_ROUT+902
#define         FLEX_LEN        KA_ROUT+903
#define         FLEX_READ       KA_ROUT+904
#define         FLEX_QSRT       KA_ROUT+905
#define         FLEX_REDN       KA_ROUT+906
#define         FLEX_WRITE      KA_ROUT+907
#define         FLEX_RELEASE    KA_ROUT+908
#define 	FLEX_ADR	KA_ROUT+909
#define		FLEX_SHRINK	KA_ROUT+910
#define		FLEX_RESERVE	KA_ROUT+911

#define RC_BRelSet		KA_ROUT+300
#define RC_PutRel		KA_ROUT+301
#define RC_RelSet		KA_ROUT+302
#define RC_DelRel		KA_ROUT+303

#define RC_OvlPunkt		KA_ROUT+310
#define RC_OvlLinie		KA_ROUT+311
#define RC_OvlFlaeche		KA_ROUT+312

// PBD-Zugriffsroutinen
#define 	RC_MDELKI	KA_ROUT+400
#define 	RC_MDELKM	KA_ROUT+401
#define		RC_MDELKR	KA_ROUT+402
#define		RC_MPUTKT	KA_ROUT+403
#define		RC_MPUTWM	KA_ROUT+404
#define 	RC_MGETKM	KA_ROUT+405
#define 	RC_MGETKR	KA_ROUT+406
#define 	RC_MFIND	KA_ROUT+407
#define 	RC_MGETKT	KA_ROUT+408
#define 	RC_MGETKTI	KA_ROUT+409
#define 	RC_MGETKTM	KA_ROUT+410
#define 	RC_MGETKTR	KA_ROUT+411
#define 	RC_MGETL	KA_ROUT+412
#define 	RC_MGETTX	KA_ROUT+413
#define 	RC_MPUTTXT	KA_ROUT+414
#define 	RC_MGETWM	KA_ROUT+415

#endif // _ROUTINES_H
