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
bool check_r(zadanie a, zadanie b){
    return a.r<b.r;
}
bool check_p(zadanie a, zadanie b){
    return a.p<b.p;
}
bool check_q(zadanie a, zadanie b){
    return a.q<b.q;
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
void lista_zadan::Schrage(){
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
            #if SCHRAGE_DEBUG
                cout<<"[SCHRAGE_DEBUG] Przenosze zadanie "<<(j.ID)<<" do zadan gotowych"<<endl;
            #endif // SCHRAGE_DEBUG
            Ng.push(j);
        }
        if(Ng.isEmpty()){
            t=Nn.peek().r;
            #if SCHRAGE_DEBUG
                cout<<"[SCHRAGE_DEBUG] Zwiekszam czas t = "<<t<<endl;
            #endif // SCHRAGE_DEBUG
        }else{
            j=Ng.pop();
            #if SCHRAGE_DEBUG
                cout<<"[SCHRAGE_DEBUG] Przenosze zadanie "<<(j.ID)<<" do rozwiazania"<<endl;
            #endif // SCHRAGE_DEBUG
            lista_rozwiazan.push_back(j);
            t+=(j.p);
        }
    }
}

uint32_t lista_zadan::Schrage_PMTN(){
    KolejkaP Nn(false);
    KolejkaP Ng(true);
    for( auto &tmp : lista_do_posortowania){
        Nn.push(tmp);
    }
    zadanie j;
    Cmax = 0;
    uint32_t t = 0;
    zadanie l;
    //lista_rozwiazan.clear();
    while((!Ng.isEmpty())||(!Nn.isEmpty())){
        while((!Nn.isEmpty())&&((Nn.peek().r)<=t)){
            j=Nn.pop();
            #if SCHRAGE_PMTN_DEBUG
                cout<<"[SCHRAGE_PMTN_DEBUG] Przenosze zadanie "<<(j.ID)<<" do zadan gotowych"<<endl;
            #endif // SCHRAGE_PMTN_DEBUG
            Ng.push(j);

            if((j.q)>(l.q)){
                #if SCHRAGE_PMTN_DEBUG
                    cout<<"[SCHRAGE_PMTN_DEBUG] Czas dostarczenia zad. "<<(j.ID)<<" jest wiekszy niz w zad. "<<(l.ID)<<endl;
                #endif // SCHRAGE_PMTN_DEBUG
                l.p = t - j.r;
                t = j.r;
                if(l.p>0){
                    #if SCHRAGE_PMTN_DEBUG
                        cout<<"[SCHRAGE_PMTN_DEBUG] Wracam zadanie "<<(l.ID) <<" do kolejki gotowych"<<endl;
                    #endif // SCHRAGE_PMTN_DEBUG
                    Ng.push(l);
                    //lista_rozwiazan.pop_back();
                }
            }

        }
        if(Ng.isEmpty()){
            t=Nn.peek().r;
            #if SCHRAGE_PMTN_DEBUG
                cout<<"[SCHRAGE_PMTN_DEBUG] Zwiekszam czas t = "<<t<<endl;
            #endif // SCHRAGE_PMTN_DEBUG
        }else{
            j=Ng.pop();
            #if SCHRAGE_PMTN_DEBUG
                cout<<"[SCHRAGE_PMTN_DEBUG] Dodaje zadanie "<<(j.ID)<<" do Cmax"<<endl;
            #endif // SCHRAGE_PMTN_DEBUG
            //lista_rozwiazan.push_back(j);
            t+=(j.p);
            l=j;
            if(t+(j.q)>Cmax)
                Cmax=t+(j.q);
        }
    }
    return Cmax;
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

uint16_t lista_zadan::policzCmax(vector<zadanie> &tmp){

    vector<uint32_t> St;
    vector<uint32_t> Ct;
    St.clear();
    Ct.clear();
    if(tmp.size()==0){
        return 0;
    }

    for(uint16_t i = 0; i<tmp.size(); ++i){
        if(i==0){
            St.push_back(tmp[i].r);
        }else{
            if(tmp[i].r>=(St.back()+tmp[i-1].p)){
                St.push_back(tmp[i].r);
            }else{
                St.push_back(St.back()+tmp[i-1].p);
            }
        }
        Ct.push_back(St.back()+tmp[i].p+tmp[i].q);
    }
    return *max_element(Ct.begin(),Ct.end());
}
void lista_zadan::startCarlier(){
    U=0;
    LB=0;
    UB=0xFFFFFFFF;
    Carlier();

}

void lista_zadan::Carlier(){
    vector<zadanie> K;
    uint32_t a,b,c;
    uint32_t tmp=-1;

    Schrage();
    policzCmax();
    U=Cmax;
    if(U<UB){
        UB=U;
        kopia_rozwiazan=lista_rozwiazan;
        //cout<<kopia_rozwiazan;
        lista_do_posortowania=kopia_rozwiazan;
    }

    //B
    b=0xFFFFFFFF;
    for(int j=lista_do_posortowania.size()-1;j>=0;--j){
        if(Cmax == C[j]){
            b=j;
            break;
        }
    }
    #if CARLIER_DEBUG
        cout<<"[CARLIER_DEBUG] Znalezione b = "<<b<<endl;
    #endif // CARLIER_DEBUG
    //A
    a=0xFFFFFFFF;
    if(b!=0xFFFFFFFF){
    for(int j=0; j<lista_do_posortowania.size(); ++j){
        tmp=0;
        for(int s=j; s<=b; ++s){
            tmp+=lista_do_posortowania[s].p;
        }
        if(Cmax==(lista_do_posortowania[j].r+tmp+lista_do_posortowania[b].q)){
            a=j;
            break;
        }
    }
    }
    #if CARLIER_DEBUG
        cout<<"[CARLIER_DEBUG] Znalezione a = "<<a<<endl;
    #endif // CARLIER_DEBUG
    //C
    c=0xFFFFFFFF;
    if(a!=0xFFFFFFFF && b!=0xFFFFFFFF){
    for(int j=b;j>=a;--j){
        if(lista_do_posortowania[j].q < lista_do_posortowania[b].q){
            c=j;
            break;
        }
    }
    }
    #if CARLIER_DEBUG
        cout<<"[CARLIER_DEBUG] Znalezione c = "<<c<<endl;
    #endif // CARLIER_DEBUG



    if(c==0xFFFFFFFF){
        //cout<<"Kopia:"<<endl<<kopia_rozwiazan<<endl;
        //lista_rozwiazan=lista_do_posortowania;
        //lista_rozwiazan=kopia_rozwiazan;
        return;
    }

    for(int j=c+1;j<=b;++j){
        K.push_back(lista_do_posortowania[j]);
    }

    uint32_t rk = max_element(K.begin(),K.end(),check_r)->r;
    uint32_t qk = min_element(K.begin(),K.end(),check_q)->q;
    uint32_t pk=0;
    for(int j = 0; j<K.size(); ++j){
        pk+=K[j].p;
    }

    //R

    if(lista_do_posortowania[c].r<rk+pk)
        lista_do_posortowania[c].r = rk+pk;

    LB = Schrage_PMTN();
    if(rk+pk+qk>LB){
        LB=rk+pk+qk;
    }
    K.insert(K.begin(),lista_do_posortowania[c]);
    rk = max_element(K.begin(),K.end(),check_r)->r;
    qk = min_element(K.begin(),K.end(),check_q)->q;
    pk=0;
    for(int j = 0; j<K.size(); ++j){
        pk+=K[j].p;
    }

    if(rk+pk+qk>LB){
        LB=rk+pk+qk;
    }
    K.erase(K.begin());
    rk = max_element(K.begin(),K.end(),check_r)->r;
    qk = min_element(K.begin(),K.end(),check_q)->q;
    pk=0;
    for(int j = 0; j<K.size(); ++j){
        pk+=K[j].p;
    }


    if(LB<UB){
        Carlier();
    }
    lista_do_posortowania[c].r = kopia_rozwiazan[c].r;

    //Q
    if(lista_do_posortowania[c].q<qk+pk)
        lista_do_posortowania[c].q = qk+pk;
    LB = Schrage_PMTN();
    if(rk+pk+qk>LB){
        LB=rk+pk+qk;
    }
    K.insert(K.begin(),lista_do_posortowania[c]);
    rk = max_element(K.begin(),K.end(),check_r)->r;
    qk = min_element(K.begin(),K.end(),check_q)->q;
    pk=0;
    for(int j = 0; j<K.size(); ++j){
        pk+=K[j].p;
    }
    if(rk+pk+qk>LB){
        LB=rk+pk+qk;
    }
    K.erase(K.begin());
    if(LB<UB){
        Carlier();
    }
    lista_do_posortowania[c].q = kopia_rozwiazan[c].q;
}
