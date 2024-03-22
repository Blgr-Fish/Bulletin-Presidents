#ifndef LISTEELECTORALE_HPP
#define LISTEELECTORALE_HPP


#include "ElecteurEngage.hpp"


#include <iostream>
#include <string>
#include <set>
#include <vector>


/**
* La liste d'electeurs représente un groupe de personne de type ElecteurEngage
* pouvant voter. Pour respecter la contrainte de compléxité temporelle en O(log*n);
* un ensemble std::set sera utilisé, étant donné que l'insertion et la recherche sont eux
* deux en O(log*n) source : cppreference
*/

class ListeElectorale {
public:

    ListeElectorale(std::vector<Personne*> listePersonne);

    size_t getTailleListeElectorale() const ;
    ElecteurEngage* getElecteur() ;



private:

    size_t p_TailleListeElectorale;
    std::set<ElecteurEngage*, CompAlpha> p_ListeElectorale;

 };

#endif