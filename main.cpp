#include "libr.h"

int main()
{

	system("chcp 1251 >nul");
	char *buff = new char[1000];
	Text T;


	while(true){

		switch(menu())
		{
		case 1:
			{
				T = GetText(buff);
				cout << "\nВсего предложений " << T.size << endl;
				cout<<T;
				cout<<endl;
				break;
			}
		case 2: 
			{
				var12(T);
				break;
			}
		case 3: return 0;

		}

	}

	system("pause");
	delete [] buff;

	return 0;
}

