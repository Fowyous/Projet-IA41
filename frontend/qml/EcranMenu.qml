import QtQuick
import QtQuick.Layouts

Item {
    id: racine
    signal jouer(string mode)
    signal ouvrirDefis()
    signal ouvrirParametres()
    signal quitter()
    readonly property int coteDecor: Math.max(240, Math.min(400, Math.floor((height - 160) / 16) * 16))

    RowLayout {
        anchors.fill: parent
        anchors.margins: 48
        spacing: 40

        ColumnLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            spacing: 24

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 8
                Texte {
                    text: Textes.t("app.titre")
                    font.pixelSize: Math.round(Math.max(36, Math.min(56, racine.width / 22)))
                    font.bold: true
                }
                Texte {
                    text: Textes.t("menu.sous")
                    discret: true
                    font.pixelSize: 18
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.maximumWidth: 480
                spacing: 10
                BoutonPrincipal {
                    Layout.fillWidth: true
                    primaire: true
                    text: Textes.t("menu.joueurs")
                    description: Textes.t("menu.joueursDesc")
                    onClicked: racine.jouer("joueurs")
                }
                BoutonPrincipal {
                    Layout.fillWidth: true
                    text: Textes.t("menu.ia")
                    description: Textes.t("menu.iaDesc")
                    onClicked: racine.jouer("ia")
                }
                BoutonPrincipal {
                    Layout.fillWidth: true
                    text: Textes.t("menu.defis")
                    description: Textes.t("menu.defisDesc")
                    onClicked: racine.ouvrirDefis()
                }
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 10
                    BoutonPrincipal { Layout.fillWidth: true; text: Textes.t("menu.parametres"); onClicked: racine.ouvrirParametres() }
                    BoutonPrincipal { Layout.fillWidth: true; text: Textes.t("menu.quitter"); onClicked: racine.quitter() }
                }
            }
        }

        PanneauCarte {
            Layout.alignment: Qt.AlignVCenter
            marge: 24
            VuePlateau { cote: racine.coteDecor; interactif: false; robotSelectionne: -1 }
        }
    }
}
