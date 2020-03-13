#include<iostream>
using namespace std;

int main (){
	int prioritas[6]={3,2,5,6,1,4};
	string barang[6]={"Kopi","Gula","Beras","Daging","Jagung","Sabun"};
	
	//bubble sort
	for (int i=0;i<6-1;i++){
		for (int j=0;j<6-i-1;j++){
			if (prioritas[j]>prioritas[j+1]){
				swap(barang[j],barang[j+1]);
				swap(prioritas[j],prioritas[j+1]);
			}
		}
	}
	for (int i=0;i<6;i++){
		cout << barang [i]<<" ";
	}
}
