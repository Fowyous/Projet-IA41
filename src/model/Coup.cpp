#include <vector>
#include "Coup.h"
#include "Joueur.h"
#include "Directions.h"
#include "Type.h"

Coup::Coup(Joueur& joueur, int nbMouves) : joueur(joueur), nbMouves(nbMouves), type(Type::choixNombreMouves){}
Coup::Coup(Joueur& joueur, std::vector<Directions> chemin, Pion& pion) : joueur(joueur), chemin(chemin), pion(pion), type(Type::choixRoute){}

void Coup::coupChoixNbMouves(Joueur& joueur, int nombre){
    this->type = Type::choixNombreMouves; 
    this->joueur = joueur;
    this->nbMouves = nombre;
}

void Coup::coupChoixRoute(Joueur& joueur, std::vector<Directions> chemin, Pion& pion){
    this->type = Type::choixRoute; 
    this->joueur = joueur;
    this->chemin = chemin;
    this->pion = pion;
}

int Coup::getNbMouves(){
    return nbMouves;
}

Joueur& Coup::getJoueur(){
    return joueur;
}

std::vector<Directions> Coup::getChemin(){
    return chemin;
}
