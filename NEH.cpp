#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <iomanip>
#include <vector>

#define DEBUG_FUNC 0
#define DEBUG 1

using namespace std;

int liczCmax(int maszyny, list<int> &ORGkolejka , int** czasy){
  list<int> kolejka = ORGkolejka;
  int zadania = kolejka.size();
  int gantt[zadania][maszyny];
  int tmp_zad;
  #if DEBUG_FUNC
      cout<<"Kolejka do policzenia:\n";
  #endif // DEBUG_FUNC
  for(int i=0;i<zadania;i++){
    tmp_zad=kolejka.front();
      kolejka.pop_front();
    for(int j=0;j<maszyny;j++){
      gantt[i][j] = czasy[tmp_zad-1][j];
      #if DEBUG_FUNC
      cout<< gantt[i][j]<<" ";
      #endif // DEBUG_FUNC
    }
    #if DEBUG_FUNC
    cout<<endl;
    #endif // DEBUG_FUNC
  }
  #if DEBUG_FUNC
 cout<<endl<<endl;
 #endif // DEBUG_FUNC
 int M[maszyny];
 int masz=0;
  for(masz=0;masz<maszyny;masz++){
    M[masz]=-1;
  }
  M[0]=0;
  int Cmax=0;

  while(gantt[zadania-1][maszyny-1]!=0){
    Cmax++;
    int masz=0;
    for(masz=0;masz<maszyny;masz++){
      if((masz==0)&&(gantt[M[masz]][0]==0)){
        M[masz]+=1;
      }else if((masz!=0) && (M[masz]==-1) && (gantt[0][masz-1]==0)){
        M[masz]+=1;
      }else if((masz!=0) && (gantt[M[masz]][masz]==0) && (gantt[M[masz]+1][masz-1]==0)){
        M[masz]+=1;
      }
    }

    masz=0;
    for(masz=0;masz<maszyny;masz++){
      if((gantt[M[masz]][masz]>0)&&(M[masz]>=0))
        gantt[M[masz]][masz]--;
    }
    ///////////////////////////////////////////////////////////
    //  DEBUG_FUNC /////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////
    #if DEBUG_FUNC
      cout<<"C: "<<Cmax<<endl<<"----------------------------"<<endl;
      for(int z=0;z<maszyny;z++){
        cout<<"M"<<z+1<<": "<<M[z]<<" ";
      }
      cout<<endl<<"----------------------------"<<endl;

      for(int i=0;i<zadania;i++){
        for(int j=0;j<maszyny;j++){
          cout<< gantt[i][j]<<" ";
        }
        cout<<endl;
      }
      cout<<endl<<"Nacisnij klawisz aby kontynuowac"<<endl;
      cin.get();
    #endif // DEBUG_FUNC
  }
  return Cmax;
}
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list){
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}

struct Zadanie{
  int ID;
  int Wartosc;
  };
bool operator>(const Zadanie& A,const Zadanie& B){
  return(A.Wartosc>B.Wartosc);
}
int main(){


  string nazwa;
  ifstream plik;
  int zadania=0;
  int maszyny=0;
  int Cmax=2147483647;
  cout<<"Podaj nazwe pliku:";
  cin>>nazwa;

  plik.open(nazwa);

  plik>>zadania;
  plik>>maszyny;

  cout<<"Zadania: "<<zadania<<endl<<"Maszyny: "<<maszyny<<endl;

  //Definicja
  int **tablica;

  //Alokacja
  tablica = (int**)malloc(zadania * sizeof *tablica);
  for(int i=0; i<zadania;++i){
    tablica[i] = (int*)malloc(maszyny * sizeof *tablica[i]);
  }


  //Inicjalizacja
  cout<<endl;
  for(int i=0;i<(maszyny*4-15)/2;++i){
    cout<<" ";
  }
  cout<<"Tablica czasowa"<<endl;
  for(int i=0;i<zadania;++i){
    for(int j=0;j<maszyny;++j){
      plik >> tablica[i][j];
      cout<<setw(3)<< tablica[i][j]<<" ";
    }
    cout<<endl;
  }

  vector<Zadanie> lZadan;
  Zadanie tmp;
  for(int i=1;i<=zadania;++i){
    tmp.ID=i;
    tmp.Wartosc=0;
    for(int j=0;j<maszyny;++j){
      tmp.Wartosc+=tablica[i-1][j];
    }
    lZadan.push_back(tmp);
  }
  sort(lZadan.begin(), lZadan.end(), greater<Zadanie>());

  #if DEBUG
   cout<<endl<<"Zadania i sumy wartosci"<<endl;
  for (Zadanie z : lZadan){
    cout<<"Z:"<<setw(3)<<z.ID<<" S:"<<setw(6)<<z.Wartosc<<endl;
  }
  #endif // DEBUG

  list<int> kolejkaZ;
  list<int> kolejkaC;
  int minCzas=0;
  int minPos=0;
  int Pos=0;
  list<int>::iterator it;
  for(int i=0;i<lZadan.size();++i){
    kolejkaC.clear();
    #if DEBUG
      if(i!=0)
        cout<<"Kolejka zatwierdzona:"<<endl<<kolejkaZ<<endl;
    #endif // DEBUG
    if(i==0){
      kolejkaZ.push_front(lZadan[i].ID);
    }else{
      for(int j=0;j<=i;++j){
        it = kolejkaZ.begin();
        advance(it,j);
        kolejkaZ.insert(it,lZadan[i].ID);
        #if DEBUG
          if(i!=0)
            cout<<"Kolejka sprawdzana:"<<endl<<kolejkaZ<<endl;
        #endif // DEBUG
        kolejkaC.push_back(liczCmax(maszyny,kolejkaZ,tablica));
        #if DEBUG
          if(i!=0)
            cout<<"Kolejka czasowa:"<<endl<<kolejkaC<<endl;
        #endif // DEBUG
        kolejkaZ.erase(--it);
        #if DEBUG
          if(i!=0)
            cout<<"Kolejka cofnieta:"<<endl<<kolejkaZ<<endl;
        #endif // DEBUG
      }
      minCzas=2147483647;
      minPos=9999;
      Pos=0;
      for(int ind : kolejkaC){
        if(minCzas>ind){
          minCzas=ind;
          minPos=Pos;
        }
        ++Pos;
      }

      it = kolejkaZ.begin();
      advance(it,minPos);
      kolejkaZ.insert(it,lZadan[i].ID);
    }

  }
  cout<<endl<<"Kolejnosc zadan:"<<endl<<kolejkaZ<<endl<<"Cmax: ";
  Cmax=liczCmax(maszyny,kolejkaZ,tablica);
  cout<<Cmax<<endl;
  cin.get();
  cin.get();
  return 0;
}
