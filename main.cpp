#include <iostream>
#include <conio.h>
#include <string.h>

using namespace std;


struct Word
{
	char *symb;
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
};

char* InText(char *buff)
{
	char ch = ' ';
	int i=0;

	while(ch!=26) // пока не введено ctrl+z
	{
		ch = _getch();

		bool isLowerLatin = ch >= 'a' && ch <= 'z';
		bool isUpperLatin = ch >= 'A' && ch <= 'Z';
		bool isBreakPoint = ch == ' ' || ch == '.' || ch == ',';

		if (isLowerLatin || isUpperLatin || isBreakPoint)
		{
			cout << ch;
			buff[i]=ch;
			i++;
		}
		else if(ch=='\b') // удаление символа из консоли и буфера
		{
			cout<<"\b \b"; 
			i--;
		}
		else if(ch!=26) cout<<"\a"; //bell

	}

	buff[i]='\0'; // окончание ввода текста

	return buff;
}

Word GetWords(char *tok)
{
	Word w;
	w.symb = tok;
	return w;
}

Sentence GetSentence(char* buff)
{
	Sentence s;

	int i = 0, kol = 0;

	char *nexttoken, *token = buff;
	const char delims[] = " ";

	// TODO: Init for s.size

	s.words = new Word[s.size];

	token = strtok_s(token, delims, &nexttoken);
	while(token != NULL)
	{
		s.words[i] = GetWords(token);
		i++;
		token = strtok_s(NULL, delims, &nexttoken);
	}
	s.size = i;
	
	return s;
}

Text GetText(char *buff)
{

	Text t;
	InText(buff);
	int i = 0;

	char *nexttoken, *token = buff;
	const char delims[] = ".";

	// TODO: Init for t.size

	t.sentence = new Sentence[t.size]; 

	token = strtok_s(token, delims, &nexttoken);
	while(token != NULL)
	{
		t.sentence[i] = GetSentence(token);
		i++;
		token = strtok_s(NULL, delims, &nexttoken);
	}
	t.size = i;

	return t;
}


int main() 
{
	char *buff = new char[1024];
	Text T = GetText(buff);
	cout << "\nTsize " << T.size << endl;
	cout << "sensize " << T.sentence[0].size << endl;
	system("pause");
	delete [] buff;
}