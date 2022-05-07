#include "Sommet.h"

Sommet::Sommet()
{}

Sommet::Sommet(int numero, const std::string& nom)
    : _numeroStation{numero}, _nomStation{nom}
{

}

int Sommet::getNumeroStation() const
{
    return _numeroStation;
}

std::string Sommet::getNomStation() const
{
    return _nomStation;
}

void Sommet::setNumeroStation(int numero)
{
    _numeroStation = numero;
}

void Sommet::setNomStation(std::string nom)
{
    _nomStation = nom;
}
