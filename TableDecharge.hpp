#ifndef TABLEDECHARGE_HPP
#define TABLEDECHARGE_HPP

#include "Personne.hpp"
#include "BulletinsCandiat.hpp"
#include "Election.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace elections;


/**
* Une table de décharge est définie par une liste de bulletins de candidats, 
* ainsi que d'un entier représentant le nombre d'élécteurs pour attribuer le 
* bon nombre de bulletins aux candidats   
*/
class TableDecharge {

public:

    TableDecharge(size_t nombreElecteurs);

    size_t getTailleListeCandidats() const ;
    size_t getNombreElecteurs() const ;

    void ajouterCandidats(Election election);

    


private: 
    size_t p_nombreElecteurs ;
    std::vector<BulletinsCandiat> p_listeCandidatsDecharge;
    bool p_estEnUtilisation ; // determinera si un electeur est dans la table de décharge

    void ajouterBulletinBlanc() ; // sera utilisée dans la methode ajouterCandidats();
};




#endif