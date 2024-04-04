#ifndef VOTECANDIDAT_HPP
#define VOTECANDIDAT_HPP

#include "ElecteurEngage.hpp"
#include <iostream>
#include <string>

/**
 * Sert à comptabiliser le nombre de votes
 */
struct VoteCandidat
{
    std::string candidat;
    int occurence;
};

#endif