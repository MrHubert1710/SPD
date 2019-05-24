#ifndef __LISTA_HPP
#define __LISTA_HPP

#include "debug.hpp"
#include "kolejka.hpp"

#ifndef OSTREAM_LISTA_DEBUG
#define OSTREAM_LISTA_DEBUG 1
#endif // OSTREAM_LISTA_DEBUG

#ifndef SCHRAGE_DEBUG
#define SCHRAGE_DEBUG 1
#endif // SCHRAGE_DEBUG

#ifndef CARLIER_DEBUG
#define CARLIER_DEBUG 1
#endif // CARLIER_DEBUG

#ifndef SCHRAGE_PMTN_DEBUG
#define SCHRAGE_PMTN_DEBUG 1
#endif // SCHRAGE_PMTN_DEBUG

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;


ostream & operator << (ostream &out, const vector<zadanie> &lista);
bool check_r(zadanie a, zadanie b);
bool check_p(zadanie a, zadanie b);
bool check_q(zadanie a, zadanie b);

class lista_zadan{
private:
    vector<zadanie> lista_do_posortowania;
    uint32_t Cmax;
    vector<uint32_t> S;
    vector<uint32_t> C;
    uint32_t U=0;
    uint32_t UB=0xFFFFFFFF;
    uint32_t LB=0;
    void Carlier();

public:
    vector<zadanie> lista_rozwiazan;
    uint8_t  Wczytaj_z_pliku(string plik);
    void pokazWejscie(ostream &out);
    void pokazWyjscie(ostream &out);
    void policzCmax();
    uint16_t policzCmax(vector<zadanie> &tmp);
    void pokazCmax(ostream &out);
    void Schrage();
    uint32_t Schrage_PMTN();
    void startCarlier();

};


#endif // __LISTA_HPP
