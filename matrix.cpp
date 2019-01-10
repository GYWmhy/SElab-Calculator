#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "cal.h"
using namespace std;

#define MAX 10

double matrix[MAX][MAX + 1] = {{0,0}};
double answer[MAX] = {0};

void exchange(int x, int y, int n){
	int i;
	double temp;
	for(i = 0;i < n + 1;i++){
		temp = matrix[x][i];
		matrix[x][i] = matrix[y][i];
		matrix[y][i] = temp;
	}
}

void prt(int n){
	int i, j;
	for(i = 0;i < n;i++){
		for(j = 0;j < n + 1;j++)	cout<<matrix[i][j]<<" ";
		cout<<endl;
	}
}

bool Gauss(int n){
	int i, j, k, m;
	double times;
	for(i = 0;i < n;i++){
		if(matrix[i][i] == 0){
			for(k = i;k < n;k++){
				if(matrix[k][i] != 0){
					exchange(i,k,n);
					break;
				}
			}
			if(k == n)	return false;
		}
		times = matrix[i][i];
		for(j = i;j < n + 1;j++){
			matrix[i][j] /= times;
		}
		for(k = 0;k < n;k++){
			if(k == i)	continue;
			else{
				times = matrix[k][i];
				for(m = i;m < n + 1;m++){
					matrix[k][m] -= times * matrix[i][m];
				}
			}
		}
	}
	for(i = 0;i < n;i++){
		if(matrix[i][i] != 1)	return false;
		for(j = 0;j < n;j++){
			if(i == j)	continue;
			else{
				if(matrix[i][j] != 0)	return false;
			}
		}
	}
	for(i = 0;i < n;i++)	answer[i] = matrix[i][n];
	return true;
}

void solve(){
	cout<<"=========="<<endl;
	int n, i, j;
	cout<<"请输入未知量的个数(2-10):";
	cin>>n;
	if(n > MAX || n <= 1){
		cout<<"Illegal input!"<<endl;
		return;
	}
	else{
		memset(matrix,0,sizeof(matrix));
		cout<<"请按行输入矩阵:"<<endl;
		for(i = 0;i < n;i++){
			for(j = 0;j < n + 1;j++){
				cin>>matrix[i][j];
			}
		}
	}
	//prt(n);
	if(Gauss(n)){
		cout<<"x = (";
		for(i = 0;i < n;i++)	cout<<answer[i]<<",";
		cout<<"\b)"<<endl;
	}
	else{
		cout<<"Infinite Solution!"<<endl;
	}
	cout<<"=========="<<endl;
	getchar();
}
