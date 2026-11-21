import QtQuick

// Le plateau 16x16. Les données ici sont factices : le vrai plateau viendra du modèle C++.
Item {
    id: racine

    property int cote: 512
    readonly property real cell: cote / 16
    property int robotSelectionne: 0
    property bool interactif: true
    property string couleurCible: "rouge"
    property int cibleC: 9
    property int cibleR: 3
    property alias robots: modeleRobots

    // Quand un robot a réellement bougé : index du robot et direction
    signal deplace(int index, string direction)

    // Murs posés sur le côté Est ("E") ou Sud ("S") de la case (c, r)
    property var murs: [
        {c: 9, r: 3, d: "E"}, {c: 9, r: 2, d: "S"},
        {c: 3, r: 5, d: "S"}, {c: 2, r: 5, d: "E"},
        {c: 12, r: 6, d: "E"}, {c: 12, r: 6, d: "S"},
        {c: 5, r: 11, d: "S"}, {c: 4, r: 12, d: "E"},
        {c: 11, r: 12, d: "E"}, {c: 11, r: 12, d: "S"},
        {c: 6, r: 0, d: "E"}, {c: 10, r: 15, d: "E"},
        {c: 0, r: 9, d: "S"}, {c: 15, r: 5, d: "S"}
    ]
    readonly property var departs: [[2, 1], [12, 3], [5, 11], [13, 13]]

    width: cote
    height: cote
    implicitWidth: cote
    implicitHeight: cote

    ListModel {
        id: modeleRobots
        ListElement { nom: "rouge"; c: 2;  r: 1 }
        ListElement { nom: "bleu";  c: 12; r: 3 }
        ListElement { nom: "vert";  c: 5;  r: 11 }
        ListElement { nom: "jaune"; c: 13; r: 13 }
    }

    function reinitialiser() {
        for (var i = 0; i < modeleRobots.count; i++) {
            modeleRobots.setProperty(i, "c", departs[i][0])
            modeleRobots.setProperty(i, "r", departs[i][1])
        }
        robotSelectionne = 0
    }

    function murEntre(c, r, d) {
        function cherche(cc, rr, dd) {
            for (var i = 0; i < racine.murs.length; i++) {
                var m = racine.murs[i]
                if (m.c === cc && m.r === rr && m.d === dd) return true
            }
            return false
        }
        if (d === "E") return cherche(c, r, "E")
        if (d === "O") return cherche(c - 1, r, "E")
        if (d === "S") return cherche(c, r, "S")
        return cherche(c, r - 1, "S")
    }

    function libre(c, r) {
        if (c < 0 || c > 15 || r < 0 || r > 15) return false
        if (c >= 7 && c <= 8 && r >= 7 && r <= 8) return false
        for (var i = 0; i < modeleRobots.count; i++) {
            var p = modeleRobots.get(i)
            if (p.c === c && p.r === r) return false
        }
        return true
    }

    // Le robot glisse jusqu'à rencontrer un mur, le bord, le centre ou un autre robot
    function deplacer(i, d) {
        var dc = d === "E" ? 1 : (d === "O" ? -1 : 0)
        var dr = d === "S" ? 1 : (d === "N" ? -1 : 0)
        var c0 = modeleRobots.get(i).c
        var r0 = modeleRobots.get(i).r
        var c = c0
        var r = r0
        while (!murEntre(c, r, d) && libre(c + dc, r + dr)) {
            c += dc
            r += dr
        }
        if (c === c0 && r === r0) return
        modeleRobots.setProperty(i, "c", c)
        modeleRobots.setProperty(i, "r", r)
        racine.deplace(i, d)
    }

    Rectangle {
        anchors.fill: parent
        radius: 6
        color: Theme.surface
        border.width: 3
        border.color: Theme.mur
        Behavior on color { ColorAnimation { duration: 200 } }
    }

    Repeater {
        model: 256
        delegate: Rectangle {
            required property int index
            x: (index % 16) * racine.cell
            y: Math.floor(index / 16) * racine.cell
            width: racine.cell
            height: racine.cell
            color: "transparent"
            border.width: 1
            border.color: Theme.grille
        }
    }

    // Bloc central 2x2 : la cible du tour s'y affiche
    Rectangle {
        x: 7 * racine.cell
        y: 7 * racine.cell
        width: 2 * racine.cell
        height: 2 * racine.cell
        color: Theme.centre
        Rectangle {
            anchors.centerIn: parent
            width: racine.cell * 0.9
            height: width
            radius: width / 2
            color: Theme.couleurRobot(racine.couleurCible)
        }
    }

    // La case cible
    Rectangle {
        x: racine.cibleC * racine.cell + 2
        y: racine.cibleR * racine.cell + 2
        width: racine.cell - 4
        height: racine.cell - 4
        radius: 3
        color: "transparent"
        border.width: 2
        border.color: Theme.couleurRobot(racine.couleurCible)
        Text {
            anchors.centerIn: parent
            text: "\u00D7"
            font.pixelSize: racine.cell * 0.7
            font.bold: true
            color: Theme.couleurRobot(racine.couleurCible)
        }
    }

    Repeater {
        model: racine.murs
        delegate: Rectangle {
            required property var modelData
            readonly property bool est: modelData.d === "E"
            x: est ? (modelData.c + 1) * racine.cell - 2 : modelData.c * racine.cell
            y: est ? modelData.r * racine.cell : (modelData.r + 1) * racine.cell - 2
            width: est ? 5 : racine.cell
            height: est ? racine.cell : 5
            radius: 2
            color: Theme.mur
        }
    }

    Repeater {
        model: modeleRobots
        delegate: PionRobot {
            required property int index
            required property string nom
            required property int c
            required property int r
            width: racine.cell * 0.68
            height: width
            x: c * racine.cell + (racine.cell - width) / 2
            y: r * racine.cell + (racine.cell - height) / 2
            teinte: Theme.couleurRobot(nom)
            selectionne: racine.interactif && racine.robotSelectionne === index
            Behavior on x { NumberAnimation { duration: 260; easing.type: Easing.OutCubic } }
            Behavior on y { NumberAnimation { duration: 260; easing.type: Easing.OutCubic } }
            TapHandler {
                enabled: racine.interactif
                onTapped: racine.robotSelectionne = index
            }
        }
    }
}
