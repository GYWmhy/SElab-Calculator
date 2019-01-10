#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include "cal.h"
using namespace std;

void error(int x, int i){
	int j;
	errorcnt++;
	if(x > 2){
		for(j = 0;j < i;j++)	cout<<" ";
		cout<<"^"<<endl;
	}
	switch(x){
		case -2: cout<<"Too long!"<<endl; break;
		case -1: cout<<"% must use integer!"<<endl; break;
		case 1:	cout<<"( ) MISMATCHED!"<<endl; break;
		case 2: cout<<"Can't divided by zero!"<<endl; break;
		case 3:	cout<<"Infinite!"<<endl; break;
		case 4:	cout<<"Undefined character!"<<endl; break;
		case 5: cout<<"Incorrect input!"<<endl; break;
		case 6: cout<<"Syntax error!"<<endl; break;
	}
}

int getsym(int len){
	int i, k, flag = 0;
	double num;
	char ch;
	
	for(i = 0;i < len;i++){
		ch = text[i];
		if(isdigit(ch) || ch == '.'){
			num = 0;
			while(isdigit(ch)){
				num = num * 10 + ch - '0';
				i++;
				ch = text[i];
			}
			if(ch == '.'){		//float
				k = 1;
				i++;
				ch = text[i];
				while(isdigit(ch)){
					num += (ch - '0') * (pow(10,0 - k));
					i++;
					k++;
					ch = text[i];
				}
				if(ch == '.')	error(5,i);
			}
			list[ltop].tag = 0;
			list[ltop].num = num;
			if(flag){
				list[ltop].num = 0 - list[ltop].num;
				flag = 0;
			}
			ltop++;
		}
		if(ch == '@'){
			flag = 1;
		}
		else if(i < len){
			if(ch == 'P' && text[i + 1] == 'I'){
				list[ltop].tag = 0;
				list[ltop++].num = PI;
				i++;
			}
			else if(ch == 'E'){
				list[ltop].tag = 0;
				list[ltop++].num = M_E;
			}
			else if(ch == 'H'){
				return 666;
			}
			else if(ch == 'M'){		//m
				if(text[i + 1] == '+'){		//m+
					m = m + ans;
					return 1;
				}
				else if(text[i + 1] == '-'){		//m-
					m = m - ans;
					return 1;
				}
				else if(text[i + 1] == 'C'){		//mc
					return -2;
				}
				else{
					list[ltop].tag = 0;
					list[ltop++].num = m;
				}
			}
			else if(ch == 'A' && text[i + 1] == 'C'){		//ac
				return -1;
			}
			else if(ch == 'A' && text[i + 1] == 'N' && text[i + 2] == 'S'){		//ans
				list[ltop].tag = 0;
				list[ltop++].num = ans;
				i += 2;
			}
			else if(ch == 'C' && text[i + 1] == 'L' && text[i + 2] == 'S'){		//cls
				return 100;
			}
			else if(ch == 's' && text[i + 1] == 'i' && text[i + 2] == 'n'){
				list[ltop].tag = 2;
				list[ltop++].num = 1;		//sin
				i += 2;
			}
			else if(ch == 'c' && text[i + 1] == 'o' && text[i + 2] == 's'){
				list[ltop].tag = 2;
				list[ltop++].num = 2;		//cos
				i += 2;
			}
			else if(ch == 't' && text[i + 1] == 'a' && text[i + 2] == 'n'){
				list[ltop].tag = 2;
				list[ltop++].num = 3;		//tan
				i += 2;
			}
			else if(ch == 'a' && text[i + 1] == 's' && text[i + 2] == 'i' && text[i + 3] == 'n'){
				list[ltop].tag = 2;
				list[ltop++].num = 4;		//asin
				i += 3;
			}
			else if(ch == 'a' && text[i + 1] == 'c' && text[i + 2] == 'o' && text[i + 3] == 's'){
				list[ltop].tag = 2;
				list[ltop++].num = 5;		//acos
				i += 3;
			}
			else if(ch == 'a' && text[i + 1] == 't' && text[i + 2] == 'a' && text[i + 3] == 'n'){
				list[ltop].tag = 2;
				list[ltop++].num = 6;		//atan
				i += 3;
			}
			else if(ch == 'l' && text[i + 1] == 'n'){
				list[ltop].tag = 2;
				list[ltop++].num = 7;		//ln
				i++;
			}
			else if(ch == 'l' && text[i + 1] == 'o' && text[i + 2] == 'g'){
				list[ltop].tag = 2;
				list[ltop++].num = 8;		//log
				i += 2;
			}
			else if(ch == 'S' && text[i + 1] == 'O' && text[i + 2] == 'L' && text[i + 3] == 'V' && text[i + 4] == 'E'){
				return -3;
			}
			else if(ch == 'O' && text[i + 1] == 'F' && text[i + 2] == 'F'){
				return 88;
			}
			else{
				list[ltop].tag = 1;
				switch(ch){
					case '+':	ch = 1; break;
					case '-':	ch = 2; break;
					case '*':	ch = 3; break;
					case '/':	ch = 4; break;
					case '^':	ch = 5; break;
					case '%':	ch = 6; break;
					case ',':	ch = 7; break;
					case '(':	ch = 8; break;
					case ')':	ch = 9; break;
					case '!':	ch = 10; break;
					default:	error(4,i);	return 999;
				}
				list[ltop++].num = ch;
			}
		}
	}
	list[ltop].tag = -1;
	return 0;
}

int check(){
	int l = 0, r = 0;
	int i;
	struct sym last;
	
	for(i = 0;list[i].tag >= 0;i++){
		if(last.tag == list[i].tag){
			if(last.tag == 1){
				if(!((last.num == 9 && list[i].num != 8) || (last.num != 9 && list[i].num == 8) || (last.num == 10)))	error(6,i);		//syntax error
			}
			else if(last.tag == 2){
				error(6,i);
			}
		}
		if(list[i].tag == 1 && list[i].num == 8)	l++;		//(
		else if(list[i].tag == 1 && list[i].num == 9)	r++;		//)
		last.tag = list[i].tag;
		last.num = list[i].num;
	}
	if(l != r){
		error(1,0);		//( ) mismatch
		return 1;
	}
	else return 0;
}

void print(){		//for test
	for(int i = 0;list[i].tag >= 0;i++){
		cout<<"tag = "<<list[i].tag<<" num = "<<list[i].num<<endl;
	}
}
