/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.  
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/
/*
 * $Source: f:/miner/source/misc/rcs/parsarg.c $
 * $Revision: 1.1 $
 * $Author: matt $
 * $Date: 1993/09/09 17:32:03 $
 *
 * Source for parse_args() function.  See header file (parsarg.h) for info
 *
 * $Log: parsarg.c $
 * Revision 1.1  1993/09/09  17:32:03  matt
 * Initial revision
 * 
 *
 */

#pragma off (unreferenced)
static char rcsid[] = "$Id: parsarg.c 1.1 1993/09/09 17:32:03 matt Exp $";
#pragma on (unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "parsarg.h"

#define ARGBUF_SIZE 500
#define MAX_ARGS 100

char arg_buf[ARGBUF_SIZE];
char *ab_ptr=arg_buf;

void perror_exit(int n,char *s)
{
	perror(s);
	exit(n);
}

void verror(char *s, ...)
{
	fprintf(stderr,"Error: ");
	va_list args;
	va_start(args, s );
	vfprintf(stderr, s, args);
	fprintf(stderr,"\n");
}

void error_exit(int ret_code,char *s,...)
{
	verror(s,((char *) &s)+sizeof(s));	/* addr of next parm on stack */
	exit(ret_code);
}

void parse_args(int argc,char **argv,void (*handler_func)(char *arg),int flags)
{

	for (;argc--;argv++) {
		if (**argv=='@') {			/* read args from file */
			char *arg_ptrs[MAX_ARGS];
			int arg_count;
			FILE *argfile;
			int len;
			char *p=ab_ptr,c;

			if ((argfile=fopen(*argv+1,"rt"))==0) perror_exit(10,*argv+1);
			if ((len=fread(ab_ptr,1,ARGBUF_SIZE-((int) (ab_ptr-arg_buf)),argfile))==ARGBUF_SIZE-(ab_ptr-arg_buf)) error_exit(20,"Argument buffer not big enough\n");
			fclose(argfile);
			ab_ptr[len++]=0;		/* write terminating null */

			/* remove comments */

			while ((p=strchr(ab_ptr,';'))!=NULL) {
				char *p2=strchr(p,'\n');

				if (p2) { 	/* found cr */
					strcpy(p,p2);	/* copy over comment */
					len = strlen(ab_ptr);
				}
				else {		/* no cr, end of string */
					*p=0;
					len = (int) (p-ab_ptr);
				}
			}
			ab_ptr[len]=0;		/* write terminating null */

			while (!ab_ptr[len-1]) len--;	/* back up over terminating nulls */
			p=ab_ptr;


			for (arg_count=0;p<ab_ptr+len;) {
				while (p<ab_ptr+len && ((c=*p)==' ' || c=='\t' || c=='\n')) p++;
				if (p<ab_ptr+len) {	/* found parm? */
					arg_ptrs[arg_count++]=p;
					if (arg_count>=MAX_ARGS) error_exit(10,"Too many args");
					while (p<ab_ptr+len && !((c=*p)==' ' || c=='\t' || c=='\n')) p++;
					*p++=0;
				}
			}
			ab_ptr+=len;
			parse_args(arg_count,arg_ptrs,handler_func,flags);
		}
		else
			if (flags&PA_EXPAND && (**argv != '-')) {
				// TODO: Port
				/*WIN32_FIND_DATAA ffblk;
				char drive[_MAX_DRIVE],dir[_MAX_DIR];
				char filename[_MAX_DRIVE+_MAX_DIR+13],*nptr;
				HANDLE fhandle;
				int done = 0;

				_splitpath(*argv,drive,dir,NULL,NULL);		//get path
				strcpy(filename,drive);
				strcat(filename,dir);
				nptr = filename + strlen(filename);			//point at name part

				fhandle = FindFirstFile(*argv, &ffblk);
				done = fhandle != INVALID_HANDLE_VALUE;

				if (done) handler_func(*argv);
			
				else while (!done) {

					strcpy(nptr,ffblk.cFileName);	//copy name after path

					handler_func(filename);

					done = FindNextFile(fhandle,&ffblk);
			
				}*/
	
			}
			else
				handler_func(*argv);

	}

}


