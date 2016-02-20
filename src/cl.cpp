#include "cl.h"

Element::Element(){
	ch = 'X';
	f = 0;
	next = NULL;	
}
Element::Element(char c,int i){
	ch = c;
	f = i;
	next = NULL;
}

Element::~Element(){
	delete next;	
}

Element & Element::operator=(const Element & E2){
	ch = E2.ch;
	f = E2.f;
	next = E2.next;
	return *this;
}

Tree::Tree(){
	L = NULL;
	R = NULL;
	s = "X";
	f = 0;
}

Tree::Tree(string sx,int fx){
	L = NULL;
	R = NULL;
	s = sx;
	f = fx;
}

Tree::Tree(Tree * T1,Tree * T2){
	if(T1->f > T2->f){
		L = T2;
		R = T1;
		f = T1->f + T2->f;
		stringstream ss;
		ss << T2->s << T1->s;
		s = ss.str();
	}
	else{
		L = T1;
		R = T2;
		f = T1->f + T2->f;
		stringstream ss;
		ss << T1->s << T2->s;
		s = ss.str();
	}
}

Tree & Tree::operator=(const Tree &T){
	L=T.L;
	R=T.R;
	s=T.s;
	f=T.f;
	return *this;
}

Tree::~Tree(){
	delete L;
	delete R;
}

string Tree::Print(){
	string Sx="";
	if(this == NULL){
		Sx = Sx+"()";
	}
	else{
		Sx=Sx+"("+s+L->Print()+R->Print()+")";
	}
	return Sx;
}

bool Tree::Search(char c){
	bool value = false;
	int i = 0;
	while(i<s.length() && value==false){
		if(s[i]==c){
			value = true;
		}
		else{
			i++;
		}
	}
	return value;
}

string Tree::Encode(char c){
	if(this==NULL){
		return "";
	}
	else{
		if(Search(c)==true){
			if(L==NULL && R==NULL){
				return "";
			}
			else if(L->Search(c)==true){
				return "0" + L->Encode(c);
			}
			else if(R->Search(c)==true){
				return "1" + R->Encode(c);
			}
		}	
	}
	
}

ListofTree::ListofTree(){
	Tree * T = new Tree();
	this->T = T;
	next = NULL;
}

ListofTree::ListofTree(Tree * T1){
	T = T1;
	next = NULL;
}

ListofTree::~ListofTree(){
	delete T;
	delete next;
}
ListofTree::ListofTree(ListofTree * L1){
	T = L1->T;
	next = L1->next;
}

void ListofTree::Add(ListofTree * Tx){
	next = Tx;
}

void ListofTree::AddSort(ListofTree * Tx){
	ListofTree * dummy = new ListofTree();
	ListofTree * dummyrec = new ListofTree();
	bool value=true;
	dummy=this;
	dummyrec=NULL;
	while(dummy!=NULL && Tx->T->f > dummy->T->f){
		dummyrec=dummy;
		dummy = dummy->next;
	}
	if(dummy==this){
		ListofTree *dummyl = new ListofTree();
		dummyl->next = dummy->next;
		dummyl->T = dummy->T;
		next=dummyl;
		T=Tx->T;
	}
	else if(dummy==NULL){
		dummyrec->next = Tx;
	}
	else{
		ListofTree * dummyl = new ListofTree();
		dummyl->next = NULL;
		dummyl->T = Tx->T;
		dummyrec->next=dummyl;
		dummyl->next=dummy;
	}
}
