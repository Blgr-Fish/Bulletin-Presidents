#include "Bureau.hpp"

Bureau::Bureau(std::vector<Personne*>& listeElecteurs, Election &election, Personne president,int numeroBureau)
    :   p_tableDechargeBureau(listeElecteurs.size()), 
        p_listeElectoraleBureau(listeElecteurs),
        p_listeCandidatsBureau(election),
        p_tableVoteBureau(president, p_listeElectoraleBureau) {

    // initialisation des isoloires
    for (size_t i = 0 ; i < (size_t)Parametrage::NOMBRE_ISOLOIRS ; ++i) {
        Isoloire isoloire ;
        p_listeIsoloires.push_back(isoloire);
    }

    p_tableDechargeBureau.ajouterCandidats(p_listeCandidatsBureau);

    p_numeroBureau = numeroBureau ;
}

ListeElectorale& Bureau::getListeElectorale() {
    return p_listeElectoraleBureau ;
}

Election& Bureau::getElection() {
    return p_listeCandidatsBureau ;
}

TableDecharge& Bureau::getTableDecharge() {
    return p_tableDechargeBureau ;
}

TableVote& Bureau::getTableVote() {
    return p_tableVoteBureau ;
}

Isoloire& Bureau::getIsoloire(int i) {
    return p_listeIsoloires[i];
}

int Bureau::getNumeroBureau() {
    return p_numeroBureau ;
}

std::queue<ElecteurEngage*>& Bureau::getFileBureauTableDecharge() {
    return p_fileBureauVersTableDecharge ;
}

std::queue<ElecteurEngage*>& Bureau::getFileTableDechargeIsoloires() {
    return p_fileTableDechargeVersIsoloires ;
}

std::queue<ElecteurEngage*>& Bureau::getFileIsoloiresTableVote() {
    return p_fileIsoloiresVersTableVote ;
}

int Bureau::choisirIsoloirDisponible() {
    for (int i = 0 ; i < (int)p_listeIsoloires.size() ; ++i) {
        if (getIsoloire(i).estVide()) {
            return i;
        }
    } 
    
    return -1 ;
}

void Bureau::main(int & temps, int & indiceElecteur) {

    std::cout << "T = " << temps << std::endl ;
    // augmentation du temps
    temps++;

    // entrer les électeurs dans la file 
    if (temps <= (int)Parametrage::TEMPS_MAX && temps % 2 == 1 && indiceElecteur < (int)getListeElectorale().getListeElectorale().size()) {
        ElecteurEngage* electeurBureau = getListeElectorale().getElecteurIndex(indiceElecteur++);
        p_fileBureauVersTableDecharge.push(electeurBureau);
        std::cout << "  ENTREE\n       "<< electeurBureau->getId() << " entre" << std::endl ;
    }

    ElecteurEngage* electeur ;
    // bureau vers table de decharge
    if (!p_fileBureauVersTableDecharge.empty() || !getTableDecharge().estVide()) {
            
        // lorsque la table est vide
        if (getTableDecharge().estVide()) {
            std::cout << "  DECHARGE" << std::endl ;
            electeur = p_fileBureauVersTableDecharge.front();
            p_fileBureauVersTableDecharge.pop();      
            std::cout << "       "<< electeur->getId() << " entre" << std::endl ;
            getTableDecharge().entrerTableDecharge(electeur);
                        
        // si elle est déjà utilisée, on décrémente simplement
        } else {     
            electeur = getTableDecharge().getOccupant();
            electeur->decrementeTempsRestant();

            if (electeur->getTempsRestant() <= 0) {
                getTableDecharge().choisirBulletins();
                std::cout << "  DECHARGE" << std::endl ;
                for (const auto& b : electeur->getBulletins()){
                    std::cout << "       " << electeur->getId() << " prend " << b.nomCandidat << std::endl;
                }
                getTableDecharge().sortirTableDecharge(p_fileTableDechargeVersIsoloires);
                std::cout << "  DECHARGE\n       "<< electeur->getId() << " sort" << std::endl ;
            }
        }
    }        

    // table de decharge vers isoloires
    int indiceIsoloire = choisirIsoloirDisponible();
    if (!p_fileTableDechargeVersIsoloires.empty() || !getIsoloire(indiceIsoloire).estVide() ) {

        if (indiceIsoloire != -1 && getIsoloire(indiceIsoloire).estVide()) {
            
            std::cout << "  ISOLOIR" << std::endl ;
            electeur = p_fileTableDechargeVersIsoloires.front();
            p_fileTableDechargeVersIsoloires.pop();         
            std::cout << "       "<< electeur->getId() << " entre" << std::endl ;
            getIsoloire(indiceIsoloire).entrerIsoloire(electeur);
            getIsoloire(indiceIsoloire).choisirBulletinFinal();
            
        }                 
        for (int i = 0 ; i < (int)p_listeIsoloires.size() ; ++i) {

            if (i != indiceIsoloire && !getIsoloire(i).estVide()) {
                getIsoloire(i).getOccupant()->decrementeTempsRestant();
                
                if (getIsoloire(i).getOccupant()->getTempsRestant() <= 0) {
                            
                    if (!getIsoloire(i).estVide()){
                        std::cout << "  ISOLOIR\n       " << getIsoloire(i).getOccupant()->getId() << " prend " << getIsoloire(i).getOccupant()->getBulletinFinal().nomCandidat << std::endl;
                        std::cout << "       " << getIsoloire(i).getOccupant()->getId() << " sort" << std::endl ;
                    }
                    getIsoloire(i).sortirIsoloire(p_fileIsoloiresVersTableVote);
                }
            }   
        }        
    }

    // isoloires vers table de vote    
    if(!p_fileIsoloiresVersTableVote.empty() || !getTableVote().estVide()) {

        if (getTableVote().estVide()) {

            std::cout << "  VOTE" << std::endl ;
            electeur = p_fileIsoloiresVersTableVote.front();
            p_fileIsoloiresVersTableVote.pop();

            std::cout << "       "<< electeur->getId() << " entre" << std::endl ;
            getTableVote().entrerTableVote(electeur);
            
        } else {
            electeur = getTableVote().getOccupant();
            electeur->decrementeTempsRestant();

            if (electeur->getTempsRestant() <= 0) {

                std::cout << "  VOTE\n       " << electeur->getId() << " vote" << std::endl;
                getTableVote().placerBulletin();
                getTableVote().emarger();

                std::cout << "  VOTE\n       " << electeur->getId() << " sort" << std::endl;
                getTableVote().sortirTableVote();
            }
        } 
    }
}
