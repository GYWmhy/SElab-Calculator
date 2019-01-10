#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include "cal.cpp"
#include "matrix.cpp"
#include "cal.h"
using namespace std;

int factorial(int n){
	if(n == 0)	return 1;
	else{
		return n * factorial(n - 1);
	}
}

void cal(){
	int opr;
	opr = op[--otop];		//pop one operator
	switch(opr){
		case 1: data[--dtop - 1] = (double)data[dtop - 1] + (double)data[dtop]; break;
		case 2: data[--dtop - 1] = (double)data[dtop - 1] - (double)data[dtop]; break;
		case 3: data[--dtop - 1] = (double)data[dtop - 1] * (double)data[dtop]; break;
		case 4:{
			if(data[dtop - 1] == 0){
				error(2,0);		//divided by 0
			}
			else data[--dtop - 1] = (double)data[dtop - 1] / (double)data[dtop];
			break;
		}
		case 5: data[--dtop - 1] = pow((double)data[dtop - 1],(double)data[dtop]); break;
		case 6:{
			if(data[dtop - 1] == 0){
				error(2,0);		//divided by 0
			}
			else if(data[dtop - 1] - (int)data[dtop - 1] != 0){
				error(-1,0);		//must be integer
			}
			else data[--dtop - 1] = (int)data[dtop - 1] % (int)data[dtop];
			break;
		}
		case 10:{
			if(data[dtop - 1] - (int)data[dtop - 1] != 0)	error(-1,0);
			if(data[dtop - 1] < 0)	error(5,otop + dtop);
			else{
				data[dtop - 1] = factorial(data[dtop - 1]);
			}
			break;
		}
	}
}

int isktimes(double n){
	int n1 = (int)n;
	double temp = n - (double)n1;
	if(temp == 0){
		return 1;
	}
	else return 0;
}

int calculate(int n){
	int i, j;
	int opr, func;
	int back;
	for(i = n;list[i].tag >= 0;i++){
		//cout<<"i:"<<i<<endl;
		if(list[i].tag == 0){		//it's a number
			data[dtop++] = list[i].num;
			/*for(j = 0;j < dtop;j++){
				cout<<"n:"<<n<<" i:"<<i<<" "<<data[j]<<" ";
			}
			cout<<endl;*/
		}
		else if(list[i].tag == 1){		//it's an operator
			opr = list[i].num;
			if(opr == 1 || opr == 2){		//+ or -
				if(op[otop - 1] >= 1 && op[otop - 1] <= 6 || op[otop - 1] == 10){		//previous operator has higher privilege
					cal();
					op[otop++] = opr;
				}
				else{
					op[otop++] = opr;
				}
			}
			else if(opr == 3 || opr == 4 || opr == 6){		//* or / or %
				if(op[otop - 1] >= 3 && op[otop - 1] <= 6 || op[otop - 1] == 10){		//previous operator has higher priority
					cal();
					op[otop++] = opr;
				}
				else{
					op[otop++] = opr;
				}
			}
			else if(opr == 5){
				if(op[otop - 1] == 5 || op[otop - 1] == 10){		//previous operator has higher priority 
					cal();
					op[otop++] = opr;
				}
				else{
					op[otop++] = opr;
				}
			}
			else if(opr == 10){
				if(op[otop - 1] == 10){		//previous operator has higher priority
					cal();
					op[otop++] = opr;
				}
				else{
					op[otop++] = opr;
				}
			}
			else{		//( and ) and ,
				if(opr == 8){		//(
					op[otop++] = opr;
					back = calculate(i + 1);
					//cout<<"back:"<<back<<endl;
					i = back;
					otop--;		//delete the ( in stack
				}
				else if(opr == 9){		//)
					while(op[otop - 1] != 8){
						cal();
					}
					return i;
				}
				else if(opr == 7){		//,
					//do nothing
				}
			}
		}
		else if(list[i].tag == 2){		//it's a function
			func = list[i].num;
			if(func == 1){		//sin
				op[otop++] = 8;
				back = calculate(i + 2);
				if(isktimes(data[dtop - 1] / PI)){
					data[dtop - 1] = 0;
				}
				else{
					data[dtop - 1] = sin(data[dtop - 1]);
				}
				i = back;
				otop--;
			}
			else if(func == 2){		//cos
				op[otop++] = 8;
				back = calculate(i + 2);
				if(isktimes(data[dtop - 1] / PI + 0.5)){
					data[dtop - 1] = 0;
				}
				else{
					data[dtop - 1] = cos(data[dtop - 1]);
				}
				i = back;
				otop--;
			}
			else if(func == 3){		//tan
				op[otop++] = 8;
				back = calculate(i + 2);
				if(isktimes(data[dtop - 1] / PI + 0.5)){
					error(3,i);		//infinite
				}
				else{
					data[dtop - 1] = tan(data[dtop - 1]);
				}
				i = back;
				otop--;
			}
			else if(func == 4){		//asin
				op[otop++] = 8;
				back = calculate(i + 2);
				if(abs(data[dtop - 1]) > 1){
					error(5,i);		//impossible
				}
				else{
					data[dtop - 1] = asin(data[dtop - 1]);
				}
				i = back;
				otop--;
			}
			else if(func == 5){		//acos
				op[otop++] = 8;
				back = calculate(i + 2);
				if(abs(data[dtop - 1]) > 1){
					error(5,i);		//impossible
				}
				else{
					data[dtop - 1] = acos(data[dtop - 1]);
				}
				i = back;
				otop--;
			}
			else if(func == 6){		//atan
				op[otop++] = 8;
				back = calculate(i + 2);
				data[dtop - 1] = atan(data[dtop - 1]);
				i = back;
				otop--;
			}
			else if(func == 7){		//ln
				op[otop++] = 8;
				back = calculate(i + 2);
				if(data[dtop - 1] <= 0)	error(5,i);
				data[dtop - 1] = log(data[dtop - 1]);
				i = back;
				otop--;
			}
			else if(func == 8){		//log(),()
				op[otop++] = 8;
				back = calculate(i + 2);
				i = back + 1;
				if(!(list[i].tag == 1 && list[i].num == 7)){		//miss the comma
					error(5,i + 1);
				}
				if(data[dtop - 1] <= 1)	error(5,i);
				otop--;
				op[otop++] = 8;
				back = calculate(i + 2);
				i = back;
				if(data[dtop - 1] <= 0)	error(5,i);
				data[--dtop - 1] = log(data[dtop]) / log(data[dtop - 1]);
				otop--;
			}
		}
	}
	if(list[i].tag == -1){
		while(otop > 0){
			cal();
		}
	}
}

void Help(){
	system("cls");
	cout<<"1.运算符："<<endl;
	cout<<"@(负号) + - * / ^ % ! . ( )"<<endl;
	cout<<"============"<<endl;
	cout<<"2.函数："<<endl;
	cout<<"sin() cos() tan() asin() acos() atan()"<<endl;
	cout<<"ln() log(底数),(真数)"<<endl;
	cout<<"============"<<endl;
	cout<<"3.常量调用："<<endl;
	cout<<"PI E"<<endl;
	cout<<"============"<<endl;
	cout<<"4.其他指令："<<endl;
	cout<<"OFF(关机) AC(清除全部) MC(清除存储) M+ M- M(调用存储数据)"<<endl;
	cout<<"ANS(调用上次运算结果) SOLVE(进入解方程界面) CLS(清屏)"<<endl;
	cout<<"============"<<endl;
	cout<<"注：不要输入空格等占位符"<<endl;
	cout<<"注：三角函数按弧度制运算"<<endl;
	cout<<"注：指令和常量要大写"<<endl;
	cout<<"注：解方程请按矩阵输入"<<endl;
	cout<<"============"<<endl;
	getchar();
	system("cls");
	cout<<"Input 'H' to get help."<<endl;
}

int main(){
	int len = 0;
	int err;
	int instr;
	char ch;
	
	cout<<"Input 'H' to get help."<<endl;
	
	for( ; ; ){
		ltop = otop = dtop = errorcnt = 0;		//initial
		
		gets(text);
		len = strlen(text);
		if(len >= 100){
			error(-2,0);		//too long
			goto skip;
		}
		
		instr = getsym(len);
		
		if(instr == 999)	goto skip;		//undefined character
		//cout<<instr<<endl;
		//print();
		err = check();
		if(!err && !instr)	calculate(0);
		if(!errorcnt && !instr){
			ans = data[0];
			cout<<"="<<data[0]<<endl;
		}
		else if(!instr){
			cout<<"There are "<<errorcnt<<" error(s)."<<endl;
		}
		if(instr == -1){		//ce
			m = ans = 0;
		}
		else if(instr == -2){		//mc
			m = 0;
		}
		else if(instr == -3){		//solve
			solve();
		}
		else if(instr == 88){		//off
			exit(0);
		}
		else if(instr == 100){		//cls
			system("cls");
			cout<<"Input 'H' to get help."<<endl;
		}
		else if(instr == 666){		//HELP
			Help();
		}
		skip: 
		memset(text,' ',sizeof(text));
		memset(data,0,sizeof(data));
	}
}
