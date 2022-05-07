#include "GrapheAvecAdjacent.h"
#include "../Graphe.h"
#include "../Sommet.h"
#include <vector>
#include <fstream>
#include <../include/GrapheAvecFsAps.h>

using std::vector;

GrapheAvecAdjacent::GrapheAvecAdjacent(bool oriente, bool value)
    : Graphe{}, d_adj{}, d_sommets{}, d_oriente{oriente}, d_value{value}
{

}

GrapheAvecAdjacent::GrapheAvecAdjacent(const GrapheAvecFsAps g)
    : Graphe {} , d_adj{}, d_sommets{}, d_oriente{g.estOriente()}, d_value{g.estValue()}
{
    fsAps2matAdj(g);
}

void GrapheAvecAdjacent :: fsAps2matAdj(const GrapheAvecFsAps g)
{
    int k;
    int n=g.nbSommets();
    d_adj.resize(g.nbSommets());
    for (int i = 0; i < n; i++)
    {
        d_adj[i].resize(n+1, 0);
    }
    for (int i = 1; i <= n; i++)
    {
         k = g.getAPS()[i];
         while ( g.getFS()[k] != 0 )
         {
             d_adj[i-1][g.getFS()[k]] = g.getPoids()[k];
             k++;
         }
    }
}

void GrapheAvecAdjacent::ajoutSommet(const Sommet& s){
    int n = nbSommets();
    d_adj.push_back(std::vector<int>(n + 1, 0));
    for (int i = 0; i < n; ++i)
        d_adj[i].push_back(0);
    d_sommets.push_back(s);
}
void GrapheAvecAdjacent::supprimeSommet(int s){
  d_adj.erase(d_adj.begin() + s);
  int n = nbSommets();
  for (int i = 0; i <= n; ++i)
    d_adj[i].erase(d_adj[i].begin() + s);
}

Sommet GrapheAvecAdjacent::getSommet(int s) const
{
  return d_sommets[s];
}

int GrapheAvecAdjacent::nbSommets() const
{
  return d_adj.size();
}

void GrapheAvecAdjacent::setOriente(bool oriente)
{
    d_oriente = oriente;
}

bool GrapheAvecAdjacent::estOriente() const
{
    return d_oriente;
}

void GrapheAvecAdjacent::setValue(bool value)
{
    d_value = value;
}

bool GrapheAvecAdjacent::estValue() const
{
    return d_value;
}

void GrapheAvecAdjacent::printSommets() const
{
  for (unsigned i = 0; i < d_adj.size(); ++i)
  {
    for (unsigned j = 0; j < d_adj[i].size(); ++j)
    {
        if(d_adj[i][j] == INT_MAX){
            std::cout<<"INF"<<" ";
        }
        else if(d_adj[i][j] == -INT_MAX){
            std::cout<<"-INF"<<" ";
        }
        else{
            std::cout<<d_adj[i][j]<<" ";
        }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void GrapheAvecAdjacent::ajoutArete(int s1, int s2, double poids)
{
    int taille = d_adj.size();
    if(s1 > taille || s2 > taille){
        return;
    }
    if(d_oriente)
        d_adj[s1-1][s2-1] = poids;
    else
        d_adj[s1-1][s2-1] = d_adj[s2-1][s1-1] = poids;

}

void GrapheAvecAdjacent::supprimeArete(int s1, int s2)
{
  int taille = d_adj.size();
    if(s1 > taille || s2 > taille){
        return;
    }
    if(d_oriente)
        d_adj[s1-1][s2-1] = 0;
    else
        d_adj[s1-1][s2-1] = d_adj[s2-1][s1-1] = 0;
}

int GrapheAvecAdjacent::nombreAretes() const
{
  int n = nbSommets();
  int m = 0;
  for (int i = 1; i < n; ++i)
  {
    for (int j = i+1; j <= n; ++j)
    {
      if (d_adj[i][j] != 0)
        ++m;
    }
  }
  return m;
}

vector<vector<int>>  GrapheAvecAdjacent::getMatAdj() const
{
    return d_adj;
}
//
void GrapheAvecAdjacent::prufer(vector<int>& prf) const
{
    vector<vector<int>> mat(d_adj.size(), vector<int>(d_adj.size()+1));

    for(unsigned i = 0; i < d_adj.size(); ++i){
        for(unsigned j = 0; j < d_adj[i].size(); ++j){
            mat[i][j+1] = d_adj[i][j];
        }
    }
    int n = d_adj.size();
    prf.resize(n-1);
    prf[0] = n - 2;
    for(unsigned i = 0; i < mat.size(); i++)
    {
        mat[i][0] = 0;
        for(unsigned j = 1; j < mat[i].size(); j++)
        {
            mat[i][0] += mat[i][j];
        }
    }
    for(int k = 1; k <= n-2; k++)
    {
        int i = 1;
        for(;mat[i][0] != 1; ++i);
        int j = 1;
        for(;mat[i][j] !=1 ; ++j);
        prf[k] = j;
        mat[i][j] = 0;
        mat[j][i] = 0;
        mat[i][0] = 0;
        mat[j][0]--;
    }
}

void GrapheAvecAdjacent::decoprufer(const vector<int>& t) const
{
    int m = t[0], n = m + 2;
    vector<int> s(n + 1, 0);
    s[0] = n;
    //for (int i = 1; i <= n; i++) s[i] = 0;
    for (int i = 1; i <= m; i++) s[t[i]]++;
    for (int k = 1; k <= m; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (s[i] == 0)
            {
                std::cout <<"[ "<<t[k]<<" ,"<<i<<" ]"<<std::endl;
                s[t[k]]--;
                s[i] = -1;
                break;
            }
        }
    }
    std::cout<<"[ ";
    for (int i = 1; i <= n; i++){
        if ( s[i] == 0 )
            std::cout <<i<<" ,";
    }
    std::cout << "]"<<std::endl;
}

bool GrapheAvecAdjacent::dantzig(vector<vector<int>>& dist) const
{
    int x;
    dist = d_adj;
    int n = dist.size();
    for(int k = 0; k < n; ++k)
    {
        for(int i = 0; i <= k; ++i)
        {
            for(int j = 0; j <= k; ++j)
            {
                if((x = dist[i][j] + dist[j][k+1]) < dist[i][k+1]){
                    dist[i][k+1] = x;
                }
                if((x = dist[k+1][j] + dist[j][i]) < dist[k+1][i]){
                    dist[k+1][i] = x;
                }
            }//j
            //int t = std::min(dist[i][k+1], dist[k+1][i]);
            if((dist[i][k+1]+ dist[k+1][i]) < 0){
                std::cout<<"Presence d'un circuit absorbant passant par "<<i<<" et "<<(k+1)<<std::endl;
                return false;
            }
        }//i
        for(int i = 0; i <= k; ++i)
        {
            for(int j = 0; j <= k; ++j)
            {
                if((x = dist[i][k+1] + dist[k+1][j]) < dist[i][j]){
                    dist[i][j] = x;
                }
            }
        }
    }//k
    return true;
}

void GrapheAvecAdjacent::tranformationMatAdjEnGrapheKruskal(grapheKruskal& g)
{
    arete a{};
    g.n = nbSommets();
    g.m = nombreAretes();
    for(unsigned i = 0; i < d_adj.size(); ++i)
    {
        for(unsigned j = 0; j < d_adj[i].size(); ++j)
        {
            if(d_adj[i][j] != 0){
                a.s = i+1;
                a.t = j+1;
                a.p = d_adj[i][j];
                g.aretes.push_back(a);
            }
        }
    }
}

void GrapheAvecAdjacent::triGrapheKruskal(grapheKruskal& g)
{
    for(unsigned i = 0; i < g.aretes.size() - 1; ++i)
    {
        for(unsigned j = i + 1; j < g.aretes.size(); ++j)
        {
           if(g.aretes[j].p < g.aretes[i].p)
           {
                std::swap(g.aretes[j], g.aretes[i]);
           }
           else if(g.aretes[j].p == g.aretes[i].p){
                if(g.aretes[j].s < g.aretes[i].s){
                    std::swap(g.aretes[j], g.aretes[i]);
                }
                else if(g.aretes[j].s == g.aretes[i].s){
                    if(g.aretes[j].t < g.aretes[i].t){
                        std::swap(g.aretes[j], g.aretes[i]);
                    }
                }
           }
        }
    }
}

void GrapheAvecAdjacent::fusion(int i, int j, vector<int>& prem, vector<int>& pilch, vector<int>& cfc, vector<int>& nbElem) const
{
    int k = prem[i];
    while(pilch[k] != 0)
        k = pilch[k];
    pilch[k] = prem[j];
    k = prem[j];
    while(k != 0){
        cfc[k] = i;
        k = pilch[k];
    }
}

void GrapheAvecAdjacent::kruskal()
{
    grapheKruskal g{}, t{};
    tranformationMatAdjEnGrapheKruskal(g);
    triGrapheKruskal(g);
    //INITIALISATION
    t.aretes.resize(g.n-1);
    int n = g.n;
    vector<int> prem(n + 1);
    vector<int> pilch(n + 1, 0);
    vector<int> cfc(n + 1);
    vector<int> nbElem(n + 1, 1);
    prem[0] = pilch[0] = cfc[0] = nbElem[0] = g.n;
    for(int i = 1; i <= n; ++i){
        prem[i] = i;
        cfc[i] = i;
    }
    int x, y;
    int i = 0, j = 0;
    while(j < g.n -1)
    {
        arete ar{};
        ar = g.aretes[i];
        x = cfc[ar.s];
        y = cfc[ar.t];
        if(x != y)
        {
            t.aretes[j++] = g.aretes[i];
            fusion(x, y, prem, pilch, cfc, nbElem);
        }
        ++i;
    }
    t.n = g.n;
    t.m = g.n-1;
    //AFFICHAGE
    for(int i = 0; i < t.m; ++i){
        std::cout<<"Arete No "<<i+1<<" : ("<<t.aretes[i].s<<", ";
        std::cout<<t.aretes[i].t<<") --- "<<t.aretes[i].p<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"prem : ";
    afficher(prem);
    std::cout<<"pilch : ";
    afficher(pilch);
    std::cout<<"cfc : ";
    afficher(cfc);
}

void GrapheAvecAdjacent::afficher(const vector<int>& tab) const
{
    for(unsigned i = 0; i < tab.size(); ++i)
        std::cout<<tab[i]<<" ";
    std::cout<<std::endl;
}

void GrapheAvecAdjacent::lectureGraphe(std::string fileName)
{
    std::ifstream grapheMatAdj(fileName);
    bool oriente;
    int nbSommets;
    grapheMatAdj>>oriente;
    d_oriente=oriente;
    grapheMatAdj>>nbSommets;
    d_adj.clear(); d_adj.resize(nbSommets);
    for(int i = 0; i < nbSommets; ++i)
        d_adj[i].resize(nbSommets);

    for (int i = 0; i < nbSommets; ++i)
    {
        for (int j = 0; j < nbSommets; ++j)
        {
            grapheMatAdj>>d_adj[i][j];
        }
    }
    d_sommets.clear(); d_sommets.resize(nbSommets);
    std::string s;
    for(int i = 0; i < nbSommets; ++i){
        grapheMatAdj>>s;
        d_sommets[i] = Sommet(i, s);
    }
}

void GrapheAvecAdjacent::ecritureGraphe(std::string fileName)
{
    std::ofstream grapheMatAdj(fileName);
    grapheMatAdj<<d_oriente<<std::endl;
    int n = nbSommets();
    grapheMatAdj<<n<<std::endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            grapheMatAdj<<d_adj[i][j]<<" ";
        }
        grapheMatAdj<<std::endl;
    }
    grapheMatAdj<<std::endl;
    for(int i = 0; i < n; ++i){
        grapheMatAdj<<d_sommets[i].getNomStation()<<" ";
    }
}
