#ifndef TABLEDECHARGE_HPP
#define TABLEDECHARGE_HPP

#include "ElecteurEngage.hpp"
#include "BulletinsCandiat.hpp"
#include "Election.hpp"

#include <iostream>
#include <string>
#include <map>

using namespace elections;

/**
 * Une table de décharge est définie par une liste de bulletins de candidats,
 * ainsi que d'un entier représentant le nombre d'électeurs pour attribuer le
 * bon nombre de bulletins aux candidats.
 */
class TableDecharge {

public:

    /**
     * Constructeur.
     * \param nombreElecteurs nombre d'électeurs pour la table de décharge
     */
    TableDecharge(size_t nombreElecteurs);

    /**
     * Accesseur.
     * \return la taille de la liste des candidats
     */
    size_t getTailleListeCandidats() const;

    /**
     * Accesseur.
     * \return le nombre d'électeurs pour la table de décharge
     */
    size_t getNombreElecteurs() const;

    /**
     * Ajoute les candidats d'une élection à la table de décharge.
     * \param election une élection contenant les candidats
     */
    void ajouterCandidats(Election election);

    /**
     * Choisis les bulletins pour un électeur.
     * \param electeur un pointeur vers un électeur
     */
    void choisirBulletins(ElecteurEngage* & electeur);

private:
    size_t p_nombreElecteurs; // Nombre d'électeurs pour la table de décharge
    std::map<size_t, BulletinsCandiat> p_tableHachageCandidatsDecharge; // Liste des bulletins de candidats
    bool p_estEnUtilisation; // Détermine si un électeur est dans la table de décharge

    /**
     * Ajoute un bulletin blanc à la table de décharge.
     * Méthode utilisée dans la méthode ajouterCandidats().
     */
    void ajouterBulletinBlanc();
};

#endif
