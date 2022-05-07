#include <iostream>
#include "GrapheAvecFsAps.h"
#include "GrapheAvecAdjacent.h"
#include <vector>
#include <stack>
#include "Application.h"
#include "Sommet.h"

using namespace std;

void testAjoutSuppression()
{
    Sommet s1{1, "Mulhouse"},
           s2{2, "Paris"},
           s3{3, "Strasbourg"},
           s4{4, "Toulouse"};
    GrapheAvecFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    //graph.printSommets();
    cout<<"APRES AJOUT D'UN SUCCESSEUR"<<endl;
    graph.ajoutArc(1, 2, 2);
    graph.ajoutArc(1, 3);
    graph.ajoutArc(1, 4);
    graph.ajoutArc(2, 1);
    graph.ajoutArc(2, 3);
    graph.ajoutArc(3, 1);
    graph.ajoutArc(3, 2);
    graph.ajoutArc(3, 4);
    graph.ajoutArc(4, 3);
    graph.ajoutArc(4, 2);
    graph.ajoutArc(4, 1);
    //
    //graph.supprimeArc(3, 2);//milieu
    //graph.supprimeArc(1, 2);//debut
    //graph.supprimeArc(3, 4);//fin
    //graph.supprimeArc(4, 6);//arc inexistant
    //
    //graph.supprimeSommet(4);
    //
    graph.printSommets();
}

void testDistance()
{
    Sommet s1{1, "Mulhouse"},
           s2{2, "Paris"},
           s3{3, "Strasbourg"},
           s4{4, "Toulouse"},
           s5{5, "Bordeaux"},
           s6{6, "Rennes"},
           s7{7, "Grenoble"};
    GrapheAvecFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    graph.ajoutSommet(s6);
    graph.ajoutSommet(s7);
    //
    graph.ajoutArc(1, 2);
    graph.ajoutArc(1, 3);
    graph.ajoutArc(1, 5);
    graph.ajoutArc(2, 3);
    graph.ajoutArc(3, 3);
    graph.ajoutArc(3, 4);
    graph.ajoutArc(4, 5);
    graph.ajoutArc(4, 6);
    graph.ajoutArc(5, 3);
    graph.ajoutArc(7, 4);
    graph.ajoutArc(7, 6);
    //
    graph.printSommets();
    //
    cout<<endl;
    cout<<"MATRICE DE DISTANCES"<<endl;
    vector<vector<int>> matDist{};
    graph.matriceDesDistances(matDist);
    for(unsigned i = 0; i < matDist.size(); ++i){
        for(unsigned j = 1; j < matDist[i].size(); ++j){
            cout<<matDist[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void afficher(const vector<int>& tab)
{
    for(unsigned i = 0; i< tab.size(); ++i){
        std::cout<<tab[i]<<" ";
    }
    std::cout<<std::endl;
}

void testRang()
{
    Sommet s1{1, "Mulhouse"},
       s2{2, "Paris"},
       s3{3, "Strasbourg"},
       s4{4, "Toulouse"},
       s5{5, "Bordeaux"},
       s6{6, "Rennes"},
       s7{7, "Grenoble"},
       s8{8, "Nantes"};

    GrapheAvecFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    graph.ajoutSommet(s6);
    graph.ajoutSommet(s7);
    graph.ajoutSommet(s8);
    //
    graph.ajoutArc(1, 8);
    graph.ajoutArc(2, 1);
    graph.ajoutArc(2, 4);
    graph.ajoutArc(2, 5);
    graph.ajoutArc(2, 6);
    graph.ajoutArc(2, 7);
    graph.ajoutArc(3, 4);
    graph.ajoutArc(3, 5);
    graph.ajoutArc(4, 1);
    graph.ajoutArc(4, 5);
    graph.ajoutArc(5, 7);
    graph.ajoutArc(6, 1);
    graph.ajoutArc(6, 4);
    graph.ajoutArc(6, 8);

    //
    graph.printSommets();
    cout<<endl;
    cout<<"RANG DES SOMMETS"<<endl;
    vector<int> rg{};
    graph.rang(rg);
    for(unsigned i = 0; i < rg.size(); ++i){
        cout<<rg[i]<<" ";
    }
    cout<<endl;
}

void testEditionBase()
{
   Sommet s1{1, "Mulhouse"},
       s2{2, "Paris"},
       s3{3, "Strasbourg"},
       s4{4, "Toulouse"},
       s5{5, "Bordeaux"},
       s6{6, "Rennes"},
       s7{7, "Grenoble"},
       s8{8, "Nantes"};
    GrapheAvecFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    graph.ajoutSommet(s6);
    graph.ajoutSommet(s7);
    graph.ajoutSommet(s8);
    //
    graph.ajoutArc(1, 2);
    graph.ajoutArc(1, 3);
    graph.ajoutArc(1, 4);
    graph.ajoutArc(3, 6);
    graph.ajoutArc(4, 7);
    graph.ajoutArc(5, 2);
    graph.ajoutArc(5, 1);
    graph.ajoutArc(5, 6);
    graph.ajoutArc(6, 3);
    graph.ajoutArc(6, 4);
    graph.ajoutArc(6, 7);
    graph.ajoutArc(6, 8);
    graph.ajoutArc(7, 4);
    graph.ajoutArc(8, 7);
    //
    graph.printSommets();
    cout<<"Composant fortement connexe"<<endl;
    vector<int> num{}, ro{}, prem{}, cfc{}, pred{}, pilch{};
    graph.composantFortementConnexe(num, ro, prem, cfc, pred, pilch);
    cout<<"EDITION BASE"<<endl;
    vector<int> apsr{}, fsr{}, br{};
    //graph.grapheReduit(fsr, apsr);
    //graph.baseReduit(br);
    graph.editionBases();
}

void testInverserGraphe()
{
    Sommet s1{1, "Mulhouse"},
       s2{2, "Paris"},
       s3{3, "Strasbourg"},
       s4{4, "Toulouse"},
       s5{5, "Bordeaux"};
       GrapheAvecFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    //
    graph.ajoutArc(1, 2);
    graph.ajoutArc(1, 3);
    graph.ajoutArc(2, 5);
    graph.ajoutArc(2, 4);
    graph.ajoutArc(3, 2);
    graph.ajoutArc(3, 4);
    graph.ajoutArc(4, 5);
    //
    cout<<"GRAPHE INITIAL"<<endl;
    graph.printSommets();
    cout<<endl;
    cout<<"GRAPHE INVERSE"<<endl<<endl;
    graph.inverser();
    graph.printSommets();
}

void testPrufer()
{
    Sommet s1{1, "Mulhouse"},
       s2{2, "Paris"},
       s3{3, "Strasbourg"},
       s4{4, "Toulouse"},
       s5{5, "Bordeaux"},
       s6{6, "Rennes"},
       s7{7, "Grenoble"},
       s8{8, "Nantes"},
       s9{9, "Marseille"};

    GrapheAvecAdjacent graph{false};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    graph.ajoutSommet(s6);
    graph.ajoutSommet(s7);
    graph.ajoutSommet(s8);
    graph.ajoutSommet(s9);
    //
    graph.ajoutArete(1, 9);
    graph.ajoutArete(1, 2);
    graph.ajoutArete(1, 3);
    graph.ajoutArete(3, 8);
    graph.ajoutArete(3, 5);
    graph.ajoutArete(3, 4);
    graph.ajoutArete(4, 6);
    graph.ajoutArete(4, 7);

    graph.printSommets();
    cout<<endl;
    //
    vector<int> prf{};
    graph.prufer(prf);
    cout<<endl;
    cout<<"CODAGE DE PRUFER"<<endl;
    for(unsigned i = 0; i < prf.size(); ++i){
        cout<<prf[i]<<" ";
    }
    cout<<endl;
    cout<<"DECODAGE DE PRUFER"<<endl;
    graph.decoprufer(prf);

}

void testDantzig()
{
    Sommet s1{1, "Mulhouse"},
       s2{2, "Paris"},
       s3{3, "Strasbourg"},
       s4{4, "Toulouse"},
       s5{5, "Bordeaux"};

    GrapheAvecAdjacent graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    //
    graph.ajoutArete(1, 2, -2);
    graph.ajoutArete(1, 3, 4);
    graph.ajoutArete(2, 4, 4);
    graph.ajoutArete(2, 5, 3);
    graph.ajoutArete(3, 4, 1);
    graph.ajoutArete(5, 1, 0);
    graph.ajoutArete(5, 3, -1);
    graph.ajoutArete(5, 4, -1);
    //
    graph.printSommets();
    cout<<endl;
    //
    vector<vector<int>> dist{{0, -2, 4, INT_MAX, INT_MAX},
                            {INT_MAX, 0, INT_MAX, 4, 3},
                            {INT_MAX, INT_MAX, 0, 1, INT_MAX},
                            {INT_MAX, INT_MAX, INT_MAX, 0, INT_MAX},
                            {0, INT_MAX, -1, -1, 0}};
    graph.dantzig(dist);
    cout<<"DANTZIG "<<endl;
    for(unsigned i = 0; i < dist.size(); ++i){
        for(unsigned j = 0; j < dist[i].size(); ++j){
            cout<<dist[i][j]<<' ';
        }
        cout<<endl;
    }
}

void testKruskal()
{
    Sommet s1{1, "Mulhouse"},
       s2{2, "Paris"},
       s3{3, "Strasbourg"},
       s4{4, "Toulouse"},
       s5{5, "Bordeaux"},
       s6{6, "Rennes"},
       s7{7, "Grenoble"},
       s8{8, "Nantes"};

    GrapheAvecAdjacent graph{false, true};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    graph.ajoutSommet(s6);
    graph.ajoutSommet(s7);
    graph.ajoutSommet(s8);
    //
    graph.ajoutArete(1, 2, 2);
    graph.ajoutArete(1, 4, 3);
    graph.ajoutArete(1, 8, 1);
    graph.ajoutArete(2, 4, 1);
    graph.ajoutArete(2, 3, 1);
    graph.ajoutArete(2, 5, 2);
    graph.ajoutArete(3, 4, 1);
    graph.ajoutArete(3, 5, 1);
    graph.ajoutArete(3, 6, 1);
    graph.ajoutArete(3, 7, 2);
    graph.ajoutArete(4, 7, 1);
    graph.ajoutArete(4, 8, 2);
    graph.ajoutArete(5, 6, 2);
    graph.ajoutArete(6, 7, 2);
    graph.ajoutArete(7, 8, 3);
    //
    cout<<"RESULTAT DE KRUSKAL"<<endl;
    graph.kruskal();
}

void testDjikstra()
{
    Sommet s1{1, "Mulhouse"},
    s2{2, "Paris"},
    s3{3, "Strasbourg"},
    s4{4, "Toulouse"},
    s5{5, "Bordeaux"},
    s6{6, "Rennes"},
    s7{7, "Grenoble"};
    //
    GrapheAvecFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    graph.ajoutSommet(s6);
    graph.ajoutSommet(s7);
    //
    graph.ajoutArc(1, 2, 1);
    graph.ajoutArc(1, 5, 3);
    graph.ajoutArc(2, 5, 1);
    graph.ajoutArc(2, 6, 4);
    graph.ajoutArc(3, 1, 0);
    graph.ajoutArc(3, 4, 2);
    graph.ajoutArc(4, 7, 4);
    graph.ajoutArc(5, 3, 1);
    graph.ajoutArc(5, 4, 6);
    graph.ajoutArc(5, 7, 0);
    graph.ajoutArc(6, 5, 1);
    graph.ajoutArc(7, 6, 1);
    //
    graph.supprimeSommet(1);
    //graph.supprimeArc(1, 2);
    graph.printSommets();
    cout<<endl;
    cout<<endl;
    vector<vector<int>> matDist{}, matPred{};
    cout<<"MATRICE DES DISTANCES DE DJIKSTRA"<<endl;
    graph.mat_dist_djikstra(matDist, matPred);
    cout<<"Distances : "<<endl;
    graph.afficherMatrice(matDist);
    cout<<"Predecesseurs : "<<endl;
    graph.afficherMatrice(matPred);
}

void testLectureEcritureFS_APS()
{
    Sommet s1{1, "Mulhouse"},
           s2{2, "Paris"},
           s3{3, "Strasbourg"},
           s4{4, "Toulouse"},
           s5{5, "Bordeaux"},
           s6{6, "Rennes"},
           s7{7, "Grenoble"};
    GrapheAvecFsAps graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    graph.ajoutSommet(s6);
    graph.ajoutSommet(s7);
    //
    graph.ajoutArc(1, 2);
    graph.ajoutArc(1, 3);
    graph.ajoutArc(1, 5);
    graph.ajoutArc(2, 3);
    graph.ajoutArc(3, 3);
    graph.ajoutArc(3, 4);
    graph.ajoutArc(4, 5);
    graph.ajoutArc(4, 6);
    graph.ajoutArc(5, 3);
    graph.ajoutArc(7, 4);
    graph.ajoutArc(7, 6);
    //
    graph.printSommets();

    //Graphe avec FS et APS
    graph.ecritureGraphe("grapheFsAps.txt");
    //GrapheAvecFsAps graph{};
    cout<<"Affichage du graphe à partir du fichier"<<endl<<endl;
    graph.lectureGraphe("grapheFsAps.txt");
    graph.printSommets();
}

void testLectureEcritureAdjacent()
{
    Sommet s1{1, "Mulhouse"},
       s2{2, "Paris"},
       s3{3, "Strasbourg"},
       s4{4, "Toulouse"},
       s5{5, "Bordeaux"};

    GrapheAvecAdjacent graph{};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    //
    graph.ajoutArete(1, 2, -2);
    graph.ajoutArete(1, 3, 4);
    graph.ajoutArete(2, 4, 4);
    graph.ajoutArete(2, 5, 3);
    graph.ajoutArete(3, 4, 1);
    graph.ajoutArete(5, 1, 0);
    graph.ajoutArete(5, 3, -1);
    graph.ajoutArete(5, 4, -1);
    //
    graph.printSommets();
    graph.ecritureGraphe("grapheAdjacent.txt");
    cout<<endl;
    //
    //GrapheAvecAdjacent graph{};
    graph.lectureGraphe("grapheAdjacent.txt");
    graph.printSommets();

}


void testOrdonnancement()
{
    Sommet s1{1, "A"},
    s2{2, "B"},
    s3{3, "C"},
    s4{4, "D"},
    s5{5, "E"},
    s6{6, "F"},
    s7{7, "G"},
    s8{8, "H"},
    s9{9, "I"},
    s10{10, "J"},
    s11{11, "K"};
    //
    GrapheAvecFsAps graph{true, true};
    graph.ajoutSommet(s1);
    graph.ajoutSommet(s2);
    graph.ajoutSommet(s3);
    graph.ajoutSommet(s4);
    graph.ajoutSommet(s5);
    graph.ajoutSommet(s6);
    graph.ajoutSommet(s7);
    graph.ajoutSommet(s8);
    graph.ajoutSommet(s9);
    graph.ajoutSommet(s10);
    graph.ajoutSommet(s11);
    //
    graph.ajoutArc(1, 2, 7);
    graph.ajoutArc(1, 4, 7);
    graph.ajoutArc(3, 4, 2);
    graph.ajoutArc(2, 5, 4);
    graph.ajoutArc(3, 6, 2);
    graph.ajoutArc(4, 7, 6);
    graph.ajoutArc(4, 9, 6);
    graph.ajoutArc(4, 6, 6);
    graph.ajoutArc(5, 6, 2);
    graph.ajoutArc(5, 7, 2);
    graph.ajoutArc(5, 9, 2);
    graph.ajoutArc(6, 8, 1);
    graph.ajoutArc(8, 10, 1);
    graph.ajoutArc(7, 11, 1);
    graph.ajoutArc(9, 11, 4);
    graph.ajoutArc(10, 11, 2);

    //
    //graph.printSommets();
    vector<int> datePlusTot, datePlusTard;
    vector<std::string> sommetCritique;
    graph.ordonnancement(datePlusTot, datePlusTard, sommetCritique);
    cout<<"Date au plus tot"<<endl;
    graph.afficher(datePlusTot);
    cout<<"Date au plus tard"<<endl;
    graph.afficher(datePlusTard);
    cout<<"sommets critiques"<<endl;
    for (int i=0; i<graph.nbSommets(); i++)
    {
        cout<<sommetCritique[i]<<"  ";
    }
}



int main()
{
    //testAjoutSuppression();
    //testDistance();
    //testRang();
    //testEditionBase();
    //testInverserGraphe();
    //testPrufer();
    //testDantzig();
    //testKruskal();
    //testDjikstra();
    //testLectureEcritureFS_APS();
    //testLectureEcritureAdjacent();
    //testOrdonnancement();
    Application appli{};
    appli.run();
    return 0;
}
