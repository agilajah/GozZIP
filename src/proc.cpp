#include "proc.h"
#include <cstdlib>

Tree crhuffman(string S){
	// Mengembalikan sebuah pohon yang telah dibentuk menggunakan aturan huffman dengan isi dari string S
	Element * First = new Element(S[0],1);
	Element * C;
	int i;
	C = First;
	for(i=1;i<S.length();i++){
		// Kamus Lokal
		Element * dummyx;
		bool value;
		// Algoritma
		dummyx = First;
		value=false;
		while(dummyx != NULL && !value){
			if(dummyx->ch==S[i]){
				dummyx->f++;
				value=true;
			}
			else{
				dummyx = dummyx->next;
			}
		}
		if(!value){
			Element * dummy = new Element(S[i],1);
			C->next = dummy;
			C = C->next;	
		}
	}
	// List of element terbentuk dengan elemen yang turut membesar frekuensinya
	// Sorting list of Element
	ListofTree * LT = new ListofTree();
	ListofTree * dummyx;
	dummyx=LT;
	while(First!=NULL){
		Element * Min;
		Element * Minrec;
		Min=First;
		Minrec = NULL;
		C=First;
		while(C->next != NULL){
			if(Min->f > C->next->f){
				Min = C->next;
				Minrec = C;
			}
			C=C->next;
		}
		string sx;
		sx.push_back(Min->ch);
		Tree * T = new Tree(sx,Min->f);
		ListofTree * dummy = new ListofTree(T);
		dummyx->Add(dummy);
		dummyx=dummyx->next;
		if(Min!=First){
			Minrec->next = Min->next;
		}
		else{
			First = Min->next;
		}
	}
	LT=LT->next;
	while(LT->next != NULL){
		ListofTree * L1 = new ListofTree(LT);
		LT = LT->next;
		ListofTree * L2 = new ListofTree(LT);
		if(LT->next == NULL){
			Tree * Tx = new Tree(L1->T,L2->T);
			ListofTree * L3 = new ListofTree(Tx);
			LT->T=L3->T;
		}
		else{
			LT = LT->next;
			Tree * Tx = new Tree(L1->T,L2->T);
			ListofTree * L3 = new ListofTree(Tx);
			LT->AddSort(L3);	
		}			
	}
	Tree Tfinal(LT->T->s,LT->T->f);
	Tfinal.L = LT->T->L;
	Tfinal.R = LT->T->R;
	return (Tfinal);
}


void BacaFile(string &input,string & filename) {
    //KAMUS
    string temp; //temporary string

    //ALGORITMA
    char ch;
    ifstream fin(filename.c_str(),ios::binary|ios::in);  // default mode ios::in
    if (!fin) {
      cerr << "error: open file for input failed!" << endl;
      abort();
    }

    //membaca file input
    while (fin.get(ch)) {  // till end-of-file
        input +=ch;
    } // selesai baca file

    fin.close();
}

string ReadFileType1(string filename){
//Memasukkan data hexa dari file dengan extensi .doc , .pdf, .zip, dan sejenisnya

  ifstream fin((filename).c_str(), ios_base::binary);
  char ch;
  string dataZIPHexa;
  while (fin.get(ch)) {
    stringstream hexa;
    if (((int)ch >= 0) && ((int)ch < 16)){
      hexa << '0' << hex << (int)ch; //ascii code dengan nilai hexa 1 digit
    } else if ((int)ch < 0){
      hexa << hex << (int)ch + 256; // extended ascii code , nilainya negatif
    } else {
      hexa << hex << (int)ch;
    }
    dataZIPHexa += hexa.str();
  }
  fin.close(); 

  return dataZIPHexa;
}

string itos(int i) { 
    stringstream stream;
    stream << i;
    return stream.str();
}


//Convert binary to hexa
string Bin_to_Hex(string const &temp2) {
    //KAMUS
    int count=0;
    int bat=0;
    string HexaKamus[16] = {  "0000", "0001", "0010", "0011", 
                                "0100", "0101", "0110", "0111", 
                                "1000", "1001", "1010", "1011", 
                                "1100", "1101", "1110", "1111" }; 

    string split;
    string hasil="";
    //ALGORITMA
    while (count < temp2.size()) {
            bool found = false;
            split += temp2[count];
            if (bat==3) { //kalau kelipatan 4
                int i = 0;
                while (!found) {
                    if (split==HexaKamus[i]) {
                        switch (i) {
                            case 0 :
                            case 1 :
                            case 2 :
                            case 3 :
                            case 4 :
                            case 5 :
                            case 6 :
                            case 7 :
                            case 8 :
                            case 9 : hasil += itos(i); break; //convert integer to string
                            case 10 : hasil += 'a'; break;
                            case 11 : hasil += 'b'; break;
                            case 12 : hasil += 'c'; break;
                            case 13 : hasil += 'd'; break;
                            case 14 : hasil += 'e'; break;
                            case 15 : hasil += 'f'; break;
                        }
                        found =true;
                    }
                    i++;                    
                }

                split = ""; // menghapus isi split
                bat=-1;
            }
        bat++;
        count++;
      }

      return hasil;
}

void TulisKeFile(string const &namafile, string const &str) {
    ofstream output2;
    output2.open(namafile.c_str(), ios::binary | ios::trunc);
    string hasil="";
    hasil = Bin_to_Hex(str);
   // cout << "ini hasil ke file : " << hasil << endl;
    output2 << hasil; //mengisi hasil ke output file

}
void TulisKeFile2(string namafile, string str) {
    ofstream output2;

    output2.open(namafile.c_str(), ios::binary | ios::trunc);
    output2 << str;

    output2.close();

}
void TulisKeFile3(string const &namafile, string const &str) {
    ofstream output2;
    //size_t pos = namafile.find(".");  //mencari posisi titik pada nama file untuk mendapatkan ekstensi
    //string ekstensi = namafile.substr (pos); //mengcopy mulai titik sampai dengan akhir 
    //string filename2 =  '1' + ekstensi; // menambah ekstensi, nama file keluaran menjadi 1 + ekstensi
    output2.open(namafile.c_str(), ios::binary | ios::trunc);
    string hasil="";
    hasil = Bin_to_Hex(str);
    //cout << hasil << endl;
   // cout << "ini hasil ke file : " << hasil << endl;

    string split;
    string temp;
    int i = 0;
    while(i < hasil.length()){
      split = "";
      for (int j = 0; j < 2; j++){
        split += hasil[i+j]; 
      }
      //scout << split << " ";
      int x = strtol(split.c_str(), NULL, 16); //cout << x << endl;
      temp += (char)x; //cout << (char)x;
      i+= 2;
    }
    hasil = temp; //cout << temp;
    output2 << hasil; //mengisi hasil ke output file

    output2.close();

}

string Extract(string input, int n, Tree * T){
  int i = 0;
  string stringbinary ="";
  while (i < input.size()) {  // till end-of-file
    
    switch(input[i]){
      case '0' : stringbinary += "0000"; break;
      case '1' : stringbinary += "0001"; break;
      case '2' : stringbinary += "0010"; break;
      case '3' : stringbinary += "0011"; break;
      case '4' : stringbinary += "0100"; break;
      case '5' : stringbinary += "0101"; break;
      case '6' : stringbinary += "0110"; break;
      case '7' : stringbinary += "0111"; break;
      case '8' : stringbinary += "1000"; break;
      case '9' : stringbinary += "1001"; break;
      case 'a' : stringbinary += "1010"; break;
      case 'b' : stringbinary += "1011"; break;
      case 'c' : stringbinary += "1100"; break;
      case 'd' : stringbinary += "1101"; break;
      case 'e' : stringbinary += "1110"; break;
      case 'f' : stringbinary += "1111"; break;
      default  : stringbinary += ""; break;
    }
    i++;     
  }

  string container;
  stringbinary = stringbinary.substr(0,n);
  string dataFile;

  Tree * Temp = T;
  i =0;
  while(i<=stringbinary.size()){
    if ((Temp->L == NULL) && (Temp->R == NULL)){
      dataFile += Temp->s;
      Temp = T;
    }else{
      if (stringbinary[i] == '0'){
        Temp = Temp->L;
      } else {
        Temp = Temp->R;
      }
      i++;
    }
  }
  return dataFile;
}
string asciitoHexa(string  str_ascii){
  
  string hasil;
  int i = 0;

  while (i < str_ascii.length()) {
    stringstream hexa;
    if (((int)str_ascii[i] >= 0) && ((int)str_ascii[i] < 16)){
      hexa << '0' << hex << (int)str_ascii[i]; //ascii code dengan nilai hexa 1 digit
    } else if ((int)str_ascii[i] < 0){
      hexa << hex << (int)str_ascii[i] + 256; // extended ascii code , nilainya negatif
    } else {
      hexa << hex << (int)str_ascii[i];
    }
    hasil += hexa.str();
    i++;
  }

  return hasil;
}
int filesize(const char* filename){
    ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}