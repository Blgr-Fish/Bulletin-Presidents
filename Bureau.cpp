#include "Bureau.hpp"

Bureau::Bureau(std::vector<Personne*>& listeElecteurs, Election &election)
        :   p_tableDechargeBureau(listeElecteurs.size()), 
            p_listeElectoraleBureau(listeElecteurs),
            p_listeCandidatsBureau(election) {

        
        //p_tableVoteBureau ;

        // initialisation des isoloires
        for (size_t i = 0 ; i < (size_t)Parametrage::NOMBRE_ISOLOIRS ; ++i) {
            Isoloire isoloire ;
            p_listeIsoloires.push_back(isoloire);
        }

        p_tableDechargeBureau.ajouterCandidats(p_listeCandidatsBureau);
}

void Bureau::init(){
        // ajout des electeurs dans le file, suivant l'ordre de la liste electorale
        for (ElecteurEngage* electeur : p_listeElectoraleBureau.getListeElectorale()){
            p_fileBureauVersTableDecharge.push(electeur);
        }
        
    }
