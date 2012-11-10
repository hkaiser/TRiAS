// Funktionen, die Datum und Zeit in Länder-spezifischer weise aufbereiten
// File: DATETIME.C

#include "trias02p.hxx"

#include <time.h>

#define YEAR  (datetime->tm_year % 100)
#define MONTH (datetime->tm_mon  + 1)
#define MDAY  (datetime->tm_mday)
#define WDAY  (datetime->tm_wday)
#define HOUR  (datetime->tm_hour)
#define MIN   (datetime->tm_min)
#define SEC   (datetime->tm_sec)

static char sDate[2], sTime[2], sAMPM[2][5];
static int iDate, iTime;

static void DateIntl (void) 
{
static char cName[] = "intl";

	iDate = GetProfileInt (cName, "iDate", 0);
	iTime = GetProfileInt (cName, "iTime", 0);

	GetProfileString (cName, "sDate", "/", sDate, 2);
	GetProfileString (cName, "sTime", ":", sTime, 2);
	GetProfileString (cName, "s1159", "AM", sAMPM[0], 5);
	GetProfileString (cName, "s2359", "PM", sAMPM[1], 5);
}

extern "C" _TRIAS02_ENTRY char * EXPORT02 FUNCTYPE FormatDate (char *cBuffer, int maxLen) 
{
static char szWday[] = 	"Sonntag   \0" 
			"Montag    \0" 
			"Dienstag  \0" 
			"Mittwoch  \0" 
			"Donnerstag\0" 
			"Freitag   \0" 
			"Sonnabend \0";
time_t lTime;
short nLength;
struct tm *datetime;
char locBuffer[100];

	DateIntl ();
	time(&lTime);
	datetime = localtime(&lTime);

	nLength = wsprintf(locBuffer, "%s %d%s%02d%s%02d ", 
			szWday + sizeof(szWday)/7 * WDAY,
			iDate == 1 ? MDAY : iDate == 2 ? YEAR : MONTH, sDate,
			iDate == 1 ? MONTH : iDate == 2 ? MONTH : MDAY, sDate,
			iDate == 1 ? YEAR : iDate == 2 ? MDAY : YEAR);

	if (iTime == 1)
		nLength += wsprintf(locBuffer + nLength, " %02d%s%02d%s%02d ",
				   HOUR, sTime, MIN, sTime, SEC);
	else
		nLength += wsprintf(locBuffer + nLength, " %d%s%02d%s%02d %s ",
				   (HOUR % 12) ? (HOUR % 12) : 12,
				   sTime, MIN, sTime, SEC, sAMPM[HOUR / 12]);

	strncpy (cBuffer, locBuffer, maxLen);

return cBuffer;
}

