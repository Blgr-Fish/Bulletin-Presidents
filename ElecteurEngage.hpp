#ifndef ELECTEURENGAGE_HPP
#define ELECTEURENGAGE_HPP

#include "Personne.hpp"
#include "BulletinsCandiat.hpp"
#include "Bureau.hpp"

#include <iostream>
#include <string>
#include <list>

using namespace elections;


/**
* Un élécteur engagé représente une personne pouvant voter, qui a commencé  
* le processus de vote, c'est-à-dire choisir des bulletins de votes etc.
*
* C'est une sous classe de Personne.
*
* L'élécteur engagé possède des attributs suplémentaires tels que le temps 
* restant pour effectuer son action, les bulletins qu'il a choisi lors de la table
* de décharge, et enfin le bulletin final qu'il a gardé. 
*/
class ElecteurEngage : public Personne  {

public:

    ElecteurEngage(const Personne& personne);

    int getTempsRestant();
    void setNouveauTempsRestant(int nouveauTemps);
    void decrementeTempsRestant();

   // Bureau getBureau() const ;

   


  


private:
    int p_TempRestant ; // temps restant pour effectuer l'action ( isoloir, table de décharge, etc)
    std::list<BulletinsCandiat> p_BulletinsChoisis ;
    BulletinsCandiat p_BulletinFinal ;

   // Bureau p_BureauElecteur ; // un electeur se voit attribuer un bureau de vote

};




#endif