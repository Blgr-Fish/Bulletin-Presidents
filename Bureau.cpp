#include "Bureau.hpp"
#include <random>

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
    for (int i = 0 ; i < (int)Parametrage::NOMBRE_ISOLOIRS ; ++i) {
        if (getIsoloire(i).estVide()) {
            return i;
        }
    } 
    
    return -1 ;
}

void Bureau::entrerElecteursDansFile(int temps, int &indiceElecteur)
{

    if (temps <= (int)Parametrage::TEMPS_MAX && temps % 2 == 1 && indiceElecteur < (int)getListeElectorale().getListeElectorale().size())
    {
        // random pour la proba d'abstention
        std::random_device seed;
        std::mt19937 gen(seed());

        std::uniform_int_distribution<size_t> AbstentionChance(0, 100);
        const double randValeur = (float)AbstentionChance(gen) / 100; // donne une val entre 0 et 1
        ElecteurEngage *electeurBureau = getListeElectorale().getElecteurIndex(indiceElecteur++);

        if (randValeur > Parametrage::PROBABILITE_ABSTENTION)
        {
            std::cout << "  ENTREE\n       " << electeurBureau->getId() << " entre" << std::endl;
            p_fileBureauVersTableDecharge.push(electeurBureau);
        }
        else
        {
            std::cout << "  ENTREE\n       " << electeurBureau->getId() << " s'abtient " << std::endl;
            
        }
    }
}


void Bureau::traiterTableDecharge(ElecteurEngage *&electeur)
{
    if (!p_fileBureauVersTableDecharge.empty() || !getTableDecharge().estVide())
    {

        // lorsque la table est vide
        if (getTableDecharge().estVide())
        {
            std::cout << "  DECHARGE" << std::endl;
            electeur = p_fileBureauVersTableDecharge.front();
            p_fileBureauVersTableDecharge.pop();
            std::cout << "       " << electeur->getId() << " entre" << std::endl;
            getTableDecharge().entrerTableDecharge(electeur);

            // si elle est déjà utilisée, on décrémente simplement
        }
        else
        {
            electeur = getTableDecharge().getOccupant();
            electeur->decrementeTempsRestant();

            if (electeur->getTempsRestant() == 0)
            {
                getTableDecharge().choisirBulletins();
                std::cout << "  DECHARGE" << std::endl;
                for (const auto &b : electeur->getBulletins())
                {
                    std::cout << "       " << electeur->getId() << " prend " << b.nomCandidat << std::endl;
                }
            }
            if (electeur->getTempsRestant() <= -1)
            {
                getTableDecharge().sortirTableDecharge(p_fileTableDechargeVersIsoloires);
                std::cout << "  DECHARGE\n       " << electeur->getId() << " sort" << std::endl;
            }
        }
    }
}

void Bureau::traiterIsoloires(ElecteurEngage *&electeur)
{

    int indiceIsoloire = choisirIsoloirDisponible();

    if (!p_fileTableDechargeVersIsoloires.empty() || !getIsoloire(indiceIsoloire).estVide())
    {
        if (indiceIsoloire != -1 && getIsoloire(indiceIsoloire).estVide())
        {
            std::cout << "  ISOLOIR" << std::endl;
            electeur = p_fileTableDechargeVersIsoloires.front();
            p_fileTableDechargeVersIsoloires.pop();
            std::cout << "       " << electeur->getId() << " entre" << std::endl;
            getIsoloire(indiceIsoloire).entrerIsoloire(electeur);
            getIsoloire(indiceIsoloire).choisirBulletinFinal();
        }
    }

    for (int i = 0; i < (int)Parametrage::NOMBRE_ISOLOIRS; ++i)
    {

        if (!getIsoloire(i).estVide())
        {

            getIsoloire(i).getOccupant()->decrementeTempsRestant();
            if (getIsoloire(i).getOccupant()->getTempsRestant() == 0)
            {

                if (!getIsoloire(i).estVide())
                {
                    std::cout << "  ISOLOIR\n       " << getIsoloire(i).getOccupant()->getId() << " prend "
                              << getIsoloire(i).getOccupant()->getBulletinFinal().nomCandidat << std::endl;
                }
            }

            if (getIsoloire(i).getOccupant()->getTempsRestant() <= -1)
            {
                std::cout << "  ISOLOIR" << std::endl;
                std::cout << "       " << getIsoloire(i).getOccupant()->getId() << " sort" << std::endl;
                getIsoloire(i).sortirIsoloire(p_fileIsoloiresVersTableVote);
            }
        }
    }
}

void Bureau::traiterTableVote(ElecteurEngage *&electeur)
{

    if (!p_fileIsoloiresVersTableVote.empty() || !getTableVote().estVide())
    {

        if (getTableVote().estVide())
        {

            std::cout << "  VOTE" << std::endl;
            electeur = p_fileIsoloiresVersTableVote.front();
            p_fileIsoloiresVersTableVote.pop();

            std::cout << "       " << electeur->getId() << " entre" << std::endl;
            getTableVote().entrerTableVote(electeur);
        }
        else
        {
            electeur = getTableVote().getOccupant();
            electeur->decrementeTempsRestant();

            if (electeur->getTempsRestant() == 0)
            {

                std::cout << "  VOTE\n       " << electeur->getId() << " vote" << std::endl;
                getTableVote().placerBulletin();
                getTableVote().emarger();
            }
            if (electeur->getTempsRestant() <= -1)
            {
                std::cout << "  VOTE\n       " << electeur->getId() << " sort" << std::endl;
                getTableVote().sortirTableVote();
            }
        }
    }
}

std::map<int,VoteCandidat> Bureau::tirageVotes() {

    std::map<int,VoteCandidat> comptage ;


    for (auto a : getElection().getListeCandidats()){
        comptage.insert(std::make_pair(a->getId(), VoteCandidat{a->getNom()+" "+a->getPrenom(), 0}));
    }
    comptage.insert(std::make_pair(-1, VoteCandidat{"blanc", 0}));
    comptage.insert(std::make_pair(-2, VoteCandidat{"nul", 0}));

    while (!getTableVote().getUrneBulletins().empty()) {
    int id = getTableVote().getUrneBulletins().top().idCandidat;
    
    comptage[id].occurence++;
    getTableVote().getUrneBulletins().pop();
}

    return comptage ;
}

void Bureau::traitement(int & temps, int & indiceElecteur) {

    ElecteurEngage *electeur;

    std::cout << "T = " << temps << std::endl ;
    // augmentation du temps
    temps++;

    // entrer les électeurs dans la file
    entrerElecteursDansFile(temps, indiceElecteur);

    // bureau vers table de decharge
    traiterTableDecharge(electeur);

    // table de decharge vers isoloires
    traiterIsoloires(electeur);

    // isoloires vers table de vote
    traiterTableVote(electeur);

}


void Bureau::simulation() {

    // On ne fait pas de simulation sans isoloirs
    if (Parametrage::NOMBRE_ISOLOIRS <= 0) {
        std::cout << "Le bureau n." << getNumeroBureau() << " ne contient aucun isoloirs.\nFermeture du bureau." << std::endl ;
        return ;
    }

    int temps = 1 ;
    int indiceElecteur = 0 ;
    bool IsoloireVide = true ;

    std::cout << "ELECTION '" << getElection().getNom() << "'" << std::endl;
    for (auto candidat : getElection().getListeCandidats()) {
        std::cout << "  Candidat n." << candidat->getId() << " : " << candidat->getNom() << " " << candidat->getPrenom() << " " << candidat->getSensiPolitique() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "BUREAU n." << getNumeroBureau() << std::endl ;
    std::cout << "LISTE ELECTORALE" << std::endl ;

    for (auto electeur : getListeElectorale()   .getListeElectorale()) {
        std::cout << "  " << electeur->getNom() << " " << electeur->getPrenom() << " (" << electeur->getId() << ")" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "PREPARATION DECHARGE" << std::endl ;

    for (auto candidat : getElection().getListeCandidats()) {
        std::cout << " " << candidat->getNom() << " " << candidat->getPrenom() << " : " << getListeElectorale()   .getTailleListeElectorale() << " bulletins" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "OUVERTURE BUREAU n." << getNumeroBureau() << std::endl ;
    std::cout << "TMAX = " << Parametrage::TEMPS_MAX <<std::endl ;
    std::cout << std::endl;

    while ((!getFileBureauTableDecharge().empty() || !getFileTableDechargeIsoloires().empty() || !getFileIsoloiresTableVote().empty() 
        ||  !getTableVote().estVide() ||  !getTableDecharge().estVide()) || IsoloireVide == false || temps <= (int) Parametrage::TEMPS_MAX) {

        // pour s'assurer de bien vider les isoloires
        IsoloireVide = true ;
        for (int i = 0 ; i< (int)Parametrage::NOMBRE_ISOLOIRS ; ++i) {
            if (!getIsoloire(i).estVide()) {
                IsoloireVide = false ;
            }
        }
        traitement(temps,indiceElecteur);
        if(temps == (int) Parametrage::TEMPS_MAX+1) {
                std::cout << "\nFERMETURE ENTREE \n" << std::endl ;
        }
    }

    std::cout << std::endl;
    std::cout << "FERMETURE BUREAU n."<< getNumeroBureau()  << std::endl ;
    std::cout << std::endl;
    std::cout << "BUREAU n." << getNumeroBureau()  << " : RESULTATS " << getElection().getNom() << std::endl ;
    std::cout << "PRESIDENT : " << getTableVote().getPresident().getNom() << " " << getTableVote().getPresident().getPrenom() << std::endl ;
    std::cout << "  nb electeurs : " << getListeElectorale().getTailleListeElectorale() << std::endl ;
    std::cout << "  nb votes : " << getTableVote().getUrneBulletins().size() << std::endl ;
    std::cout << "  participation : " << (( (float)getTableVote().getUrneBulletins().size() /(float)getListeElectorale().getTailleListeElectorale()) ) *100 << "%" << std::endl;
    std::cout << "  abstention : " << ( 1. -( (float)getTableVote().getUrneBulletins().size() /(float)getListeElectorale().getTailleListeElectorale()) ) *100 << "%" << std::endl;

    // comme on va dépiler l'urne, on va perdre sa taille, donc on la stock
    float nbrVotant = (float)getTableVote().getUrneBulletins().size() ;

    // affichage des votes
    std::map<int,VoteCandidat> comptage = tirageVotes();
    for (const auto& k : comptage) {
        const VoteCandidat& vote = k.second; // Valeur

        // on laisse pourcentage à 0 si il n'y a aucun électeurs (sinon division par 0 qui donne de -nan%)
        float pourcentage =  nbrVotant > 1 ? (float)vote.occurence / nbrVotant : 0;

        std::cout << "  " << vote.candidat << " : " << vote.occurence << " (" << pourcentage * 100<< "%)" << std::endl;
    }
}

