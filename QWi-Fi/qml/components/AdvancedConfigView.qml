import QtQuick 2.7
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0
import "../style"
import "../actions"
import "../stores"

Item {
    id: item1


    signal back()

    HeaderView{
        headerTitle:qsTr("Advanced config")
    }

    CheckBoxStyled {
        id: hiddenAP
        x: 15
        y: 99
        width: 264
        height: 38
        text: qsTr("Access point hidden")
        checked: MainStore.hidden
        onCheckedChanged: {
            AppActions.setHidden(hiddenAP.checked)
        }
    }

    CheckBoxStyled {
        id: isolate
        x: 15
        y: 69
        text: qsTr("Disable communication between clients")
        checked: MainStore.isolation
        onCheckedChanged: {
            AppActions.setIsolation(isolate.checked)
        }
    }

    Row {
        id: row1
        x: 22
        y: 130
        width: 296
        height: 47

        Label {
            id: label
            width: 110
            height: 17
            text: qsTr("Difusion channel:")
            verticalAlignment: Text.AlignTop
            anchors.verticalCenterOffset: 1
            anchors.verticalCenter: parent.verticalCenter
        }

        ComboBoxStyled {
            id: channelAp
            property int _index: MainStore.channel-1
            x: 100
            y: 8
            width: 59
            height: 28
            model: [1,2,3,4,5,6,7,8,9,10,11]
            currentIndex: _index
            onCurrentIndexChanged: {
                AppActions.setChannel(channelAp.currentIndex+1)
            }
        }


    }

    Row {
        id: row2
        x: 22
        y: 180
        width: 243
        height: 35
        spacing: 8

        Label {
            id: label2
            height: 17
            text: qsTr("Gateway:")
            anchors.verticalCenterOffset: 1
            anchors.verticalCenter: _gateway.verticalCenter
        }

        TextFieldStyled {
            id: _gateway
            x: 102
            width: 100
            height: 27
            text: MainStore.gateway
            validator: RegExpValidator {
                regExp:  /^((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){0,3}(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
           }
            onTextChanged: {
                AppActions.setGateway(_gateway.text)
            }
        }
    }
}
