#ifndef libr
#define libr

#include <iostream>
#include <conio.h>
#include <string.h>

using namespace std;

int menu();

struct Word
{
	char *symb;
	bool flag;
};

struct Sentence
{
	Word *words;
	int size;
};

struct Text
{
	Sentence *sentence;
	int size;

	friend void operator<<(ostream &os, Text &t); //перегрузка <<
	
};

char* InText(char *buff);


Word GetWords(char *tok);

Sentence GetSentence(char* buff);


Text GetText(char *buff);


void var12(Text &t);

#endif
