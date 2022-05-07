#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include "GrapheAvecAdjacent.h"
#include "GrapheAvecFsAps.h"

class Application{

public:
    Application() = default;
    void run();
private:
    //Graphe avec FS et APS
    void ajouterSommetFS_APS();
    void supprimerSommetFS_APS();
    void ajouterArc();
    void supprimerArc();
    //Graphe Adjacent
    void ajouterSommetAdj();
    void supprimerSommetAdj();
    void ajoutArete();
    void supprimeArete();
    Sommet CreerSommet();
    bool choixCorrect(int choix, int min, int max) const;
    //SOUS MENUS
    void menuCreerGraphe(int& choix) const;
    void menuGrapheAdjacent(int& choix);
    void menuGrapheFS_APS(int& choix) const;
    void menuGeneral(int& choix);
    void sousMenuCreerGraphe();
    void sousMenuGrapheAdjacent();
    void sousMenuGrapheFS_APS();
    void menuChargerGraphe(int& choix) const;
    void sousMenuChargerGraphe();
    void menuAfficherGraphe(int& choix) const;
    void sousMenuAfficherGraphe();
    void menuManipulerGraphe(int& choix) const;
    void sousMenuManipulerGraphe();
    void menuAide(int& choix) const;
    void sousMenuAide();
    void creerGraphe();
    //
    void inverser();
    void matriceDesDistances() const;
    void calculerRang() const ;
    void calculerCFC() const ;
    void calculerGrapheReduit() const;
    void baseReduit() const;
    void editerBase() const ;
    void tarjan() const;
    //
    void djikstra() const;
    void prufer() const;
    void kruskal();
    void ordonnancement();
    void dantzig();

GrapheAvecFsAps d_grapheOrienteFsAps;
GrapheAvecAdjacent d_grapheNonOrienteAdj;
};

#endif // APPLICATION_H_INCLUDED
