#ifndef ELECTION_HPP
#define ELECTION_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Personne.hpp"

using namespace elections;

class Election {
public:

   Election(std::string nom);
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