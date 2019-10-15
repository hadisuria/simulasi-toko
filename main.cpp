#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>

#define ff() cin.clear(); cin.sync();

// for login as owner id and pw is owner, pin 123456. Set by default, you can change it manualy or with the program

using namespace std;

class Barang{
	friend bool cmd(const Barang & , const Barang & );
	protected:
		string nama;
		int harga;
		int stok;		
	public:
		//default constructor
		Barang();
		
		//overload constructor
		Barang(string nama, int harga, int stok){
			this->nama = nama;
			this->harga = harga;
			this->stok = stok; 
		}
		
		//setter
		void setNama(string nama){
			this->nama = nama;
		}
		void setHarga(int harga){
			this->harga = harga;
		}
		void setStok(int stok){
			this->stok = stok;
		}
		//getter
		string getNama() const {
			return nama;
		}
		int getHarga() const {
			return harga;
		}
		int getStok() const {
			return stok;
		}	
		
};

class User{
	protected: 
		string id;
		string pw;
	public:
		string getId(){
			return id;
		}
		string getPw(){
			return pw;
		}
};

class Owner: public User{
	private:
		string pin;
	public:
		Owner();
		Owner(string id = "owner", string pw = "owner", string pin = "123456"){
			this->id = id;
			this->pw = pw;
			this->pin = pin;
		}
		
		string getPin(){
			return pin;
		}
		void menu(){
			cout << "  +--------------------------+\n"
					"  | \"KEMBANGAN SHOP [owner]\" |\n"
					"  +--------------------------+\n"
					"  1. List barang\n"
					"  2. Take out\n"
					"  3. Koreksi barang\n"
					"  4. Tambah barang baru\n"
					"  5. Tambah staff\n"
					"  6. Hapus staff\n"
					"  0. Exit\n\n"
					"  Choice: ";
		}	
};
class Staff: public User{
	private:
		
	public:
		Staff();
		Staff(string id, string pw ){	
			this->id = id;
			this->pw = pw;
		}
		
		void setId(string id){
			this->id = id;
		}
		void setPw(string pw){
			this->pw = pw;
		}
		
		void menu(){
			cout << "  +--------------------------+\n"
					"  | \"KEMBANGAN SHOP [staff]\" |\n"
					"  +--------------------------+\n"
					"  1. List barang\n"
					"  2. Take out\n"
					"  3. Change password\n"
					"  0. Exit\n\n"
					"  Choice: ";
			}		
};

void menuAwal(){
	cout << " +-------------+\n"
			" | \"KEMBANGAN\" |\n"
			" +-------------+\n"
			"  1. Login\n"
			"  0. Exit\n\n"
			"  Choice: ";
}

//staff
vector<Staff> staff;

int stringToNum( string text );

void dataSplit( string, vector<Barang>&);

void read( vector<Barang>& );

void readStaff();

void fillVector( vector<Barang>& , string , int , int);

void printListBarang( const vector<Barang>& );

int cekNama(vector<Barang>& , string );

void takeOut(vector<Barang>& );

void editBarang(vector<Barang>& );

void tambahBarang( vector<Barang> &);

void save( vector<Barang>& );

void appendStaff();

void hapusStaff();

void staffChangePassword();

void deleteStaffobj();

bool cmd(const Barang & item1, const Barang & item2)
{
   if (item1.nama != item2.nama) return item1.nama < item2.nama;
   return item1.harga < item2.harga;
}

int main(){ ////main
	Owner owner("owner", "owner");

	int choice; string pin;
	
	vector<Barang> myItem;
	read(myItem); 
	readStaff();
	
	sort(myItem.begin(), myItem.end(), cmd);
	
	string id, pw; int flagLogin = 0; int code;
	//input case 2
	string inNama;
	int inJumlah;
	
	do{
		system("cls");
		menuAwal();
		 cin >> choice; ff();
		 
		if(choice == 1){
			
			cout << "  Masukan id: ";
			 getline(cin, id); ff()
			cout << "  Masukan pw: ";
			 getline(cin, pw); ff()
			
			if(id == owner.getId() && pw == owner.getPw()){
				cout << "  Masukan pin: ";
				 cin >> pin; ff();
				if( owner.getPin() == pin){
					flagLogin = 1;
					code = 1;
				}	
			}
			else{
				for(int i=0; i<staff.size() ; i++){
					if(id == staff[i].getId() && pw == staff[i].getPw()){
						flagLogin = 1;
						code = 0;
						break;
					}
				}
			}
			//jika pw dan id tidak benar
			if(flagLogin == 0){
				system("cls");
				cout << "  Input salah\n";
				cout << "  PRESS ENTER TO CONTINUE...";
				cin.get();
				choice = -1;
			}
		}
		
		
		if(flagLogin == 1){
			do{ //menu2
				if(code == 1){ //for owner
					do{
						system("cls");
						owner.menu();
						cin >> choice; ff();
					}while(choice < 0 || choice > 6);
				}
				else{ //for Staff
					do{
						system("cls");
						staff[0].menu();
						cin >> choice; ff();
					}while(choice < 0 || choice > 3);
				}
				switch(choice){
					case 1:
						printListBarang(myItem);
						cin.get();
						break;
					case 2:
						system("cls");
						takeOut(myItem);
						break;
					case 3:
						if(code == 1){ //owner
							system("cls");
							printListBarang(myItem);
							editBarang(myItem);
							cin.get();	
						}
						else{ //staff
							system("cls");
							staffChangePassword();
							cin.get();
						}
						break;
					// 4-6 menu owner
					case 4:
						system("cls");
						tambahBarang(myItem);
						cout << "\n  Tambah barang berhasil..\n";
						cout << "  PRESS ENTER TO CONTINUE..\n";
						cin.get();
						break;
					case 5:
						system("cls");
						appendStaff();
						break;
					case 6:
						system("cls");
						hapusStaff();
						break;
				}
			}while(choice != 0);	
			choice = -1;
		}	//endif
		flagLogin = 0;
	}while(choice != 0);
	
	deleteStaffobj();
	save(myItem);
	return 0;
}


int stringToNum(string text ){
	int n = 0, size = text.size();
	
	for(int i=0, j = size; i<size; i++){
		n +=(text[--j]-'0')*pow(10,i);
	}
	return n;
}

void dataSplit(string data, vector<Barang>& newMyItem){
	string delimiter = "#";
	
	size_t pos = 0;
	string token;
	
	string nama;
	int harga;
	int stok;
	
	int flag = 0;
	
	while((pos = data.find(delimiter)) != string::npos){
		token = data.substr(0, pos);
		data.erase(0, pos + delimiter.length());
		if(flag == 0){	
			nama = token;
			flag++;
		}
		else{
			harga = stringToNum(token);
			flag--;
		}
	}
	stok = stringToNum(data);
	fillVector(newMyItem, nama, harga, stok);
}

void readStaff(){ //staff
	string id;
	string pw;

 	ifstream myfile;
	myfile.open ("staff.txt");
	if(myfile.is_open()){
  		while(myfile >> id >> pw ){	
  			staff.push_back(Staff(id,pw));
		}
		myfile.close();
 	}
 	else{	
 		cout << "  Open file failed" << endl;
	}	
}

void read(vector<Barang>& newMyItem){ //barang
	string data;
	
 	ifstream myfile;
	myfile.open ("example.txt");
	if(myfile.is_open()){
  		while(getline(myfile, data)){	
  			dataSplit(data, newMyItem); //input to vector
		}
		myfile.close();
 	}
 	else{	
 		cout << "  Open file failed" << endl;
	}	
}

void fillVector(vector<Barang>& newMyItem, string nama, int harga, int stok){
	
	Barang newItem(nama, harga, stok);
	newMyItem.push_back(newItem);
	
}

void fillVectorStaff(vector<Staff>& newStaff, string id, string pw){
	
	Staff inputStaff(id, pw);
	newStaff.push_back(inputStaff);
	
}

void printListBarang(const vector<Barang>& newMyItem){
	unsigned int size = newMyItem.size();
	
	cout << "+" << right << setw(63) << setfill('=') << "+\n" << setfill(' ');
	cout << left << "| " << setw(5) << "NO" << " | " << setw(15) << "NAMA" << " | "
		 << setw(15) << "HARGA" << " | " 
		 << setw(15) << "STOK" << " |\n";
	cout << "+" << right << setw(63) << setfill('=') << "+\n" << setfill(' ');
	
	for(unsigned int i=0; i< size; i++){
		cout << left << "| " << setw(5) << i+1 << " | ";
		cout << setw(15) << newMyItem[i].getNama()  << " | ";
		cout << setw(15) << newMyItem[i].getHarga() << " | ";
		cout << setw(15) << newMyItem[i].getStok()  << " | "<< endl;
	}
	cout << "+" << right << setw(63) << setfill('=') << "+\n" << setfill(' ');	
}

int cekNama(vector<Barang>& myItem, string inString){
	for(int i=0; i<myItem.size(); i++){
		if(myItem[i].getNama() == inString){
			return i;
		}
	}
	return -1;
}

void takeOut(vector<Barang>& myItem){
	int jmlTakeout = 0;
	string inString;
	int inJumlah;
	string nama[50];
	int jumlah[50];
	
	int sisa; int loc;
	
	int choice = 0;
	
	do{
		system("cls");
		printListBarang(myItem);
		cout << "\n  Take out list: " << endl;
			for(int i=0 ; i<jmlTakeout; ){
				cout << "| " << ++i << ". " << setw(10) << left << nama[i] << " | " << setw(5) << jumlah[i] << right << endl;
			}
			cout << endl;
		cout << "  Masukan nama barang: ";
			 getline(cin, inString); ff();
		cout << "  Masukan jumlah barang: ";
		 cin >> inJumlah; ff();
		
		if(cekNama(myItem, inString) == -1 || myItem[cekNama(myItem, inString)].getStok()-inJumlah < 0){
			cout << "  Barang tidak ada / kurang !\n";
		}
		else{
			loc = cekNama(myItem, inString);
			nama[jmlTakeout] = inString;
			jumlah[jmlTakeout] = inJumlah;
			sisa = myItem[loc].getStok() - inJumlah;
			myItem[loc].setStok(sisa);
			
			jmlTakeout++;
		}
		cout << "\n  1. Masukan lagi\n"
			"  2. Selesai\n\n"
			"  Choice: ";
		 cin >> choice; ff();
		
	}while(choice == 1);
}

void editBarang(vector<Barang>& myItem){
	string inString; int cek;
	int choice;
	
	cout << "  Masukan barang yang ingin di edit: ";
	getline(cin, inString); ff();
	cek = cekNama(myItem, inString);
	
	if(cek == -1){
		cout << "  Barang tersebut tidak ada.";
	}
	else{
		cout << endl << "  Nama: "<< "\""<< myItem[cek].getNama() <<"\"\n"
			 << "  Harga: " << "\""<< myItem[cek].getHarga() <<"\"\n"
			 << "  Stok: " << "\""<< myItem[cek].getStok() <<"\"\n";
			
		cout << "  1. Edit nama\n"
				"  2. Edit harga\n"
				"  3. Edit stok\n"
				"\n  Choice: ";
				cin >> choice; ff();
		if(choice == 1){
			string nama;
			cout << "  Masukan nama baru: ";
			getline(cin, nama); ff()
			myItem[cek].setNama(nama);
		}
		else if(choice == 2){
			int harga;
			cout << "  Masukan harga baru: ";
			cin >> harga; ff();
			myItem[cek].setHarga(harga);
		}
		else if(choice == 3){
			int stok;
			cout << "  Masukan stok baru: ";
			cin >> stok; ff();
			myItem[cek].setStok(stok);
		}
	}
}

void tambahBarang(vector<Barang> &myItem){
	string nama;
	int harga;
	int stok;
	cout << "\"  Tambah Barang\"\n\n";
	
	cout << "  Masukan nama barang: ";
	 getline(cin, nama); ff()
	cout << "  Masukan harga barang: ";
	 cin >> harga; ff();
	cout << "  Masukan stok barang: ";
	 cin >> stok; ff();
	
	fillVector(myItem, nama, harga, stok);
	
}

void printStaff(){
	cout << "\n  =STAFF= \n\n";
	for(int i=0; i<staff.size(); i++){
		cout << "  " << i+1 << ". " << staff[i].getId() << endl;
	}
}

void appendStaff(){ //tambah staff
	string id;
	string pw;
	
	printStaff();	
	do{
		cout << "  Masukan id staff baru: ";
		 cin >> id; ff();	
	}while(id.find(" ") != string::npos);
	cout << "  Masukan pw staff baru: ";
	 cin >> pw; ff();
			
	fstream myfile;
	myfile.open ("staff.txt", ios::in | ios::out | ios::app);
	if(myfile.is_open()){
		myfile << id << " " << pw << endl;
		fillVectorStaff( staff, id,pw);
		myfile.close();
 	}
	else{	
		cout << "  Open file failed" << endl;
	}	
}
		
void hapusStaff(){ //owner hapus staff
	string id;
	string pw;
	char input;
	cout << "<  Hapus Staff>\n\n";
	printStaff();
	do{
		cout << "\n  Masukan id staff [ 0 untuk batal ]: ";
		 cin >> id; ff();	
	}while(id.find(" ") != string::npos);
	for(int i=0; i<staff.size(); i++){
		if(staff[i].getId() == id){
			cout << "  Hapus staff " << id << "? Y/N : ";
			cin >> input; ff();
			if(input == 'Y' || input == 'y'){
				staff.erase(staff.begin() + i);
				cout << "\n  Staff berhasil dihapus\n";
				cin.get();
			}
			else{
				cout << "\n  Batal menghapus staff\n";
				cin.get();
			}
		}
	}
}

void deleteStaffobj(){
	for(int i=0; i<staff.size(); i++){
		staff.erase(staff.begin() + i);
	}
}

void staffChangePassword(){
	string id, pw;
	int choice;
	
	cout << "  Masukan ID: ";
	 cin >> id; ff();
	cout << "  Masukan password: ";
	 cin >> pw; ff();	
	
	for(int i=0; i<staff.size(); i++){
		if(staff[i].getId() == id && staff[i].getPw() == pw){
			do{
				cout << "  1. Ganti Password\n"
						"  0. Batal\n"
						"\n  Choice: ";
				cin >> choice; ff();		
			}while(choice < 0 || choice > 1);
			if(choice == 1){
				cout << "  Masukan password baru: ";
				 cin >> pw; ff();
				staff[i].setPw(pw);
				cout << "\n  Ganti password berhasil..\n";
			}
		}
	}
}
void save(vector<Barang>& myItem){
	ofstream myfile;
	myfile.open("example.txt");
	for(int i=0; i<myItem.size(); i++){
		myfile << myItem[i].getNama() << "#"
			   << myItem[i].getHarga() << "#"
			   << myItem[i].getStok() << "\n";
	}
}
