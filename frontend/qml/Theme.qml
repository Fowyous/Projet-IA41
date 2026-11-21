pragma Singleton
import QtQuick

// Toutes les couleurs du jeu sont ici. Changer "sombre" recolore tout l'écran.
QtObject {
    property bool sombre: false

    // Mode jour : crème et blanc, comme la boîte et le plateau du jeu physique
    readonly property color fond:         sombre ? "#0F1420" : "#EFE9DB"
    readonly property color surface:      sombre ? "#171E2E" : "#FBF9F3"
    readonly property color bordure:      sombre ? "#2B3550" : "#D6CEBB"
    readonly property color texte:        sombre ? "#ECEFF7" : "#2B2A27"
    readonly property color texteDiscret: sombre ? "#A5AEC6" : "#6A6558"
    readonly property color accent:       sombre ? "#F5C542" : "#2B2A27"
    readonly property color surAccent:    sombre ? "#0F1420" : "#FBF9F3"
    readonly property color grille:       sombre ? "#252F48" : "#E1DACA"
    readonly property color mur:          sombre ? "#ECEFF7" : "#3A3631"
    readonly property color centre:       sombre ? "#0A0E18" : "#4A4A4D"

    // Robots : mêmes couleurs jour et nuit
    readonly property color rouge: "#D93A3A"
    readonly property color bleu:  "#2F6FE0"
    readonly property color vert:  "#2FA866"
    readonly property color jaune: "#F2B705"

    readonly property int rayon: 12
    readonly property int marge: 24

    function couleurRobot(nom) {
        switch (nom) {
        case "rouge": return rouge
        case "bleu":  return bleu
        case "vert":  return vert
        default:      return jaune
        }
    }
}
