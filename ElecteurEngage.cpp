#include "ElecteurEngage.hpp"

// Constructeur prenant une personne en paramètre et initialisant le temps restant à 0
ElecteurEngage::ElecteurEngage(const Personne& personne) 
    : Personne(personne), p_tempRestant(0) {
        
    }

// Accesseur pour le temps restant
int ElecteurEngage::getTempsRestant() {
    return p_tempRestant;
}

// Méthode pour décrémenter le temps restant
void ElecteurEngage::decrementeTempsRestant() {
    if (p_tempRestant > 0) {
        p_tempRestant--;
    }
}

// Méthode pour définir un nouveau temps restant
void ElecteurEngage::setNouveauTempsRestant(int nouveauTemps) {
    p_tempRestant = nouveauTemps;
}
