#include "Personne.hpp"

namespace elections {

int Personne::p_electeurId = 0;

   Personne::Personne(const std::string& nom, const std::string& prenom,
                     int spol)
         : p_nom(nom), p_prenom(prenom), p_id(p_electeurId++), p_sensibilitePolitique(spol)
   {}

   std::string Personne::getNom() const
   {
      return p_nom;
   }

   std::string Personne::getPrenom() const
   {
      return p_prenom;
   }

   int Personne::getId() const
   {
      return p_id;
   }

   int Personne::getSensiPolitique() const
   {
      return p_sensibilitePolitique;
   }

   std::ostream& operator<<(std::ostream& os, const Personne& psn)
   {
      os << psn.getNom() << " " << psn.getPrenom() << " " << psn.getSensiPolitique();
      return os;
   }

} // namespace
