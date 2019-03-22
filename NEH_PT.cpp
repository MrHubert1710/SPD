#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <pthread.h>

#define DEBUG_FUNC_CMAX 0
#define DEBUG_FUNC 1
#define DEBUG 1

using namespace std;

int liczCmax(int maszyny, list<int> *ORGkolejka , int** czasy){
  list<int> kolejka = *ORGkolejka;
  int zadania = kolejka.size();
  int gantt[zadania][maszyny];
  int tmp_zad;
  #if DEBUG_FUNC_CMAX
      cout<<"Kolejka do policzenia:\n";
  #endif // DEBUG_FUNC_CMAX
  for(int i=0;i<zadania;i++){
    tmp_zad=kolejka.front();
      kolejka.pop_front();
    for(int j=0;j<maszyny;j++){
      gantt[i][j] = czasy[tmp_zad-1][j];
      #if DEBUG_FUNC_CMAX
      cout<< gantt[i][j]<<" ";
      #endif // DEBUG_FUNC_CMAX
    }
    #if DEBUG_FUNC_CMAX
    cout<<endl;
    #endif // DEBUG_FUNC_CMAX
  }
  #if DEBUG_FUNC_CMAX
 cout<<endl<<endl;
 #endif // DEBUG_FUNC_CMAX
 int M[maszyny];
 int masz=0;
  for(masz=0;masz<maszyny;masz++){
    M[masz]=-1;
  }
  M[0]=0;
  int Cmax=0;

  while(gantt[zadania-1][maszyny-1]!=0){
    Cmax++;
    //cout<<"CMAX++"<<endl;
    for(masz=0;masz<maszyny;masz++){
      if((masz==0)&&(gantt[M[masz]][0]==0)){
        M[masz]+=1;
      }else if((masz!=0) && (M[masz]==-1) && (gantt[0][masz-1]==0)){
        M[masz]+=1;
      }else if((masz!=0) && (gantt[M[masz]][masz]==0) && (gantt[M[masz]+1][masz-1]==0)){
        M[masz]+=1;
      }
    }

    //cout<<"Cond1"<<endl;
    for(masz=0;masz<maszyny;masz++){
      if((gantt[M[masz]][masz]>0)&&(M[masz]>=0))
        gantt[M[masz]][masz]--;
    }
    ///////////////////////////////////////////////////////////
    //  DEBUG_FUNC_CMAX /////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////

    //cout<<"Cond2"<<endl;
    #if DEBUG_FUNC_CMAX
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
      //cin.get();
    #endif // DEBUG_FUNC_CMAX
  }
  return Cmax;
}
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list){
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}
std::ostream& operator<<(std::ostream& ostr, const std::vector<int>& list){
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

struct Cmax_perm_arg{
int pozycja;
list<int> CpyKolejka;
int ID_Zad;
int Cmax;
int maszyny;
int** tablica;
};
void *liczCmax_perm(void *args){

  list<int>::iterator it;
  it=((struct Cmax_perm_arg*)args)->CpyKolejka.begin();
  advance(it,((Cmax_perm_arg*)args)->pozycja);
  if(((Cmax_perm_arg*)args)->pozycja==0){
	  ((Cmax_perm_arg*)args)->CpyKolejka.push_front(((Cmax_perm_arg*)args)->ID_Zad);
  }else{
	  ((Cmax_perm_arg*)args)->CpyKolejka.insert(it,((Cmax_perm_arg*)args)->ID_Zad);
  }
  #if DEBUG_FUNC
    cout<<"Kolejka sprawdzana:"<<endl<<((Cmax_perm_arg*)args)->CpyKolejka<<endl;
  #endif // DEBUG_FUNC
  cout<<"CMAX: "<<liczCmax((((Cmax_perm_arg*)args)->maszyny),&((Cmax_perm_arg*)args)->CpyKolejka,((Cmax_perm_arg*)args)->tablica);
  (((Cmax_perm_arg*)args)->Cmax) = liczCmax((((Cmax_perm_arg*)args)->maszyny),&((Cmax_perm_arg*)args)->CpyKolejka,((Cmax_perm_arg*)args)->tablica);
  pthread_exit(NULL);
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
  vector<int> kolejkaC;
  int minCzas=0;
  int minPos=0;
  int pt_return_value=0;
  vector<pthread_t> watki;
  vector<Cmax_perm_arg> args;
  pthread_t nWatek;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  Cmax_perm_arg tmp_args;
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  void *status;
  list<int>::iterator it;
  for(int i=0;i<lZadan.size();++i){
    kolejkaC.clear();
    tmp_args.CpyKolejka.clear();
    args.clear();
    #if DEBUG
      if(i!=0)
        cout<<"Kolejka zatwierdzona:"<<endl<<kolejkaZ<<endl;
    #endif // DEBUG
    if(i==0){
      kolejkaZ.push_front(lZadan[i].ID);
    }else{
      watki.clear();
      for(int j=0;j<=i;++j){
        tmp_args.Cmax=-1;
        tmp_args.CpyKolejka=kolejkaZ;
        tmp_args.ID_Zad=lZadan[i].ID;
        tmp_args.maszyny=maszyny;
        tmp_args.pozycja=j;
        tmp_args.tablica=tablica;
        args.push_back(tmp_args);
        pt_return_value = pthread_create(&nWatek, &attr, liczCmax_perm, (void *)(&args[j]));
        #if DEBUG
        if(!pt_return_value){
          cout<<"Stworzono watek"<<endl;
        }else{
          cerr<<"Nie udalo sie stworzyc watku"<<endl;
        }
        #endif // DEBUG
        watki.push_back(nWatek);
      }
      for(pthread_t th: watki){
        pt_return_value=pthread_join(th,&status);
        #if DEBUG
        if(!pt_return_value){
          cout<<"Dolaczono watek"<<endl;
        }else{
          cerr<<"Nie udalo sie dolaczyc watku"<<endl;
        }
        #endif // DEBUG
		
      }
	  for(Cmax_perm_arg a : args){
		  kolejkaC.push_back(a.Cmax);
	  }
      #if DEBUG
	  
        cout<<"Kolejka czasowa:"<<endl<<kolejkaC<<endl;
      #endif // DEBUG


      minCzas=2147483647;
      minPos=9999;
      for(Cmax_perm_arg ind : args){
        if(minCzas>ind.Cmax){
          minCzas=ind.Cmax;
          minPos=ind.pozycja;
        }
      }

      it = kolejkaZ.begin();
      advance(it,minPos);
      kolejkaZ.insert(it,lZadan[i].ID);
    }

  }
  cout<<endl<<"Kolejnosc zadan:"<<endl<<kolejkaZ<<endl<<"Cmax: ";
  Cmax=liczCmax(maszyny,&kolejkaZ,tablica);
  cout<<Cmax<<endl;
  cin.get();
  cin.get();
  return 0;
}
