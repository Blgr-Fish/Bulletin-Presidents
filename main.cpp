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


   // création de l'élection
   Election electionCandidat("Elections 2024") ;
   electionCandidat.ajouterCandidat(listePersonne[0]);
   electionCandidat.ajouterCandidat(listePersonne[1]);
   electionCandidat.ajouterCandidat(listePersonne[2]);
   electionCandidat.ajouterCandidat(listePersonne[3]);


   
   //ElecteurEngage* ele = listeElectorale.rechercherElecteur(*listePersonne[0]);

   Bureau bureauDeVote(listePersonne,electionCandidat,*listePersonne[2],258);


   bureauDeVote.main();


   // destruction des personnes
   for (Personne* psn : listePersonne)
   {
      delete psn;
   }

   return 0;
}
