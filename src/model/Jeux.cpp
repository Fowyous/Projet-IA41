#include "Jeux.h"
#include "PointsJoueurs.h"
#include "Tour.h"
#include "Joueur.h"
#include "rules/RuleEngine.h"
#include <memory>
#include <random>


Jeux::Jeux() : gameOver(false), points(){
}

Jeux::~Jeux(){
    for (Joueur* joueur : joueurs){
        delete joueur;
    }
    for (Tour* tour : tours){
        delete tour;
    }
}

Jeux::Jeux(const Jeux& o) : gameOver(o.gameOver), points(o.points), plateau(o.plateau){
    for (Joueur* joueur : joueurs){
        delete joueur;
    }
    joueurs.clear();
    joueurs.reserve(o.joueurs.size());
    for (const Joueur* ojoueur : o.joueurs){
        joueurs.push_back(ojoueur ? new Joueur(*ojoueur) : nullptr);
    }
    for (Tour* tour : tours){
        delete tour;
    }
    tours.clear();
    tours.reserve(o.tours.size());
    for (const Tour* otour : o.tours){
        tours.push_back(otour ? new Tour(*otour) : nullptr);
    }
}

const Tour& Jeux::getCeTour() const{
    return *tours.back();
}

Tour& Jeux::getCeTour(){
    return *tours.back();
}

void Jeux::prochainTour(){
    if (joueurs.empty()) {
        throw std::logic_error("Impossible de commencer un tour sans joueur.");
    }
    if (gameOver){
        return;
    }

    Tour* nouveauTour = new Tour(choisirProchaineCible());
    nouveauTour->commencerHorloge();
    tours.push_back(nouveauTour);
}

Cible Jeux::choisirProchaineCible() const {
    // Une cible déjà utilisée dans un tour précédent n'est pas proposée à nouveau.
    auto dejaJouee = [this](const Cible& candidate) {
        for (const Tour* tour : tours) {
            const Cible& ancienne = tour->getBut();
            if (ancienne.getCouleur() == candidate.getCouleur() &&
                ancienne.getForme() == candidate.getForme()) {
                return true;
            }
        }
        return false;
    };

    std::vector<Cible> candidates;
    for (int y = 0; y < Plateaux::TAILLE; ++y) {
        for (int x = 0; x < Plateaux::TAILLE; ++x) {
            const Case& caseCourante = plateau.getCase(x, y);
            if (caseCourante.contientCible()) {
                Cible copie = *caseCourante.getCible();
                if (!dejaJouee(copie)) {
                    candidates.push_back(copie);
                }
            }
        }
    }

    if (candidates.empty()) {
        throw std::logic_error("Plus aucune cible disponible pour un nouveau tour.");
    }

    static std::mt19937 generateur{std::random_device{}()};
    std::uniform_int_distribution<std::size_t> distribution(0, candidates.size() - 1);

    Cible choisie = candidates[distribution(generateur)];
    choisie.setBut(true);
    return choisie;
}

Joueur& Jeux::getGagnant() {
    if (joueurs.empty()) {
        throw std::logic_error("Aucun joueur dans la partie.");
    }

    Joueur* meilleur = joueurs.front();
    int meilleurScore = points.getReussiteTotal(*meilleur);

    for (std::size_t i = 1; i < joueurs.size(); ++i) {
        int score = points.getReussiteTotal(*joueurs[i]);
        if (score > meilleurScore) {
            meilleur = joueurs[i];
            meilleurScore = score;
        }
    }

    return *meilleur;
}

void Jeux::avancerEtatTour() {
    if (tours.empty()) {
        return;
    }

    Tour& tour = getCeTour();

    switch (tour.getEtat()) {
        case choixNombreMouves:
            // Tour passe seul en phase choixRoute quand le temps est écoulé.
            // L'appel vérifie l'horloge ; la valeur retournée n'est pas utilisée ici.
            (void)tour.getTempsEcoule();
            break;

        case choixRoute:
            // Personne n'a annoncé de nombre de mouvements : on passe au tour suivant.
            if (tour.pasMouvesPropose()) {
                prochainTour();
            }
            break;

        case attendreTour:
            break;

    }
}

void Jeux::enregistrerVictoire(Joueur& gagnant) {
    points.sauvegardePoints(static_cast<int>(tours.size()), gagnant);
    prochainTour();
}
