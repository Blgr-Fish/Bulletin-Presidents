#ifndef TABLEDECHARGE_HPP
#define TABLEDECHARGE_HPP

#include "ElecteurEngage.hpp"
#include "BulletinsCandiat.hpp"
#include "Election.hpp"

#include <iostream>
#include <string>
#include <map>

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

    void choisirBulletins(ElecteurEngage* & electeur) ;

    


private: 
    size_t p_nombreElecteurs ;
    std::map<size_t, BulletinsCandiat> p_tableHachageCandidatsDecharge; // ici la clé est un int, ce sera simplement l'id des candiats
    bool p_estEnUtilisation ; // determinera si un electeur est dans la table de décharge

    void ajouterBulletinBlanc() ; // sera utilisée dans la methode ajouterCandidats();
};




#endif