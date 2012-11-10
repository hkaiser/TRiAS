/*
   EXEC.C: EXEC function with memory swap - Prepare parameters.

   Public domain software by

        Thomas Wagner
        Ferrari electronic GmbH
        Beusselstrasse 27
        D-1000 Berlin 21
        Germany
*/

#include "compat.h"
#include "exec.h"
#include <ctype.h>

#define SWAP_FILENAME "$$AAAAAA.AAA" 

/*e internal flags for prep_swap */
/*d interne Flags fÅr prep_swap */

#define CREAT_TEMP      0x0080
#define DONT_SWAP_ENV   0x4000

/*e local variables */
/*d Lokale Variablen */

static char drive [MAXDRIVE], dir [MAXDIR];
static char name [MAXFILE], ext [MAXEXT];


#ifdef __cplusplus
extern "C" int
#else
extern int _cdecl
#endif
do_spawn (int swapping,     /*e swap if non-0 */
                            /*d Auslagern wenn nicht 0 */
          char *xeqfn,      /*e file to execute */
                            /*d auszufÅhrende Datei */
          char *cmdtail,    /*e command tail string */
                            /*d Kommandozeile */
          unsigned envlen,  /*e environment length */
                            /*d LÑnge Umgebungsvariablen */
          char *envp);      /*e environment pointer */
                            /*d Zeiger auf Umgebungsvariablen */

#ifdef __cplusplus
extern "C" int
#else
extern int _cdecl
#endif
prep_swap (int method,      /*e swap method */
                            /*d Auslagerungsmethode */
           char *swapfn);   /*e swap file name and/or path */
                            /*d Auslagerungsdateiname und/oder Pfad */


/*e Returns TRUE if a file with name 'fn' exists. */
/*d Liefert TRUE wenn eine Datei mit dem Namen 'fn' existiert. */

int exists (char *fn)
{
   struct ffblk fb;

   return !findfirst (fn, &fb, FA_RDONLY | FA_HIDDEN | FA_SYSTEM | FA_ARCH);
}


/*e Try '.COM' and '.EXE' on current filename, modify filename if found. */
/*>d '.COM' und '.EXE' mit dem aktuellen Dateinamen versuchen,
   Dateinamen modifizieren wenn gefunden. <*/

int tryext (char *fn)
{
   int i;

   i = strlen (fn);
   strcat (fn, ".COM");
   if (exists (fn))
      return 1;
   fn [i] = 0;
   strcat (fn, ".EXE");
   if (exists (fn))
      return 1;
   fn [i] = 0;
   return 0;
}


/*>e Try to find the file 'fn' in the current path. Modifies the filename
   accordingly. <*/
/*>d Versuchen die Datei 'fn' im aktuellen Pfad zu finden. Der Dateiname
   wird entsprechend modifiziert. <*/

int findfile (char *fn)
{
   char *path, *penv;
   char *prfx;
   int found;

   if (!fn [0])
      strcpy (fn, getenv ("COMSPEC"));

   fnsplit (fn, drive, dir, name, ext);

   if (ext [0])
      found = exists (fn);
   else
      found = tryext (fn);

   if (!found && !dir [0] && !drive [0])
      {
      penv = getenv ("PATH");
      if (!penv)
         return 0;
      path = (char *)malloc (strlen (penv) + 1);
      if (path == NULL)
         return 0;

      strcpy (path, penv);
      prfx = strtok (path, ";");

      while (!found && prfx != NULL)
         {
         fnmerge (fn, drive, prfx, name, ext);
         if (ext [0])
            found = exists (fn);
         else
            found = tryext (fn);

         prfx = strtok (NULL, ";");
         }
      free (path);
      }
   return found;
}


/*>e
   tempdir: Set temporary file path.
            Read "TMP/TEMP" environment. If empty or invalid, clear path.
            If TEMP is drive or drive+backslash only, return TEMP.
            Otherwise check if given path is a valid directory.
            If so, add a backslash, else clear path.
<*/
/*>d
   tempdir: Pfad fÅr temporÑre Datei setzen.
            Die Umgebungsvariable "TMP" oder "TEMP" wird gelesen. Ist
            keine der beiden vorhanden, oder sind sie ungÅltig, wird
            der Pfad gelîscht.
            Besteht TMP/TEMP nur aus Laufwerksbuchstaben, oder aus
            Laufwerk und Backslash, liefern TEMP.
            Sonst prÅfen ob der Pfad gÅltig ist, und einen Backslash
            anfÅgen.
<*/

void tempdir (char *outfn)
{
   int l;
   char *s;
   struct stat ff;
   union REGS regs;
   struct SREGS segregs;

   *outfn = 0;
   if ((s = getenv ("TMP")) == NULL)
      if ((s = getenv ("TEMP")) == NULL)
         return;

   strcpy (outfn, s);
   l = strlen (outfn);
   if (!l)
      return;

   if (outfn [l - 1] == '\\' || outfn [l - 1] == '/')
      outfn [--l] = 0;

   fnsplit (outfn, drive, dir, name, ext);

   if (drive [0])
      {
      regs.h.dl = (unsigned char)(toupper (drive [0]) - 'A' + 1);
      regs.h.ah = 0x1c;
      intdosx (&regs, &regs, &segregs);
      if (regs.h.al == 0xff)
         {
         *outfn = 0;
         return;
         }
      }

   if (!name [0])   /* No dir name */
      {
      if (dir [0])
         *outfn = 0;
      else
         {
         outfn [l++] = '\\';
         outfn [l] = 0;
         }
      return;
      }

   if (stat (outfn, &ff))
      *outfn = 0;
   else if (!(ff.st_mode & S_IFDIR) || !(ff.st_mode & S_IWRITE))
      *outfn = 0;
   else
      {
      outfn [l++] = '\\';
      outfn [l] = 0;
      }
}


int do_exec (char *exfn, char *epars, int spwn, unsigned needed, char **envp)
{
   static char swapfn [82];
   static char execfn [82];
   unsigned avail;
   union REGS regs;
   unsigned envlen;
   int rc;
   int idx;
   char **env;
   char *ep, *envptr, *envbuf;
   int swapping;

   strcpy (execfn, exfn);

   /*e First, check if the file to execute exists. */
   /*d ZunÑchst prÅfen ob die auszufÅhrende Datei existiert. */

   if (!findfile (execfn))
      return RC_NOFILE;

   /*e Now create a copy of the environment if the user wants it. */
   /*d Nun eine Kopie der Umgebungsvariablen anlegen wenn angefordert. */

   envlen = 0;
   envptr = NULL;

   if (envp != NULL)
      for (env = envp; *env != NULL; env++)
         envlen += strlen (*env) + 1;

   if (envlen)
      {
      /*e round up to paragraph, and alloc another paragraph leeway */
      /*d Auf Paragraphengrenze runden, plus einen Paragraphen zur Sicherheit */
      envlen = (envlen + 32) & 0xfff0;
      envbuf = (char *)malloc (envlen);
      if (envbuf == NULL)
         return RC_ENVERR;

      /*e align to paragraph */
      /*d Auf Paragraphengrenze adjustieren */
      envptr = envbuf;
      if (FP_OFF (envptr) & 0x0f)
         envptr += 16 - (FP_OFF (envptr) & 0x0f);
      ep = envptr;

      for (env = envp; *env != NULL; env++)
         {
         ep = stpcpy (ep, *env) + 1;
         }
      *ep = 0;
      }

   if (!spwn)
      swapping = -1;
   else
      {
      /*e Determine amount of free memory */
      /*d Freien Speicherbereich feststellen */

      regs.x.ax = 0x4800;
      regs.x.bx = 0xffff;
      intdos (&regs, &regs);
      avail = regs.x.bx;

      /*e No swapping if available memory > needed */
      /*d Keine Auslagerung wenn freier Speicher > benîtigter */

      if (needed < avail)
         swapping = 0;
      else
         {
         /*>e Swapping necessary, use 'TMP' or 'TEMP' environment variable
           to determine swap file path if defined. <*/
         /*>d Auslagerung notwendig, 'TMP' oder 'TEMP' Umgebungsvariable
            verwenden um Auslagerungsdateipfad festzulegen. */

         swapping = spwn;
         if (spwn & USE_FILE)
            {
            tempdir (swapfn);

            if (OS_MAJOR >= 3)
               swapping |= CREAT_TEMP;
            else
               {
               strcat (swapfn, SWAP_FILENAME);
               idx = strlen (swapfn) - 1;
               while (exists (swapfn))
                  {
                  if (swapfn [idx] == 'Z')
                     idx--;
                  if (swapfn [idx] == '.')
                     idx--;
                  swapfn [idx]++;
                  }
               }
            }
         }
      }

   /*e All set up, ready to go. */
   /*d Alles vorbereitet, jetzt kann's losgehen. */

   if (swapping > 0)
      {
      if (!envlen)
         swapping |= DONT_SWAP_ENV;

      rc = prep_swap (swapping, swapfn);
      if (rc < 0)
         return RC_PREPERR | -rc;
      }

   rc = do_spawn (swapping, execfn, epars, envlen, envptr);

   /*e Free the environment buffer if it was allocated. */
   /*d Den Umgebungsvariablenblock freigeben falls er alloziert wurde. */

   if (envlen)
      free (envbuf);

   return rc;
}

