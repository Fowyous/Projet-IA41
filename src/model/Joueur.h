#include <string>
#include <stdexcept>
#include "Type.h"
class Joueur{
    private:
    Type etat;
    std::string nom;//pas de nom dupliqué autorisé. La verification doit etre faite a la classe Jeux pour ajoutJoueur.
    int Points;

    public :
    Joueur(std::string nom);
    bool operator==(const Joueur& o) const;
};