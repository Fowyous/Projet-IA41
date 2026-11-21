import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: racine
    signal retour()
    signal enregistrer()

    // Les contrôles sont remplis depuis les réglages à chaque ouverture
    function charger() {
        rProlog.checked = Reglages.solveur === "prolog"
        rPython.checked = Reglages.solveur === "python"
        rFacile.checked = Reglages.difficulte === "facile"
        rMoyen.checked = Reglages.difficulte === "moyen"
        rDifficile.checked = Reglages.difficulte === "difficile"
        sMusique.value = Reglages.volumeMusique
        sEffets.value = Reglages.volumeEffets
        listeLangue.currentIndex = Reglages.langue === "en" ? 1 : 0
    }

    function appliquer() {
        Reglages.solveur = rProlog.checked ? "prolog" : "python"
        Reglages.difficulte = rFacile.checked ? "facile" : (rDifficile.checked ? "difficile" : "moyen")
        Reglages.volumeMusique = Math.round(sMusique.value)
        Reglages.volumeEffets = Math.round(sEffets.value)
        Reglages.langue = listeLangue.currentIndex === 1 ? "en" : "fr"
        racine.enregistrer()
        racine.retour()
    }

    onVisibleChanged: if (visible) charger()
    Component.onCompleted: charger()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 48
        spacing: 20

        Texte { text: Textes.t("param.titre"); font.pixelSize: 40; font.bold: true }

        GridLayout {
            columns: 2
            rowSpacing: 16
            columnSpacing: 16
            Layout.fillWidth: true

            PanneauCarte {
                Layout.fillWidth: true; Layout.preferredWidth: 100; Layout.alignment: Qt.AlignTop
                espacement: 4
                Texte { text: Textes.t("param.solveur"); font.pixelSize: 20; font.bold: true }
                Texte { text: Textes.t("param.solveurDesc"); discret: true; font.pixelSize: 14; wrapMode: Text.WordWrap; Layout.fillWidth: true }
                RadioButton { id: rProlog; text: "Prolog" }
                RadioButton { id: rPython; text: "Python" }
            }
            PanneauCarte {
                Layout.fillWidth: true; Layout.preferredWidth: 100; Layout.alignment: Qt.AlignTop
                espacement: 4
                Texte { text: Textes.t("param.force"); font.pixelSize: 20; font.bold: true }
                Texte { text: Textes.t("param.forceDesc"); discret: true; font.pixelSize: 14; wrapMode: Text.WordWrap; Layout.fillWidth: true }
                RadioButton { id: rFacile; text: Textes.t("param.facile") }
                RadioButton { id: rMoyen; text: Textes.t("param.moyen") }
                RadioButton { id: rDifficile; text: Textes.t("param.difficile") }
            }
            PanneauCarte {
                Layout.fillWidth: true; Layout.preferredWidth: 100; Layout.alignment: Qt.AlignTop
                espacement: 10
                Texte { text: Textes.t("param.son"); font.pixelSize: 20; font.bold: true }
                RowLayout {
                    Layout.fillWidth: true
                    Texte { text: Textes.t("param.musique"); Layout.preferredWidth: 90 }
                    Slider { id: sMusique; from: 0; to: 100; Layout.fillWidth: true }
                }
                RowLayout {
                    Layout.fillWidth: true
                    Texte { text: Textes.t("param.effets"); Layout.preferredWidth: 90 }
                    Slider { id: sEffets; from: 0; to: 100; Layout.fillWidth: true }
                }
            }
            PanneauCarte {
                Layout.fillWidth: true; Layout.preferredWidth: 100; Layout.alignment: Qt.AlignTop
                espacement: 8
                Texte { text: Textes.t("param.langue"); font.pixelSize: 20; font.bold: true }
                Texte { text: Textes.t("param.langueDesc"); discret: true; font.pixelSize: 14; wrapMode: Text.WordWrap; Layout.fillWidth: true }
                ComboBox { id: listeLangue; Layout.fillWidth: true; model: ["Français", "English"] }
            }
        }

        Item { Layout.fillHeight: true }

        RowLayout {
            Layout.fillWidth: true
            spacing: 10
            Item { Layout.fillWidth: true }
            BoutonPrincipal { text: Textes.t("nav.retour"); onClicked: racine.retour() }
            BoutonPrincipal { text: Textes.t("nav.enregistrer"); primaire: true; onClicked: racine.appliquer() }
        }
    }
}
