#include "Isoloire.hpp"
#include "Parametrage.hpp"
#include "BulletinsCandiat.hpp"


#include <random>

int Isoloire::p_isoloireId = 0; // représente le nombre total d'isoloires, s'incrémente a chaque instanciation

Isoloire::Isoloire() : p_etat(true),  p_id(p_isoloireId++){p_electeurOccupant = nullptr ;}


void Isoloire::entrerIsoloire(ElecteurEngage* electeur) {
    
    // on vérifie si l'isoloire est vide avant d'accepter un électeur
    if (estVide()) {
        p_electeurOccupant = electeur;
        p_etat = false; 
        std::cout << "L'electeur " << p_electeurOccupant->getNom() << " est entre dans l'isoloir " << p_isoloireId << std::endl; 
    } else {
         std::cout << "L'electeur " << p_electeurOccupant->getNom() << " a tente d'entrer dans l'isoloir" << p_isoloireId << " qui est deja en cours d'utilisation." << std::endl; 
    }
}


void Isoloire::sortirIsoloire(std::queue<ElecteurEngage*> file) {
    // Marche meme si il n'y a pas d'electeurs
    p_etat = true;
    std::cout << "L'isoloire " << p_isoloireId << " a ete vide."<< std::endl; 

    // on envois l'occupant dans la file et on le passe a nullptr
    if (p_electeurOccupant != nullptr) {
        file.push(p_electeurOccupant);
        p_electeurOccupant = nullptr ;
    } 

}


bool Isoloire::estVide() {
    return p_etat;
}


ElecteurEngage* Isoloire::getOccupant() {
    return p_electeurOccupant;
}

void Isoloire::choisirBulletinFinal() {
    const double probaNul = Parametrage::PROBABILITE_VOTE_NUL ;

    std::random_device seed;
    std::mt19937 gen(seed());

    std::uniform_int_distribution<size_t> BulletinBlancChance(0, 100);
    const double randValeur = (float) BulletinBlancChance(gen) / 100 ; // donne une val entre 0 et 1

    if(randValeur <= probaNul) {
        BulletinsCandiat bulletinF("Nul",-2,1);
        p_electeurOccupant->prendreBulletinFinal(bulletinF) ;
    } else {
        auto bulletins = p_electeurOccupant->getBulletins(); // pour eviter a ecrire std::list etc
        if (!bulletins.empty()) {
            std::uniform_int_distribution<size_t> bulletinR(0, bulletins.size() - 1);
            auto it = bulletins.begin();
            std::advance(it, bulletinR(gen));     

            p_electeurOccupant->prendreBulletinFinal(*it);

        } else {
            std::cout << "Erreur : Aucun bulletin disponible pour l'électeur." << std::endl;
        }
    }

}