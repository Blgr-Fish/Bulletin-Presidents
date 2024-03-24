#include "ListeElectorale.hpp"

ListeElectorale::ListeElectorale(std::vector<Personne*> listePersonne) {

    for (Personne* psn : listePersonne) {
         // Cette operation est en O(log*n)
        p_ListeElectorale.insert(new ElecteurEngage(*psn)); 
    }
}

ListeElectorale::ListeElectorale(std::vector<ElecteurEngage*> listeElecteur) {

    for (ElecteurEngage* ele : listeElecteur) {
         // Cette operation est en O(log*n)
        p_ListeElectorale.insert(ele); 
    }
}



ElecteurEngage* ListeElectorale::rechercherElecteur(ElecteurEngage& electeur) const{
   

    // Cette operation est en O(log*n)
    auto it = p_ListeElectorale.find(&electeur);

    if (it != p_ListeElectorale.end()) {
        std::cout << "L'electeur " << electeur << " est present sur la liste" << std::endl ;
        return *it; 
    } else {
        std::cout << "L'electeur " << electeur << " n'est pas present sur la liste" << std::endl ;
        return nullptr; 
    }
}

ElecteurEngage* ListeElectorale::rechercherElecteur(Personne& personne) const{
   

    // Cette operation est en O(log*n)
    auto it = p_ListeElectorale.find(new ElecteurEngage(personne));

    if (it != p_ListeElectorale.end()) {
        std::cout << "La personne " << personne << " est presente sur la liste" << std::endl ;
        return *it; 
    } else {
        std::cout << "La personne " << personne << " n'est pas presente sur la liste" << std::endl ;
        return nullptr; 
    }
}



void ListeElectorale::ajouterElecteur(Personne* & personne) {
    p_ListeElectorale.insert(new ElecteurEngage(*personne)); 
}

void ListeElectorale::ajouterElecteur(ElecteurEngage* & electeur) {
    p_ListeElectorale.insert(electeur); 
}