#ifndef cl_h
#define cl_h

#include <cstddef>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream> 
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using  namespace std;

class Element{
	public :
		Element();
		Element(char c,int i);
		Element & operator=(const Element &);
		~Element();
		//ATTRIBUTES
		char ch; 		//the character
		int f; 			// frequency
		Element * next; // pointer to next elementm
};

class Tree{
	//ctor dll
	public :
		Tree();
		Tree(string sx,int fx);
		Tree(Tree * T1,Tree * T2);
		Tree & operator=(const Tree &);
		~Tree();
		string Print();
		bool Search(char c);
		string Encode(char c);
		//Attributes
		Tree * L;
		Tree * R;
		string s;
		int f;
};

class ListofTree{
	public:
		ListofTree();
		ListofTree(Tree * );
		ListofTree(ListofTree *);
		~ListofTree();
		//method
		void Add(ListofTree * Tx); //add
		void AddSort(ListofTree *Tx);
		//Attribute
		Tree * T;
		ListofTree * next;	
};


#endif
