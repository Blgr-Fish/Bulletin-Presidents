#include "Personne.hpp"
#include "TableDecharge.hpp"
#include "Election.hpp"
#include "ListeElectorale.hpp"

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


   

   std::cout << "creation de la liste de candidats" << std::endl ;
   Election electionCandidat("Elections 2024") ;
   electionCandidat.ajouterCandidat(listePersonne[0]);
   electionCandidat.ajouterCandidat(listePersonne[1]);
   electionCandidat.ajouterCandidat(listePersonne[2]);
   electionCandidat.ajouterCandidat(listePersonne[3]);
   electionCandidat.ajouterCandidat(listePersonne[4]);
   electionCandidat.ajouterCandidat(listePersonne[5]);
   electionCandidat.ajouterCandidat(listePersonne[6]);
   electionCandidat.ajouterCandidat(listePersonne[7]);
   electionCandidat.ajouterCandidat(listePersonne[8]);


   std::cout << "creation de la liste d'electeurs" << std::endl ;
   ListeElectorale listeElectorale(listePersonne);
   
   ElecteurEngage* ele = listeElectorale.rechercherElecteur(*listePersonne[0]);

   


   // TODO
   // Code de simulation dans lequel on manipulera les personnes
   // via des pointeurs sur les éléments du vecteur vp.
   

   // ici ce n'est pas listePersonne.size() mais 
   // il faudra ajouter une liste d'electeurs

   std::cout << "creation de la table de decharge" << std::endl ;


   TableDecharge table(listePersonne.size());
   table.ajouterCandidats(electionCandidat);
   
   std::cout << table.getTailleListeCandidats() << std::endl ; 
   std::cout << table.getNombreElecteurs() << std::endl ;

   std::cout << "--- TESTS ---" << std::endl ;

   table.choisirBulletins(ele) ;
   std::cout << "affichage des candidats du bulletin :" << std::endl;
   for (BulletinsCandiat b : ele->getBulletins()) {
      std::cout << b.nomCandidat << std::endl ;
   }


   

   // destruction des personnes
   for (Personne* psn : listePersonne)
   {
      delete psn;
   }

   return 0;
}
