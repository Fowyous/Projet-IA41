import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtCore

ApplicationWindow {
    id: fenetre
    // La fenêtre s'adapte à la taille de l'écran
    width: Math.min(1280, Screen.desktopAvailableWidth - 40)
    height: Math.min(780, Screen.desktopAvailableHeight - 70)
    minimumWidth: 960
    minimumHeight: 560
    visible: true
    title: "Rasende Roboter"
    color: Theme.fond
    Behavior on color { ColorAnimation { duration: 200 } }

    property string ecran: "menu"
    property string mode: "ia"
    property string niveau: "facile"

    // Les contrôles standards (boutons radio, curseurs...) reprennent nos couleurs
    palette.windowText: Theme.texte
    palette.text: Theme.texte
    palette.buttonText: Theme.texte
    palette.button: Theme.surface
    palette.base: Theme.surface
    palette.window: Theme.fond
    palette.highlight: Theme.accent
    palette.highlightedText: Theme.surAccent
    palette.mid: Theme.bordure
    palette.dark: Theme.texteDiscret

    // Réglages mémorisés entre deux lancements
    Settings {
        id: prefs
        category: "reglages"
        property bool sombre: false
        property string langue: "fr"
        property string solveur: "prolog"
        property string difficulte: "moyen"
        property int volumeMusique: 60
        property int volumeEffets: 80
    }
    Component.onCompleted: {
        Theme.sombre = prefs.sombre
        Reglages.langue = prefs.langue
        Reglages.solveur = prefs.solveur
        Reglages.difficulte = prefs.difficulte
        Reglages.volumeMusique = prefs.volumeMusique
        Reglages.volumeEffets = prefs.volumeEffets
    }
    Connections {
        target: Theme
        function onSombreChanged() { prefs.sombre = Theme.sombre }
    }
    function sauverReglages() {
        prefs.langue = Reglages.langue
        prefs.solveur = Reglages.solveur
        prefs.difficulte = Reglages.difficulte
        prefs.volumeMusique = Reglages.volumeMusique
        prefs.volumeEffets = Reglages.volumeEffets
    }

    header: Rectangle {
        height: 56
        color: Theme.surface
        Behavior on color { ColorAnimation { duration: 200 } }
        Rectangle { anchors.bottom: parent.bottom; width: parent.width; height: 1; color: Theme.bordure }
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 24
            anchors.rightMargin: 16
            Texte { text: Textes.t("app.titre"); font.bold: true; font.pixelSize: 18 }
            Item { Layout.fillWidth: true }
            Texte { text: Textes.t("app.prototype"); discret: true; font.pixelSize: 13 }
            Item { Layout.fillWidth: true }
            BoutonPrincipal {
                implicitWidth: 44
                implicitHeight: 40
                leftPadding: 0
                rightPadding: 0
                centre: true
                text: Theme.sombre ? "\u2600\uFE0F" : "\uD83C\uDF19"
                Accessible.name: Theme.sombre ? Textes.t("jeu.modeJour") : Textes.t("jeu.modeNuit")
                onClicked: Theme.sombre = !Theme.sombre
            }
        }
    }

    EcranMenu {
        anchors.fill: parent
        visible: fenetre.ecran === "menu"
        onJouer: (mode) => { fenetre.mode = mode; fenetre.ecran = "jeu" }
        onOuvrirDefis: fenetre.ecran = "defis"
        onOuvrirParametres: fenetre.ecran = "parametres"
        onQuitter: Qt.quit()
    }
    EcranDefis {
        anchors.fill: parent
        visible: fenetre.ecran === "defis"
        onLancer: (niveau) => { fenetre.mode = "defi"; fenetre.niveau = niveau; fenetre.ecran = "jeu" }
        onRetour: fenetre.ecran = "menu"
    }
    EcranParametres {
        anchors.fill: parent
        visible: fenetre.ecran === "parametres"
        onEnregistrer: fenetre.sauverReglages()
        onRetour: fenetre.ecran = "menu"
    }
    EcranJeu {
        id: jeu
        anchors.fill: parent
        visible: fenetre.ecran === "jeu"
        mode: fenetre.mode
        niveau: fenetre.niveau
        onTerminer: fenetre.ecran = "fin"
    }
    EcranFinManche {
        anchors.fill: parent
        visible: fenetre.ecran === "fin"
        coups: jeu.coups
        reussi: jeu.reussi
        mode: fenetre.mode
        historique: jeu.historique
        onSuivante: fenetre.ecran = (fenetre.mode === "defi" ? "defis" : "jeu")
        onMenu: fenetre.ecran = "menu"
    }
}
