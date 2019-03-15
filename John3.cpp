#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

#define DEBUG 1

void pokaz(int a){
cout<<a<<" ";
return;
}

std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}

string nazwa;
ifstream plik;
int zadania=0;
int maszyny=0;



int main()
{
  cout<<"Podaj nazwe pliku:";
  cin>>nazwa;
  plik.open(nazwa);
  plik>>zadania;
  plik>>maszyny;
  cout<<zadania<<" "<<maszyny<<endl;
  int  tablica[zadania][maszyny];
  for(int i=0;i<zadania;i++){
    for(int j=0;j<maszyny;j++){
      plik >> tablica[i][j];
      cout<< tablica[i][j]<<" ";
    }
    cout<<endl;
  }
  int wirtualne[zadania][2];
  int IleElem=maszyny/2;
  if((2*IleElem)==maszyny){

  }else{
    IleElem++;
  }
  for(int k=0;k<zadania;k++){
      wirtualne[k][0]=0;
      wirtualne[k][1]=0;
    for(int m=0;m<IleElem;m++){
      wirtualne[k][0]+=tablica[k][m];
    }
    for(int m=0;m<IleElem;m++){
      wirtualne[k][1]+=tablica[k][maszyny-m-1];
    }
  }
  cout<<endl;
  #if DEBUG
  for(int xx=0; xx<2; xx++){
    for(int yy=0 ;yy<zadania; yy++)
      cout<<wirtualne[yy][xx]<<" ";
    cout<<endl;
  }
  #endif // DEBUG
  int wykonane[zadania];

  for(int p=0;p<zadania;p++){
    wykonane[p]=-1;
  }

  list<int> A;
  list<int> B;
  int least;
  int least_oposite;
  int n_least;
  int o_least;

  for(int r=0;r<zadania;r++){
    least=99999;
    least_oposite=-1;
    for(int n=0;n<2;n++){
      for(int o=0;o<zadania;o++){
        if(wykonane[o]==-1){
          if(least>wirtualne[o][n]){
            n_least=n;
            o_least=o;
            least=wirtualne[o][n];
            least_oposite=wirtualne[o][!n];
          }else if(least==wirtualne[o][n]){
            if((n_least==n)&&(least_oposite<wirtualne[o][!n])){
              n_least=n;
              o_least=o;
              least=wirtualne[o][n];
              least_oposite=wirtualne[o][!n];
            }
          }
        }
      }
    }
    wykonane[o_least]=1;
    if(n_least==0){
      A.push_back(o_least+1);
    }else{
      B.push_front(o_least+1);
    }
  }
  #if DEBUG
  cout<<A<<endl;
  cout<<B<<endl;
  #endif // DEBUG
  A.insert(A.end(), B.begin(), B.end());
  cout<<A<<endl<<endl;
  int  gantt[zadania][maszyny];
  int tmp_zad;
  for(int i=0;i<zadania;i++){
    tmp_zad=A.front();
      A.pop_front();
    for(int j=0;j<maszyny;j++){
      gantt[i][j] = tablica[tmp_zad-1][j];
      #if DEBUG
      cout<< gantt[i][j]<<" ";
      #endif // DEBUG
    }
    #if DEBUG
    cout<<endl;
    #endif // DEBUG
  }
  #if DEBUG
 cout<<endl<<endl;
 #endif // DEBUG
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
  //  DEBUG /////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  #if DEBUG
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
    cout<<endl;
    cin.get();
  #endif // DEBUG
  }
  cout<<"Cmax dla algorymu Johnsona to: "<<Cmax;
  return 0;
}
