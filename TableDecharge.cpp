#include "TableDecharge.hpp"
#include "Parametrage.hpp"

#include <random>


TableDecharge::TableDecharge(size_t nombreElecteurs) {

    p_nombreElecteurs = nombreElecteurs;

}

size_t TableDecharge::getTailleListeCandidats() const { return p_tableHachageCandidatsDecharge.size() ;} 
size_t TableDecharge::getNombreElecteurs() const { return p_nombreElecteurs ;} 


void TableDecharge::ajouterCandidats(Election election) {
    if (p_tableHachageCandidatsDecharge.empty()) {
        for (int i = 0; i < election.getNbCandidat(); ++i) {
            BulletinsCandiat bulletinC(*(election.getCandidat(i)),p_nombreElecteurs);
            p_tableHachageCandidatsDecharge[election.getCandidat(i)->getId()] = bulletinC;
        }
    } else {
        std::cout << "La table de decharge contient deja des candidats." << std::endl;
    }
}

// Un electeur prend minimum 2 bulletins (max : nombre de candidats) distincts,
// et ces bulletins sont choisis en fonction de la sensibilité politique.
void TableDecharge::choisirBulletins(ElecteurEngage* &electeur) {
    const size_t distMax = Parametrage::DISTANCE_POLITIQUE_MAXIMALE;
    const double probaBlanc = Parametrage::PROBABILITE_VOTE_BLANC;
    std::vector<BulletinsCandiat> tempListeCandidats;

    // Premier parcours de la liste pour récupérer les bulletins avec une bonne sensibilité politique
    for (auto& kv : p_tableHachageCandidatsDecharge) {
        auto& bulletin = kv.second;
        if (bulletin.candidatSpol > electeur->getSensiPolitique() - distMax 
            && bulletin.candidatSpol < electeur->getSensiPolitique() + distMax
            && bulletin.nombreDeBulletins > 0) {

            tempListeCandidats.push_back(bulletin);
        }
    }
    // On prend par défaut un bulletin blanc si la liste est vide ou alors qu'il reste qu'un seul bulletin
    if (tempListeCandidats.size() < 2) {
        electeur->prendreBulletin(p_tableHachageCandidatsDecharge[-1]);
        p_tableHachageCandidatsDecharge[-1].nombreDeBulletins -= 1 ;
    } else {
        // Recuperation aleatoire de 2 à nombre de candidats bulletins
        size_t tailleListe = tempListeCandidats.size();

        // int randNum = rand()%(max-min + 1) + min; pour génerer une val entre min et max inclus
        // size_t nombreBulletinsAChoisir = (rand() % (tailleListe - 2 + 1)) + 2;
    
        // mais utiliser mt19937 et uniform_int_distribution donne de meilleurs valeurs
        std::random_device seed;
        std::mt19937 gen(seed());
        std::uniform_int_distribution<size_t> dis(2, tailleListe);
        
        size_t nombreBulletinsAChoisir = dis(gen);

        for (size_t i = 0; i < nombreBulletinsAChoisir; ++i) {
            // dis(gen) donne une valeur min = 1 , donc -1 pour avoir 0
            size_t index = dis(gen) - 1; 
            electeur->prendreBulletin(tempListeCandidats[index]);
            p_tableHachageCandidatsDecharge[tempListeCandidats[index].idCandidat].nombreDeBulletins -= 1 ;
        }

        const double randValeur = ((double) rand() / (RAND_MAX)) ; // donne une val entre 0 et 1

        if(randValeur <= probaBlanc) {
            electeur->prendreBulletin(p_tableHachageCandidatsDecharge[-1]);
            p_tableHachageCandidatsDecharge[-1].nombreDeBulletins -= 1 ;
        }
    }

}



void TableDecharge::ajouterBulletinBlanc() {
    // Un bulletin blanc possède l'id -1
    BulletinsCandiat bulletinBlanc("Blanc",-1,getNombreElecteurs());

    // on vérifie si le bulletin blanc est déjà présent dans la liste de bulletins
    if (p_tableHachageCandidatsDecharge.find(-1) != p_tableHachageCandidatsDecharge.end()) {
        std::cout << "Le bulletin blanc est déjà présent dans la liste de bulletins. L'opération n'est pas effectuée." << std::endl;
    } else {
        // on ajoute le bulletin blanc dans l'unordered_map
        p_tableHachageCandidatsDecharge[-1] = bulletinBlanc;
        std::cout << "Le bulletin blanc a été ajouté à la liste de bulletins." << std::endl;
    }
}


