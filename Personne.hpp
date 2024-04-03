#ifndef PERSONNE_HPP
#define PERSONNE_HPP

#include <iostream>
#include <string>

namespace elections {

   /**
   * Une personne est définie par un nom, un prénom, un identifiant unique
   * et une sensibilité politique de 1 à 10 (de gauche à droite).
   * 
   * L'identifiant unique est généré automatiquement.
   */
   class Personne {
   public:
      /**
      * Constructeur.
      * \param getNom    nom de la personne
      * \param getPrenom prénom de la personne
      * \param spol   sensibilité politique (entier entre 1 et 10)
      */
      Personne(const std::string& getNom, const std::string& getPrenom, int spol);
      
      Personne() = default;

      

      /**
      * Accesseur.
      * \return le getNom
      */
      std::string getNom() const;

      /**
      * Accesseur.
      * \return le prénom
      */
      std::string getPrenom() const;

      /**
      * Accesseur.
      * \return l'identifiant
      */
      int getId() const;

      /**
      * Accesseur.
      * \return la sensibilité politique
      */
      int getSensiPolitique() const;

   private:
      std::string p_nom, p_prenom;
      int p_id, p_sensibilitePolitique;
      static int p_electeurId;

   public:
      /**
      * Définition d'une relation d'ordre sur les personnes selon l'ordre
      * alphabétique des noms, puis l'ordre alphabétique des prénoms, puis
      * l'ordre croissant des identifiants.
      * 
      * Exemple pour trier un vecteur :
      * \code{.cpp}
      * std::vector<Personne*> v;
      * CompAlpha comp;
      * ...
      * std::sort(v.begin(), v.end(), comp);
      * \endcode
      * 
      * Exemple pour définir un ensemble ordonné :
      * \code{.cpp}
      * std::set<Personne*, CompAlpha> ens;
      * \endcode
      */
      struct CompAlpha {
         bool operator()(Personne* p1, Personne* p2) const
         {
            if (p1->getNom() < p2->getNom()) return true;
            if (p1->getNom() > p2->getNom()) return false;
            if (p1->getPrenom() < p2->getPrenom()) return true;
            if (p1->getPrenom() > p2->getPrenom()) return false;
            return (p1->getId() < p2->getId());
         }
      };
   };

   /**
   * Ecriture sur un flux de sortie.
   * \param os un flux de sortie
   * \param psn une personne
   * \return le flux donné en entrée os
   */
   std::ostream& operator<<(std::ostream& os, const Personne& psn);

} // namespace

#endif
