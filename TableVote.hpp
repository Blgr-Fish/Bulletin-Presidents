#ifndef TABLEVOTE_HPP
#define TABLEVOTE_HPP

#include "ElecteurEngage.hpp"
#include "BulletinsCandiat.hpp"

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

class TableVote{

public:
    
    TableVote(ElecteurEngage* president);

    /**
     * Permet à un électeur engagé d'entrer dans la table de vote.
     * \param electeur un pointeur vers l'électeur engagé
     */
    void entrerTablrVote(ElecteurEngage* electeur);

    /**
     * Permet à l'électeur actuel de sortir de la table de vote vers la file d'attente
     * \param file une file d'attente d'électeurs engagés
     */
    void sortirTableVote();

    /**
     * Vérifie si la table de vote est vide.
     * \return true si la table de vote est vide, sinon false
     */
    bool estVide();

    /**
     * Accesseur.
     * \return l'électeur occupant actuellement la table de vote
     */
    ElecteurEngage* getOccupant();

        

private:

    std::stack<BulletinsCandiat> p_urneBulletins ;
    std::unordered_map<size_t,bool> tableEmargement ;
    ElecteurEngage* p_electeurOccupant; 
    bool p_etat; 

    ElecteurEngage* p_presidentTableVote ;

};



#endif