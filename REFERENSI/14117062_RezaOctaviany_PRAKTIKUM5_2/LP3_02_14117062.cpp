#include<iostream>
using namespace std;

int main (){
	int A[];
	
	//insertion sort
	for (int i=1;i<=6-1;i++){
		int j=i;
		while((j>0)&&(A[j-1]>A[j])){
			swap(A[j],A[j-1]);
			j=j-1;
		}
	}
	for (int i=0;i<6;i++){
		cout <<A[i]<<" ";
	}
}

