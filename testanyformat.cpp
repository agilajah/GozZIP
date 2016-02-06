/*----------------------------------------------------------------
 *  Author:        Febi Agil Ifdillah
 *  Written:       6/2/2016
 *  Last updated:  6/2/2016
 *  Description	:  File ini adalah ujicoba pembacaan beragam file. Program ini akan menghasilkan file baru yang bernama 
 *		   1 + ekstensi, misalnya ekstensi = '.mp4'. Jika file yang Anda input adalah test1.mp4, maka file yang dihasilkan
 *		   bernama 1.mp4.
 *	   	   Program hanya bisa berjalan di linux karena menggunakan sys/sat dan sys.types.
 *
 *  Compilation:   g++ -o testanyformat testanyformat.cpp
 *  Execution:     ./testanyformat YourFile
 *	
    * Character    What it means
    *    1               "d" if a directory, "-" if a file
    *    2               "r" if file is readable to user, "-" if not
    *    3               "w" if file is writable to user, "-" if not
    *    4               "x" if file is executable to user, "-" if not
    *    5-7             same as 2-4, with reference to group
    *    8-10            same as 2-4, with reference to everyone on eniac
 *	Example	:	  
 *
 *  % ./testanyformat test1.mp4
 *	Tuliskan nama file : 
 *	test1.mp4  
 *	ini nama file ke tiga sebelum pemanggilan tulis : 
 *	1.txt
 *  Information for test1.mp4
 *	---------------------
 *	File Size : 13375380
 *	Number of Links : 1
 *	File inode : 1495552
 *	File Permission : 	-rw-rw-r--
 *
 *	The file is not a symbolic link
 *	ini mode setelah diubah
 *	Ini nama file ke 3 : 1.txt
 *	Nama file adalah : test1.mp4
 *
 *----------------------------------------------------------------*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <cerrno>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;
	ofstream outputtest;
	ofstream output2;
	string filename;
	string ekstensi;
	string filename2;
	string filename3;
	string simpan;
	struct stat fileStat;


void TulisKeFile() {

	// input file
	ifstream fin(filename.c_str());  // default mode ios::in
   	if (!fin) {
      cerr << "error: open file for input failed!" << endl;
      abort();
    }

    char ch;
    while (fin.get(ch)) {  // till end-of-file
      //cout << ch;
      simpan += ch;
	  outputtest << ch;
	  output2 << ch;
    } 
    /*

    	system("chmod 700 file.txt"); // untuk mengubah file permission di unix
		to cross platform : http://stackoverflow.com/questions/592448/c-how-to-set-file-permissions-cross-platform
    */
	
    fin.close();
    outputtest.close();
    output2.close();
	
}

int main(int argc, char **argv) {
	//Membuat file dan mengubah permission
	cout << "Tuliskan nama file : " << endl;
	getline(cin, filename);
	size_t pos = filename.find(".");  //mencari posisi titik dalam nama file untuk mendapatkan ekstensi
	ekstensi = filename.substr (pos); //mengcopy mulai titi sampai dengan akhir 
	filename2 =  '1' + ekstensi;
	filename3 =  "1.txt";
	cout << " ini nama file ke tiga sebelum pemanggilan tulis : \n " << filename3 << endl;
	outputtest.open(filename2.c_str(), ios::out | ios::trunc); // opening file
    output2.open(filename3.c_str(), ios::out | ios::trunc);

    //mode sebelum diubah

    if(stat(argv[1],&fileStat) < 0) {   
        return 1;
    }
    cout << "Information for " << argv[1] << endl;
    cout << "---------------------" << endl;
    cout << "File Size : " << fileStat.st_size << endl;
    cout << "Number of Links : " << fileStat.st_nlink << endl;
    cout << "File inode : " << fileStat.st_ino << endl;

    cout << "File Permission : \t";
    
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

    printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");


    //sesudah diubah
    cout << "ini mode setelah diubah" << endl;
    char mode[] = "0777";
    int i;
    i = strtol(mode, 0, 8);
    if (chmod (filename2.c_str(),i) < 0)
    {
        fprintf(stderr, "%s: error in chmod(%s, %s) - %d (%s)\n",
                argv[0], filename2.c_str(), mode, errno, strerror(errno));
        exit(1);
    }

    //proses input
	cout << " Ini nama file ke 3 : " << filename3 << endl;
	TulisKeFile();
	cout << "Nama file adalah : " << filename << endl;
	return 0;
}
