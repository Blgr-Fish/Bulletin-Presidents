#ifndef ISOLOIRE_HPP
#define ISOLOIRE_HPP

#include "ElecteurEngage.hpp"
#include <iostream>
#include <string>
#include <list>
#include <queue>

/**
 * Un isoloir représente un espace où un électeur engagé peut aller pour 
 * voter en privé. Il peut y avoir un seul électeur dans un isoloir à la fois.
 */
class Isoloire {
public:
    /**
     * Constructeur.
     */
    Isoloire();

    /**
     * Permet à un électeur engagé d'entrer dans l'isoloir.
     * \param electeur un pointeur vers l'électeur engagé
     */
    void entrerIsoloire(ElecteurEngage* electeur);

    /**
     * Permet à l'électeur actuel de sortir de l'isoloir vers la file d'attente
     * \param file une file d'attente d'électeurs engagés
     */
    void sortirIsoloire(std::queue<ElecteurEngage*> file);

    /**
     * Vérifie si l'isoloir est vide.
     * \return true si l'isoloir est vide, sinon false
     */
    bool estVide();

    /**
     * Accesseur.
     * \return l'électeur occupant actuellement l'isoloir
     */
    ElecteurEngage* getOccupant();

    /**
     * Méthode permettant de choisir le bulletin final parmi les bulletins 
     * choisis précédemment. Choisir un bulletin implique de jeter les autres.
     */
    void choisirBulletinFinal();

private:
    ElecteurEngage* p_electeurOccupant; // Électeur occupant actuellement l'isoloir
    bool p_etat; // État de l'isoloir (vide ou occupé)
    static int p_isoloireId; // Compteur des isoloires
    const int p_id; // Identifiant unique de l'isoloir
};

#endif
