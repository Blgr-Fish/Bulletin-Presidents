#include "TableVote.hpp"
#include "Parametrage.hpp"

TableVote::TableVote(const Personne &president, const ListeElectorale listeElectorale)
{

    p_presidentTableVote = president;

    p_etat = true; // true = vide
    p_electeurOccupant = nullptr;

    // tous les electeurs sont à faux (ils n'ont pas voté)
    for (ElecteurEngage *electeur : listeElectorale.getListeElectorale())
    {
        p_tableEmargement.insert(std::make_pair(electeur->getId(), false));
    }
}

void TableVote::entrerTableVote(ElecteurEngage *&electeur)
{
    if (estVide())
    {
        p_electeurOccupant = electeur;
        p_electeurOccupant->setNouveauTempsRestant(Parametrage::TEMPS_VOTE);
        p_etat = false;
        // std::cout << "L'electeur " << electeur->getNom() << " est entre dans la table de vote " << std::endl;
    }
    else
    {
        // std::cout << "L'electeur " << electeur->getNom() << " a tente d'entrer dans la table de vote qui est deja en cours d'utilisation." << std::endl;
    }
}

void TableVote::sortirTableVote()
{
    p_etat = true;
    // std::cout << "La table de vote a ete vide."<< std::endl;

    // l'electeur sort et ne va dans aucune file desormais
    if (p_electeurOccupant != nullptr)
    {
        p_electeurOccupant = nullptr;
    }
}

bool TableVote::estVide()
{
    return p_etat;
}

ElecteurEngage *&TableVote::getOccupant() { return p_electeurOccupant; }

void TableVote::placerBulletin()
{
    p_urneBulletins.push(p_electeurOccupant->getBulletinFinal());
}

void TableVote::emarger()
{
    p_tableEmargement[p_electeurOccupant->getId()] = true;
}

bool TableVote::estPresentDansEmargement()
{
    return p_tableEmargement[p_electeurOccupant->getId()];
}

Personne TableVote::getPresident()
{
    return p_presidentTableVote;
}

std::stack<BulletinsCandiat> &TableVote::getUrneBulletins() { return p_urneBulletins; }

