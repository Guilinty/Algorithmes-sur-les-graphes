#include "GrapheAvecFsAps.h"
#include <../Graphe.h>
#include "../Sommet.h"
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <algorithm>
#include <../include/GrapheAvecAdjacent.h>

using std::vector;

GrapheAvecFsAps::GrapheAvecFsAps(bool oriente, bool value )
    : Graphe{}, _aps{0}, _fs{0}, _sommets{1}, _oriente{oriente}, _value{value}, _poids{0}
{

}

GrapheAvecFsAps::GrapheAvecFsAps(const GrapheAvecAdjacent g) : Graphe{}, _oriente{g.estOriente()}, _value{g.estValue()}
{
    MatAdj2FsAps(g);
}

void GrapheAvecFsAps::MatAdj2FsAps(const GrapheAvecAdjacent g)
{
    int n = g.nbSommets();
    int m = g.nombreAretes();
    _aps.resize(n+1);
    _aps[0] = n;
    _fs.resize(n+m+1);
    _fs[0] = n+m;
    int k = 1;
    for (int i = 1; i <= n; i++)
    {
         _aps[i] = k;
         for (int j = 1; j <= n; j++)
             if (g.getMatAdj()[i][j] != 0)
                 _fs[k++] = j;
         _fs[k++] = 0;
    }
}

void GrapheAvecFsAps::ajoutSommet(const Sommet& s)
{
    _aps.push_back(_fs.size());
    _fs.push_back(0);
    _poids.push_back(INT_MAX);
    _aps[0]++;
    _fs[0]++;
    _poids[0]++;
    _sommets.push_back(s);
}


void GrapheAvecFsAps::supprimeSommet(int s)
{
    if(s > nbSommets())
    {
        return;
    }
    for(int i = 1; i <= nbSommets(); ++i){
        supprimeArc(i, s);
    }
    if(s == nbSommets())
    {
        _fs.erase(_fs.begin() + _aps[s], _fs.end());
        _aps.erase(_aps.begin() + s);
        _poids.erase(_poids.begin() + _aps[s], _poids.end());
    }
    else{
        int limite = _aps[s+1] - 1;
        int nbSuccDeS = limite - _aps[s];
        _fs.erase(_fs.begin() + _aps[s], _fs.begin() + limite);
        _aps.erase(_aps.begin() + s);
        _poids.erase(_poids.begin() + _aps[s], _poids.begin() + limite);
        for(unsigned i = s; i < _aps.size(); ++i){
            _aps[i] -= nbSuccDeS;
        }
    }
    _fs[0] = _fs.size() - 1;
    --_aps[0];
    _poids[0] = _poids.size() - 1;
    _sommets.erase(_sommets.begin() + s);
    for(int i = _aps[1]; i <= _fs[0]; ++i){
        if(_fs[i] > s){
            --_fs[i];
            //--_poids[i];
        }
    }
}

Sommet GrapheAvecFsAps::getSommet(int s) const
{
    return _sommets[s];
}

int  GrapheAvecFsAps::nbSommets() const
{
    return _aps[0];
}

vector<int> GrapheAvecFsAps::getFS() const
{
    return _fs;
}

vector<int> GrapheAvecFsAps::getAPS() const
{
    return _aps;
}

vector<int> GrapheAvecFsAps::getPoids() const
{
    return _poids;
}
vector<Sommet> GrapheAvecFsAps::getSommets() const
{
    return _sommets;
}

void GrapheAvecFsAps::printSommets() const
{
    for(int i = 1; i <= nbSommets(); ++i){
        std::cout<<_sommets[i].getNomStation()<<" ";
    }
    std::cout<<std::endl;
    for(int i = 1; i <= nbSommets(); ++i){
        std::cout<<_sommets[i].getNumeroStation()<<" ";
    }
    std::cout<<std::endl;
    for(int i = 1; i <= nbSommets(); ++i)
    {
        std::cout<<"Sommet : "<<i<<std::endl;
        std::cout<<"\t"<<"Successeurs : "<<std::endl;
        int j = _aps[i];
        std::cout<<"\t"<<"[";
        while(_fs[j] != 0){
            std::cout<<_fs[j++]<<" ,";
        }
        std::cout<<"]"<<std::endl;
        if(estValue())
        {
            std::cout<<"\t"<<"Couts des arcs : "<<std::endl;
            int k = _aps[i];
            std::cout<<"\t"<<"[";
            while(_poids[k] != INT_MAX){
                std::cout<<_poids[k++]<<" ,";
            }
            std::cout<<"]"<<std::endl;
        }
        std::cout<<std::endl;
    }
}

void GrapheAvecFsAps::setOriente(bool oriente)
{
    _oriente = oriente;
}

bool GrapheAvecFsAps::estOriente() const
{
    return _oriente;
}

void GrapheAvecFsAps::setValue(bool value)
{
    _value = value;
}

bool GrapheAvecFsAps::estValue() const
{
    return _value;
}

void GrapheAvecFsAps::ajoutArc(int s, int t, int couts)
{
    if(s > nbSommets() || t > nbSommets())
    {
        return;
    }
    int i = _aps[s];
    while(_fs[i] != 0 && _fs[i] != t) ++i;
    if(_fs[i] == t)
        return;
    _fs.insert(_fs.begin() + i, t);
    _poids.insert(_poids.begin() + i, couts);
    ++_fs[0];
    ++_poids[0];
    for(int j = s + 1; j <= nbSommets(); ++j){
        ++_aps[j];
    }
}

void GrapheAvecFsAps::supprimeArc(int s, int t)
{
    if(s > nbSommets() || t > nbSommets())
    {
        return;
    }
    int i = _aps[s];
    while(_fs[i] != 0 && _fs[i] !=t) ++i;
    if(_fs[i] == 0)
    {
        return;
    }
    _fs.erase(_fs.begin() + i);
    _poids.erase(_poids.begin() + i);
    --_fs[0];
    --_poids[0];
    for(int j = s + 1; j <= nbSommets(); ++j){
        --_aps[j];
    }
}

void GrapheAvecFsAps::inverser()
{
    vector<int> ddi = calculDDI();
    vector<int> app = calculAPP();
    vector<int> fp = calculFP();
    //Inversion
    for(int i = 1; i <= fp[0]; ++i){
        _fs[i] = fp[i];
    }
    for(int i = 1; i <= app[0]; ++i){
        _aps[i] = app[i];
    }
}

void GrapheAvecFsAps::matriceDesDistances(vector<vector<int>>& matDist) const
{
    matDist.resize(nbSommets()+1);
    for(int r = 1; r <= nbSommets(); ++r){
        descenteEnLarg(r, matDist[r]);
    }
}

void GrapheAvecFsAps::descenteEnLarg(int r, vector<int>& distances) const
{
    int k = 0;
    std::queue<int> fileAttente{};
    fileAttente.push(r);
    distances.resize(nbSommets() + 1, -1);
    distances[0] = nbSommets();
    distances[r] = 0;
    while(!fileAttente.empty())
    {
        ++k;
        for(int i = 0, n = fileAttente.size(); i < n; ++i)
        {
            int s = fileAttente.front();
            fileAttente.pop();
            int t;
            for(int j = _aps[s]; (t =_fs[j]) != 0; ++j)
            {
                if(distances[t] == -1){
                    distances[t] = k;
                    fileAttente.push(t);
                }
            }
        }
    }
}

void GrapheAvecFsAps::empiler(int x, vector<int>& pilch) const
{
    pilch[x] = pilch[0];
    pilch[0] = x;
}

void GrapheAvecFsAps::rang(vector<int>& rang) const
{
    rang.resize(nbSommets() + 1);
    vector<int> ddi(nbSommets() + 1, 0);
    vector<int> pilch(nbSommets() + 1);
    vector<int> prem(nbSommets() + 1);
    rang[0] = nbSommets();
    //CALCUL DE DDI
    ddi[0] = nbSommets();
    for(int i = 1; i < _fs[0]; ++i){
        int s = _fs[i];
        if(s != 0) ++ddi[s];
    }
    //CALCUL DU RANG
    pilch[0] = 0;
    for(int s = 1; s <= nbSommets(); ++s){
        rang[s] = -1;
        if(ddi[s] == 0){
            empiler(s, pilch);
        }
    }
    int k = -1;
    int s = pilch[0];
    prem[0] = s;
    while(pilch[0] > 0)
    {
        ++k;
        pilch[0] = 0;
        while(s > 0){
            rang[s] = k;
            int h = _aps[s];
            int t = _fs[h];
            while(t > 0){
                --ddi[t];
                if(ddi[t] == 0) empiler(t, pilch);
                ++h;
                t = _fs[h];
            }
            s = pilch[s];
        }
        s = pilch[0];
        prem[k+1] = s;
    }
}

void GrapheAvecFsAps::traverse(int s, int& ns, int& nc, vector<int>& num,
                               vector<int>& pilch, vector<int>& ro,
                               vector<bool>& entarj, vector<int>& cfc,
                               std::stack<int>& tarj, vector<int>& pred, vector<int>& prem) const
{
    num[s] = ro[s] = ++ns;
    tarj.push(s);
    entarj[s] = true;
    for(int k = _aps[s], t; (t = _fs[k]) != 0; ++k)
    {
        if(num[t] == 0){
            pred[t] = s;
            traverse(t, ns, nc, num, pilch, ro, entarj, cfc, tarj, pred, prem);
            if(ro[t] < ro[s])
                ro[s] = ro[t];
        }
        else{
            if(num[t] < ro[s] && entarj[t])
                ro[s] = num[t];
        }
    }
    if(ro[s] == num[s])
    {
        int u;
        ++nc;
        do{
            u = tarj.top();
            tarj.pop();
            entarj[u] = false;
            empiler(u, pilch);
            cfc[u] = nc;
        }while(u != s);
        prem[nc] = pilch[0];
        pilch[0] = 0;
    }
}

void GrapheAvecFsAps::composantFortementConnexe(vector<int>& num, vector<int>& ro, vector<int>& prem, vector<int>& cfc, vector<int>& pred, vector<int>& pilch) const
{
    num.resize(nbSommets() + 1, 0);
    ro.resize(nbSommets() + 1, 0);
    prem.resize(nbSommets() + 1, 0);
    cfc.resize(nbSommets() + 1);
    pred.resize(nbSommets() + 1, 0);
    pilch.resize(nbSommets() + 1);

    std::stack<int> tarj{};
    vector<bool> entarj(nbSommets() + 1, false);
    num[0] = nbSommets();
    ro[0] = nbSommets();
    int ns = 0, nc = 0;
    pilch[0] = 0;
    for(int s = 1; s <= nbSommets(); ++s){
        if(num[s] == 0)
            traverse(s, ns, nc, num, pilch, ro, entarj, cfc, tarj, pred, prem);
    }
    prem[0] = nc;
    cfc[0] = ns;
}

void GrapheAvecFsAps::grapheReduit(vector<int>& fsr, vector<int>& apsr) const
{
    vector<int> num{}, ro{}, prem{}, cfc{}, pred{}, pilch{};
    composantFortementConnexe(num, ro, prem, cfc, pred, pilch);
    //
    int kr = 1, nbc = prem[0];
    vector<bool> deja_mis(nbc + 1);
    fsr.resize(_fs[0] + 1);
    apsr.resize(nbc + 1);
    apsr[0] = nbc;
    //
    for(int i = 1; i <= nbc; ++i)
    {
        apsr[i] = kr;
        for(int i = 1; i <= nbc; ++i){
            deja_mis[i] = false;
        }
        deja_mis[i] = true;
        int s = prem[i];
        while(s != 0)
        {
            for(int t = _aps[s]; _fs[t] != 0; ++t){
                if(deja_mis[cfc[_fs[t]]] == false){
                    fsr[kr++] = cfc[_fs[t]];
                    deja_mis[cfc[_fs[t]]] = true;
                }
            }
            s = pilch[s];
        }
        fsr[kr++] = 0;
    }
    fsr[0] = kr - 1;
}

void GrapheAvecFsAps::baseReduit(vector<int>& br) const
{
    vector<int> fsr{}, apsr{};
    grapheReduit(fsr, apsr);
    int nr = apsr[0];
    br.resize(nr + 1);
    //ddir
    vector<int> ddir(nr + 1, 0);
    for(int kr = 1; kr <= fsr[kr]; ++kr){
        ++ddir[fsr[kr]];
    }
    int nb = 0;
    for(int c = 1; c <= nr; ++c){
        if(ddir[c] == 0)
            br[++nb] = c;
    }
    br[0] = nb;
}

void GrapheAvecFsAps::editionBases() const
{
    vector<int> num{}, ro{}, prem{}, cfc{}, pred{}, pilch{}, br{};
    composantFortementConnexe(num, ro, prem, cfc, pred, pilch);
    baseReduit(br);

    int nb = br[0];
    vector<int> base(nb + 1);
    base[0] = nb;
    int p = 1, s = prem[br[1]];
    while(p >= 1)
    {
        if(p <= nb && s != 0)
        {
            base[p++] = s;
            if(p <= nb)
                s = prem[br[p]];
            else
                afficher(base);
        }
        else{
            --p;
            s = pilch[base[p]];
        }
    }
}

bool GrapheAvecFsAps::poidsPositif() const
{
    for(unsigned i = 1; i < _poids.size(); ++i){
       if(_poids[i] < 0)
           return false;
    }
    return true;
}

void GrapheAvecFsAps::djikstra(int s, vector<int>& dist, vector<int>& pred) const
{
    int n = _aps[0];
    dist.resize(n + 1, INT_MAX);
    pred.resize(n + 1);
    dist[0] = pred[0] = n;
    vector<bool> inS(n + 1);
    for(int i = _aps[s]; _poids[i] != INT_MAX; ++i){
        dist[_fs[i]] = _poids[i];
    }
    for(int i = 1; i <= n; ++i){
        inS[i] = true;
        if(dist[i] != INT_MAX)
            pred[i] = s;
        else
            pred[i] = -1;
    }
    dist[s] = pred[s] = 0;
    inS[s] = false; //on supprime le sommet 1
    int ind = n -1; //Nb elements qui restent à traiter
    int j;
    while(ind > 0)
    {
        int mini = INT_MAX;
        for(int i = 1; i <= n; ++i)
        {
            if(inS[i]){
                if(dist[i] < mini){
                    mini = dist[i];
                    j = i;
                }
            }
        }
        if(mini == INT_MAX) return;
        inS[j] = false;
        for(int k = _aps[j]; (_fs[k]) != 0; ++k)
        {
            if(inS[_fs[k]])
            {
                int v;
                if(_poids[k]!= INT_MAX){
                    v = dist[j] + _poids[k];
                    if(v < dist[_fs[k]]){
                        dist[_fs[k]] = v;
                        pred[_fs[k]] = j;
                    }
                }
            }
        }
        --ind;
    }
}

vector<int> GrapheAvecFsAps::meilleurCheminDjikstra(int s, int t) const
{
    vector<int> dist, pred, chemin, inverse;
    djikstra(s, dist, pred);
    int arrive = t;
    do{
        inverse.push_back(arrive);
        arrive = pred[arrive];
    }while(arrive != -1 && arrive != 0);
    for(int i = inverse.size() - 1; i >= 0; --i){
        chemin.push_back(inverse[i]);
    }
    return chemin;
}

void GrapheAvecFsAps::mat_dist_djikstra(vector<vector<int>>& matDist, vector<vector<int>>& matPred) const
{
    int n = _aps[0];
    matDist.resize(n + 1);
    matPred.resize(n + 1);
    for(int s = 1; s <= n; ++s)
        djikstra(s, matDist[s], matPred[s]);
}

void GrapheAvecFsAps::afficher(const vector<int> & tab) const
{
    for(unsigned i = 0; i< tab.size(); ++i){
        std::cout<<tab[i]<<" ";
    }
    std::cout<<std::endl;
}

void GrapheAvecFsAps::lectureGraphe(std::string fileName)
{
    std::ifstream grapheFsAps(fileName);
    int nbSommets, nbArcs, nbPoids;
    _aps.clear(); _fs.clear(); _poids.clear(); _sommets.clear();
    bool oriente;
    grapheFsAps>>oriente;
    _oriente = oriente;
    grapheFsAps>>nbSommets;
    _aps.resize(nbSommets + 1);
    _aps[0] = nbSommets;
    for (int i = 1; i <= nbSommets; ++i)
    {
        grapheFsAps>>_aps[i];
    }
    std::string s = "";
    _sommets.resize(nbSommets + 1);
    _sommets[0] = Sommet();
    for (int i = 1; i <= nbSommets; ++i)
    {
        grapheFsAps>>s;
        _sommets[i] = Sommet(i, s);
    }
    grapheFsAps>>nbArcs;
    _fs.resize(nbArcs + 1);
    _fs[0] = nbArcs;
    for (int i = 1; i <= nbArcs; ++i)
    {
        grapheFsAps>>_fs[i];
    }
    grapheFsAps>>nbPoids;
    _poids.resize(nbPoids + 1);
    _poids[0] = nbPoids;
    for (int i = 1; i <= nbPoids; ++i)
    {
        grapheFsAps>>_poids[i];
    }
}

void GrapheAvecFsAps::ecritureGraphe(std::string fileName)
{
    std::ofstream grapheFsAps(fileName);
    int n = nbSommets();
    grapheFsAps<<_oriente<<std::endl;
    grapheFsAps<<n<<std::endl;
    for (int i = 1; i <= n; ++i)
    {
        grapheFsAps<<_aps[i]<<" ";
    }

    grapheFsAps<<std::endl;
    for (int i = 1; i <= n; ++i)
    {
        grapheFsAps<<_sommets[i].getNomStation()<<" ";
    }
    grapheFsAps<<std::endl;
    int m = _fs[0];
    grapheFsAps<<m<<std::endl;
    for (int i = 1; i <= m; ++i)
    {
        grapheFsAps<<_fs[i]<<" ";
    }
    grapheFsAps<<std::endl;
    int p = _poids[0];
    grapheFsAps<<p<<std::endl;
    for (int i = 1; i <= p; ++i)
    {
        grapheFsAps<<_poids[i]<<" ";
    }
}

void GrapheAvecFsAps::afficherMatrice(const vector<vector<int>>& tab) const
{
    for(unsigned i = 0; i < tab.size(); ++i)
    {
        for(unsigned j = 0; j < tab[i].size(); ++j)
        {
            if(tab[i][j] == INT_MAX){
                std::cout<<"INF"<<" ";
            }
            else if(tab[i][j] == -INT_MAX){
                std::cout<<"-INF"<<" ";
            }
            else{
                std::cout<<tab[i][j]<<" ";
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
//

void GrapheAvecFsAps::ordonnancement(vector<int>& dateAuPlusTot, vector<int>& dateAuPlusTard,vector<std::string>& sommetCritique )
{
    int n = nbSommets();
    //Déterminer une numérotation num des sommets telle que pour tout arc (s,t), num(s) < num(t)
    vector<int> tabRang;
    rang(tabRang);
    tabRang[0]=0;
    int rangMax = *std::max_element(tabRang.begin(), tabRang.end());
    vector<int> numerotation;
    numerotation.push_back(0);
    for (int i = 0; i <= rangMax ; i++ )
    {
        for (int j=1;j<=n;j++)
        {
            if (tabRang[j]==i)
                numerotation.push_back(j);
        }
    }
    //Déterminer la date au plus tot pour chaque sommet
    vector<int> calculFp = calculFP();
    vector<int> calculApp = calculAPP();
    vector<int> calculDdi = calculDDI();
    dateAuPlusTot.resize(n+1);
    dateAuPlusTard.resize(n+1);
    for (int i=0; i<=n; i++)
    {
        dateAuPlusTot[i]=0;
        dateAuPlusTard[i]=0;

    }
    for (int i=1; i<=n; i++)
    {
        int current = numerotation[i];
        int arcMaximum = 0;
        for (int j=0; j<calculDdi[current];j++)
        {
            int pred = calculFp[calculApp[current]+j];
            int duree = getArc(pred,current)+dateAuPlusTot[pred];
            if(duree>arcMaximum)
            {

                arcMaximum=duree;
            }
        }

        dateAuPlusTot[current]=arcMaximum;
    }

    //Déterminer la date au plus tard pour chaque sommet
    for (int i=n; i>0; i--)
    {
        int current = numerotation[i];
        int arcMinimum = dateAuPlusTot[n];
        int k = _aps[current];
        while(_fs[k]!=0)
        {
            int succ=_fs[k];
            int duree = dateAuPlusTard[succ]-getArc(current,succ);
            if (duree<arcMinimum)
            {
                arcMinimum=duree;
            }
            k++;
        }
        dateAuPlusTard[current]=arcMinimum;
    }
    //determination des chemins critiques
    for (int i=1; i<=n; i++)
    {
        if (dateAuPlusTard[i]==dateAuPlusTot[i])
            sommetCritique.push_back(_sommets[i].getNomStation());
    }

}

int GrapheAvecFsAps::getArc(int pred, int succ)
{
    int i=_aps[pred];
    while(_fs[i]!= succ)
    {
        ++i;
    }
    return _poids[i];

}

vector<int> GrapheAvecFsAps::calculAPP() const
{
	vector<int> app;
	vector<int> calculDdi = calculDDI();
	int n=_aps[0];
	app.resize(n+1);
	app[0] = n;
	app[1] = 1;
	for(int i=1; i<n; i++)
		app[i+1] = app[i] + calculDdi[i] + 1;
	return app;
}

vector<int> GrapheAvecFsAps::calculFP() const
{
	vector<int> calculApp = calculAPP();
	vector<int> fp;
	int n = _aps[0];
	int m = _fs[0];
	fp.resize(m+1);
	fp[0] = m;
	int k=1,j;
	for(int i=1; i<=n; i++)
	{
		 while ((j=_fs[k]) > 0)
		{
			fp[calculApp[j]] = i;
			calculApp[j]++;
			k++;
		 }
	 k++;
 	}
 	fp[calculApp[n]] = 0;
	for(int i=n-1; i>=1; i--)
	{
		fp[calculApp[i]] = 0;
		calculApp[i+1] = calculApp[i] + 1;
	}
	calculApp[1] = 1;
 	return fp;
}

vector<int> GrapheAvecFsAps::calculDDI() const
{
	int n= nbSommets();
    vector <int> ddi;
    ddi.resize(n+1);
    ddi[0] = n;
    for(int s = 1; s <= n; s++)
       ddi[s] = 0;
    for(int k = 1; k < _fs[0]; k++)
    {
        if (_fs[k] !=0)
            ddi[_fs[k]] ++;
    }
    return ddi;
}
