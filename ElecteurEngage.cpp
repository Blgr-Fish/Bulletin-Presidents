#include "ElecteurEngage.hpp"

ElecteurEngage::ElecteurEngage(const Personne& personne) 
    : Personne(personne), p_TempRestant(0) {
    }

int ElecteurEngage::getTempsRestant() {
    return p_TempRestant;
}

void ElecteurEngage::decrementeTempsRestant() {
    if (p_TempRestant > 0) {
        p_TempRestant--;
    }
}


void ElecteurEngage::setNouveauTempsRestant(int nouveauTemps) {
    p_TempRestant = nouveauTemps;
}

void ElecteurEngage::prendreBulletin(BulletinsCandiat bulletin)  {
    p_BulletinsChoisis.push_back(bulletin);
}