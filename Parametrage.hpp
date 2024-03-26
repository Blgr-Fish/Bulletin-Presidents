/**
 * Ce fichier contient tous les paramètres modifiables de temps, et de probabilités
 * de tirage de bulletins.
*/

#ifndef PARAMETRAGE_HPP
#define PARAMETRAGE_HPP

#include <iostream>

namespace Parametrage {
    // Valeurs de paramètre
    const size_t TEMPS_MAX = 20;
    const size_t TEMPS_DECHARGE = 3;
    const size_t TEMPS_ISOLOIR = 6;
    const size_t TEMPS_VOTE = 4;
    const double PROBABILITE_VOTE_BLANC = 0.35;
    const double PROBABILITE_VOTE_NUL = 0.15;
    const size_t NOMBRE_ISOLOIRS = 3;
    const size_t DISTANCE_POLITIQUE_MAXIMALE = 10;
}

#endif