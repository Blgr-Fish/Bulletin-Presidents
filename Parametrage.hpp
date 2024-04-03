#ifndef PARAMETRAGE_HPP
#define PARAMETRAGE_HPP

#include <iostream>

namespace Parametrage {
    /**
     * Ce fichier contient tous les paramètres modifiables de temps, et de probabilités
     * de tirage de bulletins.
     */

    // Valeurs de paramètre
    const size_t TEMPS_MAX = 20;                    // Temps maximal pour une opération
    const size_t TEMPS_DECHARGE = 3;                // Temps de déchargement des bulletins dans l'urne
    const size_t TEMPS_ISOLOIR = 6;                 // Temps maximum passé dans l'isoloir
    const size_t TEMPS_VOTE = 4;                    // Temps maximum pour voter
    const double PROBABILITE_VOTE_BLANC = 0.35;     // Probabilité de vote blanc
    const double PROBABILITE_VOTE_NUL = 0.15;       // Probabilité de vote nul
    const size_t NOMBRE_ISOLOIRS = 3;               // Nombre d'isoloirs disponibles
    const size_t DISTANCE_POLITIQUE_MAXIMALE = 3;   // Distance politique maximale entre deux électeurs
}

#endif
