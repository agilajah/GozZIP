#ifndef proc_h
#define proc_h

#include "cl.h"

Tree crhuffman(string S);
void TulisKeFile();
void BacaFile(string &input,string & filename);
string ReadFileType1(string filename);
void TulisKeFile(string const &namafile, string const &str);
void TulisKeFile2(string namafile, string str);
void TulisKeFile3(string const &namafile, string const &str);
string Bin_to_Hex(string const &temp2);
string itos(int i);
string Extract(string input, int n, Tree * T);
string asciitoHexa(string  str_ascii);
int filesize(const char* filename);

#endif


//harus udah ada start dulu
