#include"Application.h"
#include"Sommet.h"
#include<iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

void Application::run()
{
    int choix;
    do{
        menuGeneral :
        menuGeneral(choix);
        switch (choix)
        {
            case 1: system("cls"); sousMenuCreerGraphe(); system("cls"); goto menuGeneral;
                    break;
            case 2: system("cls"); sousMenuManipulerGraphe(); system("cls"); goto menuGeneral;
                    break;
            case 3: system("cls"); sousMenuChargerGraphe(); system("cls"); goto menuGeneral;
                    break;
            case 4: system("cls"); sousMenuAfficherGraphe(); system("cls"); goto menuGeneral;
                    break;
            case 5: system("cls"); inverser(); system("cls"); goto menuGeneral;
                    break;
            case 6: system("cls"); matriceDesDistances(); system("cls"); goto menuGeneral;
                    break;
            case 7: system("cls"); calculerRang(); system("cls"); goto menuGeneral;
                    break;
            case 8: system("cls"); tarjan(); system("cls"); goto menuGeneral;
                    break;
            case 9: system("cls"); djikstra(); system("cls"); goto menuGeneral;
                    break;
            case 10: system("cls"); prufer(); system("cls"); goto menuGeneral;
                    break;
            case 11: system("cls"); kruskal(); system("cls"); goto menuGeneral;
                    break;
            case 12: system("cls"); ordonnancement(); system("cls"); goto menuGeneral;
                    break;
            case 13: system("cls"); dantzig(); system("cls"); goto menuGeneral;
                    break;
            case 14: system("cls"); sousMenuAide(); system("cls"); goto menuGeneral;
                    break;
            default : break;
        }
    }while(!choixCorrect(choix, 1, 14));

}

void Application::menuGeneral(int &choix)
{
    cout<<"+---------------------------------------+"<<endl;
    cout<<"|               MENU GENERAL            |"<<endl;
    cout<<"+---------------------------------------+"<<endl;
    cout<<"|    1 - Creer un graphe                |"<<endl;
    cout<<"|    2 - Manipuler un graphe            |"<<endl;
    cout<<"|    3 - Charger un graphe              |"<<endl;
    cout<<"|    4 - Afficher un graphe             |"<<endl;
    cout<<"|    5 - Inverser un graphe             |"<<endl;
    cout<<"|    6 - Matrice des distances          |"<<endl;
    cout<<"|    7 - Calcul du rang                 |"<<endl;
    cout<<"|    8 - CFC selon Tarjan               |"<<endl;
    cout<<"|    9 - Djikstra                       |"<<endl;
    cout<<"|   10 - Codage de prufer               |"<<endl;
    cout<<"|   11 - Kruskal                        |"<<endl;
    cout<<"|   12 - Ordonnancement                 |"<<endl;
    cout<<"|   13 - Dantzig                        |"<<endl;
    cout<<"|   14 - Aide                           |"<<endl;
    cout<<"|   15 - Quitter                        |"<<endl;
    cout<<"+---------------------------------------+"<<endl;
    cout<<"choix : ";
    cin>>choix;
    cout<<endl;
}

bool Application::choixCorrect(int choix, int min, int max) const
{
    return (choix < min || choix > max);
}

// GRAPHE AVEC ORIENTE FS ET APS VALUE/NON VALUE
void Application::ajouterSommetFS_APS()
{
    cout<<"ajouter un sommet"<<endl;
    Sommet s=CreerSommet();
    d_grapheOrienteFsAps.ajoutSommet(s);
}

void Application::supprimerSommetFS_APS()
{
    cout<<"Numero du sommet à supprimer "<<endl;
    int num;
    cin>>num;
    d_grapheOrienteFsAps.supprimeSommet(num);
}

void Application::ajouterArc()
{
    int s1, s2, poid;
    cout<<"numero de sommet de départ"<<endl;
    cin>>s1;
    cout<<"numero de sommet d'arrivé"<<endl;
    cin>>s2;
    if(d_grapheOrienteFsAps.estValue()){
        cout<<"donner son cout"<<endl;
        cin>>poid;
        d_grapheOrienteFsAps.ajoutArc(s1, s2, poid);
    }
    else{
        d_grapheOrienteFsAps.ajoutArc(s1, s2);
    }
}

void Application::supprimerArc()
{
    int s, t;
    cout<<"numero de sommet de départ"<<endl;
    cin>>s;
    cout<<"numero de sommet d'arrivé"<<endl;
    cin>>t;
    if(d_grapheOrienteFsAps.estValue()){
        d_grapheOrienteFsAps.supprimeArc(s, t);
    }
    else{
        d_grapheOrienteFsAps.supprimeArc(s, t);
    }
}
//
Sommet Application::CreerSommet()
{
    int numero;
    string nom;
    cout<<"entrez le numero"<<endl;
    cin>>numero;
    cout<<"entrez le nom"<<endl;
    cin>>nom;
    return Sommet{numero, nom};
}

// GRAPHE AVEC NON ORIENTE ADJACENT ORIENTE VALUE/NON VALUE
void Application::ajouterSommetAdj()
{
    cout<<"ajouter un sommet"<<endl;
    Sommet s=CreerSommet();
    d_grapheNonOrienteAdj.ajoutSommet(s);

}

void Application::supprimerSommetAdj()
{
    cout<<"Numero du sommet à supprimer"<<endl;
    int num;
    cin>>num;
    d_grapheNonOrienteAdj.supprimeSommet(num);
}

void Application::ajoutArete()
{
    int s1, s2, poid;

    cout<<"numero de sommet de départ"<<endl;
    cin>>s1;
    cout<<"numero de sommet d'arrivé"<<endl;
    cin>>s2;
    if(d_grapheNonOrienteAdj.estValue()){
        cout<<"donner son poid"<<endl;
        cin>>poid;
        d_grapheNonOrienteAdj.ajoutArete(s1, s2, poid);
    }
    else{
        d_grapheNonOrienteAdj.ajoutArete(s1, s2);
    }
}

void Application::supprimeArete()
{
    int s1, s2;

    cout<<"numero de sommet de départ"<<endl;
    cin>>s1;
    cout<<"numero de sommet d'arrivé"<<endl;
    cin>>s2;
    if(d_grapheNonOrienteAdj.estValue()){
        d_grapheNonOrienteAdj.supprimeArete(s1, s2);
    }
    else{
        d_grapheNonOrienteAdj.supprimeArete(s1, s2);
    }
}

void Application::menuCreerGraphe(int& choix) const
{
    cout<<"+--------------------------------+"<<endl;
    cout<<"|        CREER GRAPHE            |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<"|    1 - Graphe Orienté          |"<<endl;
    cout<<"|    2 - Graphe Non Orienté      |"<<endl;
    cout<<"|    3 - Retour                  |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<"choix : ";
    cin>>choix;
    cout<<endl;
}

void Application::sousMenuCreerGraphe()
{
    int choix;
    do{
        menuGraphe :
        menuCreerGraphe(choix);
        switch(choix)
        {
            case 1 : system("cls");
                int choix;
                do{
                    cout<<"1- Pour graphe orienté valué"<<endl;
                    cout<<"2- Pour graphe orienté non valué"<<endl;
                    cin>>choix;
                }while(choix != 1 && choix != 2);
                if(choix == 1){
                    d_grapheOrienteFsAps = new GrapheAvecFsAps{true, true};
                    d_grapheOrienteFsAps.setValue(true);
                    cout<<"Graphe Oriente Value cree !!"<<endl;
                }
                else{
                    d_grapheOrienteFsAps = new GrapheAvecFsAps{true, false};
                    d_grapheOrienteFsAps.setValue(false);
                    cout<<"Graphe Oriente Non Value cree !!"<<endl;
                }
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            case 2 : system("cls");
                int choix1;
                do{
                    cout<<"1- Pour graphe non orienté valué"<<endl;
                    cout<<"2- Pour graphe non orienté non valué"<<endl;
                    cin>>choix1;
                }while(choix1 != 1 && choix1 != 2);
                if(choix1 == 1){
                    d_grapheNonOrienteAdj = new GrapheAvecAdjacent{false, true};
                    d_grapheNonOrienteAdj.setValue(true);
                    d_grapheNonOrienteAdj.setOriente(false);
                    cout<<"Graphe Non Oriente Value cree !!"<<endl;
                }
                else{
                    d_grapheNonOrienteAdj = new GrapheAvecAdjacent{false, false};
                    d_grapheNonOrienteAdj.setValue(false);
                    d_grapheNonOrienteAdj.setOriente(false);
                    cout<<"Graphe Non Oriente Non Value cree !!"<<endl;
                }
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            default :
                break;
        }

    }while(!choixCorrect(choix, 1, 2));
}
//
void Application::menuManipulerGraphe(int& choix) const
{
    cout<<"+--------------------------------+"<<endl;
    cout<<"|        MANIPULER GRAPHE        |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<"|    1 - Graphe Orienté          |"<<endl;
    cout<<"|    2 - Graphe Non Orienté      |"<<endl;
    cout<<"|    3 - Retour                  |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<"choix : ";
    cin>>choix;
    cout<<endl;
}

void Application::sousMenuManipulerGraphe()
{
    int choix;
    do{
        menuGraphe :
        menuManipulerGraphe(choix);
        switch(choix)
        {
            case 1 : system("cls");
                sousMenuGrapheFS_APS();
                system("cls");
                goto menuGraphe;
                break;
            case 2 : system("cls");
                sousMenuGrapheAdjacent();
                //system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            default : break;
        }

    }while(!choixCorrect(choix, 1, 2));
}
//
void Application::menuGrapheAdjacent(int& choix)
{
    cout<<"+------------------------------------+"<<endl;
    cout<<"|           GRAPHE NON ORIENTE       |"<<endl;
    cout<<"+------------------------------------+"<<endl;
    cout<<"|  1 - Ajouter un sommet             |"<<endl;
    cout<<"|  2 - Ajouter un arete              |"<<endl;
    cout<<"|  3 - Supprimer un sommet           |"<<endl;
    cout<<"|  4 - Supprimer un arete            |"<<endl;
    cout<<"|  5 - Enregistrer le graphe         |"<<endl;
    cout<<"|  6 - Retour                        |"<<endl;
    cout<<"+------------------------------------+"<<endl;
    cout<<"choix : ";
    cin>>choix;
    cout<<endl;
}

void Application::sousMenuGrapheAdjacent()
{
    int choix;
    do{
        menuAdjacent :
        menuGrapheAdjacent(choix);
        switch(choix)
        {
            case 1 : ajouterSommetAdj(); system("cls"); goto menuAdjacent; break;
            case 2 : ajoutArete(); system("cls"); goto menuAdjacent; break;
            case 3 : supprimerSommetAdj(); system("cls"); goto menuAdjacent; break;
            case 4 : supprimeArete(); system("cls"); goto menuAdjacent; break;
            case 5 :
            {
                cout<<"Nom du fichier : ";
                std::string fileName;
                cin>>fileName;
                d_grapheNonOrienteAdj.ecritureGraphe(fileName + ".txt");
                cout<<"Enregistrement effectue !!!"<<endl;
                system("PAUSE");
                system("cls");
                goto menuAdjacent;
                break;
            }
            default : break;
        }

    }while(!choixCorrect(choix, 1, 5));
}

void Application::menuGrapheFS_APS(int& choix) const
{
    cout<<"+------------------------------------+"<<endl;
    cout<<"|            GRAPHE ORIENTE          |"<<endl;
    cout<<"+------------------------------------+"<<endl;
    cout<<"|  1 - Ajouter un sommet             |"<<endl;
    cout<<"|  2 - Ajouter un arc                |"<<endl;
    cout<<"|  3 - Supprimer un sommet           |"<<endl;
    cout<<"|  4 - Supprimer un arc              |"<<endl;
    cout<<"|  5 - Enregistrer le graphe         |"<<endl;
    cout<<"|  6 - Retour                        |"<<endl;
    cout<<"+------------------------------------+"<<endl;
    cout<<"choix : ";
    cin>>choix;
    cout<<endl;
}

void Application::sousMenuGrapheFS_APS()
{
    int choix;
    do{
        menuFS_APS :
        menuGrapheFS_APS(choix);
        switch(choix)
        {
            case 1 : ajouterSommetFS_APS(); system("cls"); goto menuFS_APS; break;
            case 2 : ajouterArc(); system("cls"); goto menuFS_APS; break;
            case 3 : supprimerSommetFS_APS(); system("cls"); goto menuFS_APS; break;
            case 4 : supprimerArc(); system("cls"); goto menuFS_APS; break;
            case 5 :
            {
                cout<<"Nom du fichier : ";
                std::string fileName;
                cin>>fileName;
                d_grapheOrienteFsAps.ecritureGraphe(fileName + ".txt");
                cout<<"Enregistrement effectue !!!"<<endl;
                system("PAUSE");
                system("cls");
                goto menuFS_APS;
                break;
            }
            default : break;
        }

    }while(!choixCorrect(choix, 1, 5));
}

void Application::menuChargerGraphe(int& choix) const
{
    cout<<"+-----------------------------------+"<<endl;
    cout<<"|           CHARGER GRAPHE          |"<<endl;
    cout<<"+-----------------------------------+"<<endl;
    cout<<"|    1 - Graphe Orienté             |"<<endl;
    cout<<"|    2 - Graphe Non Orienté         |"<<endl;
    cout<<"|    3 - Retour                     |"<<endl;
    cout<<"+-----------------------------------+"<<endl;
    cout<<"choix : ";
    cin>>choix;
    cout<<endl;
}

void Application::sousMenuChargerGraphe()
{
    int choix;
    do{
        menuGraphe :
        menuChargerGraphe(choix);
        switch(choix)
        {
            case 1 :
            {
                system("cls");
                cout<<"FileName : ";
                std::string fileName;
                cin>>fileName;
                d_grapheOrienteFsAps.lectureGraphe(fileName + ".txt");
                cout<<endl;
                cout<<"Graphe orienté chargé avec succès "<<endl;
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            }
            case 2 :
            {
                system("cls");
                cout<<"FileName : ";
                std::string fileName;
                cin>>fileName;
                d_grapheNonOrienteAdj.lectureGraphe(fileName + ".txt");
                cout<<endl;
                cout<<"Graphe Non orienté chargé avec succès "<<endl;
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            }

            default : break;
        }

    }while(!choixCorrect(choix, 1, 2));
}

void Application::menuAfficherGraphe(int& choix) const
{
    cout<<"+-----------------------------------+"<<endl;
    cout<<"|           AFFICHER GRAPHE         |"<<endl;
    cout<<"+-----------------------------------+"<<endl;
    cout<<"|    1 - Graphe Orienté             |"<<endl;
    cout<<"|    2 - Graphe Non Orienté         |"<<endl;
    cout<<"|    3 - Retour                     |"<<endl;
    cout<<"+-----------------------------------+"<<endl;
    cout<<"choix : ";
    cin>>choix;
    cout<<endl;
}

void Application::sousMenuAfficherGraphe()
{
    int choix;
    do{
        menuGraphe :
        menuAfficherGraphe(choix);
        switch(choix)
        {
            case 1 : system("cls");
                cout<<"GRAPHE ORIENTE "<<endl;
                d_grapheOrienteFsAps.printSommets();
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            case 2 : system("cls");
                cout<<"GRAPHE NON ORIENTE "<<endl;
                d_grapheNonOrienteAdj.printSommets();
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            default : break;
        }

    }while(!choixCorrect(choix, 1, 2));
}

void Application::inverser()
{
    d_grapheOrienteFsAps.inverser();
    cout<<"Inversion du graphe oriente effectue!!!"<<endl<<endl;
    system("PAUSE");
}

void Application::matriceDesDistances() const
{
    vector<vector<int>> distances{};
    if(d_grapheOrienteFsAps.estOriente() && !d_grapheOrienteFsAps.estValue()){
        d_grapheOrienteFsAps.matriceDesDistances(distances);
        cout<<"MATRICE DES DISTANCES DU GRAPHE ORIENTE"<<endl;
        for( unsigned i = 0 ; i < distances.size(); i++){
            for(unsigned j = 0 ;j < distances[i].size(); j++){
                cout<<distances[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    else{
        cout<<"Le calcul de la MATRICE DE DISTANCE ne se fait que sur un graphe Orienté Non Valué!!"<<endl;
    }
    system("PAUSE");
}

void Application::calculerRang() const
{
    vector<int> rg;
    if(d_grapheOrienteFsAps.estOriente() && !d_grapheOrienteFsAps.estValue()){
        d_grapheOrienteFsAps.rang(rg);
        cout<<"RANG DU GRAPHE ORIENTE"<<endl;
        cout<<"Rang : ";
        d_grapheOrienteFsAps.afficher(rg);
    }
    else{
        cout<<"Le calcul du RANG ne se fait que sur un graphe Orienté Non Valué!!"<<endl;
    }
    system("PAUSE");
}
void Application::calculerCFC() const
{
    vector<int> num;
    vector<int> ro;
    vector<int> prem;
    vector<int> pilch;
    vector<int> pred;
    vector<int> cfc;
    cout<<"COMPOSANTS FORTEMENTS CONNEXES "<<endl;
    d_grapheOrienteFsAps.composantFortementConnexe(num, ro, prem, cfc, pred, pilch);
    cout<<"num : ";
    d_grapheOrienteFsAps.afficher(num);
    cout<<"ro : ";
    d_grapheOrienteFsAps.afficher(ro);
    cout<<"prem : ";
    d_grapheOrienteFsAps.afficher(prem);
    cout<<"pilch : ";
    d_grapheOrienteFsAps.afficher(pilch);
    cout<<"cfc : ";
    d_grapheOrienteFsAps.afficher(cfc);
    cout<<"pred : ";
    d_grapheOrienteFsAps.afficher(pred);
    cout<<endl;
}

void Application::calculerGrapheReduit() const
{
    vector<int> fsr{}, apsr{};
    cout<<"GRAPHE REDUIT"<<endl;
    d_grapheOrienteFsAps.grapheReduit(fsr, apsr);
    cout<<"apsr : ";
    d_grapheOrienteFsAps.afficher(apsr);
    cout<<"fsr : ";
    d_grapheOrienteFsAps.afficher(fsr);
    cout<<endl;
}

void Application::baseReduit() const
{
    vector<int> br{};
    d_grapheOrienteFsAps.baseReduit(br);
    cout<<"base reduite : ";
    d_grapheOrienteFsAps.afficher(br);
    cout<<endl;
}

void Application::editerBase() const
{
    cout<<"BASES REDUITES"<<endl;
    d_grapheOrienteFsAps.editionBases();
    cout<<endl;
}

void Application::tarjan() const
{
    if(d_grapheOrienteFsAps.estOriente() && !d_grapheOrienteFsAps.estValue()){
        calculerCFC();
        calculerGrapheReduit();
        editerBase();
    }
    else{
        cout<<"L'algorithme de TARJAN ne peut s'appliquer que sur un graphe Orienté et Non Valué"<<endl;
    }

    system("PAUSE");
}

void Application::prufer() const
{
    if((!d_grapheNonOrienteAdj.estValue() && !d_grapheNonOrienteAdj.estOriente()) && d_grapheNonOrienteAdj.nbSommets() > 2){
        vector<int> prf{};
        cout<<"CODAGE DE PRUFER"<<endl;
        d_grapheNonOrienteAdj.prufer(prf);
        for(unsigned i = 0; i < prf.size(); ++i){
            cout<<prf[i]<<" ";
        }
        cout<<endl;
        cout<<"DECODAGE DE PRUFER"<<endl;
        d_grapheNonOrienteAdj.decoprufer(prf);
    }
    else{
        cout<<"Le codage de PRUFER ne peut s'appliquer que sur un graphe non orienté et non valué ayant plus de 2 sommets"<<endl;
    }
    system("PAUSE");
}

void Application::djikstra() const
{
    if(d_grapheOrienteFsAps.poidsPositif() && d_grapheOrienteFsAps.estOriente() && d_grapheOrienteFsAps.estValue())
    {
        int choix;
        do{
            cout<<"1- Pour matrice des distances"<<endl;
            cout<<"2- Pour distance entre deux sommets"<<endl;
            cin>>choix;
        }while(choix != 1 && choix != 2);
        if(choix == 1){
            system("cls");
            vector<vector<int>> matDist{}, matPred{};
            cout<<"MATRICE DES DISTANCES DE DJIKSTRA"<<endl;
            d_grapheOrienteFsAps.mat_dist_djikstra(matDist, matPred);
            cout<<"Distances : "<<endl;
            d_grapheOrienteFsAps.afficherMatrice(matDist);
            cout<<endl;
            cout<<"Predecesseurs : "<<endl;
            d_grapheOrienteFsAps.afficherMatrice(matPred);
        }
        else{
            system("cls");
            int s, t;
            cout<<"Numero depart : "; cin>>s;
            cout<<"Numero arrive : "; cin>>t;
            vector<int> chemin = d_grapheOrienteFsAps.meilleurCheminDjikstra(s, t);
            cout<<endl;
            cout<<"MEILLEUR ITINERAIRE"<<endl;
            if(chemin.empty() || chemin.size() < 2){
                cout<<"Pas de chemin entre ces deux sommets"<<endl;
            }
            else{
                for(unsigned i = 0; i < chemin.size(); ++i){
                    cout<<d_grapheOrienteFsAps.getSommet(chemin[i]).getNomStation()<<" ";
                }
                cout<<endl;
                d_grapheOrienteFsAps.afficher(chemin);
            }
        }

    }
    else{
        cout<<"L'algorithme de DJIKSTRA ne peut s'appliquer que sur un graphe orienté et ayant des couts positifs"<<endl;
    }
    system("PAUSE");
}

void Application::kruskal()
{
    if(!d_grapheNonOrienteAdj.estOriente() && d_grapheNonOrienteAdj.estValue() && d_grapheNonOrienteAdj.nbSommets() > 2){
        cout<<"ARBRE RECOUVRANT MINIMAL DU GRAPHE NON ORIENTE"<<endl<<endl;
        d_grapheNonOrienteAdj.kruskal();
    }
    else{
        cout<<"L'algorithme de KRUSKAL ne peut s'appliquer que sur un graphe Non Orienté et Valué"<<endl;
    }
    system("PAUSE");
}

void Application::ordonnancement()
{
    if(d_grapheOrienteFsAps.estOriente() && d_grapheOrienteFsAps.estValue()){
        vector<int> datePlusTot, datePlusTard;
        vector<string> sommetCritique;
        d_grapheOrienteFsAps.ordonnancement(datePlusTot, datePlusTard, sommetCritique);
        cout<<"Date au plus tot"<<endl;
        d_grapheOrienteFsAps.afficher(datePlusTot);
        cout<<"Date au plus tard"<<endl;
        d_grapheOrienteFsAps.afficher(datePlusTard);
        cout<<"sommets critiques"<<endl;
        for (int i=0; i<d_grapheOrienteFsAps.nbSommets(); i++)
        {
            cout<<sommetCritique[i]<<"  ";
        }
        cout<<endl;
    }
    else{
        cout<<"L'algorithme d'ORDONNANCEMENT ne peut s'appliquer que sur un graphe orienté et valué"<<endl;
    }
    system("PAUSE");
}

void Application::dantzig()
{
    if(d_grapheOrienteFsAps.estOriente() && d_grapheOrienteFsAps.estValue()){
        vector<vector<int>> dist;
        GrapheAvecAdjacent d_graphe = new GrapheAvecAdjacent(d_grapheOrienteFsAps);
        d_graphe.dantzig(dist);
        cout<<" RESULTAT DE L'ALGORITHME DE DANTZIG"<<endl;
        //d_grapheOrienteFsAps.afficherMatrice(dist);
        for(unsigned i = 0; i < dist.size(); ++i){
            for(unsigned j = 0; j <dist[i].size(); ++j){
                cout<<dist[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    else{
        cout<<"L'algorithme de DANTZIG ne peut s'appliquer que sur un graphe orienté et valué"<<endl;
    }
    system("PAUSE");
}

void Application::menuAide(int& choix) const
{
    cout<<"+-----------------------------------+"<<endl;
    cout<<"|                 AIDE              |"<<endl;
    cout<<"+-----------------------------------+"<<endl;
    cout<<"|    1 - Matrice des distances      |"<<endl;
    cout<<"|    2 - Inversion d'un graphe      |"<<endl;
    cout<<"|    3 - Tarjan                     |"<<endl;
    cout<<"|    4 - Djikstra                   |"<<endl;
    cout<<"|    5 - Ordonancement              |"<<endl;
    cout<<"|    6 - Codage de Prufer           |"<<endl;
    cout<<"|    7 - Kruskal                    |"<<endl;
    cout<<"|    8 - Dantzig                    |"<<endl;
    cout<<"|    9 - Retour                     |"<<endl;
    cout<<"+-----------------------------------+"<<endl;
    cout<<"choix : ";
    cin>>choix;
    cout<<endl;
}

void Application::sousMenuAide()
{
    int choix;
    do{
        menuGraphe :
        menuAide(choix);
        switch(choix)
        {
            case 1 : system("cls");
                cout<<"Permet de calculer la distance entre les sommets de la matrice. Cette fonctionnalité s'applique sur un graphe"<<endl;
                cout<<"oriente."<<endl<<endl;
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            case 2 : system("cls");
                cout<<"Cette fonctionnalité permet d'inverser les arcs d'un graphe. Elle s'applique sur un graphe"<<endl;
                cout<<"oriente qui peut etre value ou non."<<endl<<endl;
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            case 3 : system("cls");
                cout<<"L'algorithme de TARJAN permet de calculer les composants fortement connexes d'un graphe, de determiner egalement"<<endl;
                cout<<" un graphe reduit à partir de ces composants. Il s'applique sur un graphe orienté et non valué."<<endl<<endl;
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            case 4 : system("cls");
                cout<<"L'algorithme de DJIKSTRA permet de trouver le chemin le plus court entre un sommet de depart et tous les sommets"<<endl;
                cout<<"accessible à partir de ce sommet. Il s'execute sur un graphe orienté et valué avec des couts positifs"<<endl<<endl;
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            case 5 : system("cls");
                cout<<"L'algorithme d'ORDONANCEMENT permet de determiner les chemins critques d'un projet ainsi que la date au plus tot et"<<endl;
                cout<<"au plus tard des differentes taches. Elle s'execute sur un graphe oriente et possedant comme poids sur "<<endl;
                cout<<"les arcs la durée des taches"<<endl<<endl;
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            case 6 : system("cls");
                cout<<"Le codage de PRUFER permet de coder un arbre dont dont les sommets sont numerotes de 1 à n en une suite de n-2 entiers."<<endl;
                cout<<"Il s'applique sur un graphe non oriente et non value et qui ne contient pas de circuit."<<endl<<endl;
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            case 7 : system("cls");
                cout<<"L'agorithme de KRUSKAL permet de trouvé l'arbre recouvrant minimal d'un graphe. "<<endl;
                cout<<"Il s'execute sur un graphe non oriente et value."<<endl<<endl;
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            case 8 : system("cls");
                cout<<"L'algorihtme de DANTZIG comme celui de Djikstra, sert à trouver le plus court chemin mais entre tous les sommets."<<endl;
                cout<<"Les plus courts chemin sont construits par extensions successives du graphe."<<endl;
                cout<<"IL s'applique sur un graphe oriente et value"<<endl<<endl;
                system("PAUSE");
                system("cls");
                goto menuGraphe;
                break;
            default : break;
        }

    }while(!choixCorrect(choix, 1, 8));
}
