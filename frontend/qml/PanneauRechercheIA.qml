import QtQuick
import QtQuick.Layouts

// Avancée du solveur. Plus tard : alimenté par les messages "progress" du solveur.
PanneauCarte {
    id: carte
    property string solveur: "Prolog"
    property int profondeur: 1
    property int explorees: 0
    property int meilleure: 0
    marge: 16
    espacement: 8

    RowLayout {
        Layout.fillWidth: true
        Texte { text: Textes.t("ia.titre"); font.pixelSize: 18; font.bold: true; Layout.fillWidth: true }
        Texte { text: Textes.t("ia.solveur", carte.solveur); discret: true; font.pixelSize: 14 }
    }
    RowLayout {
        Layout.fillWidth: true
        spacing: 36
        Column {
            Texte { text: Textes.t("ia.profondeur"); discret: true; font.pixelSize: 13 }
            Texte { text: carte.profondeur; font.pixelSize: 26; font.bold: true }
        }
        Column {
            Texte { text: Textes.t("ia.explorees"); discret: true; font.pixelSize: 13 }
            Texte { text: carte.explorees.toLocaleString(Qt.locale("fr_FR"), "f", 0); font.pixelSize: 26; font.bold: true }
        }
    }
    Rectangle {
        Layout.fillWidth: true
        Layout.preferredHeight: 8
        radius: 4
        color: Theme.bordure
        Rectangle {
            height: parent.height
            radius: 4
            color: Theme.rouge
            width: parent.width * Math.min(1, carte.profondeur / 12)
            Behavior on width { NumberAnimation { duration: 300 } }
        }
    }
    Texte {
        Layout.fillWidth: true
        wrapMode: Text.WordWrap
        text: carte.meilleure === 0 ? Textes.t("ia.aucune") : Textes.t("ia.meilleure", carte.meilleure)
        discret: true
        font.pixelSize: 14
    }
}
