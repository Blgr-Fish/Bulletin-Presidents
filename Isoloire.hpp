#ifndef ISOLOIRE_HPP
#define ISOLOIRE_HPP

#include "ElecteurEngage.hpp"

#include <iostream>
#include <string>
#include <list>
#include <queue>


class Isoloire{
    public:
    Isoloire();
    void entrerIsoloire(ElecteurEngage* electeur);
    void sortirIsoloire(std::queue<ElecteurEngage*> file);
    bool estVide() ;
    ElecteurEngage* getOccupant();
    void choisirBulletinFinal(); // choisir un bulletin implique de jeter les autres

    private:
    ElecteurEngage* p_electeurOccupant;
    bool p_etat;
    static int p_isoloireId ; // compteur des isoloires
    const int p_id ;
};


#endif