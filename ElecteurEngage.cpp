#include "ElecteurEngage.hpp"

ElecteurEngage::ElecteurEngage(const Personne& personne) 
    : Personne(personne), p_tempRestant(0) {
        
    }

int ElecteurEngage::getTempsRestant() {
    return p_tempRestant;
}

void ElecteurEngage::decrementeTempsRestant() {
    if (p_tempRestant > 0) {
        p_tempRestant--;
    }
}


void ElecteurEngage::setNouveauTempsRestant(int nouveauTemps) {
    p_tempRestant = nouveauTemps;
}
