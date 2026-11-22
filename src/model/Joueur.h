#include <string>
#include <stdexcept>
#include "Type.h"
class Joueur{
    private:
    Type etat;
    std::string nom;
    int Points;

    public :
    Joueur(std::string nom);

};