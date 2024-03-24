#ifndef LISTEELECTORALE_HPP
#define LISTEELECTORALE_HPP


#include "ElecteurEngage.hpp"


#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace elections;


/**
* La liste d'electeurs représente un groupe de personne de type ElecteurEngage
* pouvant voter. Pour respecter la contrainte de compléxité temporelle en O(log*n);
* un ensemble std::set sera utilisé, étant donné que l'insertion et la recherche sont eux
* deux en O(log*n) source : cppreference
*/

class ListeElectorale {
public:

    ListeElectorale(std::vector<Personne*> listePersonne);
    ListeElectorale(std::vector<ElecteurEngage*> listeElecteur);


    size_t getTailleListeElectorale() const ;
    ElecteurEngage* rechercherElecteur(ElecteurEngage& electeur) const;
    ElecteurEngage* rechercherElecteur(Personne& personne) const;


    void ajouterElecteur(Personne* & electeur) ;
    void ajouterElecteur(ElecteurEngage* & electeur);


    



private:

    size_t p_TailleListeElectorale;
    std::set<ElecteurEngage*, ElecteurEngage::CompAlpha> p_ListeElectorale;
    
 };

#endif