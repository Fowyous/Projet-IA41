import QtQuick

Text {
    property bool discret: false
    color: discret ? Theme.texteDiscret : Theme.texte
    font.pixelSize: 16
}
