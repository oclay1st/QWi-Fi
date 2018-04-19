import QtQuick 2.6
import QtQuick.Controls 2.2

Item{
    property string messageText
    width: parent.width
    height: 40
    Popup {
        id: rectSection
        width: parent.width - 10
        x:5; y:5;
        opacity: 0.4
        visible: true

        background: Rectangle{
            radius: 0
        }

        Text {
            text:messageText
        }


    }
}
