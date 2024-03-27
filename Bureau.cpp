#include "Bureau.hpp"


Bureau::Bureau(const std::vector<Isoloire> & isoloires, const TableVote& tableVote,
               std::vector<ElecteurEngage*>& listeElecteurs, Election &election)
               : p_tableDechargeBureau(listeElecteurs.size()), 
                 p_listeIsoloires(isoloires.begin(), isoloires.end()), 
                 p_listeElectoraleBureau(listeElecteurs),
                 p_listeCandidatsBureau(election) {
                 p_tableVoteBureau = tableVote;
}

void Bureau::init(){
        // ajout des electeurs dans le file, suivant l'ordre de la liste electorale
        for (ElecteurEngage* electeur : p_listeElectoraleBureau.getListeElectorale()){
            p_fileBureauVersTableDecharge.push(electeur);
        }
        
    }
