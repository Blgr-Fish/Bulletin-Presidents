#include "TableDecharge.hpp"
#include "Parametrage.hpp"

#include <random>
#include <algorithm> 



TableDecharge::TableDecharge(size_t nombreElecteurs) {
 p_nombreElecteurs = nombreElecteurs;
 p_electeurOccupant = nullptr ;
 p_etat = true ;
}


void TableDecharge::entrerTableDecharge(ElecteurEngage* &electeur) {
    
    if (estVide()) {
        p_electeurOccupant = electeur;
        p_electeurOccupant->setNouveauTempsRestant(Parametrage::TEMPS_DECHARGE);
        p_etat = false ;
        //std::cout << "L'electeur " << electeur->getNom() << " est entre dans la table de decharge " << std::endl; 
    } else {
        //std::cout << "L'electeur " << electeur->getNom() << " a tente d'entrer dans la table de decharge qui est deja en cours d'utilisation." << std::endl; 
    }
}


void TableDecharge::sortirTableDecharge(std::queue<ElecteurEngage*> &file) {
    
    // Marche meme si il n'y a pas d'electeurs
    p_etat = true;
    //std::cout << "La table de decharge a ete vide."<< std::endl; 

    // on envois l'occupant dans la file et on le passe a nullptr
    if (p_electeurOccupant != nullptr) {
        file.push(p_electeurOccupant);
        p_electeurOccupant = nullptr ;
    } 
}


bool TableDecharge::estVide() {
    return p_etat;
}

size_t TableDecharge::getTailleListeCandidats() const { return p_tableHachageCandidatsDecharge.size() ;} 
size_t TableDecharge::getNombreElecteurs() const { return p_nombreElecteurs ;} 

ElecteurEngage* & TableDecharge::getOccupant()  {
    return p_electeurOccupant;
}


void TableDecharge::ajouterCandidats(Election election) {
    if (p_tableHachageCandidatsDecharge.empty()) {
        for (int i = 0; i < election.getNbCandidat(); ++i) {
            BulletinsCandiat bulletinC(*(election.getCandidat(i)),p_nombreElecteurs);
            p_tableHachageCandidatsDecharge[election.getCandidat(i)->getId()] = bulletinC;
        }
        ajouterBulletinBlanc();
    } else {
        std::cout << "La table de decharge contient deja des candidats." << std::endl;
    }
    
}

// Un electeur prend minimum 2 bulletins (max : nombre de candidats) distincts,
// et ces bulletins sont choisis en fonction de la sensibilité politique.
void TableDecharge::choisirBulletins() {
    const size_t distMax = Parametrage::DISTANCE_POLITIQUE_MAXIMALE;
    const double probaBlanc = Parametrage::PROBABILITE_VOTE_BLANC;
    std::vector<BulletinsCandiat> tempListeCandidats;

    // Premier parcours de la liste pour récupérer les bulletins avec une bonne sensibilité politique
    for (auto& kv : p_tableHachageCandidatsDecharge) {
        auto& bulletin = kv.second;
       
        if ( std::max(bulletin.candidatSpol,(size_t)p_electeurOccupant->getSensiPolitique())
           - std::min(bulletin.candidatSpol,(size_t)p_electeurOccupant->getSensiPolitique()) < distMax
            && bulletin.nombreDeBulletins > 0) {

            tempListeCandidats.push_back(bulletin);
        }
    }
    // On prend par défaut un bulletin blanc si la liste est vide ou alors qu'il reste qu'un seul bulletin
    if (tempListeCandidats.size() < 2) {
        p_electeurOccupant->prendreBulletin(p_tableHachageCandidatsDecharge[-1]);
        p_tableHachageCandidatsDecharge[-1].nombreDeBulletins -= 1 ;
    } else {
        // Recuperation aleatoire de 2 à nombre de candidats bulletins
        size_t tailleListe = tempListeCandidats.size();

        // int randNum = rand()%(max-min + 1) + min; pour génerer une val entre min et max inclus
        // size_t nombreBulletinsAChoisir = (rand() % (tailleListe - 2 + 1)) + 2;
    
        // mais utiliser mt19937 et uniform_int_distribution donne de meilleurs valeurs
        std::random_device seed;
        std::mt19937 gen(seed());

        // va donner un size_t aleatoire entre 2 et tailleListe
        std::uniform_int_distribution<size_t> distance(2, tailleListe);
        size_t nombreBulletinsAChoisir = distance(gen);

        // on mélange la liste et on recupere les nombreBulletinsAChoisir premiers elements 
        std::shuffle(tempListeCandidats.begin(), tempListeCandidats.end(), gen);

        for (size_t i = 0; i < nombreBulletinsAChoisir; ++i) {     
            p_electeurOccupant->prendreBulletin(tempListeCandidats[i]);
            p_tableHachageCandidatsDecharge[tempListeCandidats[i].idCandidat].nombreDeBulletins -= 1 ;
        }

    
        std::uniform_int_distribution<size_t> BulletinBlancChance(0, 100);
        const double randValeur = (float) BulletinBlancChance(gen) / 100 ; // donne une val entre 0 et 1

        if(randValeur <= probaBlanc) {
            p_electeurOccupant->prendreBulletin(p_tableHachageCandidatsDecharge[-1]);
            p_tableHachageCandidatsDecharge[-1].nombreDeBulletins -= 1 ;
        }
    }

}



void TableDecharge::ajouterBulletinBlanc() {
    // Un bulletin blanc possède l'id -1
    BulletinsCandiat bulletinBlanc("Blanc",-1,getNombreElecteurs());

    // on vérifie si le bulletin blanc est déjà présent dans la liste de bulletins
    if (p_tableHachageCandidatsDecharge.find(-1) != p_tableHachageCandidatsDecharge.end()) {
        //std::cout << "Le bulletin blanc est déjà présent dans la liste de bulletins. L'opération n'est pas effectuée." << std::endl;
    } else {
        // on ajoute le bulletin blanc dans l'unordered_map
        p_tableHachageCandidatsDecharge[-1] = bulletinBlanc;
        //std::cout << "Le bulletin blanc a été ajouté à la liste de bulletins." << std::endl;
    }
}


