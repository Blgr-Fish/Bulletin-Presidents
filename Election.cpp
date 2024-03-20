#include "Election.hpp"

Election::Election(std::string nom) {
    p_nomElection = nom ;
}

std::string Election::getNom() const { return p_nomElection ;}
Personne* Election::getCandidat(int index) const { return p_listeCandidat[index];}
int Election::getNbCandidat() const { return p_listeCandidat.size();}
std::vector<Personne*> Election::getListeCandidats() const  { return p_listeCandidat;}

void Election::ajouterCandidat(Personne* &candidat) {
    p_listeCandidat.push_back(candidat);
}
