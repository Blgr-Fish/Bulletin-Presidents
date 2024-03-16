#include "Personne.hpp"


#include <iostream>
#include <string>


using namespace elections ;

// Sert à assigner le nombre de bulletins restants à un candidat, 
// il faudra désincrémenter nombreDeBulletins à chaque fois que le bulletin du candidat est choisi par un élécteur
struct BulletinsCandiat {
    std::string nomCandidat;
    int idCandidat ;
    size_t nombreDeBulletins;

    BulletinsCandiat(Personne candidat, size_t nombreDeBulletins) 
        :nomCandidat(candidat.getNom()), idCandidat(candidat.getId()), nombreDeBulletins(nombreDeBulletins) {}

    BulletinsCandiat(std::string nom, int id,size_t nombreDeBulletins) 
        :nomCandidat(nom), idCandidat(id), nombreDeBulletins(nombreDeBulletins) {}

};