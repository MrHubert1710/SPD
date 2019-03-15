#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

int main()
{
    srand( time( NULL ) );
    stringstream nazwaPliku;
    int a, b, c;
    string buffer;

    cout<<"Podaj nazwe pliku: "<<endl;
    cin>>buffer;

    

    cout<<"Ile zadan?"<<endl;
    cin>>a;
    cout<<"Ile maszyn?"<<endl;
    cin>>b;
    cout<<"Ile plikow? "<<endl;
    cin>>c;

    for (int i = 0; i < c; i++)
    {
        nazwaPliku.str("");
        nazwaPliku<<buffer;
        nazwaPliku<<i;

    ofstream plik(nazwaPliku.str());

    plik<<a;
    plik<<" ";
    plik<<b;
    plik<<'\n';

    for(int i = 0; i < a ; i++)
    {
        for(int j = 0; j < b ; j++)
        {
            plik<<(rand() % 16) + 1;
            plik<<" ";
        }
        plik<<'\n';
    }

    }

    return 0;
}