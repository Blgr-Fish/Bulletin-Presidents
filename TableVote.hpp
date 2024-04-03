#ifndef TABLEVOTE_HPP
#define TABLEVOTE_HPP

#include "ElecteurEngage.hpp"
#include "BulletinsCandiat.hpp"
#include "ListeElectorale.hpp"

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

/**
 * Classe représentant la table de vote où les électeurs engagés déposent leur vote et émargent.
 */
class TableVote {

public:
    
    /**
     * Constructeur.
     * \param president Personne élue présidente du bureau.
     * \param listeElectorale Liste électorale pour la table de vote.
     */
    TableVote(const Personne& president, const ListeElectorale listeElectorale);

    /**
     * Permet à un électeur engagé d'entrer dans la table de vote.
     * \param electeur Un pointeur vers l'électeur engagé.
     */
    void entrerTableVote(ElecteurEngage* &electeur);

    /**
     * Permet à l'électeur actuel de sortir de la table de vote vers la file d'attente.
     * \param file Une file d'attente d'électeurs engagés.
     */
    void sortirTableVote();

    /**
     * Vérifie si la table de vote est vide.
     * \return true si la table de vote est vide, sinon false.
     */
    bool estVide();

    /**
     * Accesseur.
     * \return l'électeur occupant actuellement la table de vote.
     */
    ElecteurEngage* & getOccupant();

    /**
     * Place le bulletin de vote dans l'urne.
     */
    void placerBulletin();

    /**
     * Émarge l'électeur actuel dans la liste d'émargement.
     */
    void emarger();

    /**
     * Vérifie si l'électeur actuel est présent dans la liste d'émargement.
     * \return true si l'électeur est présent, sinon false.
     */
    bool estPresentDansEmargement();

    /**
     * Compte les bulletins de vote présents dans l'urne.
     */
    void compterBulletins();

    /**
     * Accesseur.
     * \return le président associé à la table de vote.
     */
    Personne getPresident();

private:

    std::stack<BulletinsCandiat> p_urneBulletins; // Urne contenant les bulletins de vote
    std::unordered_map<size_t,bool> p_tableEmargement; // Liste d'émargement
    ElecteurEngage* p_electeurOccupant; // Électeur actuellement dans la table de vote
    bool p_etat; // État de la table de vote (vide ou non)
    Personne p_presidentTableVote; // Président associé à la table de vote

};

#endif
