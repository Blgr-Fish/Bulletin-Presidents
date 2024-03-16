#include "Personne.hpp"
#include "TableDecharge.hpp"

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
   std::vector<Personne*> listeElectorale = {
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
   


   // TODO
   // Code de simulation dans lequel on manipulera les personnes
   // via des pointeurs sur les éléments du vecteur vp.
   


   TableDecharge table(listeElectorale.size());
   table.ajouterBulletinBlanc();

   table.ajoutCandidatDansListe(*listeElectorale[0]) ;
   table.ajoutCandidatDansListe(*listeElectorale[1]) ;
   table.ajoutCandidatDansListe(*listeElectorale[2]) ;
   table.ajoutCandidatDansListe(*listeElectorale[0]) ;
   table.supprimeCandidatDansListe(*listeElectorale[0]) ;

   std::cout << table.getTailleListeCandidats() << std::endl ; 
   std::cout << table.getNombreElecteurs() << std::endl ;


   

   // destruction des personnes
   for (Personne* psn : listeElectorale)
   {
      delete psn;
   }

   return 0;
}
