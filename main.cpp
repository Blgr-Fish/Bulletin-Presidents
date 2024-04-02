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
      new Personne("Benmammar", "adel", 5),
      new Personne("D", "pol", 5),
      new Personne("E", "lam", 4),
      new Personne("F", "bul", 6),
      new Personne("G", "yap", 3),
      new Personne("Ijja", "ziad", 7),
      new Personne("Traore", "alfousseny", 2),
      new Personne("X", "nel", 5),
      new Personne("Y", "rik", 2),
      new Personne("Z", "pat", 8)
   };


   // création de l'élection
   Election electionCandidat("Elections 2024") ;
   electionCandidat.ajouterCandidat(listePersonne[0]);
   electionCandidat.ajouterCandidat(listePersonne[1]);
   electionCandidat.ajouterCandidat(listePersonne[2]);
   electionCandidat.ajouterCandidat(listePersonne[3]);


   
   //ElecteurEngage* ele = listeElectorale.rechercherElecteur(*listePersonne[0]);

   Bureau bureauDeVote(listePersonne,electionCandidat);



/*
   std::cout << "creation de la table de decharge" << std::endl ;


   TableDecharge table(listePersonne.size());
   table.ajouterCandidats(electionCandidat);
   
   std::cout << table.getTailleListeCandidats() << std::endl ; 
   std::cout << table.getNombreElecteurs() << std::endl ;

   std::cout << "--- TESTS ---" << std::endl ;

   table.entrerTableDecharge(ele);
   table.choisirBulletins() ;
   std::cout << "l'electeur a recupere les bulletins suivants :" << std::endl;
   for (BulletinsCandiat b : ele->getBulletins()) {
      std::cout << b.nomCandidat << std::endl ;
   }

   
   Isoloire isoloire ;
   isoloire.entrerIsoloire(ele);
   isoloire.choisirBulletinFinal();
   //isoloire.sortirIsoloire();
   std::cout << "le bulletin final est : " << ele->getBulletinFinal().nomCandidat << std::endl ;
   */

   // destruction des personnes
   for (Personne* psn : listePersonne)
   {
      delete psn;
   }

   return 0;
}
