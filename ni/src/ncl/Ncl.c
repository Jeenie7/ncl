#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <ncarg/hlu/hlu.h>
#include <ncarg/hlu/NresDB.h>
#include "defs.h"
#include "Symbol.h"
#include "NclData.h"
#include "Machine.h"
#include "DataSupport.h"
#include <unistd.h>
#include <ncarg/hlu/Convert.h>
#include <ncarg/hlu/Error.h>
#include <netcdf.h>

FILE *thefptr;
FILE *theoptr;
int cmd_line;
extern int cur_line_number;

#ifdef SunOS
extern FILE *nclin;
extern int nclparse(int);
#else
extern FILE *yyin;
extern int yyparse(int);
#endif /*SunOs*/

#define BUFF_SIZE 512

extern FILE *error_fp;
extern FILE *stdout_fp ;
extern FILE *stdin_fp ;


main() {

	int errid = -1;
#ifdef YYDEBUG
	extern int yydebug;
	yydebug = 1;
#endif
	ncopts = NC_VERBOSE;

	cmd_line =isatty(fileno(stdin));

	error_fp = stderr;
	stdout_fp = stdout;
	stdin_fp = stdin;

#ifdef NCLDEBUG
	thefptr = fopen("ncl.tree","w");
	theoptr = fopen("ncl.seq","w");
#else
	thefptr = NULL;
	theoptr = NULL;
#endif
	NhlOpen();
	errid = NhlErrGetID();
	NhlVASetValues(errid,
		NhlNerrFilePtr,stdout,NULL);
	_NclInitMachine();
	_NclInitSymbol();	
	_NclInitDataClasses();

	_NhlRegSymConv(NhlTGenArray,NhlTNclData,NhlTGenArray,NhlTGenArray);

	if(cmd_line)	
		fprintf(stdout_fp,"ncl %d> ",0);
#ifdef SunOS
	nclparse(1);
#else
	yyparse(1);
#endif
	fclose(thefptr);
#ifdef NCLDEBUG
	fprintf(stdout,"Number of unfreed objects %d\n",_NclNumObjs());
	_NclPrintUnfreedObjs(stdout);
	_NclObjsSize(stdout);
	_NclNumGetObjCals(stdout);
#endif
	NhlClose();
	exit(0);
}





#ifdef __cplusplus
}
#endif
