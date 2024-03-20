#include "TableDecharge.hpp"

TableDecharge::TableDecharge(size_t nombreElecteurs) {

    p_nombreElecteurs = nombreElecteurs;


}

size_t TableDecharge::getTailleListeCandidats() const { return p_listeCandidatsDecharge.size() ;} 
size_t TableDecharge::getNombreElecteurs() const { return p_nombreElecteurs ;} 


void TableDecharge::ajouterCandidats(Election election) {
    if(p_listeCandidatsDecharge.empty()) {
        for (auto it = election.getListeCandidats().begin(); it != election.getListeCandidats().end(); ++it) {
            p_listeCandidatsDecharge.push_back(BulletinsCandiat(it, getNombreElecteurs()));
            std::cout << "Le candidat : " << it->getPrenom() << " " << it->getNom() << ", avec une sensibilite politique de " << it->getSensiPolitique() << " a ete ajoute a la liste de candidats." << std::endl ;
        }
        ajouterBulletinBlanc(); 
    } else {
        std::cout << "La table de decharge contient deja des candidats." << std::endl ;
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


