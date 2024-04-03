#ifndef TABLEVOTE_HPP
#define TABLEVOTE_HPP

#include "ElecteurEngage.hpp"
#include "BulletinsCandiat.hpp"
#include "ListeElectorale.hpp"

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

class TableVote{

public:
    
    TableVote(const Personne & president, const ListeElectorale listeElectorale);

    /**
     * Permet à un électeur engagé d'entrer dans la table de vote.
     * \param electeur un pointeur vers l'électeur engagé
     */
    void entrerTableVote(ElecteurEngage* &electeur);

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
    ElecteurEngage* & getOccupant();

    void placerBulletin() ;

    void emarger() ;

    bool estPresentDansEmargement() ;

    void compterBulletins() ;

    Personne getPresident();
        

private:

    std::stack<BulletinsCandiat> p_urneBulletins ;
    std::unordered_map<size_t,bool> p_tableEmargement ;
    ElecteurEngage* p_electeurOccupant; 
    bool p_etat; 

    Personne p_presidentTableVote ;

};



#endif