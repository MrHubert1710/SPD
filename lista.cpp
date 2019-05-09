#include "lista.hpp"

ostream & operator << (ostream &out, const vector<zadanie> &lista){

    #if !OSTREAM_LISTA_DEBUG
    uint16_t item=0;
    #endif // !OSTREAM_LISTA_DEBUG
    for(auto &tmp : lista){
    #if OSTREAM_LISTA_DEBUG
        out << "ID: "<<setw(3)<< tmp.ID << "| R: " <<setw(4)<< tmp.r << " P: " <<setw(4)<< tmp.p  << " Q: " <<setw(4)<< tmp.q << endl;
    #else
        if(item==10){
            out<<endl;
            item=0;
        }
        out <<setw(3)<< tmp.ID << " ";
        ++item;
    #endif // OSTREAM_LISTA_DEBUG

    }
    #if !OSTREAM_LISTA_DEBUG
        out << endl;
    #endif // !OSTREAM_LISTA_DEBUG
    return out;
}

uint8_t lista_zadan::Wczytaj_z_pliku(string plik){
    ifstream dane(plik);
    zadanie tmp;
    uint16_t k;
    uint16_t w;
    lista_do_posortowania.clear();
    //Check  ////////
    if((dane.rdstate() & ifstream::failbit)!=0){
        cerr << "Nie mozna otworzyc " <<plik<<" !"<<endl;
        return 1;
    }
    if(dane.eof()){
        cerr << "Plik pusty!"<<endl;
        return 2;
    }
    /////////////////

    dane>>w>>k;

    //Check  ////////
    if(dane.eof()){
        cerr << "Plik niekompletny!"<<endl;
        return 3;
    }
    if(k!=3){
        cerr << "Niepoprawna liczba kolumn!"<<endl;
        return 4;
    }
    if(w<=0){
        cerr << "Niepoprawna liczba wierszy!"<<endl;
        return 5;
    }
    /////////////////

    for(int i = 0; i<w ; ++i){
        dane>>tmp.r>>tmp.p>>tmp.q;
        tmp.ID=i+1;
        //Check /////////
        if((i+1!=w)&&(dane.eof())){
            cerr << "Niespodziewany koniec pliku!"<<endl;
            return 6;
        }
        /////////////////
        lista_do_posortowania.push_back(tmp);
    }
    return 0;
}

void lista_zadan::pokazWejscie(ostream &out){
    out<<lista_do_posortowania;
    return;
}
void lista_zadan::pokazWyjscie(ostream &out){
    out<<lista_rozwiazan;
    return;
}
void lista_zadan::pokazCmax(ostream &out){
    if(Cmax!=0)
        out<<"Cmax wynosi: "<<Cmax;
    return;
}
void lista_zadan::Schrange(){
    KolejkaP Nn(false);
    KolejkaP Ng(true);
    for( auto &tmp : lista_do_posortowania){
        Nn.push(tmp);
    }
    zadanie j;
    uint32_t t = Nn.peek().r;
    lista_rozwiazan.clear();
    Cmax=0;
    while((!Ng.isEmpty())||(!Nn.isEmpty())){
        while((!Nn.isEmpty())&&((Nn.peek().r)<=t)){
            j=Nn.pop();
            #if SCHRANGE_DEBUG
                cout<<"[SCHRANGE_DEBUG] Przenosze zadanie "<<(j.ID)<<" do zadan gotowych"<<endl;
            #endif // SCHRANGE_DEBUG
            Ng.push(j);
        }
        if(Ng.isEmpty()){
            t=Nn.peek().r;
            #if SCHRANGE_DEBUG
                cout<<"[SCHRANGE_DEBUG] Zwiekszam czas t = "<<t<<endl;
            #endif // SCHRANGE_DEBUG
        }else{
            j=Ng.pop();
            #if SCHRANGE_DEBUG
                cout<<"[SCHRANGE_DEBUG] Przenosze zadanie "<<(j.ID)<<" do rozwiazania"<<endl;
            #endif // SCHRANGE_DEBUG
            lista_rozwiazan.push_back(j);
            t+=(j.p);
        }
    }
}

uint32_t lista_zadan::Schrange_PMTN(){
    KolejkaP Nn(false);
    KolejkaP Ng(true);
    for( auto &tmp : lista_do_posortowania){
        Nn.push(tmp);
    }
    zadanie j;
    Cmax = 0;
    uint32_t t = 0;
    zadanie l;
    lista_rozwiazan.clear();
    while((!Ng.isEmpty())||(!Nn.isEmpty())){
        while((!Nn.isEmpty())&&((Nn.peek().r)<=t)){
            j=Nn.pop();
            #if SCHRANGE_PMTN_DEBUG
                cout<<"[SCHRANGE_PMTN_DEBUG] Przenosze zadanie "<<(j.ID)<<" do zadan gotowych"<<endl;
            #endif // SCHRANGE_PMTN_DEBUG
            Ng.push(j);

            if((j.q)>(l.q)){
                #if SCHRANGE_PMTN_DEBUG
                    cout<<"[SCHRANGE_PMTN_DEBUG] Czas dostarczenia zad. "<<(j.ID)<<" jest wiekszy niz w zad. "<<(l.ID)<<endl;
                #endif // SCHRANGE_PMTN_DEBUG
                l.p = t - j.r;
                t = j.r;
                if(l.p>0){
                    #if SCHRANGE_PMTN_DEBUG
                        cout<<"[SCHRANGE_PMTN_DEBUG] Wracam zadanie "<<(l.ID) <<" do kolejki gotowych"<<endl;
                    #endif // SCHRANGE_PMTN_DEBUG
                    Ng.push(l);
                    lista_rozwiazan.pop_back();
                }
            }

        }
        if(Ng.isEmpty()){
            t=Nn.peek().r;
            #if SCHRANGE_PMTN_DEBUG
                cout<<"[SCHRANGE_PMTN_DEBUG] Zwiekszam czas t = "<<t<<endl;
            #endif // SCHRANGE_PMTN_DEBUG
        }else{
            j=Ng.pop();
            #if SCHRANGE_PMTN_DEBUG
                cout<<"[SCHRANGE_PMTN_DEBUG] Dodaje zadanie "<<(j.ID)<<" do Cmax"<<endl;
            #endif // SCHRANGE_PMTN_DEBUG
            lista_rozwiazan.push_back(j);
            t+=(j.p);
            l=j;
            if(t+(j.q)>Cmax)
                Cmax=t+(j.q);
        }
    }
    return 0;
}
void lista_zadan::policzCmax(){
    S.clear();
    C.clear();
    if(lista_rozwiazan.size()==0){
        return;
    }

    for(uint16_t i = 0; i<lista_rozwiazan.size(); ++i){
        if(i==0){
            S.push_back(lista_rozwiazan[i].r);
        }else{
            if(lista_rozwiazan[i].r>=(S.back()+lista_rozwiazan[i-1].p)){
                S.push_back(lista_rozwiazan[i].r);
            }else{
                S.push_back(S.back()+lista_rozwiazan[i-1].p);
            }
        }
        C.push_back(S.back()+lista_rozwiazan[i].p+lista_rozwiazan[i].q);
    }
    Cmax = *max_element(C.begin(),C.end());
}
