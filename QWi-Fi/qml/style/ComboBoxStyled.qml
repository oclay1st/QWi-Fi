import QtQuick 2.6
import QtQuick.Controls 2.0

ComboBox {
    id: control
    x: 54
    y: 100
    width: 232
    height: 30

    indicator:Image{
            width:14;
            height:width;
            x: control.width - width - control.rightPadding + 3;
            y: control.topPadding + (control.availableHeight - height) / 2;
            source:"qrc:/resources/images/go-down.svg";
     }

    delegate: ItemDelegate {
        id:itemDlgt
        width: control.width
        height:34
        padding:34
        topPadding: 17
        leftPadding: 10

        contentItem: Text {
            id:textItem
            text: modelData
            color: "#000"
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter

        }

        background: Rectangle {
            color:itemDlgt.hovered?"#e3e3e3":"white" | (control.currentIndex === index)?"#eff0f1":"white";
            anchors.left: itemDlgt.left
            anchors.leftMargin: 0
            visible: !control.flat || control.down
        }
    }
}

