#ifndef LISTEELECTORALE_HPP
#define LISTEELECTORALE_HPP

#include "ElecteurEngage.hpp"
#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace elections;

/**
 * La liste d'électeurs représente un groupe de personnes de type ElecteurEngage
 * pouvant voter. Pour respecter la contrainte de complexité temporelle en O(log*n),
 * un ensemble std::set sera utilisé, étant donné que l'insertion et la recherche sont tous deux
 * en O(log*n). Source : cppreference
 */
class ListeElectorale {
public:

    /**
     * Constructeur prenant une liste de personnes pour initialiser la liste électorale.
     * \param listePersonne liste de personnes à convertir en électeurs
     */
    ListeElectorale(std::vector<Personne*> listePersonne);

    /**
     * Constructeur prenant une liste d'électeurs engagés pour initialiser la liste électorale.
     * \param listeElecteur liste d'électeurs engagés
     */
    ListeElectorale(std::vector<ElecteurEngage*> listeElecteur);

    /**
     * Accesseur.
     * \return la taille de la liste électorale
     */
    size_t getTailleListeElectorale() const;

    /**
     * Recherche un électeur engagé dans la liste électorale.
     * \param electeur un électeur engagé à rechercher
     * \return un pointeur vers l'électeur engagé s'il est trouvé, sinon nullptr
     */
    ElecteurEngage* rechercherElecteur(ElecteurEngage& electeur) const;

    /**
     * Recherche un électeur engagé par sa personne associée dans la liste électorale.
     * \param personne une personne associée à un électeur à rechercher
     * \return un pointeur vers l'électeur engagé s'il est trouvé, sinon nullptr
     */
    ElecteurEngage* rechercherElecteur(Personne& personne) const;

    /**
     * Accesseur.
     * \return la liste électorale sous forme d'un ensemble
     */
    std::set<ElecteurEngage*, ElecteurEngage::CompAlpha> getListeElectorale() const;

    /**
     * Ajoute un électeur à la liste électorale.
     * \param electeur un pointeur vers un électeur à ajouter
     */
    void ajouterElecteur(Personne* & electeur);

    /**
     * Ajoute un électeur engagé à la liste électorale.
     * \param electeur un pointeur vers un électeur engagé à ajouter
     */
    void ajouterElecteur(ElecteurEngage* & electeur);

    ElecteurEngage* getElecteurIndex(size_t index) const ;
    
    

private:
    size_t p_TailleListeElectorale; // Taille de la liste électorale
    std::set<ElecteurEngage*, ElecteurEngage::CompAlpha> p_ListeElectorale; // Liste électorale
};

#endif
