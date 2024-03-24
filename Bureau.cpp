#include "Bureau.hpp"


Bureau::Bureau(const std::vector<Isoloire> & isoloires, const TableVote& tableVote,
               std::vector<ElecteurEngage*>& listeElecteurs, Election &election)
               : p_tableDechargeBureau(listeElecteurs.size()), 
                 p_listeIsoloires(isoloires.begin(), isoloires.end()), 
                 p_listeElectoraleBureau(listeElecteurs),
                 p_listeCandidatsBureau(election) {
                 p_tableVoteBureau = tableVote;
}