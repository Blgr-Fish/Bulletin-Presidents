#include "Isoloire.hpp"

int Isoloire::p_isoloireId = 0; // représente le nombre total d'electeurs, s'incrémente a chaque instanciation

Isoloire::Isoloire(int temps) : p_etat(true), p_dureeChoix(temps) , p_id(p_isoloireId++){}


void Isoloire::entrerIsoloire(ElecteurEngage* electeur) {
    
    // Vérifie si l'isoloire est vide avant d'accepter un électeur
    if (estVide()) {
        p_electeurOccupant = electeur;
        p_etat = false; 
        std::cout << "L'electeur " << electeur << " est entre dans l'isoloir " << p_isoloireId << std::endl; 
    } else {
         std::cout << "L'electeur " << electeur << " a tente d'entrer dans l'isoloir" << p_isoloireId << " qui est deja en cours d'utilisation." << std::endl; 
    }
}


void Isoloire::sortirIsoloire() {
    // Marche meme si il n'y a pas d'electeurs
    p_etat = true;
    std::cout << "L'isoloire " << p_isoloireId << " a ete vide."<< std::endl; 
}


bool Isoloire::estVide() {
    return p_etat;
}


ElecteurEngage* Isoloire::getOccupant() {
    return p_electeurOccupant;
}

void Isoloire::choisirBulletin() {

}