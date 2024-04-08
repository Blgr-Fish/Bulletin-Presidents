#include "Personne.hpp"
#include "TableDecharge.hpp"
#include "Election.hpp"
#include "ListeElectorale.hpp"
#include "Isoloire.hpp"
#include "Bureau.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;
using namespace elections;



int main(void)
{
   // initialisation du générateur de nombres aléatoires
   std::srand(std::time(nullptr));



   // création des personnes
   std::vector<Personne*> listePersonne = {
      new Personne("A", "bic", 7),
      new Personne("B", "gad", 9),
      new Personne("C", "ann", 2),
      new Personne("D", "pol", 5),
      new Personne("E", "lam", 1),
      new Personne("F", "bul", 10),
      new Personne("G", "yap", 3),
      new Personne("X", "nel", 5),
      new Personne("Y", "rik", 2),
      new Personne("Z", "pat", 8)
   };

    // les candiats qui vont être convertis en élécteurs
   std::vector<Personne*> listeElecteur = {
      listePersonne[0],
      listePersonne[1],
      listePersonne[2],
      listePersonne[3],
      listePersonne[4],
      listePersonne[5],
      listePersonne[6]
   };

   // création de l'élection
   Election electionCandidat("Elections 2024") ;
   electionCandidat.ajouterCandidat(listePersonne[6]);
   electionCandidat.ajouterCandidat(listePersonne[7]);
   electionCandidat.ajouterCandidat(listePersonne[8]);

   
   //ElecteurEngage* ele = listeElectorale.rechercherElecteur(*listePersonne[0]);

   Bureau bureauDeVote(listeElecteur,electionCandidat,*listePersonne[2],258);

   int temps = 1 ;
   int indiceElecteur = 0 ;
   bool IsoloireVide = true ;

    std::cout << "ELECTION '" << bureauDeVote.getElection().getNom() << "'" << std::endl;
    for (auto candidat : bureauDeVote.getElection().getListeCandidats()) {
        std::cout << "  Candidat n." << candidat->getId() << " : " << candidat->getNom() << " " << candidat->getPrenom() << " " << candidat->getSensiPolitique() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "BUREAU n." << bureauDeVote.getNumeroBureau() << std::endl ;
    std::cout << "LISTE ELECTORALE" << std::endl ;
    for (auto electeur : bureauDeVote.getListeElectorale()   .getListeElectorale()) {
        std::cout << "  " << electeur->getNom() << " " << electeur->getPrenom() << " (" << electeur->getId() << ")" << std::endl;
    }

    std::cout << std::endl;

    std::cout << "PREPARATION DECHARGE" << std::endl ;
    for (auto candidat : bureauDeVote.getElection().getListeCandidats()) {
        std::cout << " " << candidat->getNom() << " " << candidat->getPrenom() << " : " << bureauDeVote.getListeElectorale()   .getTailleListeElectorale() << " bulletins" << std::endl;
    }


    std::cout << std::endl;

    std::cout << "OUVERTURE BUREAU n." << bureauDeVote.getNumeroBureau() << std::endl ;
    std::cout << "TMAX = " << Parametrage::TEMPS_MAX <<std::endl ;

    std::cout << std::endl;

    


    while ((!bureauDeVote.getFileBureauTableDecharge().empty() || !bureauDeVote.getFileTableDechargeIsoloires().empty() || !bureauDeVote.getFileIsoloiresTableVote().empty() 
        ||  !bureauDeVote.getTableVote().estVide() ||  !bureauDeVote.getTableDecharge().estVide()) || IsoloireVide == false || temps <= (int) Parametrage::TEMPS_MAX) {

        if(temps == (int) Parametrage::TEMPS_MAX) {
                std::cout << "\nFERMETURE ENTREE \n" << std::endl ;
        }

        // pour s'assurer de bien vider les isoloires
        IsoloireVide = true ;
        for (int i = 0 ; i< (int)Parametrage::NOMBRE_ISOLOIRS ; ++i) {
            if (!bureauDeVote.getIsoloire(i).estVide()) {
                IsoloireVide = false ;
            }
        }

        bureauDeVote.main(temps,indiceElecteur);
    }



    std::cout << std::endl;

    std::cout << "FERMETURE BUREAU n."<< bureauDeVote.getNumeroBureau()  << std::endl ;

    std::cout << std::endl;

    std::cout << "BUREAU n." << bureauDeVote.getNumeroBureau()  << " : RESULTATS " << bureauDeVote.getElection().getNom() << std::endl ;
    std::cout << "PRESIDENT : " << bureauDeVote.getTableVote().getPresident().getNom() << " " << bureauDeVote.getTableVote().getPresident().getPrenom() << std::endl ;
    std::cout << "  nb electeurs : " << bureauDeVote.getListeElectorale().getTailleListeElectorale() << std::endl ;
    std::cout << "  nb votes : " << bureauDeVote.getTableVote().getUrneBulletins().size() << std::endl ;
    std::cout << "  participation : " << (( (float)bureauDeVote.getTableVote().getUrneBulletins().size() /(float)bureauDeVote.getListeElectorale().getTailleListeElectorale()) ) *100 << "%" << std::endl;
    std::cout << "  abstention : " << ( 1. -( (float)bureauDeVote.getTableVote().getUrneBulletins().size() /(float)bureauDeVote.getListeElectorale().getTailleListeElectorale()) ) *100 << "%" << std::endl;

    // comme on va dépiler l'urne, on va perdre sa taille, donc on la stock
    float nbrVotant = (float)bureauDeVote.getTableVote().getUrneBulletins().size() ;

    // affichage des votes
    std::map<int,VoteCandidat> comptage = bureauDeVote.tirageVotes();
    for (const auto& k : comptage) {
        const VoteCandidat& vote = k.second; // Valeur
        float pourcentage = (float)vote.occurence / nbrVotant ;
        std::cout << "  " << vote.candidat << " : " << vote.occurence << " (" << pourcentage * 100<< "%)" << std::endl;
    }

    



   // destruction des personnes
   for (Personne* psn : listePersonne)
   {
      delete psn;
   }

   return 0;
}
