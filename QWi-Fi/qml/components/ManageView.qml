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
        x: 30
        y: 19
        width: 125
        height: 17
        text: qsTr("Interface to share:")
    }
    ComboBoxStyled {
        id: inIface
        x: 30
        y: 40
        width: 280
        height: 30
    }
    Label {
        id: label3
        x: 30
        y: 79
        text: qsTr("Share with:")
    }

    ComboBoxStyled {
        id: outIface
        x: 30
        y: 99
        width: 280
        height: 30
    }

    Label {
        id: label
        x: 30
        y: 150
        text: qsTr("SSID:")
    }

    TextFieldStyled {
        id: ssid
        x: 30
        y: 171
        width: 280
        height: 30
        selectByMouse:true
        leftPadding: 30
        placeholderText: qsTr("Access point name")
    }

    Label {
        id: label1
        x: 30
        y: 210
        text: qsTr("Password:")
    }

    TextFieldStyled {
        id: password
        x: 30
        y: 231
        width: 280
        height: 30
        rightPadding:40
        leftPadding: 30
        selectByMouse:true
        echoMode: "Password"
        placeholderText: qsTr("Password")
    }
    Image {
        id: showPasswordImage
        x: 285
        y: 239
        width: 16
        height: 16
        source:"qrc:/resources/images/visibility.svg"
    }

    MouseArea {
        id: mouseAreaPassword
        x: 273
        y: 232
        width: 33
        height: 29
        hoverEnabled: true
        onClicked: {
            if(password.echoMode==2){
                password.echoMode = "Normal"
                showPasswordImage.source = "qrc:/resources/images/hint.svg"
            }else{
                password.echoMode = "Password"
                showPasswordImage.source = "qrc:/resources/images/visibility.svg"
            }
        }
    }

    Button {
        id: startButton
        x: 101
        y: 307
        width: 138
        height: 40
        font.pixelSize: 14
        text: qsTr("Start")
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
        x: 38
        y: 237
        width: 16
        height: 16
        source: "qrc:/resources/images/password.svg"
    }

    Image {
        id: image1
        x: 38
        y: 177
        width: 16
        height: 16
        source: "qrc:/resources/images/wifi.svg"
    }

}
