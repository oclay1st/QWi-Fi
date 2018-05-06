import QtQuick 2.6
import QtQuick.Controls 2.2
import "../style"

Item {
    property string _name: qsTr("Unknown")
    property string _mac: "00:00:00:00:00"
    property string _ip: "0.0.0.0"
    property string _downBytes: "0 Bytes"
    property string _downRateBytes: "0 Bytes/s"
    property string _upBytes: "0 Bytes"
    property string _upRateBytes: "0 Bytes/s"
    property string _manufacturer: qsTr("Unknown MAC identity")
    property int _connTime: 0

    Rectangle{
        TextStyled{
            visible: _name ? true:false
            text:_name
        }
        TextStyled{
            text:qsTr("MAC: ")+_mac
        }
        TextStyled{
            text:qsTr("Ip address: ") + _ip
        }
        TextStyled{
            text:qsTr("Recibing: ") + _downRateBytes
        }
        TextStyled{
            text:qsTr("Sending: ") + _upRateBytes
        }
    }
}
