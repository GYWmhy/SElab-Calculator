#ifndef CAL_H
#define CAL_H

#include <cstdio>

/*  1  */
/*op1 +*/
/*op2 -*/
/*op3 **/
/*op4 /*/
/*op5 ^*/
/*op6 %*/
/*op7 ,*/
/*op8 (*/
/*op9 )*/
/*op10 !*/

/*  2  */
/*f1 sin*/
/*f2 cos*/
/*f3 tan*/
/*f4 asin*/
/*f5 acos*/
/*f6 atan*/
/*f7 ln*/
/*f8 log*/

/*  3  */
/*ir-3 solve*/
/*ir-2 MC*/
/*ir-1 AC*/
/*ir0 cal*/
/*ir1 M+M-*/
/*ir88 off*/
/*ir100 cls*/
/*ir666 help*/


#define PI 3.1415925635897932384626

int errorcnt = 0;
double ans = 0;
double m = 0;

void error(int x, int i);
int getsym(int len);
int check();
void print();

void solve();

struct sym{
	int tag;		//0 as number, 1 as operator, 2 as functions, -1 as the end of expression
	double num;
}list[100];
int ltop = 0;

char text[100];
double data[100];
int dtop = 0;
int op[100] = {' '};
int otop = 0;

#endif
