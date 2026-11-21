import QtQuick
import QtQuick.Layouts

Item {
    id: racine
    signal lancer(string niveau)
    signal retour()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 48
        spacing: 20

        Texte { text: Textes.t("defis.titre"); font.pixelSize: 40; font.bold: true }
        Texte { text: Textes.t("defis.sous"); discret: true; font.pixelSize: 17; wrapMode: Text.WordWrap; Layout.fillWidth: true }

        RowLayout {
            Layout.fillWidth: true
            Layout.topMargin: 8
            spacing: 20
            Repeater {
                model: ["facile", "moyen", "difficile"]
                delegate: PanneauCarte {
                    id: carteNiveau
                    required property string modelData
                    Layout.fillWidth: true
                    Layout.preferredWidth: 100
                    Layout.alignment: Qt.AlignTop
                    marge: 24
                    espacement: 10
                    Texte { text: Textes.t("param." + carteNiveau.modelData); font.pixelSize: 26; font.bold: true }
                    Texte { text: Textes.t("defis.desc." + carteNiveau.modelData); discret: true; wrapMode: Text.WordWrap; Layout.fillWidth: true }
                    BoutonPrincipal {
                        Layout.fillWidth: true
                        Layout.topMargin: 8
                        primaire: true
                        text: Textes.t("defis.lancer")
                        onClicked: racine.lancer(carteNiveau.modelData)
                    }
                }
            }
        }

        Item { Layout.fillHeight: true }
        RowLayout {
            Layout.fillWidth: true
            Item { Layout.fillWidth: true }
            BoutonPrincipal { text: Textes.t("nav.retour"); onClicked: racine.retour() }
        }
    }
}
