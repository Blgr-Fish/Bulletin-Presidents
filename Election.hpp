#ifndef ELECTION_HPP
#define ELECTION_HPP

#include "Personne.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace elections;

/**
 * L'élection représente la liste des candidats à élire. Elle possède un nom ainsi qu'un vecteur contenant
 * l'ensemble des candidats.
 */
class Election
{
public:
    /**
     * Constructeur.
     * \param nom le nom de l'élection
     */
    Election(std::string nom);

    /**
     * Constructeur par copie.
     * \param copy l'élection à copier
     */
    Election(const Election &copy);

    /**
     * Accesseur.
     * \return le nom de l'élection
     */
    std::string getNom() const;

    /**
     * Accesseur.
     * \param index l'index du candidat dans le vecteur
     * \return un pointeur vers le candidat à l'index spécifié
     */
    Personne *getCandidat(int index) const;

    /**
     * Accesseur.
     * \return le nombre de candidats dans l'élection
     */
    int getNbCandidat() const;

    /**
     * Accesseur.
     * \return la liste des candidats sous forme de vecteur
     */
    std::vector<Personne *> getListeCandidats() const;

    /**
     * Ajoute un candidat à l'élection.
     * \param candidat un pointeur vers le candidat à ajouter
     */
    void ajouterCandidat(Personne *&candidat);

private:
    std::string p_nomElection;               // Nom de l'élection
    std::vector<Personne *> p_listeCandidat; // Liste des candidats
};

#endif
