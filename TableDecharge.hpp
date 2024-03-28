#ifndef TABLEDECHARGE_HPP
#define TABLEDECHARGE_HPP

#include "ElecteurEngage.hpp"
#include "BulletinsCandiat.hpp"
#include "Election.hpp"

#include <iostream>
#include <string>
#include <map>
#include <queue>

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
     * Permet à un électeur engagé d'entrer dans la table de décgarge
     * \param electeur un pointeur vers l'électeur engagé
     */
    void entrerTableDecharge(ElecteurEngage* electeur);

    /**
     * Permet à l'électeur actuel de sortir de la table de décharge vers la file d'attente
     * \param file une file d'attente d'électeurs engagés
     */
    void sortirTableDecharge(std::queue<ElecteurEngage*> file);

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
     * Vérifie si la table de decharge est vide.
     * \return true si la table est vide, sinon false
     */
    bool estVide();

    /**
     * Accesseur.
     * \return l'électeur occupant actuellement la table de decharge
     */
    ElecteurEngage* getOccupant();

    /**
     * Ajoute les candidats d'une élection à la table de décharge.
     * \param election une élection contenant les candidats
     */
    void ajouterCandidats(Election election);

    /**
     * Choisis les bulletins pour l'électeur.
     */
    void choisirBulletins();

private:
    size_t p_nombreElecteurs; // Nombre d'électeurs pour la table de décharge
    std::map<size_t, BulletinsCandiat> p_tableHachageCandidatsDecharge; // Liste des bulletins de candidats
    bool p_etat; // Détermine si un électeur est dans la table de décharge
    ElecteurEngage* p_electeurOccupant;

    /**
     * Ajoute un bulletin blanc à la table de décharge.
     * Méthode utilisée dans la méthode ajouterCandidats().
     */
    void ajouterBulletinBlanc();
};

#endif
