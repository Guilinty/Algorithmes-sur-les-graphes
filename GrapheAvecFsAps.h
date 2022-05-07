#ifndef GrapheAvecFsAps_H
#define GrapheAvecFsAps_H
#include "../Graphe.h"
#include "../Sommet.h"
#include <vector>
#include <queue>
#include <stack>

using std::vector;
class GrapheAvecAdjacent;

class GrapheAvecFsAps : public Graphe
{
public:
    GrapheAvecFsAps(bool oriente = true, bool value = false);
    GrapheAvecFsAps(const GrapheAvecAdjacent g);
    void MatAdj2FsAps(const GrapheAvecAdjacent g);
    virtual void ajoutSommet(const Sommet& s) override;
    virtual void supprimeSommet(int s) override;
    virtual Sommet getSommet(int s) const override;
    virtual int  nbSommets() const override;
    virtual void printSommets() const override;
    virtual void setOriente(bool oriente);
    virtual bool estOriente() const;
    virtual void setValue(bool value);
    virtual bool estValue() const;
    //GETTERS
    vector<int> getFS() const;
    vector<int> getAPS() const;
    vector<int> getPoids() const;
    vector<Sommet> getSommets() const;
    void ajoutArc(int s, int t, int couts = 1) ;
    void supprimeArc(int s, int t);
    //Changement d'orientation des arcs
    void inverser();
    //Calcul des distances
    void matriceDesDistances(vector<vector<int>>& matDist) const;
    void descenteEnLarg(int r, vector<int>& distances) const;
    //Rang
    void rang(vector<int>& rang) const;
    //Tarjan
    void composantFortementConnexe(vector<int>& num, vector<int>& ro, vector<int>& prem, vector<int>& cfc, vector<int>& pred, vector<int>& pilch) const;
    void grapheReduit(vector<int>& fsr, vector<int>& apsr) const;
    void baseReduit(vector<int>& br) const;
    void editionBases() const;
    //Djikstra
    bool poidsPositif() const;
    void djikstra(int s, vector<int>& dist, vector<int>& pred) const;
    vector<int> meilleurCheminDjikstra(int s, int t) const;
    void mat_dist_djikstra(vector<vector<int>>& matDist, vector<vector<int>>& matPred) const;
    //Ordonnancement
    void ordonnancement(vector<int>& dateAuPlusTot, vector<int>& dateAuPlusTard, vector<std::string>& sommetCritique);
    //Ecriture et lecture dans un fichier
    virtual void lectureGraphe(std::string fileName) override;
    virtual void ecritureGraphe(std::string fileName) override;
    virtual void afficher(const vector<int> & tab) const override;
    void afficherMatrice(const vector<vector<int>>& tab) const;
private:
    vector<int> _aps;
    vector<int> _fs;
    vector<Sommet> _sommets;
    bool _oriente;
    bool _value;
    vector<int> _poids;
    //
    void traverse(int s, int& ns, int& nc,
                  vector<int>& num, vector<int>& pilch,
                  vector<int>& ro, vector<bool>& entarj,
                  vector<int>& cfc,
                  std::stack<int>& tarj, vector<int>& pred,
                  vector<int>& prem) const;
    void empiler(int x, vector<int>& pilch) const;
    int getArc(int pred, int current);
    vector<int> calculAPP() const;
    vector<int> calculFP() const;
    vector<int> calculDDI() const;
    vector<int> calculDDE() const;
};

#endif // GrapheAvecFsAps_H
