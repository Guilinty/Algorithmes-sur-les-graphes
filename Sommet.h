#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include "iostream"
#include <vector>

class Sommet{
public:
    Sommet();
    Sommet(int numero, const std::string& nom);
    int getNumeroStation() const;
    std::string getNomStation() const;
    void setNumeroStation(int numero);
    void setNomStation(std::string nom);

private:
    int _numeroStation;
    std::string _nomStation;

};

#endif // SOMMET_H_INCLUDED
