#ifndef BUREAU_HPP
#define BUREAU_HPP

#include "TableDecharge.hpp"
#include "Isoloire.hpp"
#include "TableVote.hpp"
#include "ElecteurEngage.hpp"
#include "ListeElectorale.hpp"
#include "Parametrage.hpp"
#include "VoteCandidat.hpp"

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
     * \param listeElecteurs Liste des électeurs assignés à ce bureau.
     * \param election Élection en cours dans ce bureau.
     * \param president Personne élue présidente du bureau.
     * \param numeroBureau Numéro du bureau.
     */
    Bureau(std::vector<Personne*>& listeElecteurs, Election& election, Personne president, int numeroBureau);

    /**
     * Accesseur.
     * \return la liste électorale.
     */
    ListeElectorale& getListeElectorale();

    /**
     * Accesseur.
     * \return l'élection en cours dans ce bureau.
     */
    Election& getElection();

    /**
     * Accesseur.
     * \return la table de décharge.
     */
    TableDecharge& getTableDecharge();

    /**
     * Accesseur.
     * \return la table de vote.
     */
    TableVote& getTableVote();

    /**
     * Accesseur.
     * \param i Indice de l'isoloir.
     * \return l'isoloir à l'indice spécifié.
     */
    Isoloire& getIsoloire(int i);

    /**
     * Accesseur.
     * \return le numéro du bureau.
     */
    int getNumeroBureau();

    /**
     * Accesseur.
     * \return la file entre le bureau et la table de décharge.
     */
    std::queue<ElecteurEngage*>& getFileBureauTableDecharge();

    /**
     * Accesseur.
     * \return la file entre la table de décharge et les isoloirs.
     */
    std::queue<ElecteurEngage*>& getFileTableDechargeIsoloires();

    /**
     * Accesseur.
     * \return la file entre les isoloirs et la table de vote.
     */
    std::queue<ElecteurEngage*>& getFileIsoloiresTableVote();

    /**
     * Méthode pour choisir un isoloir disponible.
     * \return indice de l'isoloir disponible, -1 si aucun isoloir n'est disponible.
     */
    int choisirIsoloirDisponible();

    /**
     * Méthode principale pour la gestion du bureau de vote.
     * \param temps Temps continu
     * \param indiceElecteur Indice de l'électeur pour entrer dans le bureau.
     */
    void main(int& temps, int& indiceElecteur);

    /**
     * Méthode permettant le comptage des votes.
     * \return un dictionnaire liant les indices des candidats a leur nom + occurence de vote
     */
    std::map<int,VoteCandidat> tirageVotes();

    /**
     * Méthode permettant l'entrée dans le bureau d'un electeur
     * \param temps Temps continu
     * \param indiceElecteur Indice de l'électeur pour entrer dans le bureau.
     */
    void entrerElecteursDansFile(int temps, int & indiceElecteur) ;

    /**
     * Méthode permettant l'insertion d'un electeur dans la table de décharge
     * ainsi que du fait de choisir les bulletins
     * \param electeur l'electeur entrant ou tentant d'entrer
     */
    void traiterTableDecharge(ElecteurEngage * &electeur) ;

    /**
     * Méthode permettant l'insertion d'un electeur dans l'un des isoloirs
     * ainsi que du fait de choisir son bulletin final
     * \param electeur l'electeur entrant ou tentant d'entrer
     */
    void traiterIsoloires(ElecteurEngage* &electeur) ;

    /**
     * Méthode permettant l'insertion d'un electeur dans la table de vote 
     * ainsi que du fait d'emarger et de déposer son vote
     * \param electeur l'electeur entrant ou tentant d'entrer
     */
    void traiterTableVote(ElecteurEngage* &electeur);

private:
    TableDecharge p_tableDechargeBureau;
    std::vector<Isoloire> p_listeIsoloires;
    ListeElectorale p_listeElectoraleBureau;
    Election p_listeCandidatsBureau;
    TableVote p_tableVoteBureau;
    std::queue<ElecteurEngage*> p_fileBureauVersTableDecharge;
    std::queue<ElecteurEngage*> p_fileTableDechargeVersIsoloires;
    std::queue<ElecteurEngage*> p_fileIsoloiresVersTableVote;
    int p_numeroBureau;
};

#endif
