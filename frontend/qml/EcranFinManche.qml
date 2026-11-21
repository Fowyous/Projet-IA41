import QtQuick
import QtQuick.Layouts

Item {
    id: racine
    property int coups: 0
    property bool reussi: false
    property string mode: "ia"
    property var historique: []
    signal suivante()
    signal menu()

    PanneauCarte {
        anchors.centerIn: parent
        width: Math.min(760, parent.width - 64)
        marge: 32
        espacement: 16

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4
            Texte { text: Textes.t("jeu.manche", 3, 8); discret: true; font.pixelSize: 14 }
            Texte {
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
                font.pixelSize: 34
                font.bold: true
                text: !racine.reussi ? Textes.t("fin.echec")
                      : (racine.mode === "defi" ? Textes.t("fin.reussiDefi") : Textes.t("fin.reussiIA"))
            }
            Texte {
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
                discret: true
                font.pixelSize: 17
                text: !racine.reussi ? Textes.t("fin.echecDetail")
                      : (racine.mode === "ia" ? Textes.t("fin.detailIA", racine.coups)
                         : Textes.t("fin.detailJoueurs", racine.coups))
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            visible: racine.historique.length > 0
            spacing: 8
            Texte { text: Textes.t("fin.solution"); discret: true; font.pixelSize: 14 }
            Flow {
                Layout.fillWidth: true
                Layout.preferredHeight: childrenRect.height
                spacing: 8
                Repeater {
                    model: racine.historique
                    delegate: Rectangle {
                        required property var modelData
                        width: puce.implicitWidth + 24
                        height: 40
                        radius: 8
                        color: "transparent"
                        border.width: 1
                        border.color: Theme.bordure
                        Row {
                            id: puce
                            anchors.centerIn: parent
                            spacing: 8
                            Rectangle { width: 14; height: 14; radius: 7; color: Theme.couleurRobot(modelData.nom); anchors.verticalCenter: parent.verticalCenter }
                            Texte { text: Textes.t("couleur." + modelData.nom) + " " + modelData.fleche }
                        }
                    }
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            visible: racine.mode !== "defi"
            spacing: 4
            Texte { text: Textes.t("fin.scores"); discret: true; font.pixelSize: 14 }
            RowLayout { Layout.fillWidth: true; Texte { text: Textes.t("score.j1"); Layout.fillWidth: true } Texte { text: Textes.missions(racine.reussi ? 3 : 2); font.bold: true } }
            RowLayout { Layout.fillWidth: true; Texte { text: Textes.t("score.j2"); Layout.fillWidth: true } Texte { text: Textes.missions(1); font.bold: true } }
            RowLayout {
                Layout.fillWidth: true
                visible: racine.mode === "ia"
                Texte { text: Textes.t("score.ia", Reglages.nomSolveur, Textes.t("param." + Reglages.difficulte).toLowerCase()); Layout.fillWidth: true }
                Texte { text: Textes.missions(1); font.bold: true }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.topMargin: 8
            spacing: 10
            BoutonPrincipal { text: Textes.t("nav.menu"); onClicked: racine.menu() }
            Item { Layout.fillWidth: true }
            BoutonPrincipal {
                text: racine.mode === "defi" ? Textes.t("fin.nouveauDefi") : Textes.t("fin.suivante")
                primaire: true
                onClicked: racine.suivante()
            }
        }
    }
}
