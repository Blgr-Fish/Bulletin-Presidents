#include "Bureau.hpp"

Bureau::Bureau(std::vector<Personne*>& listeElecteurs, Election &election, Personne* president)
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

void Bureau::tests() {

    // entrer les electeurs dans la file 
    for (ElecteurEngage* electeur :  getListeElectorale().getListeElectorale()) {
        p_fileBureauVersTableDecharge.push(electeur);
    }
    int temps = 1 ;

    while (!p_fileBureauVersTableDecharge.empty() || !p_fileTableDechargeVersIsoloires.empty() || !p_fileIsoloiresVersTableVote.empty() 
        ||  !getTableVote().estVide() ||  !getTableDecharge().estVide()) {

        std::cout << "T = " << temps++ << std::endl ;
        
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

       /* 
       bool isoloireEstPlein = false;
        for ( auto & iso : p_listeIsoloires){
            if(!iso.estVide()) isoloireEstPlein = true ;
        }
        */


        if (!p_fileTableDechargeVersIsoloires.empty() ) {
    
            int indiceIsoloire = choisirIsoloirDisponible();
            if (indiceIsoloire != -1 && getIsoloire(indiceIsoloire).estVide()) {
                
                std::cout << "  ISOLOIR" << std::endl ;
                electeur = p_fileTableDechargeVersIsoloires.front();
                p_fileTableDechargeVersIsoloires.pop();
                    
                std::cout << "       "<< electeur->getId() << " entre" << std::endl ;
                getIsoloire(indiceIsoloire).entrerIsoloire(electeur);
                getIsoloire(indiceIsoloire).choisirBulletinFinal();
                
                //std::cout << "\nL'electeur a choisi le bulletin final : " << electeur->getBulletinFinal().nomCandidat<< std::endl;
            } else {
                for (int i = 0 ; i < (int)p_listeIsoloires.size() ; ++i) {
                    getIsoloire(i).getOccupant()->decrementeTempsRestant();
                    

                    if (getIsoloire(i).getOccupant()->getTempsRestant() <= 0) {
                            

                            if (!getIsoloire(i).estVide()){
                            std::cout << "  ISOLOIR\n       " << getIsoloire(i).getOccupant()->getId() << " prend " << getIsoloire(i).getOccupant()->getBulletinFinal().nomCandidat << std::endl;
                            std::cout << "  ISOLOIR\n       " << getIsoloire(i).getOccupant()->getId() << " sort" << std::endl ;
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

    std::cout << "c fini" << std::endl ;

     

}