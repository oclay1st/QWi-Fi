import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id: container
    property string headerTitle: ""

    Image {
        id: backIcon
        source:"qrc:/resources/images/back_icon.png";
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 15
        anchors.leftMargin: 15

        MouseArea {
            anchors.fill: parent
            onClicked: container.parent.back();
        }
    }

    Text {
        id: headerText
        anchors.left: backIcon.right
        anchors.top: parent.top
        anchors.leftMargin: 7
        anchors.topMargin: 20
        font.pixelSize: 20
        color:"#888888"
        text: headerTitle
    }
}
