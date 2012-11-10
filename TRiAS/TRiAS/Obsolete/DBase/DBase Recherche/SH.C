/*
SH.C -- Command Shell for Windows

Microsoft C, Windows SDK:
cl -c -AS -Gsw -Oais -Zpe sh.c winio.c wmhandlr.c
link sh winio wmhandlr,sh,nul,/nod slibcew libw,winio.def
rc winio.rc sh.exe

Borland C++:
bcc -WS -G -O -Z -w-par -Hu sh.c winio.c wmhandlr.c
rc winio.rc sh.exe
*/

#include "windows.h"
#include <stdlib.h>
#include <string.h>
#ifdef __BORLANDC__
#define __MSC
#include <dir.h>
#else
#include <direct.h>
#endif
#include <dos.h>
#include "winio.h"

int do_command(char *s);
char *pwd(void);

static char buf[2048] = {0};
static char orig[2048] = {0};
static char title[80] = "Command Shell";
static unsigned instance = 0;

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, 
    LPSTR lpCmdLine, int nCmdShow)
{
    if (hPrevInstance)
        GetInstanceData(hPrevInstance, &instance, sizeof(instance));
    if (++instance > 1)
        sprintf(title, "Command Shell #%d", instance);
    winio_settitle(title);
    
    if (! winio_init(hInstance, hPrevInstance, nCmdShow, 0))
        return 1;
    
    winio_setfont(ANSI_FIXED_FONT);
    
    for (;;)
    {
        printf("%s>", pwd());
        gets(buf);
        if ((buf[0] == '\0') || (buf[0] == '\n')) 
            continue;
        strcpy(orig, buf);  // unmodified buffer
        strupr(buf);
        if (strcmp(buf, "EXIT") == 0) 
            break;
        if (! do_command(buf))
            puts("Bad command or file name");
    }
    
    winio_close();
    return 0;
}

char *pwd(void)
{
    static char buf[256];
    char *s;
    return (s = getcwd(buf, 255)) ? s : "invalid";
}

// NOTE: running multiple instances, Windows takes care of maintaining
// multiple pwd within each instance
int do_chdrive(char *s)
{
#ifdef __BORLANDC__ 
    return (s[1] == ':') ? setdisk(s[0] - 'A') : 0;
#else
    return (s[1] == ':') ? (_chdrive(1 + s[0] - 'A') == 0) : 0;
#endif
}

int do_cd(char *s)
{
    if (s[1] == ':')
    {
        // allow drives in here too
        if (! do_chdrive(s)) return 0;
        s += 2;
    }
    return (chdir(s) == 0);
}

void show_filename(struct find_t *pinfo)
{
    if (pinfo->attrib & _A_SUBDIR)
        printf("%-13s\t<DIR>\n", pinfo->name);
    else
        printf("%-13s\t%9lu\n", pinfo->name, pinfo->size);
}

int do_dir(char *s)
{
    struct find_t info;
    char wildcard[80];
    unsigned long bytes;
    unsigned attrib, files;
    strcpy(wildcard, s);
    if (! strchr(wildcard, '.'))
        strcat(wildcard, "*.*");
    attrib = _A_NORMAL | _A_SUBDIR | _A_RDONLY;
    if (_dos_findfirst(wildcard, attrib, &info) != 0)
        return 0;
    files = 1;
    bytes = info.size;
    winio_setpaint(FALSE);
    show_filename(&info);
    while (_dos_findnext(&info) == 0)
    {
        show_filename(&info);
        files++;
        bytes += info.size;
    }
    printf("%5u File(s)\t%lu bytes\n", files, bytes);
    winio_setpaint(TRUE);
    return 1;
}

int do_activate(char *s)
{
    HWND hwnd = FindWindow(NULL, s);
    if (! hwnd) return FALSE;
    BringWindowToTop(hwnd);
    if (IsIconic(hwnd)) ShowWindow(hwnd, SW_RESTORE);
    return TRUE;
}

// distinguish between built-in that failed, and not built-in
#define NOT_BUILTIN     -1

#define MATCH(str, func)  if (strcmp(cmd, str) == 0) return func(args)

int do_builtin(char *s)
{
    char *cmd = strtok(s, " \t");
    char *args = strtok(0, "\t");
    if (strcmp(cmd, "ACTIVATE") == 0)
        return do_activate(&orig[args-cmd]);    // unmodified string
    else if ((strlen(cmd) == 2) && (cmd[1] == ':'))     // drive:
        return do_chdrive(cmd);
    else MATCH("CD", do_cd);
    else MATCH("DIR", do_dir);
    return NOT_BUILTIN;
}

int do_command(char *s)
{
    int ret; 
    if ((ret = do_builtin(s)) == NOT_BUILTIN)
    {
        unsigned retval;
        HWND focus = GetFocus();    // changed from MSJ version
        ret = ((retval = WinExec(orig, SW_SHOWMINIMIZED)) > 32);
        SetFocus(focus);            // changed from MSJ version
        printf("%04X\n", retval);
    }
    return ret;
}

