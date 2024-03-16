#include "TableDecharge.hpp"

TableDecharge::TableDecharge(size_t nombreElecteurs) {

    p_nombreElecteurs = nombreElecteurs;


}

size_t TableDecharge::getTailleListeCandidats() const { return p_listeCandidatsDecharge.size() ;} 
size_t TableDecharge::getNombreElecteurs() const { return p_nombreElecteurs ;} 


// A MODIFIER SI IL FAUT QUE LA LISTE SOIT TRIEE PAR ORDRE ALPHABETIQUE EN FONCTION DU NOM
// FAIRE COMME DANS LE TP AVEC CONSIGNES
void TableDecharge::ajoutCandidatDansListe(Personne candidat) {
    bool estPresent = false;

    // Vérifie si le candidat est déjà présent dans la liste
    for (auto it = p_listeCandidatsDecharge.begin(); it != p_listeCandidatsDecharge.end(); ++it) {
        if (it->idCandidat == candidat.getId()) {
            estPresent = true;
            std::cout << "Le candidat est deja present dans la liste de candidats, l'operation n'est pas effectue." << std::endl;
            break; // On stop le parcours si le candidat a été trouvé
        }
    }

    if (!estPresent && getNombreElecteurs() > 0) {
        p_listeCandidatsDecharge.push_back(BulletinsCandiat(candidat, getNombreElecteurs()));
        std::cout << "Le candidat : " << candidat.getPrenom() << " " << candidat.getNom() << ", avec une sensibilite politique de " << candidat.getSensiPolitique() << " a ete ajoute a la liste de candidats." << std::endl ;
    }
}

// SI LA LISTE EST TRIEE, UTILISER DICOTHOMIE POUR ALLER PLUS VITE
void TableDecharge::supprimeCandidatDansListe(Personne candidat) {
    bool candidatTrouve = false;
    
    // Vérifie si le candidat est présent dans la liste
    for (auto it = p_listeCandidatsDecharge.begin(); it != p_listeCandidatsDecharge.end(); ++it) {
        if (it->idCandidat == candidat.getId()) {
            p_listeCandidatsDecharge.erase(it);
            std::cout << "Le candidat : " << candidat.getPrenom() << " " << candidat.getNom() << ", a ete supprime de la liste de candidats." << std::endl;
            candidatTrouve = true; 
            break; 
        }
    }
    
    if (!candidatTrouve) {
        std::cout << "Le candidat : " << candidat.getPrenom() << " " << candidat.getNom() << ", n'a pas ete trouve dans la liste de candidats." << std::endl;
    }
}


void TableDecharge::ajouterBulletinBlanc() {
    // Un bulletin blanc possède l'id -1, il faudra donc que un electeur puisse voter aussi une spol de -1 meme si il a une spol élevée
    BulletinsCandiat bulletinBlanc("Blanc",-1,getNombreElecteurs());

    bool estPresent = false;

    for (auto it = p_listeCandidatsDecharge.begin(); it != p_listeCandidatsDecharge.end(); ++it) {
        if (it->idCandidat == -1) {
            estPresent = true;
            std::cout << "Le bulletin blanc est deja present dans la liste de bulletins, l'operation n'est pas effectue." << std::endl;
            break; 
        }
    }

    if (!estPresent && getNombreElecteurs() > 0) {
        p_listeCandidatsDecharge.push_back(bulletinBlanc);
        std::cout << "Le bulletin blanc a ete ajoute a la liste de bulletins." << std::endl ;
    }


}


