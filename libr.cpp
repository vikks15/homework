#ifndef libr
#define libr

#include <iostream>
#include <conio.h>
#include <string.h>

using namespace std;

int menu()
{
	int a;
	cout<<"1 - Ввод текста"<<endl;
	cout<<"2 - Выполнение варианта"<<endl;
	cout<<"3 - Выход"<<endl;

	cin>>a;
	cin.clear();
	return a;
}

struct Word
{
	char *symb;
	bool flag; //для удаления слов
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

	//перегрузка <<
	friend void operator<<(ostream &os, Text &t)
	{
		int kol=0;
		for(int i = 0; i<t.size; i++)
		{
			cout<<"Предложение "<<i<<": ";
			for(int j=0; j<t.sentence[i].size; j++)
			{
				kol++;
				if(t.sentence[i].words[j].flag==true) //для var12
				{
					cout<<t.sentence[i].words[j].symb;
					if((j+1)!=t.sentence[i].size) cout<<" "; //вывод пробела между словами
				}				
			}

			cout<<'.'<<" Слов: "<<t.sentence[i].size<<endl;
		}
	}
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
	w.flag=true; 
	return w;
}

Sentence GetSentence(char* buff)
{
	Sentence s;

	int i = 0, kol = 0;

	char *nexttoken, *token = buff;
	const char delims[] = " ";

	s.size=1;
	for(int i=1; i<strlen(buff); i++) // определение количества слов по пробелам
	{
		if(buff[i]==' ' && buff[i-1]!=' ') s.size++;
	}

	s.words = new Word[s.size];//выделение памяти под массив слов

	token = strtok_s(token, delims, &nexttoken);
	while(token != NULL)
	{
		s.words[i] = GetWords(token);
		i++;
		token = strtok_s(NULL, delims, &nexttoken);
	}

	return s;
}

Text GetText(char *buff)
{

	Text t;
	InText(buff); //считавание символов, проверка правильности ввода
	int i = 0;

	char *nexttoken, *token = buff;
	const char delims[] = ".";

	t.size=0;
	for(int i=0; i<strlen(buff); i++) //определение количества предложений в тексте
	{
		if(buff[i]=='.')
			t.size++;
	}

	t.sentence = new Sentence[t.size]; //выделение памяти под массив предложений
	token = strtok_s(token, delims, &nexttoken);

	while(token != NULL)
	{
		t.sentence[i] = GetSentence(token);
		i++;
		token = strtok_s(NULL, delims, &nexttoken);
	}

	return t;
}

void var12(Text &t) //Вариант 12
{
	int maxlen = 0, word1len = 0, word2len = 0, j = 0;

	for(int i = 0; i<t.size; i++)
	{
		Word last = t.sentence[i].words[(t.sentence[i].size)-1];
		t.sentence[i].words[(t.sentence[i].size)-1].flag=false;

		for(j = 0; j<(t.sentence[i].size)-2; j++)
		{
			word1len = strlen(t.sentence[i].words[j].symb);
			word2len = strlen(t.sentence[i].words[j+1].symb);

			if (t.sentence[i].words[j].symb[word1len-1] == ',') word1len--;
			if (t.sentence[i].words[j+1].symb[word2len-1] == ',') word2len--;

			if(word1len>maxlen && (strcmp(t.sentence[i].words[j].symb, last.symb))!=0) maxlen=word1len;

			else if (word2len>maxlen && strcmp(t.sentence[i].words[j+1].symb, last.symb)!=0) maxlen=word2len;
		}

		if(strcmp(t.sentence[i].words[j].symb, last.symb)==0 || strlen(t.sentence[i].words[j].symb)<maxlen) t.sentence[i].words[j].flag=false;
		
		maxlen=0;
	}
	cout<<t;
}

#endif
