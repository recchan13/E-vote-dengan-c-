#include <iostream>
#include <fstream>
#include <conio.h> //untuk password bintang-bintang
#include <stdlib.h>//header untuk generate password dan untuk batas 2 angka di belakang koma
#include <time.h> //header untuk generate password
using namespace std;

struct Prodi{
	int kode[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	string nama[14]={"FISIKA","GEOFISIKA","TEKNIK ELEKTRO","TEKNIK INFORMATIKA",
					"TEKNIK GEOLOGI","MATEMATIKA","TEKNIK MESIN","BIOLOGI",
					"TEKNIK INDUSTRI","TEKNIK SIPIL","PERENCANAAN WILAYAH DAN KOTA",
					"TEKNIK GEOMATIKA","ARSITEKTUR","TEKNIK LINGKUNGAN"};
};
struct dataMahasiswa{
	int voting;
	string nim, prodi;
	bool keterangan;
};
struct datalogin{
	string username;
	string password;
};
struct Calon{
	int id;
	string nama;
	int ket;
};

int hitungData(char tipedata);
bool searchData1(dataMahasiswa data[],int N, string cari,int *x);
bool searchData2(datalogin data[],int N, string uname, string pass);
void login();
bool bisaLogin(string uname);
void admin();
void generatePass(int panjangPass,string nim);
void voter(string uname);
void hasilVote();
void sudahVote(string uname, int nomorCalon);
void sortingProdi();
void tampilkanData();

int main(){
	login();
	
}

int hitungData(char tipedata){			//menghitung data dalam file external
	int i=0;
	int tempInt ;
	bool tempV;
	string temp;
	ifstream load;
	
	if (tipedata=='m'){
		load.open("datamhs.txt");
		while (!load.eof()){
			load>>temp; load>>temp; load>>tempV; load>>tempInt;
			i++;
		}
	}else if (tipedata=='u'){
		load.open("unamepass.txt");
		while (!load.eof()){
			load>>temp; load>>temp; 
			i++;
		}
	}else if (tipedata=='c'){
		load.open("calon.txt");
		while (!load.eof()){
			load>>tempInt; getline(load,temp,'#'); load>>tempInt;
			i++;
		}
	}return i;
}

bool searchData1(dataMahasiswa data[],int N, string cari,int *x){
	for(int i=0;i<N;i++){
		if (cari==data[i].nim){
			*x=i;
			return true;
		}
	}return false;
}
bool searchData2(datalogin data[],int N, string uname, string pass){		//fungsi untuk mencari data apakah data ada/tidak
	for(int i=0;i<N;i++){
		if ((uname==data[i].username)&&(pass==data[i].password)){
			return true;
		}
	}return false;
}
string passBintang(){
	int j=0; //menghitung panjang
	char ch; 
	string pass=""; //membuat isi tmpkata kosong lagi ketika kembali ke awal
	ch=_getch(); //mendeteksi input keyboard
	
	while(ch!=13){ //13 kode ascii untuk enter
		if(ch==8){ // 8 adalah code ascii untuk backspace
			if(j!=0){
				cout<<'\b'; //untuk memundurkan type select
				cout<<" "; //menimpah * dengan spasi
				cout<<'\b'; //mundurin lagi
				pass.erase(j-1,1); //akan menghapus dari huruf ke j-1 dari depan sampai 1 dari belakang.
				j--;
			}
		}else{
			pass.push_back(ch);
			cout<<"*";
			j++;
		}ch=_getch(); 
	}cout<<"\n"; 
	return pass;
}
void login(){					//prosedur ini mebutuhkan semua fungsi di atas ini adalah prosedur login
	string uname,pass;
	
	cout<<"Username : "; cin>>uname;
	cout<<"Password : "; pass=passBintang();
	if ((uname=="admin")&&(pass=="12345678")){ //data admin itu dinamis
		cout<<"\n+-------------------------+\n";
		cout<<"|   MASUK SEBAGAI ADMIN   |\n";
		cout<<"+-------------------------+\n\n";
			admin();
	}else{
		int i=0;
		int N=hitungData('u');
		datalogin data[N];
		ifstream load;		//memanggil file yang tadi
		
		load.open("unamepass.txt");
		while (!load.eof()){
			load>>data[i].username; load>>data[i].password;
			i++;
		}
		if (searchData2(data,N,uname,pass)){
			if (bisaLogin(uname)){
				cout<<"\nMASUK SEBAGAI VOTER\n\n";
				voter (uname);
			}else{
				cout<<"\nMAAF ANDA SUDAH VOTE\n\nLanjutkan...";
				cin.get(); cin.ignore();
				system("CLS");
				login();
			}
		}else{ 
			cout<<"\n-PASSWORD SALAH-\n\nLanjutkan...";
			cin.get(); cin.ignore();
			system("CLS");
			login();
		}
	}
}
bool bisaLogin(string uname){
	int i=0;
	ifstream load;
	int N=hitungData ('m');
	dataMahasiswa data[N];
	
	load.open("datamhs.txt");
	while (!load.eof()){
		load>>data[i].nim; load>>data[i].prodi ;load>>data[i].keterangan; load>>data[i].voting;
		i++;
	}load.close();
	for(int i=0;i<N;i++){
		if (uname==data[i].nim && data[i].keterangan==1){
			return false;
		}
	}
	return true;
}

void admin(){
	int x; int i=0;
	int N=hitungData('m');
	dataMahasiswa data[N];
	ifstream load;
	
	//admin searching uname
	load.open("datamhs.txt");
	while (!load.eof()){
		load>>data[i].nim; load>>data[i].prodi ; load>>data[i].keterangan; load>>data[i].voting;
		i++;
	}
	
	pilihan:
	int pilih;
	cout<<"1. Search\n2. Tampilkan hasil vote\n3. Tampilkan data mahasiswa\n4. Logout\nPilihan : "; cin>>pilih;
	switch (pilih){
		case 1 : goto search; break;
		case 2 : cout<<"\nTekan ENTER untuk lanjutkan..."; cin.get(); cin.ignore(); system("CLS"); 
				pilihan2 :
				hasilVote();  // memanggil prosedur hasilVote()
				cout<<"1. Lihat detail vote\n2. Kembali\nPilihan : "; cin>>pilih;
					switch (pilih){
						case 1 : sortingProdi(); goto pilihan2; break;
						case 2 : cout<<"\nTekan ENTER untuk lanjutkan..."; cin.get(); cin.ignore();
								system("CLS"); goto pilihan; break;
						default : cout<<"\nPilihan yang anda masukkan salah ..."; cin.get(); cin.ignore();
								system("CLS"); goto pilihan2; break;
					}
				cout<<"\nTekan ENTER untuk lanjutkan..."; cin.get(); cin.ignore();
				system("CLS"); goto pilihan; break;
		case 3 : tampilkanData(); cin.get(); cin.ignore();
				system("CLS"); goto pilihan; break; 
		case 4 : cout<<"\nTekan ENTER untuk lanjutkan..."; cin.get(); cin.ignore();
				system("CLS");
				login();
				break;
		default : goto pilihan; break;
	}
	
	search:
	string cari;
	cout<<"\nMasukkan NIM mahasiswa yang ingin di cari : "; cin>>cari;
	
	if (searchData1(data,N,cari,&x)){
		cout <<"\n---- Mahasiswa No."<<x+1<<" ----\n\n";
		A:
		cout <<"1. Dapatkan Password\n2. Kembali\nPilihan : "; cin>>pilih;
		
		switch (pilih){
			case 1 : generatePass(8,data[x].nim);  //admin save password file external keubah	 
					cout<<"\nTekan ENTER untuk lanjutkan..."; cin.get(); cin.ignore();
					system("CLS");
					goto pilihan; 
					break;
			case 2 : cout<<"\n"; cout<<"\nTekan ENTER untuk kembali ke menu awal ..."; cin.get(); cin.ignore();
				system("CLS"); goto pilihan; break;
			default : cout<<"Maaf silahkan masukkan angka yang sesuai."; goto A;
		}
	}else{
		cout<<"Maaf NIM yang anda masukkan tidak sesuai\n"; goto search;
	}
}

void generatePass(int panjangPass,string nim) {
	ifstream load;		
	int i=0;
	int N=hitungData('u');
	datalogin data[N+1];
	bool found=false;
	
	load.open("unamepass.txt");
	while (!load.eof()){
		load>>data[i].username; load>>data[i].password;
		i++;
	}load.close();
	for (i=0;i<N && !found ;i++){ //untuk nyari nim mahasiswa udh ada blm di file ex
		if (nim==data[i].username){
			cout<<"\nPassword : "<<data[i].password<<"\n";
			found=true;
		}
	}if (!found){
		//jangan di ubah
		string x;
		srand (time(NULL));
		char gen[panjangPass];
		char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		for (i=0; i<panjangPass; i++) {
			gen[i] = alphanum[rand() % (sizeof(alphanum)-1)];
	    }
	    
	    ofstream save;
	    save.open("unamepass.txt");
				    
	    gen[panjangPass] = 0;
	    x=gen;
	    data[N].password=x; data[N].username=nim; 
		    
	    cout<<"\nPassword : "<<x<<"\n";
	    
	    for (i=0;i<=N;i++){
	    	if (i==N){
	    		save<<data[i].username; save<<"\t"<<data[i].password;
			}else{
				save<<data[i].username; save<<"\t"<<data[i].password<<"\n";
			}
		}
	}	
}
void voter(string uname){
	int pilih,yakin,nomorCalon;
	int N=hitungData('c');
	Calon calon[N];
	bool vote=false;
	
	int i=0,j=0;
	ifstream load;
	load.open("calon.txt");
	while(!load.eof()){
		load>>calon[i].id;
		getline(load,calon[i].nama,'#');
		load>>calon[i].ket;
		i++;
	}load.close();
	
	voting:
	cout<<"Silahkan memilih pilihan anda sesuai nomor berikut:\n";
	for(j=0;j<N;j++){
		cout<<calon[j].id<<"."<<calon[j].nama<<"\n";
	}cout<<"\nPilihan :";
	cin >> pilih;
	
	for(int i=0;i<N && vote==false;i++){
		if (pilih==calon[i].id){
			nomorCalon=pilih;
			cout<<"\nvote "<<pilih<<"\n\n"; 
			vote=true;
		}
	}if (vote){
		cout<<"Apakah anda yakin memilih nomor "<<pilih<<" ?\n1. Ya\t2. Tidak\n"; cin>>yakin;
	}else{
		cout<<"\nPilihan anda tidak terdaftar, silahkan masukkan angka yang terdaftar. \n\n"; cin.get(); cin.ignore();
		system("CLS"); goto voting;
	}
	
	ofstream save;
	switch (yakin){
		case 1 : cout<<"\nVOTING BERHASIL\nTERIMAKASIH TELAH MENGGUNAKAN HAK ANDA!\n\nTekan ENTER untuk lanjutkan..."; cin.get(); cin.ignore();
				system("CLS");
				calon[pilih-1].ket++; 
				
				save.open("calon.txt");
				for(int j=0;j<N;j++){
					if (j==i-1){
						save<<calon[j].id<<calon[j].nama<<"# "<<calon[j].ket;
					}else{
						save<<calon[j].id<<calon[j].nama<<"# "<<calon[j].ket<<"\n";
					}	
				}save.close();
				sudahVote(uname, nomorCalon);
				
				login(); 
				break;
		case 2 : cout<<"\nTekan ENTER untuk lanjutkan..."; cin.get(); cin.ignore();
				system("CLS");
				voter(uname); break;
	}
}
void hasilVote(){
	ifstream load;
	int N=hitungData('c');
	Calon calon[N];
	
	load.open("calon.txt");
	int i=0;
	while(!load.eof()){
		load>>calon[i].id;
		getline(load,calon[i].nama,'#');
		load>>calon[i].ket;
		i++;
	}load.close();
	
	int sum=0;
	for (int i=0;i<N;i++){
		sum+=calon[i].ket;
	}
	cout<<"+------------------HASIL  VOTE------------------+\n";
	cout<<"+-----------------------------------------------+\n";
	cout<<"|  ID\t  NAMA CALON\t   PERSENTASE VOTE\t|\n";
	cout<<"+-----------------------------------------------+\n";
	for (int i=0;i<N;i++){
		cout<<"|  "<<i+1<<"\t"<<calon[i].nama<<"\t\t"; printf("%.2f",(float)calon[i].ket/sum*100); cout<<"%\t\t|"<<"\n";
	}cout<<"+-----------------------------------------------+\n\n"; // printf untuk menampilkan hanya 2 angka di belakang koma
}
void sudahVote(string uname, int nomorCalon){
	int i=0;
	ifstream load;
	ofstream save;
	int N=hitungData('m');
	dataMahasiswa data[N];		
	
	load.open("datamhs.txt");
	while (!load.eof()){
		load>>data[i].nim; load>>data[i].prodi ;load>>data[i].keterangan; load>>data[i].voting;
		i++;
	}load.close();
	
	save.open("datamhs.txt");
	for(int i=0;i<N;i++){
		if(uname==data[i].nim){
			data[i].keterangan=1;
			data[i].voting=nomorCalon;
			if (i==N-1){
				save<<data[i].nim<<"\t"; save<<data[i].prodi<<"\t"; save<<data[i].keterangan<<"\t"; save<<data[i].voting;
			}else{
				save<<data[i].nim<<"\t"; save<<data[i].prodi<<"\t"; save<<data[i].keterangan<<"\t"; save<<data[i].voting<<endl;
			}
		}else{
			if (i==N-1){
				save<<data[i].nim<<"\t"; save<<data[i].prodi<<"\t"; save<<data[i].keterangan<<"\t"; save<<data[i].voting;
			}else{
				save<<data[i].nim<<"\t"; save<<data[i].prodi<<"\t"; save<<data[i].keterangan<<"\t"; save<<data[i].voting<<endl;
			}
		}
	}save.close();
}
void sortingProdi(){
	int i=0;
	int pilih;
	ifstream load;
	int N=hitungData('c');
	Calon calon[N];
	int X=hitungData('m');
	dataMahasiswa data[X];
	Prodi prodi;
	
	load.open("calon.txt");
	while (!load.eof()){
		load>>calon[i].id; 
		getline(load,calon[i].nama,'#'); 
		load>>calon[i].ket;
		i++;
	}load.close();
	
	cout<<"\nMasukkan id calon : ";cin>>pilih;
	int sum=calon[pilih-1].ket;
	
	i=0;
	load.open("datamhs.txt");
	while (!load.eof()){
		load>>data[i].nim; load>>data[i].prodi; load>>data[i].keterangan; load>>data[i].voting;
		i++;
	}load.close();
	
	for(i=0;i<X;i++){
		if (data[i].voting==pilih){
			if (data[i].prodi=="FI"){
				prodi.kode[0]++;
			}else if (data[i].prodi=="GF"){
				prodi.kode[1]++;
			}else if (data[i].prodi=="EL"){
				prodi.kode[2]++;
			}else if (data[i].prodi=="IF"){
				prodi.kode[3]++;
			}else if (data[i].prodi=="GL"){
				prodi.kode[4]++;
			}else if (data[i].prodi=="MA"){
				prodi.kode[5]++;
			}else if (data[i].prodi=="ME"){
				prodi.kode[6]++;
			}else if (data[i].prodi=="BI"){
				prodi.kode[7]++;
			}else if (data[i].prodi=="TI"){
				prodi.kode[8]++;
			}else if (data[i].prodi=="SI"){
				prodi.kode[9]++;
			}else if (data[i].prodi=="PWK"){
				prodi.kode[10]++;
			}else if (data[i].prodi=="TG"){
				prodi.kode[11]++;
			}else if (data[i].prodi=="AR"){
				prodi.kode[12]++;
			}else if (data[i].prodi=="TL"){
				prodi.kode[13]++;
			}
		}
	}cout<<"\n";
	
	//bubble sort
	for (int i=0;i<14-1;i++){
		for (int j=0;j<14-i-1;j++){
			if (prodi.kode[j]<prodi.kode[j+1]){
				swap(prodi.kode[j],prodi.kode[j+1]);
				swap(prodi.nama[j],prodi.nama[j+1]);
			}
		}
	} 
	for (int i=0;i<14;i++){
		if (prodi.kode[i]!=0){
			cout << prodi.nama[i]<<" "; printf("%.2f",(float)prodi.kode[i]/sum*100); cout<<"%\n"; 
		} //printf untuk menampilkan hanya 2 angka di belakang koma
	} cout<<"\nTekan ENTER untuk lanjutkan..."; cin.get(); cin.ignore();
	system("CLS");
}
void tampilkanData(){
	int i=0;
	int N=hitungData('m');
	dataMahasiswa data[N];
	ifstream load;
	
	load.open("datamhs.txt");
	while (!load.eof()){
		
		load>>data[i].nim; load>>data[i].prodi; load>>data[i].keterangan; load>>data[i].voting;
		i++;
	}load.close();
	
	cout<<"+-----------------------------------------------+\n";
	cout<<"|	  NIM		|	KETERANGAN	|\n";
	cout<<"+-----------------------------------------------+\n";
	for (int i=0;i<N;i++){
		if (data[i].keterangan==0){
			cout<<"|\t"<<data[i].nim<<"\t|\tbelum vote\t|\n";
		}else{
			cout<<"|\t"<<data[i].nim<<"\t|-------SUDAH VOTE------|\n";
		}
	}cout<<"+-----------------------------------------------+";
}
