#include "ElecteurEngage.hpp"

ElecteurEngage::ElecteurEngage(const Personne &personne)
    : Personne(personne), p_TempRestant(0)
{
}

int ElecteurEngage::getTempsRestant()
{
    return p_TempRestant;
}

void ElecteurEngage::decrementeTempsRestant()
{
    p_TempRestant--;
}

void ElecteurEngage::setNouveauTempsRestant(int nouveauTemps)
{
    p_TempRestant = nouveauTemps;
}

void ElecteurEngage::prendreBulletin(BulletinsCandiat bulletin)
{
    p_BulletinsChoisis.push_back(bulletin);
}

std::list<BulletinsCandiat> ElecteurEngage::getBulletins() const
{
    return p_BulletinsChoisis;
}

void ElecteurEngage::prendreBulletinFinal(BulletinsCandiat bulletin)
{
    p_BulletinFinal = bulletin;
}

BulletinsCandiat ElecteurEngage::getBulletinFinal() const
{
    return p_BulletinFinal;
}