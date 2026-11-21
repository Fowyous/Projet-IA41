import QtQuick
import QtQuick.Layouts

// Choix du robot (à gauche) et flèches de déplacement (à droite)
RowLayout {
    id: racine
    property int courant: 0
    signal choisi(int index)
    signal bouger(string direction)
    spacing: 6

    SelecteurRobot { courant: racine.courant; onChoisi: (i) => racine.choisi(i) }
    Item { Layout.fillWidth: true }
    Repeater {
        model: [
            {d: "N", s: "\u2191", k: "jeu.haut"},
            {d: "O", s: "\u2190", k: "jeu.gauche"},
            {d: "S", s: "\u2193", k: "jeu.bas"},
            {d: "E", s: "\u2192", k: "jeu.droite"}
        ]
        delegate: BoutonPrincipal {
            required property var modelData
            implicitWidth: 44
            implicitHeight: 44
            leftPadding: 0
            rightPadding: 0
            centre: true
            text: modelData.s
            Accessible.name: Textes.t(modelData.k)
            onClicked: racine.bouger(modelData.d)
        }
    }
}
