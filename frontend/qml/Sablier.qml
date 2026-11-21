import QtQuick

Column {
    id: racine
    property int secondes: 60
    property string etiquette: Textes.t("jeu.sablier")
    property string texte: format(secondes)
    function format(s) {
        var m = Math.floor(s / 60)
        var r = s % 60
        return (m < 10 ? "0" : "") + m + ":" + (r < 10 ? "0" : "") + r
    }
    spacing: 0
    Texte { text: racine.etiquette; discret: true; font.pixelSize: 13; anchors.right: parent.right }
    Texte { text: racine.texte; font.pixelSize: 36; font.bold: true; anchors.right: parent.right }
}
