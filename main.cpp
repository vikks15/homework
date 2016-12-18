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

char* InText(char buff[], int & size)
{
	char ch = ' ';
	char delims[] = " ,";
	int i=0;

	while(ch!=26) // пока не введено ctrl+z
	{
		ch = _getch();

		if(ch>='A' && ch<='Z' || ch>='a' && ch<='z' || ch==' ' || ch=='.') //ввод только латинских букв
		{
			cout<<ch;
			buff[i]=ch;
			i++;
			size++;
		}
		else if(ch=='\b') // удаление символа из консоли и буфера
		{
			cout<<"\b \b"; 
			i--;
			size--;
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

Sentence GetSentence(char* token)
{
	Sentence s;
	s.words = new Word[];

	int i = 0, kol = 0;

	char *nexttoken = token;
	char *sen=" ";

	while(sen!=NULL)
	{

		sen = strtok_s(nexttoken," ",&nexttoken);
		if(sen==NULL) break;
		s.words[i] = GetWords(sen);
		i++;
	}
	s.size = i;
	return s;
}

Text GetText(char buff[], int &buffsize)
{

	Text t;
	InText(buff, buffsize);
	int i = 0;

	char *nexttoken=buff, *token = " ";
	t.sentence = new Sentence[]; 

	while(token!=NULL)
	{
		token = strtok_s(nexttoken,".",&nexttoken);
		if(token==NULL) break;
		t.sentence[i] = GetSentence(token);
		i++;
	}
	t.size=i;

	return t;
}


int main() {

	int buffsize=0;
	char buff[1000];

	Text T = GetText(buff,buffsize);
	cout<<endl<<"buffsize"<<buffsize<<endl;
	cout<<"Tsize"<<T.size<<endl;
	cout<<"sensize"<<T.sentence[0].size<<endl;

	for(int i = 0; i<T.size; i++)
	{
		for (int j = 0; j<T.sentence[i].size; j++)
		{
			cout<<T.sentence[i].words[j].symb;
		}
	}

	return 0;

}