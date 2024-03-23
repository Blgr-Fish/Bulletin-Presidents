#ifndef BUREAU_HPP
#define BUREAU_HPP

#include "TableDecharge.hpp"
#include "Isoloire.hpp"
#include "TableVote.hpp"
#include "ElecteurEngage.hpp"
#include "ListeElectorale.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <queue>

class Bureau{

/**
 * Un bureau de vote est le conteneur des 3 processus de vote : 
 * - La table de décharge, où l'on va choisir au moins 2 bulletins parmi l'ensemble des bulletins
 * - L'isoloire, où l'on va garder un seul des bulletins choisis
 * - La table de vote, où l'on va confirmer son vote, et émarger son nom sur une liste.
 * 
 * Il peux exister plusieurs bureaux de votes, et un bureau de vote se voit assigner une 
 * liste d'élécteurs, qui ne peuvent voter que dans ce bureau.
 * 
 * Les 3 lieux seront séparés par des files.
**/
public:
    Bureau(const TableDecharge& tableDecharge, const std::vector<Isoloire> & isoloires, const TableVote& tableVote, std::vector<ElecteurEngage*> listeElecteurs );

private:

    TableDecharge p_tableDechargeBureau;
    std::vector<Isoloire> p_listeIsoloires; // 1 ou plusieurs isoloires
    //TableVote p_tableVoteBureau;




    // ensemble représentant les electeurs votant dans ce bureau
    // c'est un sous ensemble de la liste electorale 
    ListeElectorale p_listeElectoraleBureau ;
    Election p_listeCandidatsBureau ;

    


    /**                    
     *                     --> Isoloire ↘            
     *  --> Table décharge --> Isoloire --> Table de vote
     *                     --> Isoloire ↗                                  
    */
    std::queue<ElecteurEngage*> p_fileBureauVersTableDecharge ;
    std::vector<std::queue<ElecteurEngage*>> p_fileTableDechargeVersIsoloires; // c'est un vecteur de files, car il y a plusieurs isoloires, donc plusieurs files
    std::queue<ElecteurEngage*> p_fileIsoloiresVersTableVote;

    

};


#endif