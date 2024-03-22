#include "Personne.hpp"
#include "TableDecharge.hpp"
#include "Election.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;
using namespace elections;

/*
* Valeurs de paramètre
*/
const size_t TEMPS_MAX = 20 ;
const size_t TEMPS_DECHARGE = 3 ;
const size_t TEMPS_ISOLOIR = 6 ;
const size_t TEMPS_VOTE= 4 ;
const double PROBABILITE_VOTE_BLANC = 0.35;
const double PROBABILITE_VOTE_NUL = 0.15 ;
const size_t NOMBRE_ISOLOIRS = 3 ;
const size_t DISTANCE_POLITIQUE_MAXIMALE = 3 ;


int main(void)
{
   // initialisation du générateur de nombres aléatoires
   std::srand(std::time(nullptr));



   // création des personnes
   std::vector<Personne*> listePersonne = {
      new Personne("Benmammar", "adel", 9),
      new Personne("D", "pol", 5),
      new Personne("E", "lam", 1),
      new Personne("F", "bul", 10),
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


   

   // destruction des personnes
   for (Personne* psn : listePersonne)
   {
      delete psn;
   }

   return 0;
}
