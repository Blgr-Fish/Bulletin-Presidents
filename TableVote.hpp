#ifndef TABLEVOTE_HPP
#define TABLEVOTE_HPP

#include "ElecteurEngage.hpp"
#include "BulletinsCandiat.hpp"

#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

class TableVote{

public:
        TableVote();
        

private:

    std::stack<BulletinsCandiat> p_urneBulletins ;
    std::unordered_map<size_t,std::string> tableEmargement ;

};



#endif