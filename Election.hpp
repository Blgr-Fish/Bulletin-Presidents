#ifndef ELECTION_HPP
#define ELECTION_HPP

#include "Personne.hpp"

#include <iostream>
#include <string>
#include <vector>


using namespace elections;


/**
* L'election représente la liste des candidats à élir. Elle pssède un nom ainsi qu'un vecteur contenant
* l'ensemble des candidats.
*/
class Election {
public:

   Election(std::string nom);
   Election(const Election& copy);
   std::string getNom() const;
   Personne* getCandidat(int index) const;
   int getNbCandidat() const;
   std::vector<Personne*> getListeCandidats() const;
   void ajouterCandidat(Personne* &candidat);

private:
    std::string p_nomElection;
    std::vector<Personne*> p_listeCandidat;
};

#endif