#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <deque>
#include <sys/time.h>
#define DEBUG_INPUT 0
#define DEBUG 0

using namespace std;


struct Zadanie{
  int ID;
  int Wartosc;
};
struct Wezel{
  int Kolumna;
  int Wiersz;
  int Wartosc;
};
struct ZadanieMaszyn{
  int ID;
  deque<int> Wartosc;
  deque<int> LC;
  deque<int> PC;
};

std::ostream& operator<<(std::ostream& ostr, const std::deque<ZadanieMaszyn>& list){

   #if DEBUG
    for(int w=0;w<list[0].Wartosc.size();++w){
      for (auto &i : list) {
        ostr << "Z:" <<i.ID<<"L:"<<i.LC[w]<<"W:"<<i.Wartosc[w]<<"P:"<<i.PC[w]<<"  ";
      }
      ostr<<endl;
    }
    return ostr;
  #else
    for (auto &i : list) {
      ostr << " " <<setw(3)<<i.ID;
    }
    ostr<<endl;
    return ostr;
  #endif // DEBUG
}
std::ostream& operator<<(std::ostream& ostr, const std::deque<Wezel>& list){
  for (auto &i : list) {
    ostr << "K: " <<setw(3)<<i.Kolumna<< " W: " <<setw(3)<<i.Wiersz<< " Wa: " <<setw(3)<<i.Wartosc<<endl;
  }
  return ostr;
}
void ClearZadM(ZadanieMaszyn &Src){
  Src.ID=-1;
  Src.Wartosc.clear();
  Src.LC.clear();
  Src.PC.clear();
  return;
}
bool operator>(const Zadanie& A,const Zadanie& B){
  return(A.Wartosc>B.Wartosc);
}
void UpdateC(deque<ZadanieMaszyn> &lista,int pos){
 if(lista.size()==0){
    return;
 }else if (lista.size()==1){
    for(int w=0;w<lista[0].Wartosc.size();++w){
      if(w==0){
        lista[0].PC[w]=(lista[0].Wartosc[w]);
      }else{
        lista[0].PC[w]=(lista[0].Wartosc[w]+lista[0].PC[w-1]);
      }
    }
    for(int w=(lista[0].Wartosc.size()-1);w>=0;--w){
      if(w==(lista[0].Wartosc.size()-1)){
        lista[0].LC[w]=(lista[0].Wartosc[w]);
      }else{
        lista[0].LC[w]=(lista[0].Wartosc[w]+lista[0].LC[w+1]);
      }
    }

 }else{
    if(pos==0){
      for(int w=(lista[0].Wartosc.size()-1);w>=0;--w){
        if(w==(lista[0].Wartosc.size()-1)){
          lista[0].LC[w]=(lista[0].Wartosc[w]+lista[1].LC[w]);
        }else{
          if(lista[1].LC[w]>=lista[0].LC[w+1]){
            lista[0].LC[w]=(lista[0].Wartosc[w]+lista[1].LC[w]);
          }else{
            lista[0].LC[w]=(lista[0].Wartosc[w]+lista[0].LC[w+1]);
          }
        }

      }
      //PC
      for(int w=0;w<lista[0].Wartosc.size();w++){
        for(int k=0;k<lista.size();k++){
          if(w==0){
            if(k==0){
              lista[k].PC[w]=(lista[k].Wartosc[w]);
            }else{
              lista[k].PC[w]=((lista[k].Wartosc[w]+lista[k-1].PC[w]));
            }
          }else{
            if(k==0){
              lista[k].PC[w]=(lista[k].Wartosc[w]+lista[k].PC[w-1]);
            }else{
              if(lista[k].PC[w-1]>=lista[k-1].PC[w]){
                lista[k].PC[w]=(lista[k].Wartosc[w]+lista[k].PC[w-1]);
              }else{
                lista[k].PC[w]=(lista[k].Wartosc[w]+lista[k-1].PC[w]);
              }
            }
          }

        }

      }

    }else if(pos==(lista.size()-1)){
      for(int w=0;w<lista[0].Wartosc.size();++w){
        if(w==0){
          lista[pos].PC[w]=(lista[pos].Wartosc[w]+lista[pos-1].PC[w]);
        }else{
          if(lista[pos].PC[w-1]>=lista[pos-1].PC[w]){
            lista[pos].PC[w]=(lista[pos].Wartosc[w]+lista[pos].PC[w-1]);
          }else{
            lista[pos].PC[w]=(lista[pos].Wartosc[w]+lista[pos-1].PC[w]);
          }
        }
      }
      for(int k=pos;k>=0;--k){
        for(int w=(lista[0].Wartosc.size()-1);w>=0;--w){
          if(w==(lista[0].Wartosc.size()-1)){
            if(k==pos){
              lista[k].LC[w]=(lista[k].Wartosc[w]);
            }else{
              lista[k].LC[w]=(lista[k].Wartosc[w]+lista[k+1].LC[w]);
            }
          }else{
            if(k==pos){
              lista[k].LC[w]=(lista[k].Wartosc[w]+lista[k].LC[w+1]);
            }else{
              if(lista[k+1].LC[w]>=lista[k].LC[w+1]){
                lista[k].LC[w]=(lista[k].Wartosc[w]+lista[k+1].LC[w]);
              }else{
                lista[k].LC[w]=(lista[k].Wartosc[w]+lista[k].LC[w+1]);
              }
            }
          }
        }
      }

    }else{
      for(int k=pos;k>=0;--k){//LC
        for(int w=(lista[0].Wartosc.size()-1);w>=0;--w){
          if(w==(lista[0].Wartosc.size()-1)){
            if(k==(lista.size()-1)){
              lista[k].LC[w]=(lista[k].Wartosc[w]);
            }else{
              lista[k].LC[w]=(lista[k].Wartosc[w]+lista[k+1].LC[w]);
            }
          }else{
            if(k==(lista.size()-1)){
              lista[k].LC[w]=(lista[k].Wartosc[w]+lista[k].LC[w+1]);
            }else{
              if(lista[k+1].LC[w]>=lista[k].LC[w+1]){
                lista[k].LC[w]=(lista[k].Wartosc[w]+lista[k+1].LC[w]);
              }else{
                lista[k].LC[w]=(lista[k].Wartosc[w]+lista[k].LC[w+1]);
              }
            }
          }
        }
      }
      for(int k=pos;k<lista.size();++k){//RC
        for(int w=0;w<lista[0].Wartosc.size();++w){
          if(w==0){
            if(k==0){
              lista[k].PC[w]=(lista[k].Wartosc[w]);
            }else{
              lista[k].PC[w]=((lista[k].Wartosc[w]+lista[k-1].PC[w]));
            }
          }else{
            if(k==0){
              lista[k].PC[w]=(lista[k].Wartosc[w]+lista[k].PC[w-1]);
            }else{
              if(lista[k].PC[w-1]>=lista[k-1].PC[w]){
                lista[k].PC[w]=(lista[k].Wartosc[w]+lista[k].PC[w-1]);
              }else{
                lista[k].PC[w]=(lista[k].Wartosc[w]+lista[k-1].PC[w]);
              }
            }
          }
        }
      }
    }
 }
  return;
}
int CheckC(deque<ZadanieMaszyn> &lista,ZadanieMaszyn src,int pos){
  int Cmax=-1;
  int PosMax=-1;
  int C[src.Wartosc.size()];
  if(lista.size()==0){
    Cmax=0;
    for(int i=0;i<src.Wartosc.size();++i){
      Cmax+=src.Wartosc[i];
    }
    return Cmax;
  }else{
    if(pos==0){
      for(int i=0;i<src.Wartosc.size();++i){
        if(i==0)
          C[i]=src.Wartosc[i];
        else
          C[i]=C[i-1]+src.Wartosc[i];
        if(Cmax<=(C[i]+lista[pos].LC[i])){
          Cmax=(C[i]+lista[pos].LC[i]);
        }
      }

    }else if(pos==lista.size()){
      for(int i=0;i<src.Wartosc.size();++i){
        if(i==0){
          C[i]=src.Wartosc[i]+lista[pos-1].PC[i];
        }else{
          if(C[i-1]>=lista[pos-1].PC[i]){
            C[i]=src.Wartosc[i]+C[i-1];
          }else{
            C[i]=src.Wartosc[i]+lista[pos-1].PC[i];
          }

        }
        Cmax=C[i];
        //if(Cmax<=(C[i]+lista[pos].LC[i])){
        //  Cmax=(C[i]+lista[pos].LC[i]);
        // }
      }

      return Cmax;
    }else{
      for(int w=0;w<src.Wartosc.size();++w){
        if(w==0){
          C[w]=lista[pos-1].PC[w]+src.Wartosc[w];
        }else{
          if(C[w-1]>=lista[pos-1].PC[w]){
            C[w]=src.Wartosc[w]+C[w-1];
          }else{
            C[w]=src.Wartosc[w]+lista[pos-1].PC[w];
          }
        }
        if(Cmax<=C[w]+lista[pos].LC[w])
          Cmax=C[w]+lista[pos].LC[w];

      }
      return Cmax;
    }
    return Cmax;
  }
  return -2;
}
float timedifference_msec(struct timeval t0, struct timeval t1){
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}


int main(int argc,char* argv[]){
  string nazwa;
  string nazwa_pliku;
  string nazwa_danych;
  ifstream plik;
  ofstream plik_danych;
  int zadania=0;
  int maszyny=0;
  int Cmax=2147483647;
  struct timeval start, stop;
  double czas=0;

  //Wczytanie danych w zaleznosci od sposobu wprowadzania
  //{
  if(argc==1){                        //Jesli brak argumentow to zapytaj o plik (z folderu Dane)
    cout<<"Podaj nazwe pliku:";
    cin>>nazwa;
  }else{                              //Jesli sa argumenty to wczytaj pierwszy jako nazwe pliku (z folderu Dane)
    nazwa=(string)argv[1];
    if(argc>2)                        //Jesli jest ich wiecej niz jeden to potraktuj drugi jako nazwe pliku do wypelnienia wynikiem
      nazwa_danych=(string)argv[2];
  }
  nazwa_pliku=nazwa;    //Zapamietaj nazwe pliku
  nazwa="Dane/"+nazwa;  //Stworz sciezke do pliku (z folderu Dane)
  //}

  plik.open(nazwa);
  plik>>zadania; //Wczytaj liczbe zadan
  plik>>maszyny; //Wczytaj liczbe maszyn

  cout<<"Zadania: "<<zadania<<endl<<"Maszyny: "<<maszyny<<endl; //Wyswietl ilosc zadan i maszyn

  gettimeofday(&start, NULL); //Zacznij mierzyc czas
  //Definicja tablicy
  //{
  int **tablica;
  //}

  //Alokacja tablicy
  //{
  tablica = (int**)malloc(zadania * sizeof *tablica);
  for(int i=0; i<zadania;++i){
    tablica[i] = (int*)malloc(maszyny * sizeof *tablica[i]);
  }
  //}

  cout<<endl;

  //Tablica czasowa (napis)
  //{
  #if DEBUG_INPUT
  for(int i=0;i<(maszyny*4-15)/2;++i){
    cout<<" ";
  }
  cout<<"Tablica czasowa"<<endl;
  #endif // DEBUG_INPUT
  //}

  //Wypelnienie i pokazanie tablicy
  //{
  for(int i=0;i<zadania;++i){
    for(int j=0;j<maszyny;++j){
      plik >> tablica[i][j];
      #if DEBUG_INPUT
        cout<<setw(3)<< tablica[i][j]<<" ";
      #endif // DEBUG_INPUT
    }
    #if DEBUG_INPUT
      cout<<endl;
    #endif // DEBUG_INPUT
  }
  //}

  vector<Zadanie> lZadan;
  Zadanie tmp;

  //Wstępne sortowanie listy zadan
  //{
  for(int i=1;i<=zadania;++i){
    tmp.ID=i;
    tmp.Wartosc=0;
    for(int j=0;j<maszyny;++j){
      tmp.Wartosc+=tablica[i-1][j];
    }
    lZadan.push_back(tmp);
  }
  sort(lZadan.begin(), lZadan.end(), greater<Zadanie>());
  //}

  //Wyswietlenie kolejnosci wpisywania zadan
  //{
  #if DEBUG
   cout<<endl<<"Zadania i sumy wartosci"<<endl;
  for (Zadanie z : lZadan){
    cout<<"Z:"<<setw(3)<<z.ID<<" S:"<<setw(6)<<z.Wartosc<<endl;
  }
  #endif // DEBUG
  //}

  deque<Wezel> SciezkaKryt;
  Wezel tmpKryt;
  deque<ZadanieMaszyn> kolejkaZad;
  deque<ZadanieMaszyn>::iterator it;
  ZadanieMaszyn tymczas;
  int minCza=0;
  int tmpCza=0;
  int minPos=0;
  int lastCol=-1;
  int HighestVal = -1;
  int HighestTsk = -1;

  //Wypelnienie listy zgodnie z zasadami algorytmu NEH
  //{
  for(int i=0;i<lZadan.size();++i){
    ClearZadM(tymczas);
    tymczas.ID=lZadan[i].ID;
    //Wypelnienie tymczasowej kolumny grafu wartosciami wezlow
    //{
    for(int j=0;j<maszyny;++j){
      tymczas.Wartosc.push_back(tablica[lZadan[i].ID-1][j]);
      tymczas.PC.push_back(-1);
      tymczas.LC.push_back(-1);
      #if DEBUG
      cout<<"j:"<<j;
      cin.get();
      #endif // DEBUG
    }
    //}


    if(i==0){
      //Jesli pierwsze zadanie na liscie to wpisz je bez liczenia permutacji
      //{

      #if DEBUG
      cout<<"i:"<<i;
      cin.get();
      #endif // DEBUG

      kolejkaZad.push_front(tymczas); //Wpisz na liste

      #if DEBUG
      cout<<"kolejka";
      cin.get();
      #endif // DEBUG

      UpdateC(kolejkaZad,i);  //Policz LC i PC
      //}
    }else{
      //Jesli kolejne zadanie na liscie to sprawdz permutacje
      //i wpisz na pozycje z najmniejsza wartoscia Cmax
      //{
      #if DEBUG
      cout<<"i:"<<i;
      cin.get();
      #endif // DEBUG

      minCza=2147483647; //Minimalny czas to maksymalny zakres aby napewno czas zostal nadpisany
      minPos=-1;         //Pozycja dla minimalnego czasu, -1 aby wykryc brak podstawienia

      //Sprawdz wszystkie pozycje j, ilosc pozycji to i+1
      //{
      for(int j=0;j<=i;++j){
        #if DEBUG
        cout<<"Check j:"<<j;
        cin.get();
        #endif // DEBUG
        tmpCza = CheckC(kolejkaZad,tymczas,j); //Wylicz Cmax dla tymczasowego zadania na pozycji j
        if(minCza>=tmpCza){                    //Jesli Cmax jest mniejszy od ostatniego najmniejszego
          minPos=j;                            //To nadpisz najmniejsza pozycje
          minCza=tmpCza;                       //Oraz najmniejszy Cmax
        }
        #if DEBUG
        cout<<"Check tmp:"<<tmpCza;
        cin.get();
        #endif // DEBUG
      }
      //}

      #if DEBUG
      cout<<"Check minpos:"<<minPos;
      cin.get();
      #endif // DEBUG

      //Wpisz zadanie na liste kolejnosci
      //{
      if(minPos==i){                    //Jesli minimalna pozycja to ostatnia pozycja
        kolejkaZad.push_back(tymczas);  //To dodaj zadanie na koniec listy
      }else{                            //Jesli nie
        it = kolejkaZad.begin()+minPos; //To iterator pozycji it
        kolejkaZad.insert(it,tymczas);  //Wskazuje miejsce gdzie nalezy wstawic zadanie
      }
      //}

      UpdateC(kolejkaZad,minPos); //Odswiez LC i PC zaczynajac od ostatnio wstawionego elementu


      SciezkaKryt.clear();
      tmpKryt.Kolumna=0;
      tmpKryt.Wiersz=0;
      tmpKryt.Wartosc=kolejkaZad.front().Wartosc.front();
      SciezkaKryt.push_back(tmpKryt);
      while((SciezkaKryt.back().Kolumna!=i) || (SciezkaKryt.back().Wiersz!=(maszyny-1)) ){
        if(SciezkaKryt.back().Kolumna!= i){
          if(SciezkaKryt.back().Wiersz !=(maszyny-1)){
            if(kolejkaZad[SciezkaKryt.back().Kolumna+1].LC[SciezkaKryt.back().Wiersz]>kolejkaZad[SciezkaKryt.back().Kolumna].LC[SciezkaKryt.back().Wiersz+1]){
              tmpKryt.Kolumna=SciezkaKryt.back().Kolumna+1;
              tmpKryt.Wiersz=SciezkaKryt.back().Wiersz;
              tmpKryt.Wartosc=kolejkaZad[SciezkaKryt.back().Kolumna+1].Wartosc[SciezkaKryt.back().Wiersz];
              if(tmpKryt.Wartosc>HighestVal){
                HighestVal=tmpKryt.Wartosc;
                HighestTsk=tmpKryt.Kolumna;
              }
              SciezkaKryt.push_back(tmpKryt);
            }else{
              tmpKryt.Kolumna=SciezkaKryt.back().Kolumna;
              tmpKryt.Wiersz=SciezkaKryt.back().Wiersz+1;
              tmpKryt.Wartosc=kolejkaZad[SciezkaKryt.back().Kolumna].Wartosc[SciezkaKryt.back().Wiersz+1];
              if(tmpKryt.Wartosc>HighestVal){
                HighestVal=tmpKryt.Wartosc;
                HighestTsk=tmpKryt.Kolumna;
              }
              SciezkaKryt.push_back(tmpKryt);
            }
          }else{
            tmpKryt.Kolumna=SciezkaKryt.back().Kolumna+1;
            tmpKryt.Wiersz=SciezkaKryt.back().Wiersz;
            tmpKryt.Wartosc=kolejkaZad[SciezkaKryt.back().Kolumna+1].Wartosc[SciezkaKryt.back().Wiersz];
            if(tmpKryt.Wartosc>HighestVal){
              HighestVal=tmpKryt.Wartosc;
              HighestTsk=tmpKryt.Kolumna;
            }
            SciezkaKryt.push_back(tmpKryt);
          }
        }else{
          tmpKryt.Kolumna=SciezkaKryt.back().Kolumna;
          tmpKryt.Wiersz=SciezkaKryt.back().Wiersz+1;
          tmpKryt.Wartosc=kolejkaZad[SciezkaKryt.back().Kolumna].Wartosc[SciezkaKryt.back().Wiersz+1];
          if(tmpKryt.Wartosc>HighestVal){
            HighestVal=tmpKryt.Wartosc;
            HighestTsk=tmpKryt.Kolumna;
          }
          SciezkaKryt.push_back(tmpKryt);
        }
      }

      tymczas=kolejkaZad[HighestTsk];
      it = kolejkaZad.begin()+HighestTsk;
      cout<<"Podmieniam zadanie: "<<HighestTsk<<" O wartosci: "<< HighestVal<<endl;
      kolejkaZad.erase(it);
      minCza=2147483647; //Minimalny czas to maksymalny zakres aby napewno czas zostal nadpisany
      minPos=-1;         //Pozycja dla minimalnego czasu, -1 aby wykryc brak podstawienia

      for(int j=0;j<=i;++j){
        tmpCza = CheckC(kolejkaZad,tymczas,j); //Wylicz Cmax dla tymczasowego zadania na pozycji j
        if(minCza>=tmpCza){                    //Jesli Cmax jest mniejszy od ostatniego najmniejszego
          minPos=j;                            //To nadpisz najmniejsza pozycje
          minCza=tmpCza;                       //Oraz najmniejszy Cmax
        }
      }

      if(minPos==i){                    //Jesli minimalna pozycja to ostatnia pozycja
        kolejkaZad.push_back(tymczas);  //To dodaj zadanie na koniec listy
      }else{                            //Jesli nie
        it = kolejkaZad.begin()+minPos; //To iterator pozycji it
        kolejkaZad.insert(it,tymczas);  //Wskazuje miejsce gdzie nalezy wstawic zadanie
      }
      UpdateC(kolejkaZad,minPos);
      //}
    }

    #if DEBUG //Wyswietl kolejnosc zadan
    cout<<endl<<"Kolejnosc zadan:"<<endl<<kolejkaZad<<endl;
    #endif // DEBUG
  }
  //}
  gettimeofday(&stop, NULL);                //Skoncz mierzyc czas
  czas = timedifference_msec(start, stop);  //Uzyskaj wynik czasu obliczen


  //Wypisywanie wartosci (wyniki)
  //{
  if(argc>2){
    plik_danych.open(nazwa_danych,ios::app);
    plik_danych<<setw(4)<<atoi(nazwa_pliku.c_str())<<" "<<setw(11)<<setprecision(6)<<fixed<<czas<<" "<<setw(6)<<kolejkaZad[0].LC[0]<<" "<<setw(6)<<kolejkaZad[zadania-1].PC[maszyny-1]<<"    "<<kolejkaZad;

  }else{
    cout<<endl<<"Kolejnosc zadan:"<<endl<<kolejkaZad<<endl;
    cout<<"CmaxL: "<< kolejkaZad[0].LC[0]                 <<endl;
    cout<<"CmaxP: "<< kolejkaZad[zadania-1].PC[maszyny-1] <<endl;
    cout<<"Czas: "<< setprecision(6) << czas <<endl;
    cout<<"Sciezka kryt:"<<endl<<SciezkaKryt;
    if(argc==1){
      cin.get();
      cin.get();
    }
  }
  //}

  return 0;
}
