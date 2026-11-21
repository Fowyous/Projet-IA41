import QtQuick
import QtQuick.Layouts

// Une carte : elle prend automatiquement la hauteur de son contenu,
// donc rien ne peut dépasser. Les enfants sont rangés en colonne.
Rectangle {
    id: carte
    default property alias contenu: colonne.data
    property int marge: 20
    property alias espacement: colonne.spacing

    implicitWidth: colonne.implicitWidth + 2 * marge
    implicitHeight: colonne.implicitHeight + 2 * marge
    radius: Theme.rayon
    color: Theme.surface
    border.width: 1
    border.color: Theme.bordure
    Behavior on color { ColorAnimation { duration: 200 } }

    ColumnLayout {
        id: colonne
        anchors.fill: parent
        anchors.margins: carte.marge
        spacing: 8
    }
}
