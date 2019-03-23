#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <deque>

#define DEBUG_INPUT 0
#define DEBUG 0

using namespace std;


struct Zadanie{
  int ID;
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
      ostr << " " <<i.ID;
    }
    ostr<<endl;
  #endif // DEBUG
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
        //}
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
  #if DEBUG_INPUT
  for(int i=0;i<(maszyny*4-15)/2;++i){
    cout<<" ";
  }
  cout<<"Tablica czasowa"<<endl;
  #endif // DEBUG_INPUT


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

  deque<ZadanieMaszyn> kolejkaZad;
  deque<ZadanieMaszyn>::iterator it;
  ZadanieMaszyn tymczas;
  int minCza=0;
  int tmpCza=0;
  int minPos=0;
  int lastCol=-1;
  for(int i=0;i<lZadan.size();++i){
    ClearZadM(tymczas);
    tymczas.ID=lZadan[i].ID;
    for(int j=0;j<maszyny;++j){
      tymczas.Wartosc.push_back(tablica[lZadan[i].ID-1][j]);
      tymczas.PC.push_back(-1);
      tymczas.LC.push_back(-1);
      #if DEBUG
      cout<<"j:"<<j;
      cin.get();
      #endif // DEBUG
    }
    if(i==0){
      #if DEBUG
      cout<<"i:"<<i;
      cin.get();
      #endif // DEBUG

      kolejkaZad.push_front(tymczas);

      #if DEBUG
      cout<<"kolejka";
      cin.get();
      #endif // DEBUG

      UpdateC(kolejkaZad,i);
    }else{

      #if DEBUG
      cout<<"i:"<<i;
      cin.get();
      #endif // DEBUG

      minCza=2147483647;
      minPos=-1;
      for(int j=0;j<=i;++j){
        lastCol=j;
        #if DEBUG
        cout<<"Check j:"<<j;
        cin.get();
        #endif // DEBUG
        tmpCza = CheckC(kolejkaZad,tymczas,j);
        if(minCza>=tmpCza){
          minPos=j;
          minCza=tmpCza;
        }
        #if DEBUG
        cout<<"Check tmp:"<<tmpCza;
        cin.get();
        #endif // DEBUG
      }
      #if DEBUG
      cout<<"Check minpos:"<<minPos;
      cin.get();
      #endif // DEBUG
      if(minPos==lastCol){
        kolejkaZad.push_back(tymczas);
      }else{
        it = kolejkaZad.begin()+minPos;
        kolejkaZad.insert(it,tymczas);
      }
      UpdateC(kolejkaZad,minPos);

    }
      #if DEBUG
      cout<<endl<<"Kolejnosc zadan:"<<endl<<kolejkaZad<<endl;

      #endif // DEBUG
  }

  cout<<endl<<"Kolejnosc zadan:"<<endl<<kolejkaZad<<endl<<"Cmax: ";
  cout<< kolejkaZad[0].LC[0]<<endl;
  cout<< kolejkaZad[zadania-1].PC[maszyny-1]<<endl;
  cin.get();
  cin.get();
  return 0;
}
