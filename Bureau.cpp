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


ListeElectorale &Bureau::getListeElectorale() {
    return p_listeElectoraleBureau ;
}


Election &Bureau::getElection() {
    return p_listeCandidatsBureau ;
}

TableDecharge &Bureau::getTableDecharge() {
    return p_tableDechargeBureau ;
}


TableVote &Bureau::getTableVote() {
    return p_tableVoteBureau ;
}


Isoloire &Bureau::getIsoloire(int i) {
    return p_listeIsoloires[i];
}

int Bureau::choisirIsoloirDisponible() {
    for (int i = 0 ; i < (int)p_listeIsoloires.size() ; ++i) {
        if (getIsoloire(i).estVide()) {
            return i;
        }
    } 
    
    return -1 ;
}

void Bureau::main() {

    int temps = 1 ;
    size_t indiceElecteur = 0 ;

    std::cout << "ELECTION '" << p_listeCandidatsBureau.getNom() << "'" << std::endl;
    for (auto candidat : p_listeCandidatsBureau.getListeCandidats()) {
        std::cout << "  Candidat n." << candidat->getId() << " : " << candidat->getNom() << " " << candidat->getPrenom() << " " << candidat->getSensiPolitique() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "BUREAU n." << p_numeroBureau << std::endl ;
    std::cout << "LISTE ELECTORALE" << std::endl ;
    for (auto electeur : p_listeElectoraleBureau.getListeElectorale()) {
        std::cout << "  " << electeur->getNom() << " " << electeur->getPrenom() << " (" << electeur->getId() << ")" << std::endl;
    }

    std::cout << std::endl;

    std::cout << "PREPARATION DECHARGE" << std::endl ;
    for (auto candidat : p_listeCandidatsBureau.getListeCandidats()) {
        std::cout << " " << candidat->getNom() << " " << candidat->getPrenom() << " : " << p_listeElectoraleBureau.getTailleListeElectorale() << " bulletins" << std::endl;
    }


    std::cout << std::endl;

    std::cout << "OUVERTURE BUREAU n." << p_numeroBureau << std::endl ;
    std::cout << "TMAX = " << Parametrage::TEMPS_MAX <<std::endl ;

    std::cout << std::endl;

    while ((!p_fileBureauVersTableDecharge.empty() || !p_fileTableDechargeVersIsoloires.empty() || !p_fileIsoloiresVersTableVote.empty() 
        ||  !getTableVote().estVide() ||  !getTableDecharge().estVide()) || temps <= (int) Parametrage::TEMPS_MAX) {

        if(temps == (int) Parametrage::TEMPS_MAX) {
            std::cout << "\nFERMETURE ENTREE \n" << std::endl ;
        }

        // augmentatino du temps
        std::cout << "T = " << temps++ << std::endl ;



        // entrer les electeurs dans la file 
        if (temps <= (int)Parametrage::TEMPS_MAX && temps % 2 == 1 && indiceElecteur < getListeElectorale().getListeElectorale().size()) {
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
                          
            // si elle est déjà utilisée, on décremente simplement
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
                
                //std::cout << "\nL'electeur a choisi le bulletin final : " << electeur->getBulletinFinal().nomCandidat<< std::endl;
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

    std::cout << std::endl;

    std::cout << "FERMETURE BUREAU n."<< p_numeroBureau << std::endl ;

    std::cout << std::endl;

    std::cout << "BUREAU n." << p_numeroBureau << " : RESULTATS " << p_listeCandidatsBureau.getNom() << std::endl ;
    std::cout << "PRESIDENT : " << p_tableVoteBureau.getPresident().getNom() << " " << p_tableVoteBureau.getPresident().getPrenom() << std::endl ;

     

}