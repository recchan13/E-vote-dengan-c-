#include<iostream>
using namespace std;

int main (){
	int prioritas[6]={3,2,5,6,1,4},tempPrts;
	string barang[6]={"Kopi","Gula","Beras","Daging","Jagung","Sabun"},tempBrg;
	
	//insertion sort
	for (int i=1;i<=6-1;i++){
		int j=i;
		while((j>0)&&(prioritas[j-1]>prioritas[j])){
			swap(prioritas[j],prioritas[j-1]);
			swap(barang[j],barang[j-1]);
			j=j-1;
		}
	}
	for (int i=0;i<6;i++){
		cout << barang [i]<<" ";
	}
}

