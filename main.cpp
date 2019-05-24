#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include "lista.hpp"
#include "kolejka.hpp"
using namespace std;

float timedifference_msec(struct timeval t0, struct timeval t1){
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

int main()
{
    string plik;
    lista_zadan lista;
    struct timeval start, stop;
    double czas=0;

    while(true){
        cout<< "Podaj nazwe pliku: ";
        cin>>plik;
        if(lista.Wczytaj_z_pliku(plik))
            break;
        gettimeofday(&start, NULL);
        lista.Schrage();
        gettimeofday(&stop, NULL);
        czas = timedifference_msec(start, stop);


        cout<<endl<<"Algorytm Schrage"<<endl<<endl<<"Czas wykonywania: "<< setprecision(6) << czas <<endl;
        lista.policzCmax();
        lista.pokazCmax(cout);
        cout<<endl;

        gettimeofday(&start, NULL);
        lista.startCarlier_new();
        gettimeofday(&stop, NULL);
        czas = timedifference_msec(start, stop);

        cout<<endl<<"Algorytm Carlier"<<endl<<endl<<"Czas wykonywania: "<< setprecision(6) << czas <<endl;
        lista.pokazCmax(cout<<endl);
        lista.policzCmax();
        lista.pokazCmax(cout<<endl);
        lista.pokazWyjscie(cout<<endl);
        cout<<endl<<endl;


    }
    return 0;
}
