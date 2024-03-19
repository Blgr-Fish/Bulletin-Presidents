#ifndef ISOLOIRE_HPP
#define ISOLOIRE_HPP

#include "ElecteurEngage.hpp"

#include <iostream>
#include <string>
#include <list>


class Isoloire{
    public:
    Isoloire(int temps);
    void entrerIsoloire(ElecteurEngage* electeur);
    void sortirIsoloire();
    bool estVide() ;
    ElecteurEngage* getOccupant();
    void choisirBulletin(); // choisir un bulletin implique de jeter les autres

    private:
    ElecteurEngage* p_electeurOccupant;
    bool p_etat;
    int p_dureeChoix;
    static int p_isoloireId ; // compteur des isoloires
    const int p_id ;
};


#endif