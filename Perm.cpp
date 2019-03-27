#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

void permut(int k, vector<int> &P, vector<vector<int>> &ODP)
{
  if(k==1)
  {
    ODP.push_back(P);

  }else
    {
      for(int i=0;i<k;i++)
      {
        iter_swap(P.begin()+i,P.begin()+k-1);
        permut(k-1,P,ODP);
        iter_swap(P.begin()+i,P.begin()+k-1);
      }
    }

  return;
}

vector<vector<int>> permutacje(vector<int> V)
{
  
  vector<vector<int>> ans;
  permut(V.size(),V,ans);

  return ans;
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

  int tablica[zadania][maszyny];

  for(int i=0;i<zadania;i++)
  {
    for(int j=0;j<maszyny;j++)
    {
      plik >> tablica[i][j];
      cout<< tablica[i][j]<<" ";
    }

    cout<<endl;
  }

  vector<int> tabela;
  
  for ( int x=1 ; x <= zadania; x++ )
  {
    tabela.push_back(x);
  }
    
  vector<vector<int>> ans = permutacje(tabela);

  int M[maszyny];
  int masz = 0;
  int Cmax = 0;
  int ind = 0;
  int gantt[zadania][maszyny];
  int Cmin = 999999;
  int Cmmax = -1;

  for (vector<int> A : ans)
  {
    ind=0;

    for (int B : A)
    {
      cout<<B<<" ";
      for( int y = 0 ; y < maszyny ; y++ )
      {
        gantt[ind][y] = tablica[B-1][y];
      }
      ind++;
    }

    for( masz = 0 ; masz < maszyny ; masz++ )
    {
      M[masz]=-1;
    }

    M[0]=0;
    Cmax=0;

    while( gantt[zadania-1][maszyny-1] != 0)
    {
      Cmax++;
      masz=0;

      for(masz=0;masz<maszyny;masz++)
      {
        if((masz==0)&&(gantt[M[masz]][0]==0))
        {
          M[masz]+=1;
          
        }else if((masz!=0) && (M[masz]==-1) && (gantt[0][masz-1]==0))
                {
                  M[masz]+=1;
                }else if((masz!=0) && (gantt[M[masz]][masz]==0) && (gantt[M[masz]+1][masz-1]==0))
                        {
                          M[masz]+=1;
                        }
      }

      masz=0;

      for( masz=0 ; masz<maszyny ; masz++ )
      {
        if((gantt[M[masz]][masz]>0)&&(M[masz]>=0))
        {
          gantt[M[masz]][masz]--;
        }
      }
    }

    cout<<" C: "<<Cmax<<endl;

    if (Cmax>=Cmmax)
      Cmmax=Cmax;
    if (Cmax<=Cmin)
      Cmin=Cmax;
  }

  cout<<endl<<"Cmin: "<<Cmin<<endl<<"Cmax: "<<Cmmax<<endl;
  return 0;
}

