import QtQuick
import QtQuick.Controls.Basic

Row {
    id: racine
    property int courant: 0
    signal choisi(int index)
    spacing: 6

    Repeater {
        model: ["rouge", "bleu", "vert", "jaune"]
        delegate: Button {
            id: pastille
            required property int index
            required property string modelData
            implicitWidth: 44
            implicitHeight: 44
            padding: 0
            Accessible.name: Textes.t("jeu.robot", pastille.index + 1, Textes.t("couleur." + pastille.modelData))
            onClicked: racine.choisi(pastille.index)
            contentItem: Text {
                text: pastille.index + 1
                font.pixelSize: 17
                font.bold: true
                color: "#1A1A1A"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                radius: 22
                color: Theme.couleurRobot(pastille.modelData)
                border.width: racine.courant === pastille.index ? 4 : 1
                border.color: racine.courant === pastille.index ? Theme.texte : Qt.darker(Theme.couleurRobot(pastille.modelData), 1.5)
            }
        }
    }
}
