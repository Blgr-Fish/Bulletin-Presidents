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

/**
 * Un bureau de vote est le conteneur des 3 processus de vote :
 * - La table de décharge, où l'on va choisir au moins 2 bulletins parmi l'ensemble des bulletins
 * - L'isoloir, où l'on va garder un seul des bulletins choisis
 * - La table de vote, où l'on va confirmer son vote et émarger son nom sur une liste.
 *
 * Il peut exister plusieurs bureaux de vote, et un bureau de vote se voit assigner une 
 * liste d'électeurs, qui ne peuvent voter que dans ce bureau.
 *
 * Les lieux seront séparés par des files.
 */
class Bureau {
public:
    /**
     * Constructeur.
     * \param isoloires liste des isoloires disponibles dans le bureau
     * \param tableVote table de vote où se termine le processus de vote
     * \param listeElecteurs liste des électeurs assignés à ce bureau
     * \param election élection en cours dans ce bureau
     */
    Bureau(const std::vector<Isoloire> & isoloires, const TableVote& tableVote,
           std::vector<ElecteurEngage*>&  listeElecteurs, Election&  election);

    /**
     * Initialise le bureau de vote.
     */
    void init();

private:
    TableDecharge p_tableDechargeBureau; // Table de décharge du bureau
    std::vector<Isoloire> p_listeIsoloires; // Liste des isoloires disponibles dans le bureau
    TableVote p_tableVoteBureau; // Table de vote du bureau

    ListeElectorale p_listeElectoraleBureau; // Liste des électeurs votant dans ce bureau
    Election p_listeCandidatsBureau; // Liste des candidats de l'élection en cours dans ce bureau

    // Files pour gérer le flux d'électeurs entre les différentes étapes du vote
    std::queue<ElecteurEngage*> p_fileBureauVersTableDecharge; // File entre le bureau et la table de décharge
    std::queue<ElecteurEngage*> p_fileIsoloiresVersTableVote; // File entre les isoloires et la table de vote
};

#endif
