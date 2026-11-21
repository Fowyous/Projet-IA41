import QtQuick

Rectangle {
    property color teinte: Theme.rouge
    property bool selectionne: false

    radius: width / 2
    color: teinte
    border.width: selectionne ? 3 : 1
    border.color: selectionne ? Theme.texte : Qt.darker(teinte, 1.5)

    // Petit reflet pour donner du volume
    Rectangle {
        x: parent.width * 0.22
        y: parent.height * 0.14
        width: parent.width * 0.28
        height: width
        radius: width / 2
        color: "white"
        opacity: 0.35
    }
}
