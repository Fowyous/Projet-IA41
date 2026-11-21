pragma Singleton
import QtQuick

// Réglages choisis par le joueur (écran Paramètres)
QtObject {
    property string langue: "fr"
    property string solveur: "prolog"
    property string difficulte: "moyen"
    property int volumeMusique: 60
    property int volumeEffets: 80
    readonly property string nomSolveur: solveur === "prolog" ? "Prolog" : "Python"
}
