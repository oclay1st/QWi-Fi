import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../style"

Item {
    property alias startButton: startButton
    property alias inIface: inIface
    property alias outIface: outIface
    property alias ssid: ssid
    property alias password: password
    width: 340
    height: 440
    antialiasing: false
    transformOrigin: Item.Center

    Label {
        id: label2
        x: 39
        y: 17
        text: qsTr("Compartir desde:")
    }
    ComboBoxStyled {
        id: inIface
        x: 39
        y: 40
        width: 260
        height: 30
    }
    Label {
        id: label3
        x: 39
        y: 76
        text: qsTr("Compartir a:")
    }

    ComboBoxStyled {
        id: outIface
        x: 40
        y: 99
        width: 260
        height: 30
    }

    Label {
        id: label
        x: 40
        y: 153
        text: qsTr("SSID:")
    }

    TextFieldStyled {
        id: ssid
        x: 40
        y: 176
        width: 260
        height: 30
        selectByMouse:true
        leftPadding: 30
        placeholderText: qsTr("Nombre Ap")
    }

    Label {
        id: label1
        x: 42
        y: 213
        text: qsTr("Contraseña:")
    }

    TextFieldStyled {
        id: password
        x: 40
        y: 236
        width: 260
        height: 30
        rightPadding:40
        leftPadding: 30
        selectByMouse:true
        echoMode: "Password"
        placeholderText: qsTr("Contraseña")
    }
    Image {
        id: showPasswordImage
        x: 273
        y: 243
        width: 16
        height: 17
        source:"qrc:/resources/visibility.svg"
    }

    MouseArea {
        id: mouseAreaPassword
        x: 265
        y: 236
        width: 33
        height: 29
        hoverEnabled: true
        onClicked: {
            if(password.echoMode==2){
                password.echoMode = "Normal"
                showPasswordImage.source = "qrc:/resources/hint.svg"
            }else{
                password.echoMode = "Password"
                showPasswordImage.source = "qrc:/resources/visibility.svg"
            }
        }
    }

    Button {
        id: startButton
        x: 101
        y: 302
        width: 138
        height: 40
        font.pixelSize: 14
        text: qsTr("Inciar")
        enabled: inIface.currentText != "" && outIface.currentText != "" && ssid.text != "" && password.length >= 8
//                contentItem: Text {
//                    text: startButton.text
//                    font: startButton.font
//                    color: "#fff"
//                    horizontalAlignment: Text.AlignHCenter
//                    verticalAlignment: Text.AlignVCenter
//                    elide: Text.ElideRight
//                }
//                background: Rectangle {
//                    implicitWidth: 100
//                    implicitHeight: 40
//                    color:"red"
//                    radius: 2
//                }
    }

    Image {
        id: image
        x: 47
        y: 243
        width: 16
        height: 16
        source: "qrc:/resources/password.svg"
    }

    Image {
        id: image1
        x: 47
        y: 183
        width: 16
        height: 16
        source: "qrc:/resources/wifi.svg"
    }

}
