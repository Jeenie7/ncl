/*
 * $Id: c_ccpila.c,v 1.1 1994-06-08 14:44:41 haley Exp $
 */

#include <stdio.h>
#include <math.h>

#include <ncarg/ncargC.h>
#include <ncarg/gks.h>

#define M  40
#define N  40
#define LRWK  3500
#define LIWK  4000

main()
{
	float z[N][M], rwrk[LRWK];
	int iwrk[LIWK];
	extern void getdat();

	getdat (z, M, N);
/*
 * Open GKS
 */
	c_opngks();
	gset_clip_ind(GIND_NO_CLIP);
/*
 * Initialize Conpack
 */
	c_cpsetr("HLA - HIGH/LOW LABEL ANGLE",30.);
	c_cpsetr("ILA - INFORMATION LABEL ANGLE",90.);
	c_cpsetr("ILX - INFORMATION LABEL X COORD",-0.02);
	c_cpsetr("ILY - INFORMATION LABEL Y COORD",0.25);
	c_cpseti("ILP - INFORMATION LABEL POSITION", 0);
	c_cprect((float *)z, M, M, N, rwrk, LRWK, iwrk, LIWK);
/*
 * Draw Perimeter
 */
	c_cpback((float *)z, rwrk, iwrk);
/*
 * Draw Contours
 */
	c_cplbdr((float *)z,rwrk,iwrk);
	c_cpcldr((float *)z,rwrk,iwrk);
/*
 * Close frame and close GKS
 */
	c_frame();
	c_clsgks();
}


void getdat (z, m, n)
float z[N][M];
int m, n;
{
	int i, j;
	FILE *fp;

	fp = fopen("ccpila.dat","r");
	for( i = 0; i < m; i++ ) {
		for( j = 0; j < n; j++ ) {
			fscanf( fp, "%g", &z[j][i] );
		}
	}
	fclose(fp);
	return;
}
