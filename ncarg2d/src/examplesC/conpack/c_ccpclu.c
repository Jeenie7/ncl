/*
 * $Id: c_ccpclu.c,v 1.1 1994-06-08 14:44:32 haley Exp $
 */

#include <stdio.h>
#include <math.h>

#include <ncarg/ncargC.h>
#include <ncarg/gks.h>

#define   K   40
#define   N   40
#define   LRWK   1000
#define   LIWK   1000

main()
{
	float z[N][K], rwrk[LRWK];
	int i, m, iwrk[LIWK];
	extern void getdat();

	getdat (z, K, &m, N) ;
/*
 * Open GKS
 */
	c_opngks();

	c_cpseti("CLS - CONTOUR LEVEL SELECTION FLAG",0);
	c_cpseti("NCL - NUMBER OF CONTOUR LEVELS",40);
	for( i = 1; i <= 40; i++ ) {
		c_cpseti ("PAI - PARAMETER ARRAY INDEX",i);
		c_cpsetr ("CLV - CONTOUR LEVEL VALUES",5.0*(float)i-15.);
		c_cpseti ("CLU - CONTOUR LEVEL USE FLAG",i%4);
	}
/*
 * Call conpack normally
 */
	c_cprect((float *)z,K,m,N,rwrk,LRWK,iwrk,LIWK);
	c_cpback((float *)z, rwrk, iwrk);
	c_cpcldr((float *)z,rwrk,iwrk);
/*
 * Close frame and close GKS
 */
	c_frame();
	c_clsgks();
}

void getdat (z, n, m, k)
float *z;
int k, *m, n;
{
    int i,j,l;

    l = 0;
    *m = k;
    for( j = 1; j <= n; j++ ) {
        for( i = 1; i <= *m; i++ ) {
            z[l++] = 10.e-5*(-16.0*(float)(i*i*j) + 34.0*(float)(i*j*j) - (float)(6.0*i) + 93.0);
        }
    }
    return;
}
