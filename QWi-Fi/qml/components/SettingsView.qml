import QtQuick 2.6
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0

import "../style"
import "../actions"
import "../stores"

Item {
    signal back()

    HeaderView{
        headerTitle: qsTr("QWi-Fi settings")
    }

    CheckBoxStyled {
        id: _storeCredentials
        x: 13
        y: 70
        checked: MainStore.storeCredentials
        text: qsTr("Store the access point configuration")
        onCheckedChanged: {
            AppActions.setStoreCredentials(_storeCredentials.checked)
        }
    }

    CheckBoxStyled {
        id: _minimizeOnStart
        x: 13
        y: 102
        checked: MainStore.minimizeOnStart
        text: qsTr("Minimize to the system tray on starting")
        onCheckedChanged: {
            AppActions.setMinimizeOnStart(_minimizeOnStart.checked)
        }
    }



    Row {
        id: row1
        x: 18
        y: 135
        width: 296
        height: 44

        Label {
            id: label
            width: 70
            height: 17
            text: qsTr("Language:")
            antialiasing: true
            verticalAlignment: Text.AlignTop
            anchors.verticalCenterOffset: -1
            anchors.verticalCenter: parent.verticalCenter
        }

        ComboBoxStyled {            
            id: _languageCombobox
            y: 5
            currentIndex: 0
            width: 95
            height: 28
            model: ListModel {
                id: languageModel
                ListElement { modelData: qsTr("English"); value: "en" }
                ListElement { modelData: qsTr("Spanish"); value: "es" }
            }
            onCurrentIndexChanged: {               
               AppActions.setLanguage(languageModel.get(currentIndex).value)
            }
        }
    }

    TextStyled {
        id: label1
        x: row1.x
        anchors.top: row1.bottom
        anchors.topMargin: 5
        height: 17
        font.italic: true
        font.pixelSize: 10
        color: "#333"
        text: qsTr("*You need to restart de application to see changes on language")
    }




    Component.onCompleted: {
        switch(MainStore.language){
        case "en":
            _languageCombobox.currentIndex = 0;
            break;
        case "es":
            _languageCombobox.currentIndex = 1;
            break;
        }
    }



}
