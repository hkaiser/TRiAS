/**
 **	$Header: /sdsc/dev/vis/image/imtools/v3.0/libim/src/RCS/immiscschemes.c,v 1.2 1995/06/29 00:28:04 bduggan Exp $
 **	Copyright (c) 1989-1995  San Diego Supercomputer Center (SDSC)
 **		a division of General Atomics, San Diego, California, USA
 **
 **	Users and possessors of this source code are hereby granted a
 **	nonexclusive, royalty-free copyright and design patent license to
 **	use this code in individual software.  License is not granted for
 **	commercial resale, in whole or in part, without prior written
 **	permission from SDSC.  This source is provided "AS IS" without express
 **	or implied warranty of any kind.
 **
 **	For further information contact:
 **		E-Mail:		info@sds.sdsc.edu
 **
 **		Surface Mail:	Information Center
 **				San Diego Supercomputer Center
 **				P.O. Box 85608
 **				San Diego, CA  92138-5608
 **				(619) 534-5000
 **/

#define HEADER	"	$Header: /sdsc/dev/vis/image/imtools/v3.0/libim/src/RCS/immiscschemes.c,v 1.2 1995/06/29 00:28:04 bduggan Exp $"

/**
 **  FILE
 **	imschemes.c	- several compression schemes' i/o routines
 **
 **  PROJECT
 **	libim		-  SDSC image manipulation library
 **
 **  DESCRIPTION
 **	imschemes.c contains various routines for reading and writing
 **	files with certain types of compression.
 **
 **  PUBLIC CONTENTS
 **			d =defined constant
 **			f =function
 **			m =defined macro
 **			t =typedef/struct/union
 **			v =variable
 **			? =other
 **
 **  PRIVATE CONTENTS
 **
 **	imCompress...     v   	structures for various schemes
 **	im..Names	  v	names (suffixes) 
 **	im..Magic..	  v	magic numbers
 **	im..Decode	  v	decode (read) routines
 **	im..Encode	  v	encode (write) routines
 **
 **  HISTORY
 **	$Log: immiscschemes.c,v $
 * Revision 1.2  1995/06/29  00:28:04  bduggan
 * updated copyright year
 *
 * Revision 1.1  1995/06/16  08:46:30  bduggan
 * Initial revision
 *
 * Revision 1.1  1995/05/24  17:05:59  bduggan
 * Initial revision
 *
 **/

#include <unistd.h>
//#include <sys/wait.h>
#include "im.h"
#include "iminternal.h"


/**
 **  CODE CREDITS
 **	Custom development, Brian Duggan, San Diego Supercomputer Center, 1995.
 **/


/*
 * COMPRESSION SCHEME
 *	Z - Lempel Ziv Encoding
 *
 * DESCRIPTION
 *	We search for the executables 'compress' and
 * 'uncompress' in the environment's PATH. 
 *
 * 	We use the -f flag to force encoding/decoding
 * even if a) the file already exists or b) compression
 * does not save any space.
 */

static unsigned char imZMagic1[] = { 0x1f, 0x9d };
static unsigned char imZMagic2[] = { 0x9d, 0x1f };
static ImFileMagic imZMagic[] =
{
	{ 0, 2, imZMagic1},
	{ 0, 2, imZMagic2},
	{ 0, 0, NULL}
};
#ifdef __STDC__
static int imZDecode(char* inFile, char* outFile, TagTable* flagsTable);
static int imZEncode(char* inFile, char* outFile, TagTable* flagsTable);
#else
static int imZDecode();
static int imZEncode();
#endif

static char* imCompressZNames[] = { "Z", NULL };

ImCompressScheme imCompressZ =
	{ imCompressZNames,   		/* Suffixes                      */
	  "Lempel-Ziv Encoding",	/* Name                          */
	  imZMagic,			/* magic number(s)		 */
	  imZDecode,			/* Encode routine		 */
	  imZEncode,			/* Decode routine		 */
	}; 

/*
 *  FUNCTION
 *	imZDecode
 *
 *  DESCRIPTION
 *	Uncompress a file.
 *	Destroy the compressed file.
 *	Return the name of the new file.
 */
static int   /* returns status */
#ifdef __STDC__
imZDecode(char* inFile, char* outFile, TagTable* flagsTable)
#else
imZDecode(inFile, outFile, flagsTable)
char* inFile;
char* outFile;
TagTable* flagsTable;
#endif
{
	char tmpName[1024];	/* We need to name the file something.Z */
	int statusp[1];		/* status of child process              */

	sprintf(tmpName,"%s.Z",inFile);

	/*
	 * If there is a file named <inFile>.Z then it will
	 * be destroyed.
	 */

	/*
	 * Rename the file to the tmpName name
	 */
	link(inFile,tmpName);
	unlink(inFile);

	/*
	 * Uncompress the file, thus creating inFile and destroying the old
	 * file.
	 */
	strcpy(outFile, inFile);

	if (fork()==0)
	{   /* Child process */
	 	execlp("uncompress","uncompress","-f",tmpName,NULL);
		unlink(tmpName);
		ImErrorFatalExit("Couldn't execute uncompress.  Is it in your path?", 1, IMESYS);
	}

	wait(statusp);  /* Wait for child to finish */

	if ( (statusp[0] & 0x00ff)!=0)
	{	
		/* Process was terminated or stopped.  This is bad. */
		ImErrorFatal("Process was terminated or stopped.",-1,IMESYS);
	}
	if ( (statusp[0] & 0xff00)!=0)
	{	
		/* Process exited with a nonzero value  */
		ImErrNo = IMESYS;
		return -1;
	}
	 
	return 1;
}


/*
 *  FUNCTION
 *	imZEncode
 *
 *  DESCRIPTION
 *	Compress a file.
 *	Destroy the file
 *	Return the name of the compressed file.
 */
static int   /* returns status */
#ifdef __STDC__
imZEncode(char* inFile, char* outFile, TagTable *flagsTable)
#else
imZEncode(inFile, outFile, flagsTable)
char* inFile;
char* outFile;
TagTable* flagsTable;
#endif
{
	int statusp[1];		/* status of child process              */

	/*
	 * If there is a file named <inFile>.Z, then
	 * it will be destroyed.
	 */
	sprintf(outFile,"%s.Z",inFile);

	if (fork()==0)
	{
		/* We are the child process */
		execlp("compress","compress","-f",inFile,0);
		ImErrNo = IMESYS;
		unlink(inFile);
		ImErrorFatalExit("Couldn't execute compress.  Is it in your path?",-1, IMESYS);
	}

	wait(statusp);  /* Wait for child to finish */

	if ( (statusp[0] & 0x00ff)!=0)
	{	
		/* Process was terminated or stopped.  This is bad. */
		ImErrorFatal("Process was terminated or stopped.",-1,IMESYS);
	}
	if ( (statusp[0] & 0xff00)!=0)
	{	
		/* Process exited with a nonzero value  */
		ImErrNo = IMESYS;
		return -1;
	}

	return 1;
}



/*
 * COMPRESSION SCHEME
 *	GZ - Gnu's Lempel Ziv Encoding
 *
 * DESCRIPTION
 *	We search for the executables 'gzip' and
 * 'gunzip' in the environment's PATH. 
 *
 * 	We use the -f flag to force encoding/decoding
 * even if a) the file already exists or b) compression
 * does not save any space.
 */

static unsigned char imGZMagic1[] = { 0x1f, 0x8b };

static ImFileMagic imGZMagic[] =
{
	{ 0, 2, imGZMagic1},
	{ 0, 0, NULL}
};
#ifdef __STDC__
static int imGZDecode(char* inFile, char* outFile, TagTable* flagsTable);
static int imGZEncode(char* inFile, char* outFile, TagTable* flagsTable);
#else
static int imGZDecode();
static int imGZEncode();
#endif

static char* imCompressGZNames[] = { "gz", NULL };

ImCompressScheme imCompressGZ =
	{ imCompressGZNames,  		/* Suffixes                      */
	  "Gnu Lempel-Ziv Encoding",	/* Name                          */
	  imGZMagic,			/* magic number(s)		 */
	  imGZDecode,			/* Encode routine		 */
	  imGZEncode,			/* Decode routine		 */
	}; 


/*
 *  FUNCTION
 *	imGZDecode
 *
 *  DESCRIPTION
 *	Uncompress a file.
 *	Destroy the compressed file.
 *	Return the name of the new file.
 */
static int   /* returns status */
#ifdef __STDC__
imGZDecode(char* inFile, char* outFile, TagTable* flagsTable)
#else
imGZDecode(inFile, outFile, flagsTable)
char* inFile;
char* outFile;
TagTable* flagsTable;
#endif
{
	char tmpName[1024];	/* We need to name the file something.Z */
	int  statusp[1];	/* status of child process              */

	sprintf(tmpName,"%s.gz",inFile);
	/*
	 * If there's a file named <inFile>.gz, it'll be destroyed.
	 */

	/*
	 * Rename the file to the tmpName name
	 */
	link(inFile,tmpName);
	unlink(inFile);

	/*
	 * Uncompress the file, thus creating inFile and destroying the old
	 * file.
	 */
	 strcpy(outFile, inFile);

	 if (fork()==0)
	 {   /* Child process */
	 	execlp("gunzip","gunzip","-f",tmpName,NULL);
		unlink(tmpName);
		ImErrorFatalExit("Couldn't execute gunzip.  Is it in your path?",-1, IMESYS);
	 }

	wait(statusp);  /* Wait for child to finish */

	if ( (statusp[0] & 0x00ff)!=0)
	{	
		/* Process was terminated or stopped.  This is bad. */
		ImErrorFatal("Process was terminated or stopped.",-1,IMESYS);
	}
	if ( (statusp[0] & 0xff00)!=0)
	{	
		/* Process exited with a nonzero value  */
		ImErrNo = IMESYS;
		return -1;
	}
	 
	 return 1;
}


/*
 *  FUNCTION
 *	imGZEncode
 *
 *  DESCRIPTION
 *	Compress a file.
 *	Destroy the file
 *	Return the name of the compressed file.
 */
static int   /* returns status */
#ifdef __STDC__
imGZEncode(char* inFile, char* outFile, TagTable* flagsTable)
#else
imGZEncode(inFile, outFile, flagsTable)
char* inFile;
char* outFile;
TagTable* flagsTable;
#endif
{
	int statusp[1];		/* status of child process              */

	/*
	 * If there's a file named <inFile>.gz, it'll be destroyed.
	 */
	sprintf(outFile,"%s.gz",inFile);

	if (fork()==0)
	{
		/* We are the child process */
		execlp("gzip","gzip","-f",inFile,0);
		ImErrNo = IMESYS;
		unlink(inFile);
		ImErrorFatalExit("Couldn't execute gzip.  Is it in your path?",-1, IMESYS);
	}

	wait(statusp);  /* Wait for child to finish */

	if ( (statusp[0] & 0x00ff)!=0)
	{	
		/* Process was terminated or stopped.  This is bad. */
		ImErrorFatal("Process was terminated or stopped.",-1,IMESYS);
	}
	if ( (statusp[0] & 0xff00)!=0)
	{	
		/* Process exited with a nonzero value  */
		ImErrNo = IMESYS;
		return -1;
	}

	return 1;
}



/*
 * COMPRESSION SCHEME
 *	z	- Huffman encoding
 *
 * DESCRIPTION
 *	We search for the executables 'pack' and
 * 'unpack' in the environment's PATH. 
 *
 * 	We use the -f flag to force encoding even
 * if compression doesn't save any space.
 *
 */

static unsigned char imzMagic1[] = { 0x1f, 0x1e };
static unsigned char imzMagic2[] = { 0x1e, 0x1f };

static ImFileMagic imzMagic[] =
{
	{ 0, 2, imzMagic1},
	{ 0, 2, imzMagic2},
	{ 0, 0, NULL}
};

#ifdef __STDC__
static int imzDecode(char* inFile, char* outFile, TagTable* flagsTable);
static int imzEncode(char* inFile, char* outFile, TagTable* flagsTable);
#else
static int imzDecode();
static int imzEncode();
#endif

static char* imCompresszNames[] = {"z", NULL};

ImCompressScheme imCompressz =
	{ imCompresszNames,  		/* Suffixes                      */
	  "'Pack' Huffman Encoding",	/* Name                          */
	  imzMagic,			/* magic number(s)		 */
	  imzDecode,			/* Encode routine		 */
	  imzEncode,			/* Decode routine		 */
	}; 

/*
 *  FUNCTION
 *	imzDecode
 *
 *  DESCRIPTION
 *	Uncompress a file.
 *	Destroy the compressed file.
 *	Return the name of the new file.
 */
static int   /* returns status */
#ifdef __STDC__
imzDecode(char* inFile, char* outFile, TagTable* flagsTable)
#else
imzDecode(inFile, outFile, flagsTable)
char* inFile;
char* outFile;
TagTable* flagsTable;
#endif
{
	int statusp[1];		/* status of child process              */
	char tmpName[1024];	/* We need to name the file something.Z */

	/*
	 * If there's a file named <inFile>.z, it'll be destroyed
	 */
	sprintf(tmpName,"%s.z",inFile);
	/*
	 * Rename the file to the tmpName name
	 */
	link(inFile,tmpName);
	unlink(inFile);

	strcpy(outFile, inFile);

	/*
	 * Uncompress the file, thus creating inFile and destroying the old
	 * file.
	 */

	 if (fork()==0)
	 {   /* Child process */
	 	execlp("unpack","unpack",tmpName,NULL);
		unlink(tmpName);
		ImErrorFatalExit("Couldn't execute unpack.  Is it in your path?",-1, IMESYS);
	 }

	wait(statusp);  /* Wait for child to finish */

	if ( (statusp[0] & 0x00ff)!=0)
	{	
		/* Process was terminated or stopped.  This is bad. */
		ImErrorFatal("Process was terminated or stopped.",-1,IMESYS);
	}
	if ( (statusp[0] & 0xff00)!=0)
	{	
		/* Process exited with a nonzero value  */
		ImErrNo = IMESYS;
		return -1;
	}
	 
	 return 1;
}


/*
 *  FUNCTION
 *	imzEncode
 *
 *  DESCRIPTION
 *	Compress a file.
 *	Destroy the file
 *	Return the name of the compressed file.
 */
static int   /* returns status */
#ifdef __STDC__
imzEncode(char* inFile, char* outFile, TagTable* flagsTable)
#else
imzEncode(inFile, outFile, flagsTable)
char* inFile;
char* outFile;
TagTable* flagsTable;
#endif
{
	int statusp[1];		/* status of child process              */

	sprintf(outFile,"%s.z",inFile);

	/*
	 * If there's a file named <inFile>.z, we destroy it.
	 */
	if (fopen(outFile,"r")!=NULL)
		unlink(outFile);

	if (fork()==0)
	{
		/* We are the child process */
		execlp("pack","pack","-f",inFile,0);
		ImErrNo = IMESYS;
		unlink(inFile);
		ImErrorFatalExit("Couldn't execute pack.  Is it in your path?",-1, IMESYS);
	}

	wait(statusp);  /* Wait for child to finish */

	if ( (statusp[0] & 0x00ff)!=0)
	{	
		/* Process was terminated or stopped.  This is bad. */
		ImErrorFatal("Process was terminated or stopped.",-1,IMESYS);
	}
	if ( (statusp[0] & 0xff00)!=0)
	{	
		/* Process exited with a nonzero value  */
		ImErrNo = IMESYS;
		return -1;
	}

	return 1;
}


/*
 * COMPRESSION SCHEME
 *	uu	- ascii encoding
 *
 * DESCRIPTION
 *	We search for the executables 'uuencode' and
 * 'uudecode' in the environment's PATH. 
 *
 * 	uuEncode uses a filename to refer to what
 * the name of the unencoded file should be.  We
 * take this out of the flagsTable.
 *
 */

static unsigned char imuuMagic1[] = { 'b', 'e', 'g', 'i', 'n' };

static ImFileMagic imuuMagic[] =
{
	{ 0, 5, imuuMagic1},
	{ 0, 0, NULL}
};

#ifdef __STDC__
static int imuuDecode(char* inFile, char* outFile, TagTable* flagsTable);
static int imuuEncode(char* inFile, char* outFile, TagTable* flagsTable);
#else
static int imuuDecode();
static int imuuEncode();
#endif

static char* imCompressuuNames[] = {"uu", NULL};

ImCompressScheme imCompressuu =
	{ imCompressuuNames,  		/* Suffixes                      */
	  "ASCII encoding",		/* Name                          */
	  imuuMagic,			/* magic number(s)		 */
	  imuuDecode,			/* Encode routine		 */
	  imuuEncode,			/* Decode routine		 */
	}; 

/*
 *  FUNCTION
 *	imuuDecode
 *
 *  DESCRIPTION
 *	Decode a file.
 *	Destroy the original file.
 *	Return the name of the new file.
 */
static int   /* returns status */
#ifdef __STDC__
imuuDecode(char* inFile, char* outFile, TagTable* flagsTable)
#else
imuuDecode(inFile, outFile)
char* inFile;
char* outFile;
#endif
{
	int statusp[1];		/* status of child process              */
	FILE* fp;		/* file pointer   			*/
	char str[200];		/* holds a string 			*/
	char tmpName[1024];	/* What we want to name the output file */
	char newInFile[1024];	/* similar to inFile, but with new output filename */
	FILE *newFp;		/* file we're creating 			*/
	unsigned char* buffer[1024]; /* buffer for copying file		*/
	int n;			/* number of bytes read			*/

	/*
	 * The name of the file that uudecode creates is given
	 * on the line of the file that starts with the word 'begin'.
	 *
	 * We'd rather not create this file, since it'll most likely
	 * create something in the working directory.
	 *
	 * Instead, we'll make a copy of the file, substituting our
	 * own name for the given name.
	 */

	sprintf(tmpName,"%s2",inFile);
	sprintf(newInFile,"%s.uu",tmpName);

	/*
	 * Read from infile, create newInFile, which has tmpName
	 * as the name of the file it's going to create
	 */
	fp = fopen(inFile,"r");
	strcpy(str,"\0");
	while (strncmp(str,"begin",5)!=0 && !feof(fp))
	{
		fgets(str,200,fp);
	}
	if (strncmp(str,"begin",5)!=0)
	{
		ImErrorFatal("Couldn't find 'begin'",-1,IMEUNKNOWN);
	}

	/*
	 * Open our new file 
	 */
	 newFp = fopen(newInFile,"w");
	 fprintf(newFp,"begin 777 %s\n",tmpName);

	/* Read from fp, write to newFp */
	while ( (n=fread(buffer, 1, sizeof(buffer), fp)) != 0)
		fwrite( buffer, 1, n, newFp);

	fclose(fp);
	fclose(newFp);

	strcpy(outFile,tmpName);
	/*
	 * If outFile exists, it'll be destroyed
	 */
	/*
	 * Uncompress the file, thus creating outFile. 
	 */

	if (fork()==0)
	{   /* Child process */
	 	execlp("uudecode","uudecode",newInFile,NULL);
		unlink(inFile);
		ImErrorFatalExit("Couldn't execute uudecode.  Is it in your path?",-1, IMESYS);
	}

	wait(statusp);  /* Wait for child to finish */

	if ( (statusp[0] & 0x00ff)!=0)
	{	
		/* Process was terminated or stopped.  This is bad. */
		ImErrorFatal("Process was terminated or stopped.",-1,IMESYS);
	}
	if ( (statusp[0] & 0xff00)!=0)
	{	
		/* Process exited with a nonzero value  */
		ImErrNo = IMESYS;
		return -1;
	}

	/* Get rid of both infiles */
	unlink(inFile);
	unlink(newInFile); 
	 
	return 1;
}


/*
 *  FUNCTION
 *	imuuEncode
 *
 *  DESCRIPTION
 *	Encode a file.
 *	Destroy the file
 *	Return the name of the encoded file.
 */
static int   /* returns status */
#ifdef __STDC__
imuuEncode(char* inFile, char* outFile, TagTable* flagsTable)
#else
imuuEncode(inFile, outFile, flagsTable)
char* inFile;
char* outFile;
TagTable* flagsTable;
#endif
{
	int statusp[1];		/* status of child process              */
	char *fileName;		/* name of unencoded file */
	TagEntry* tmpEntry;	/* holds a tag table entry */
	int n;			/* length of file name    */
	FILE* fp;		/* goes to outFile        */

	sprintf(outFile,"%s.uu",inFile);
	/*
	 * If outFile exists, remove it.
	 */
	if (fopen(outFile,"r")!=NULL)
		unlink(outFile);

	/*
	 * Get the name of the uncompressed file from the flagsTable
	 */
	fileName = NULL;
	if (flagsTable!=TAGTABLENULL)
	{
		tmpEntry = TagTableQDirect( flagsTable, "file name", 0);
		if (tmpEntry!=TAGENTRYNULL)
		{
			TagEntryQValue( tmpEntry, &fileName );
			/*
			 * If the filename ended in .uu, take that
			 * off.
			 */
			 n = strlen(fileName);
			 if (n>3)
			 {
				if (fileName[n-1]=='u' && fileName[n-2]=='u'
				    && fileName[n-3]=='.')
					fileName[n-3] = '\0';
			 }
		}
	}
	
	/* Open the file for writing */
	fp = fopen(outFile,"w");

	if (fork()==0)
	{
		/* We are the child process */

		/* I want my stdout to go to outFile! */
		dup2(fileno(fp), fileno(stdout));
		execlp("uuencode","uuencode",inFile,( fileName ? fileName : outFile) ,0);
		unlink(outFile);
		ImErrNo = IMESYS;
		ImErrorFatalExit("Couldn't execute uuencode.  Is it in your path?",-1, IMESYS);
	}

	wait(statusp);  /* Wait for child to finish */

	/*
	 * Remove the unencoded file.
	 */
	unlink(inFile);

	if ( (statusp[0] & 0x00ff)!=0)
	{	
		/* Process was terminated or stopped.  This is bad. */
		ImErrorFatal("Process was terminated or stopped.",-1,IMESYS);
	}
	if ( (statusp[0] & 0xff00)!=0)
	{	
		/* Process exited with a nonzero value  */
		ImErrNo = IMESYS;
		return -1;
	}
	fclose(fp);

	return 1;
}

