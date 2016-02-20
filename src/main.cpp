#include "cl.h"
#include "proc.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <map>


using namespace std;

int main(){
	string S;
	string filename = "A.pdf";
	cout << endl << "File size before compressed = " << filesize(filename.c_str()) << endl;
	map<const char,string> huffmanMap;
	map<const char,string>::iterator it;
	pair<map<const char,string>::iterator,bool> ret;

	clock_t start = clock();
	//time(&start);
	BacaFile(S,filename); //cout << S << endl;
	
	Tree T=crhuffman(S);

	int i;
	string Sx = T.Print(); //cout << Sx << endl;

	string F=""; 
	string temp;
	int x=S.length();

	for(i=0;i<x;i++){
		string temp;
		it = huffmanMap.find(S[i]);
  		if (it != huffmanMap.end()){
  			F += it->second;
  		} else {
  			temp = T.Encode(S[i]);
  			huffmanMap.insert(pair<const char,string>(S[i],temp));
  			F += temp;
  		}
	} 

	Tree * Tx = new Tree();
	Tx->s=T.s;
	Tx->f=T.f;
	Tx->L=T.L;
	Tx->R=T.R;

	//string * huffman = new string[16];
	//LoadStringHuffman(Tx,huffman);

	//cout << "Load Huffman done!" << endl;

	//for(i=0;i<x;i++){
		//F=F+Encoding(S[i],huffman); //cout << S[i] << " " << Encoding(S[i],huffman) << endl;
	//} //cout << "okee" << endl; 

	x=F.length();
	while(F.length()%4!=0){
		F=F+'0';
	}
	
	TulisKeFile3("Zipper1.txt",F);
	
	clock_t finish = clock();
	//time(&finish); 
	
	double Time = finish - start;
	cout << endl << "Compressed in " << ((float)Time)/CLOCKS_PER_SEC << " seconds" << endl;

	string N1 = "Zipper1.txt";
	string Sn;
	cout << endl << "File size after compressed = " << filesize(N1.c_str()) << endl;

	start = clock();
	BacaFile(Sn,N1); //cout << endl << Sn << endl;

	string hexaFromASCII = asciitoHexa(Sn); //cout << hexaFromASCII << endl;

	string NN =Extract(hexaFromASCII,x,Tx); //cout << endl << NN << endl;
	
	TulisKeFile2("A2.pdf",NN);
	
	finish = clock();
	
	Time = finish - start;
	cout << endl << "Extracted in " << ((float)Time)/CLOCKS_PER_SEC << " seconds" << endl;
	

	return 0;
}
