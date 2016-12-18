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

	while(ch!=26) // ���� �� ������� ctrl+z
	{
		ch = _getch();

		if(ch>='A' && ch<='Z' || ch>='a' && ch<='z' || ch==' ' || ch=='.') //���� ������ ��������� ����
		{
			cout<<ch;
			buff[i]=ch;
			i++;
			size++;
		}
		else if(ch=='\b') // �������� ������� �� ������� � ������
		{
			cout<<"\b \b"; 
			i--;
			size--;
		}
		else if(ch!=26) cout<<"\a"; //bell

	}

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

	for(int i = 0; i<T.size; i++)
	{
		cout<<T.sentence[i].words[i].symb;
	}

	cout<<endl<<buffsize;

	/*for(int i =0; i<size; i++){
	cout<<buff[i];
	*/

}