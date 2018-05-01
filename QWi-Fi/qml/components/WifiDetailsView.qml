import QtQuick 2.6
import QtQuick.Controls 2.0
import "../style"

Item {
    id: root
    property string _ssid : ""
    property string _gateway : ""
    property string _password : ""
    property string _channel : ""
    property string _interface : ""
    property string _devicesCount : ""
    property string _hidden : ""
    property string _clientComunication : ""
    property bool _running: false
    property alias stopButton: stopButton
    width: 340
    height: 440

    SpriteSequence {
        id: sprite
        anchors.horizontalCenter: parent.horizontalCenter
        y:90
        height: 161
        width: 161
        visible: !_running
        running: !_running && root.visible
        interpolate: false
        Sprite {
            name: "bird"
            source: "qrc:/resources/images/network_status.png"
            frameCount: 4
            frameRate:2
            frameWidth: 161
            frameHeight: 161
            frameY: 20
        }

    }

    Image {
        visible: _running
        id:statusImage
        height: 161
        width: 161
        anchors.horizontalCenter:  parent.horizontalCenter
        y:90
        source:  "qrc:/resources/images/network_running.png"
    }
    //this can be done better
    Rectangle{        
        id: rectangle
        width: parent.width
        height: 200
        color: "transparent"
        y:110
        Column{
            id: column
            y: 30
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 5
            TextStyled {
                id:ssid
                opacity: 0
                text: "SSID: "+ _ssid
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
//                u2022
                id:password
                opacity: 0
                text: qsTr("Password: ") + _password
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
                id:gateway
                opacity: 0
                text: qsTr("Gateway: ") + _gateway
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
                id:channel
                opacity: 0
                text: qsTr("Channel: ") + _channel
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
                id:interfaceId
                opacity: 0
                text: qsTr("Interface: ") + _interface
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
                id:devicesCount
                opacity: 0
                text: qsTr("Devices: ") + _devicesCount
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
                id:clientComunication
                opacity: 0
                text: qsTr("Clients comunication: ") + _clientComunication
                anchors.horizontalCenter: parent.horizontalCenter;
            }
        }

    }

    Button {
        id: stopButton
        opacity: 0
        x: 110
        y: 300
        width: 120
        height: 34
        font.pixelSize: 13
        text: qsTr("Stop")
        topPadding: 5
        visible: _running
    }

    SequentialAnimation {
        id:secuence
        running: _running
        ParallelAnimation {
            NumberAnimation { target: statusImage; property: "y"; from:80; to: 5; duration: 800 }
            ScaleAnimator {
                target: statusImage
                from: 0.9
                to: 0.7
                duration: 800
            }
        }
        NumberAnimation { target: ssid; property: "opacity";  to:1; duration: 300  }
        NumberAnimation { target: password; property: "opacity";  to:1; duration: 300 }
        NumberAnimation { target: gateway; property: "opacity";  to:1; duration: 300 }
        NumberAnimation { target: channel; property: "opacity";  to:1; duration: 300 }
        NumberAnimation { target: interfaceId; property: "opacity";  to:1; duration: 300 }
        NumberAnimation { target: devicesCount; property: "opacity";  to:1; duration: 300 }
        NumberAnimation { target: clientComunication; property: "opacity";  to:1; duration: 300 }

        NumberAnimation { target: stopButton; property: "opacity";  to:1; duration: 300 }
    }


}

