#include "ListeElectorale.hpp"

ListeElectorale::ListeElectorale(std::vector<Personne*> listePersonne) {

    for (Personne* psn : listePersonne) {

    p_ListeElectorale.insert(ElecteurEngage(psn)); // ICI IL FAUT CONTINUER , AJOUTER LA TAILLE ET VERIFIER QUE LINSERTION FONCTIONNE  

    }
}