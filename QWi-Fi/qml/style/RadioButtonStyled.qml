import QtQuick 2.6
  import QtQuick.Controls 2.0

  RadioButton {
      id: control
      text: qsTr("RadioButton")
      checked: true

      indicator: Rectangle {
          implicitWidth: 16
          implicitHeight: 16
          x: control.leftPadding
          y: parent.height / 2 - height / 2 -1
          radius: 13
          border.color: "#a0a0a0"

          Rectangle {
              width: 8
              height: 8
              x: 4
              y: 4
              radius: 7
              color: "#a0a0a0"
              visible: control.checked
          }
      }

      contentItem: Text {
          text: control.text
          font: control.font
          opacity: enabled ? 1.0 : 0.3
          color: "#404244"
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
          leftPadding: control.indicator.width + control.spacing -4
      }
  }
