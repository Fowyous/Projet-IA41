import QtQuick
import QtQuick.Controls.Basic

// Bouton : sa largeur s'adapte toujours à son texte.
Button {
    id: bouton
    property bool primaire: false
    property bool centre: false
    property string description: ""

    implicitHeight: description === "" ? 48 : 72
    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding
    leftPadding: 20
    rightPadding: 20
    hoverEnabled: true

    contentItem: Item {
        implicitWidth: colonne.implicitWidth
        implicitHeight: colonne.implicitHeight
        Column {
            id: colonne
            spacing: 2
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: bouton.centre ? parent.horizontalCenter : undefined
            Text {
                text: bouton.text
                font.pixelSize: 17
                font.bold: true
                color: bouton.primaire ? Theme.surAccent : Theme.texte
            }
            Text {
                visible: bouton.description !== ""
                text: bouton.description
                font.pixelSize: 13
                color: bouton.primaire ? Theme.surAccent : Theme.texteDiscret
            }
        }
    }

    background: Rectangle {
        radius: Theme.rayon
        color: bouton.primaire ? Theme.accent
                               : (bouton.down ? Theme.bordure : Theme.surface)
        border.width: bouton.visualFocus ? 3 : 1
        border.color: bouton.visualFocus ? Theme.rouge
                      : (bouton.hovered ? Theme.texteDiscret : (bouton.primaire ? Theme.accent : Theme.bordure))
        opacity: bouton.enabled ? 1.0 : 0.45
        Behavior on color { ColorAnimation { duration: 150 } }
    }
}
