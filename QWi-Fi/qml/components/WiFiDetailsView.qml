import QtQuick 2.6
import QtQuick.Controls 2.2
import "../style"
import "../stores"

Item {
    id: root
    property alias stopButton: stopButton
    property alias clientsButton: clientsButton

    function startAnimations(){
        detailSecuence.start()
    }

    width: 340

    Image {
        id: backgroundDetail
        anchors.horizontalCenter: parent.horizontalCenter
        y:40
        source: "qrc:/resources/images/background_detail.png"
    }

    Image {
        id: wifiStatusImage
        anchors.horizontalCenter: parent.horizontalCenter
        y:160
        source: "qrc:/resources/images/network_running.png"
    }

    TextStyled{
        id: startingText
        anchors.top: wifiStatusImage.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 18
        font.italic: true
        text: qsTr("Staring Access Point ...")
    }


    Image {
        id: backgroundBottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        width: 340
        source: "qrc:/resources/images/background.png"
    }



    Rectangle{
        id: rectangle
        x: 0
        color: "transparent"
        width: 340
        height: 200
        y:151
        Column{
            id: column
            y: 30
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 5
            TextStyled {
                id:ssid
                opacity: 0
                text: "SSID: "+ MainStore.ssid
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
                //                u2022
                id:password
                opacity: 0
                text: qsTr("Password: %1").arg(MainStore.password)
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
                id:gateway
                opacity: 0
                text: qsTr("Gateway: %1").arg(MainStore.gateway)
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
                id:channel
                opacity: 0
                text: qsTr("Channel: %1").arg(MainStore.channel)
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
                id:interfaceId
                opacity: 0
                text: qsTr("Interface: %1").arg(MainStore.outIface)
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
                id:devicesCount
                opacity: 0
                text: qsTr("Devices: %1").arg(MainStore.devicesCount)
                anchors.horizontalCenter: parent.horizontalCenter;
            }
            TextStyled {
                id:clientComunication
                opacity: 0
                text: qsTr("Clients comunication: %1").arg(!MainStore.isolation ? qsTr("yes") : qsTr("no"))
                anchors.horizontalCenter: parent.horizontalCenter;
            }
        }

    }

    Button {
        id: stopButton
        x: 110
        y: 348
        width: 169
        height: 40
        font.pixelSize: 13
        text: qsTr("STOP")
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        topPadding: 5
    }


    Image {
        id: imageClients
        visible: false
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin:15
        anchors.rightMargin:15
        width: 13
        height: 18
        source: "qrc:/resources/images/clients.png"

        ToolTip {
            id: toolTip
            text: qsTr("Connected clients")
            parent: imageClients
            visible: clientsButton.containsMouse
        }

        MouseArea {
            id: clientsButton
            x: parent.x
            y:parent.y
            hoverEnabled: true
            anchors.fill: parent
        }
    }

    Text{
        visible: imageClients.visible
        anchors.bottom: imageClients.top
        anchors.left: imageClients.right
        anchors.bottomMargin: -4
        font.pixelSize: 10
        text: MainStore.devicesCount != 0 ? MainStore.devicesCount : ""
        color: "#fff"
    }

    SequentialAnimation {
        id:detailSecuence
        running: false
        NumberAnimation { target: startingText; property: "opacity";  to: 0; duration: 300 }
        NumberAnimation { target: wifiStatusImage; property: "y";  to: 75; duration: 800 }
        NumberAnimation { target: ssid; property: "opacity";  to:1; duration: 300  }
        NumberAnimation { target: password; property: "opacity";  to:1; duration: 300 }
        NumberAnimation { target: gateway; property: "opacity";  to:1; duration: 300 }
        NumberAnimation { target: channel; property: "opacity";  to:1; duration: 300 }
        NumberAnimation { target: interfaceId; property: "opacity";  to:1; duration: 300 }
        NumberAnimation { target: devicesCount; property: "opacity";  to:1; duration: 300 }
        NumberAnimation { target: clientComunication; property: "opacity";  to:1; duration: 300 }
        NumberAnimation { target: stopButton; property: "visible";  to:1; duration: 300 }
        NumberAnimation { target: imageClients; property: "visible";  to:1; duration: 300 }
    }

}

