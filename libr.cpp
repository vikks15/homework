#ifndef libr
#define libr

#include <iostream>
#include <conio.h>
#include <string.h>

using namespace std;

int menu()
{
	int a;
	cout<<"1 - ���� ������"<<endl;
	cout<<"2 - ���������� ��������"<<endl;
	cout<<"3 - �����"<<endl;

	cin>>a;
	cin.clear();
	return a;
}

struct Word
{
	char *symb;
	bool flag; //��� �������� ����
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

	//���������� <<
	friend void operator<<(ostream &os, Text &t)
	{
		int kol=0;
		for(int i = 0; i<t.size; i++)
		{
			cout<<"����������� "<<i<<": ";
			for(int j=0; j<t.sentence[i].size; j++)
			{
				kol++;
				if(t.sentence[i].words[j].flag==true) //��� var12
				{
					cout<<t.sentence[i].words[j].symb;
					if((j+1)!=t.sentence[i].size) cout<<" "; //����� ������� ����� �������
				}				
			}

			cout<<'.'<<" ����: "<<t.sentence[i].size<<endl;
		}
	}
};

char* InText(char *buff)
{
	char ch = ' ';
	int i=0;

	while(ch!=26) // ���� �� ������� ctrl+z
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
		else if(ch=='\b') // �������� ������� �� ������� � ������
		{
			cout<<"\b \b"; 
			i--;
		}
		else if(ch!=26) cout<<"\a"; //bell

	}

	buff[i]='\0'; // ��������� ����� ������

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
	for(int i=1; i<strlen(buff); i++) // ����������� ���������� ���� �� ��������
	{
		if(buff[i]==' ' && buff[i-1]!=' ') s.size++;
	}

	s.words = new Word[s.size];//��������� ������ ��� ������ ����

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
	InText(buff); //���������� ��������, �������� ������������ �����
	int i = 0;

	char *nexttoken, *token = buff;
	const char delims[] = ".";

	t.size=0;
	for(int i=0; i<strlen(buff); i++) //����������� ���������� ����������� � ������
	{
		if(buff[i]=='.')
			t.size++;
	}

	t.sentence = new Sentence[t.size]; //��������� ������ ��� ������ �����������
	token = strtok_s(token, delims, &nexttoken);

	while(token != NULL)
	{
		t.sentence[i] = GetSentence(token);
		i++;
		token = strtok_s(NULL, delims, &nexttoken);
	}

	return t;
}

void var12(Text &t) //������� 12
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
