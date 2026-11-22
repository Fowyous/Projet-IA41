#include <vector>
#include "Coup.h"
#include "Joueur.h"
#include "Directions.h"
#include "Type.h"
void Coup::coupChoixNbMouves(Joueur joueur, int nombre){
    //this->type = Type::choixNombreMouves; //a enlever le commentaire après implementation
    this->joueur = joueur;
    this->NbMouves = nombre;
}

void Coup::coupChoixRoute(Joueur joueur, std::vector<Directions> chemin){
    //this->type = Type::choixRoute; //a enlever le commentaire après implementation
    this->joueur = joueur;
    this->chemin = chemin;
}
