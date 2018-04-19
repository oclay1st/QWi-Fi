import QtQuick 2.6
import QtQuick.Controls 2.2
import "../style"

Item {
    id: item1
    width: 340
    height: 440

    CheckBoxStyled {
        id: hiddenAP
        x: 24
        y: 63
        width: 264
        height: 38
        text: qsTr("Punto de acceso oculto")
        checked: false
    }

    CheckBoxStyled {
        id: isonlate
        x: 24
        y: 105
        text: qsTr("Desabilitar comunicación entre clientes")
        checked: false
    }

    Row {
        id: row
        x: 31
        y: 23
        width: 282
        height: 48

        Label {
            id: label1
            width: 122
            height: 18
            text: qsTr("Banda de frecuencia:")
            anchors.verticalCenter: parent.verticalCenter
        }

        RadioButtonStyled {
            id: frec2
            width: 87
            height: 40
            text: qsTr("2.4 GHz")
            anchors.verticalCenterOffset: -1
            anchors.verticalCenter: parent.verticalCenter
            checked: true
        }

        RadioButtonStyled {
            id: frec5
            width: 76
            height: 40
            text: qsTr("5 GHz")
            anchors.verticalCenterOffset: -1
            anchors.verticalCenter: parent.verticalCenter
            checked: false
        }
    }

    Row {
        id: row1
        x: 31
        y: 135
        width: 296
        height: 49

        Label {
            id: label
            width: 110
            height: 17
            text: qsTr("Número de canal:")
            verticalAlignment: Text.AlignTop
            anchors.verticalCenterOffset: 1
            anchors.verticalCenter: parent.verticalCenter
        }

        ComboBoxStyled {
            id: channel
            x: 100
            y: 10
            width: 59
            height: 28
            model: [1,2,3,4,5,6,7,8,9,10,11]
        }


    }

    Row {
        id: row2
        x: 31
        y: 191
        width: 243
        height: 35
        spacing: 8

        Label {
            id: label2
            width: 99
            height: 17
            text: qsTr("Puerta de enlace:")
            anchors.verticalCenterOffset: 1
            anchors.verticalCenter: ipAdress3.verticalCenter
        }

        TextFieldStyled {
            id: ipAdress3
            x: 102
            width: 100
            height: 27
            text:"192.168.12.1"
        }
    }
}
