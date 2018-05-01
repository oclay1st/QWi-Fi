import QtQuick 2.0

ListView {
    id: root

    delegate: DeviceItemView {
        _name: name
        _mac: mac
        _ip: ip
        _downBytes: bytesReaded
        _upBytes: bytesWrited
        _downRateBytes: downloadRate
        _upRateBytes: uploadRate
        _manufacturer: manufacturer
        _connCount: connCount
        _connTime: connTime
    }

    populate: Transition {
        NumberAnimation {
            properties: "x,y"
            duration: 1000
        }
    }

    add: Transition {
        ParallelAnimation {
            NumberAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 1000
            }
        }
    }

    remove: Transition {
        ParallelAnimation {
            NumberAnimation {
                property: "opacity"
                to: 0
                duration: 1000
            }

            NumberAnimation {
                properties: "x,y"
                to: 100
                duration: 1000
            }
        }
    }

    removeDisplaced: Transition {
        NumberAnimation {
            properties: "x,y"
            duration: 1000
        }
    }
}
