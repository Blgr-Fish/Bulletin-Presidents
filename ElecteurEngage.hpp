#ifndef ELECTEURENGAGE_HPP
#define ELECTEURENGAGE_HPP

#include "Personne.hpp"
#include "BulletinsCandiat.hpp"
#include <iostream>
#include <string>
#include <list>

using namespace elections;

/**
 * Un électeur engagé représente une personne pouvant voter, qui a commencé
 * le processus de vote, c'est-à-dire choisir des bulletins de vote, etc.
 *
 * C'est une sous-classe de Personne.
 *
 * L'électeur engagé possède des attributs supplémentaires tels que le temps
 * restant pour effectuer son action, les bulletins qu'il a choisis lors de la table
 * de décharge, et enfin le bulletin final qu'il a gardé.
 */
class ElecteurEngage : public Personne
{
public:
    /**
     * Constructeur.
     * \param personne une personne dont les attributs sont copiés pour créer un électeur engagé
     */
    ElecteurEngage(const Personne &personne);

    /**
     * Accesseur.
     * \return le temps restant pour effectuer l'action (isoloir, table de décharge, etc)
     */
    int getTempsRestant();

    /**
     * Modifieur.
     * \param nouveauTemps le nouveau temps restant à définir
     */
    void setNouveauTempsRestant(int nouveauTemps);

    /**
     * Diminue le temps restant de l'électeur engagé.
     */
    void decrementeTempsRestant();

    /**
     * Ajoute un bulletin de candidat choisi par l'électeur engagé.
     * \param bulletin un bulletin de candidat choisi
     */
    void prendreBulletin(BulletinsCandiat bulletin);

    /**
     * Définit le bulletin final choisi par l'électeur engagé.
     * \param bulletin le bulletin final choisi
     */
    void prendreBulletinFinal(BulletinsCandiat bulletin);

    /**
     * Accesseur.
     * \return la liste des bulletins choisis par l'électeur engagé
     */
    std::list<BulletinsCandiat> getBulletins() const;

    /**
     * Accesseur.
     * \return le bulletin final choisi par l'électeur engagé
     */
    BulletinsCandiat getBulletinFinal() const;

private:
    int p_TempRestant;                              // Temps restant pour effectuer l'action (isoloir, table de décharge, etc)
    std::list<BulletinsCandiat> p_BulletinsChoisis; // Liste des bulletins choisis
    BulletinsCandiat p_BulletinFinal;               // Bulletin final choisi
};

#endif
