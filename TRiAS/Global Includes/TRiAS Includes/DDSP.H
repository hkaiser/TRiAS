/* Header-File fuer ddsp.y -- YACC-Stack-Definition u.a.        */
/* File: DDSP.H         last update: 17. Mai 1989               */

#ifndef _DDSP_H
#define _DDSP_H

#include <pshpack1.h>

typedef struct id_info {
        struct id_info *next_id;
        char id_name[NAMELEN];
} ID_INFO;
 
typedef struct strtok {
        int strline;
        char str[80];
} STRTOK;
 
typedef struct numtok {
        int numline;
        int num;
} NUMTOK;
 
//#define isalpha(c) ((c>='a'&&c<='z')||(c>='A'&&c<='Z'))
//#define isdigit(c) (c>='0'&&c<='9')
//#define isalnum(c) (isalpha(c)||isdigit(c))
 
#define INT_SIZE        sizeof(int)
#define SHORT_SIZE      sizeof(short)
#define LONG_SIZE       sizeof(long)
#define FLOAT_SIZE      sizeof(float)
#define DOUBLE_SIZE     sizeof(double)
#define CHAR_SIZE       sizeof(char)
#define DB_ADDR_SIZE    sizeof(DB_ADDR)

#include <poppack.h>

#endif // _DDSP_H
