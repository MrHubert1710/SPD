#ifndef __LISTA_HPP
#define __LISTA_HPP

#include "debug.hpp"
#include "kolejka.hpp"

#ifndef OSTREAM_LISTA_DEBUG
#define OSTREAM_LISTA_DEBUG 1
#endif // OSTREAM_LISTA_DEBUG

#ifndef SCHRANGE_DEBUG
#define SCHRANGE_DEBUG 1
#endif // SCHRANGE_DEBUG

#ifndef SCHRANGE_PMTN_DEBUG
#define SCHRANGE_PMTN_DEBUG 1
#endif // SCHRANGE_PMTN_DEBUG

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
    vector<zadanie> lista_rozwiazan;
    uint32_t Cmax;
    vector<uint32_t> S;
    vector<uint32_t> C;

public:
    uint8_t  Wczytaj_z_pliku(string plik);
    void pokazWejscie(ostream &out);
    void pokazWyjscie(ostream &out);
    void policzCmax();
    void pokazCmax(ostream &out);
    void Schrange();
    uint32_t Schrange_PMTN();

};


#endif // __LISTA_HPP
