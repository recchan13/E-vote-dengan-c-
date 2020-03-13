#include<iostream>
using namespace std;

int main (){
	int A[];
	
	//bubble sort
	for (int i=0;i<6-1;i++){
		for (int j=0;j<6-i-1;j++){
			if (A[j]>A[j+1]){
				swap(A[j],A[j+1]);
			}
		}
	}
	for (int i=0;i<6;i++){
		cout << A[i]<<" ";
	}
}
