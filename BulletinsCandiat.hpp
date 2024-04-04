#ifndef BULLETINCANDIDAT_HPP
#define BULLETINCANDIDAT_HPP

#include "Personne.hpp"
#include <iostream>
#include <string>

using namespace elections;

/**
 * Structure représentant un bulletin de candidat.
 * 
 * Cette structure sert à assigner le nombre de bulletins restants à un candidat.
 * Il faudra décrementer nombreDeBulletins à chaque fois que le bulletin du candidat est choisi par un électeur.
 */
struct BulletinsCandiat {
    std::string nomCandidat; // Nom du candidat
    int idCandidat; // Identifiant du candidat
    size_t nombreDeBulletins; // Nombre de bulletins restants pour ce candidat
    size_t candidatSpol; // Sensibilité politique du candidat


    /**
     * Constructeur prenant une personne (candidat) et un nombre de bulletins.
     * \param candidat la personne (candidat) associée au bulletin
     * \param nombreDeBulletins le nombre de bulletins initialement disponibles pour ce candidat
     */
    BulletinsCandiat(Personne& candidat, size_t& nombreDeBulletins)
        : nomCandidat(candidat.getNom()), idCandidat(candidat.getId()), nombreDeBulletins(nombreDeBulletins) {
        candidatSpol = candidat.getSensiPolitique();
  
    }

    /**
     * Constructeur pour un bulletin blanc, prenant un nom, un identifiant et un nombre de bulletins.
     * \param nom le nom associé au bulletin blanc
     * \param id l'identifiant associé au bulletin blanc
     * \param nombreDeBulletins le nombre de bulletins initialement disponibles pour ce bulletin blanc
     */
    BulletinsCandiat(std::string nom, int id, size_t nombreDeBulletins)
        : nomCandidat(nom), idCandidat(id), nombreDeBulletins(nombreDeBulletins) {
        candidatSpol = -1; // Un bulletin blanc ou nul n'a pas de sensibilité politique
    }

    // Constructeur par défaut
    BulletinsCandiat() = default;
};

#endif
