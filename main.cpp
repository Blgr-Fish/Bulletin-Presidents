#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "Personne.hpp"

using namespace std;
using namespace elections;

int main(void)
{
   // initialisation du générateur de nombres aléatoires
   std::srand(std::time(nullptr));

   // création des personnes
   std::vector<Personne*> listeElectorale = {
      new Personne("ijja", "ziad", 7),
      new Personne("benmammar", "adel", 9),
      new Personne("traore", "alfousseny", 2),
      new Personne("D", "pol", 5),
      new Personne("E", "lam", 1),
      new Personne("F", "bul", 10),
      new Personne("G", "yap", 3),
      new Personne("X", "nel", 5),
      new Personne("Y", "rik", 2),
      new Personne("Z", "pat", 8)
   };


   // TODO
   // Code de simulation dans lequel on manipulera les personnes
   // via des pointeurs sur les éléments du vecteur vp.
   size_t tMax = 20 ;
   size_t tDecharge = 3 ;
   size_t tIsoloir = 6 ;
   size_t tVote = 4 ;
   double probaBlanc = 0.35;
   double probaNul = 0.15 ;
   size_t nombreIsoloire = 3 ;
   size_t distanceMaximale = 3 ;

   // destruction des personnes
   for (Personne* psn : vp)
   {
      delete psn;
   }

   return 0;
}
