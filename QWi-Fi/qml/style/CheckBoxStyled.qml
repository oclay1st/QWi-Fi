import QtQuick 2.6
import QtQuick.Controls 2.0

CheckBox {
      id: control
      checked: true

      indicator: Rectangle {
          implicitWidth: 16
          implicitHeight: 16
          x: control.leftPadding
          y: parent.height / 2 - height / 2 -1
          radius: 2
          border.color: control.down ? "#a0a0a0" : "#a0a0a0"

          Rectangle {
              width: 8
              height: 8
              x: 4
              y: 4
              radius: 2
              color: control.down ? "#e0e0e0" : "#e0e0e0"
              visible: control.checked
          }
      }

      contentItem: Text {
          text: control.text
          font: control.font
          opacity: enabled ? 1.0 : 0.3
          color: control.down ? "#404244" : "#404244"
          horizontalAlignment: Text.AlignLeft
          verticalAlignment: Text.AlignVCenter
          leftPadding : control.indicator.width + control.spacing
      }
  }
