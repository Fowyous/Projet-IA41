cmake_minimum_required(VERSION 3.21)
project(RasendeRoboter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick QuickControls2)
qt_standard_project_setup()

qt_policy(SET QTP0001 NEW)
if(QT_KNOWN_POLICY_QTP0004)
    qt_policy(SET QTP0004 NEW)
endif()

qt_add_executable(appRasendeRoboter src/main.cpp)

# Theme est un singleton : un seul objet partagé par tous les écrans
set_source_files_properties(qml/Theme.qml qml/Textes.qml qml/Reglages.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(appRasendeRoboter
    URI RasendeRoboter
    VERSION 1.0
    QML_FILES
        qml/Theme.qml
        qml/Textes.qml
        qml/Reglages.qml
        qml/Texte.qml
        qml/BoutonPrincipal.qml
        qml/PanneauCarte.qml
        qml/PionRobot.qml
        qml/VuePlateau.qml
        qml/SelecteurRobot.qml
        qml/Commandes.qml
        qml/Sablier.qml
        qml/PanneauRechercheIA.qml
        qml/EcranMenu.qml
        qml/EcranParametres.qml
        qml/EcranDefis.qml
        qml/EcranJeu.qml
        qml/EcranFinManche.qml
        qml/Main.qml
)

target_link_libraries(appRasendeRoboter PRIVATE Qt6::Quick Qt6::QuickControls2)
