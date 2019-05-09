#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include "lista.hpp"
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
        //lista.pokazWejscie(cout);
        gettimeofday(&start, NULL);
        lista.Schrange();
        gettimeofday(&stop, NULL);
        czas = timedifference_msec(start, stop);


        cout<<endl<<"Algorytm Schrange"<<endl<<endl<<"Czas wykonywania: "<< setprecision(6) << czas <<endl;
        //lista.pokazWyjscie(cout<<endl);
        lista.pokazCmax(cout);
        lista.policzCmax();
        lista.pokazCmax(cout);
        cout<<endl;



        gettimeofday(&start, NULL);
        lista.Schrange_PMTN();
        gettimeofday(&stop, NULL);
        czas = timedifference_msec(start, stop);

        cout<<endl<<"Algorytm Schrange z przerwaniami"<<endl<<endl<<"Czas wykonywania: "<< setprecision(6) << czas <<endl;
        //lista.pokazWyjscie(cout<<endl);
        lista.pokazCmax(cout);
        lista.policzCmax();
        lista.pokazCmax(cout<<endl);
        cout<<endl<<endl;



    }
    return 0;
}
