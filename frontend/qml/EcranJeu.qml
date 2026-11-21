import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: racine
    property string mode: "ia"          // "joueurs", "ia" ou "defi"
    property string niveau: "facile"    // niveau du défi
    signal terminer()

    property int secondes: 60
    property int profondeur: 1
    property int explorees: 0
    property int coups: 0
    property int annonce: 0
    property bool termine: false
    property bool reussi: false
    property string message: ""
    property string indice: ""
    property var historique: []
    readonly property int optimal: niveau === "facile" ? 4 : (niveau === "moyen" ? 6 : 9)
    readonly property string texteStatut: message !== "" ? message
        : (secondes === 0 && mode !== "defi" ? Textes.t("jeu.tempsEcoule") : Textes.t("jeu.statut", coups))

    function reset() {
        secondes = 60
        profondeur = 1
        explorees = 0
        coups = 0
        annonce = 0
        termine = false
        reussi = false
        message = ""
        indice = ""
        historique = []
        plateau.reinitialiser()
    }

    function bouger(d) {
        if (!termine && plateau.robotSelectionne >= 0)
            plateau.deplacer(plateau.robotSelectionne, d)
    }

    function apresDeplacement(i, d) {
        coups += 1
        var p = plateau.robots.get(i)
        var fleches = {N: "\u2191", S: "\u2193", O: "\u2190", E: "\u2192"}
        historique = historique.concat([{nom: p.nom, fleche: fleches[d]}])
        if (p.nom === plateau.couleurCible && p.c === plateau.cibleC && p.r === plateau.cibleR) {
            reussi = true
            termine = true
            message = Textes.t("jeu.objectif", coups)
            finTimer.start()
        }
    }

    onVisibleChanged: if (visible) reset()

    // Faux sablier et fausse recherche, pour le prototype. Tout s'arrête à 00:00.
    Timer {
        interval: 1000; repeat: true
        running: racine.visible && racine.mode !== "defi" && racine.secondes > 0 && !racine.termine
        onTriggered: racine.secondes = Math.max(0, racine.secondes - 1)
    }
    Timer {
        interval: 400; repeat: true
        running: racine.visible && racine.mode === "ia" && racine.secondes > 0 && !racine.termine
        onTriggered: {
            racine.explorees += 1800
            racine.profondeur = Math.min(12, 1 + Math.floor(racine.explorees / 6000))
        }
    }
    Timer { id: finTimer; interval: 1200; onTriggered: racine.terminer() }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        RowLayout {
            Layout.fillWidth: true
            spacing: 16
            ColumnLayout {
                spacing: 0
                Texte {
                    text: racine.mode === "ia" ? Textes.t("menu.ia")
                          : (racine.mode === "defi" ? Textes.t("menu.defis") : Textes.t("menu.joueurs"))
                    discret: true; font.pixelSize: 13
                }
                Texte { text: Textes.t("jeu.manche", 3, 8); font.pixelSize: 26; font.bold: true }
            }
            Item { Layout.fillWidth: true }
            PanneauCarte {
                marge: 10
                RowLayout {
                    spacing: 10
                    Rectangle { Layout.preferredWidth: 16; Layout.preferredHeight: 16; radius: 8; color: Theme.rouge }
                    Texte { text: Textes.t("jeu.cible", Textes.t("couleur." + plateau.couleurCible)) }
                }
            }
            Item { Layout.fillWidth: true }
            BoutonPrincipal { text: Textes.t("jeu.terminer"); onClicked: racine.terminer() }
            Sablier {
                visible: racine.mode !== "defi"
                secondes: racine.secondes
            }
            Sablier {
                visible: racine.mode === "defi"
                etiquette: Textes.t("jeu.coups")
                texte: String(racine.coups)
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 24

            ColumnLayout {
                Layout.fillWidth: true
                Layout.preferredWidth: 480
                Layout.maximumWidth: 560
                Layout.alignment: Qt.AlignTop
                spacing: 12

                // Mode joueurs / IA : scores
                PanneauCarte {
                    Layout.fillWidth: true
                    visible: racine.mode !== "defi"
                    marge: 14
                    espacement: 4
                    Repeater {
                        model: racine.mode === "ia"
                            ? [{nom: Textes.t("score.j1"), n: 2}, {nom: Textes.t("score.j2"), n: 1},
                               {nom: Textes.t("score.ia", Reglages.nomSolveur, Textes.t("param." + Reglages.difficulte).toLowerCase()), n: 1}]
                            : [{nom: Textes.t("score.j1"), n: 2}, {nom: Textes.t("score.j2"), n: 1}]
                        delegate: RowLayout {
                            required property var modelData
                            Layout.fillWidth: true
                            Texte { text: modelData.nom; Layout.fillWidth: true }
                            Texte { text: Textes.missions(modelData.n); discret: true }
                        }
                    }
                }

                // Mode joueurs / IA : annonce et commandes
                PanneauCarte {
                    Layout.fillWidth: true
                    visible: racine.mode !== "defi"
                    marge: 14
                    espacement: 10
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10
                        Texte { text: Textes.t("jeu.annoncerLabel"); wrapMode: Text.WordWrap; Layout.fillWidth: true }
                        SpinBox { id: spin; from: 1; to: 99; value: 5; editable: true; font.pixelSize: 16 }
                        BoutonPrincipal {
                            text: Textes.t("jeu.annoncer")
                            primaire: true
                            enabled: racine.secondes > 0 && !racine.termine && (racine.annonce === 0 || spin.value < racine.annonce)
                            onClicked: {
                                racine.annonce = spin.value
                                racine.message = Textes.t("jeu.annonceFaite", spin.value)
                                racine.secondes = 30
                            }
                        }
                    }
                    Commandes {
                        Layout.fillWidth: true
                        enabled: !racine.termine
                        courant: plateau.robotSelectionne
                        onChoisi: (i) => plateau.robotSelectionne = i
                        onBouger: (d) => racine.bouger(d)
                    }
                    Texte { text: racine.texteStatut; discret: true; font.pixelSize: 14; wrapMode: Text.WordWrap; Layout.fillWidth: true }
                }

                PanneauRechercheIA {
                    Layout.fillWidth: true
                    visible: racine.mode === "ia"
                    solveur: Reglages.nomSolveur
                    profondeur: racine.profondeur
                    explorees: racine.explorees
                    meilleure: racine.explorees > 30000 ? 6 : 0
                }

                // Mode défis
                PanneauCarte {
                    Layout.fillWidth: true
                    visible: racine.mode === "defi"
                    marge: 14
                    espacement: 4
                    Texte { text: Textes.t("defis.niveau", Textes.t("param." + racine.niveau)); font.pixelSize: 20; font.bold: true }
                    Texte { text: Textes.t("defis.optimal", racine.optimal); discret: true }
                }
                PanneauCarte {
                    Layout.fillWidth: true
                    visible: racine.mode === "defi"
                    marge: 14
                    espacement: 10
                    Commandes {
                        Layout.fillWidth: true
                        enabled: !racine.termine
                        courant: plateau.robotSelectionne
                        onChoisi: (i) => plateau.robotSelectionne = i
                        onBouger: (d) => racine.bouger(d)
                    }
                    Texte { text: racine.texteStatut; discret: true; font.pixelSize: 14; wrapMode: Text.WordWrap; Layout.fillWidth: true }
                }
                PanneauCarte {
                    Layout.fillWidth: true
                    visible: racine.mode === "defi"
                    marge: 14
                    espacement: 10
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10
                        BoutonPrincipal {
                            Layout.fillWidth: true
                            text: Textes.t("defis.indice")
                            onClicked: racine.indice = Textes.t("defis.indiceTexte", Textes.t("couleur." + plateau.couleurCible))
                        }
                        BoutonPrincipal {
                            Layout.fillWidth: true
                            text: Textes.t("defis.recommencer")
                            onClicked: racine.reset()
                        }
                    }
                    Texte { visible: racine.indice !== ""; text: racine.indice; wrapMode: Text.WordWrap; Layout.fillWidth: true }
                }
            }

            Item {
                id: zonePlateau
                Layout.fillWidth: true
                Layout.fillHeight: true
                VuePlateau {
                    id: plateau
                    anchors.centerIn: parent
                    cote: Math.max(240, Math.floor(Math.min(zonePlateau.width, zonePlateau.height) / 16) * 16)
                    onDeplace: (index, direction) => racine.apresDeplacement(index, direction)
                }
            }
        }
    }
}
