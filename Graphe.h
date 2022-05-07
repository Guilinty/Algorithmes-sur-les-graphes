#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <iostream>
#include <vector>

class Sommet;

class Graphe{
public:
    Graphe() = default;
    virtual void ajoutSommet(const Sommet& s) = 0;
    virtual void supprimeSommet(int s) = 0;
    virtual Sommet getSommet(int s) const = 0;
    virtual int  nbSommets() const = 0;
    virtual void printSommets() const = 0;
    virtual void setOriente(bool oriente) = 0;
    virtual bool estOriente() const = 0;
    virtual void setValue(bool value) = 0;
    virtual bool estValue() const = 0;
    virtual void afficher(const std::vector<int>& tab) const = 0;
    virtual void lectureGraphe(std::string fileName) = 0;
    virtual void ecritureGraphe(std::string fileName) = 0;
};


#endif // GRAPHE_H_INCLUDED
