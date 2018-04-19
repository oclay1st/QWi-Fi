import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.0
import Qt.labs.platform 1.0
import QWiFi 1.0
import "components"

ApplicationWindow {
    property bool starting: false
    property bool running: false
    property int currentViewIndex: 0
    id: qwifiWindow
    width: 340
    visible: true
    color: "#fff"
    minimumHeight: 450
    maximumHeight: 450
    maximumWidth: 340
    minimumWidth: 340
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    font.family: "Roboto Thin"
    font.letterSpacing : 0.5
    font.weight: Font.Bold
    title: qsTr("QWi-Fi")

    function restoreWindow(){
        qwifiWindow.show()
        qwifiWindow.raise()
        qwifiWindow.requestActivate()
    }


    QWiFiApp {
        id: qwifiapp
        onStarted: {
            running = true
            starting  = false
            console.log('started')
        }
        onStopped: {
            running = false
            currentViewIndex = 0
            restoreWindow()
            console.log('stopped')
        }
        onNewMessage:{
            starting = false
            messageBox.messageText = msg
        }
    }

    FontLoader {
        id: qwififont
        source: "qrc:/resources/Roboto-Thin.ttf"
    }

    Timer {
        id: delayStartingTimer
        interval:800;
        onTriggered: {
            if(starting){
                currentViewIndex = 1
                messageBox.messageText = ""
            }
        }
    }

    Timer {
        id: delayStoppingTimer
        interval: 800;
        onTriggered: {
            if(!running){
                Qt.quit()
            }
        }
    }


    header: Message {
        id:messageBox
    }

    SwipeView {
        id: swipeView
        interactive: false
        anchors.fill: parent
        currentIndex: currentViewIndex

        ManageView {
            startButton.onClicked: {
                starting = true
                qwifiapp.start(inIface.currentText, outIface.currentText, ssid.text, password.text)
                delayStartingTimer.start()
            }
            inIface.model: qwifiapp.getAllInterfaces()
            outIface.model: qwifiapp.getWirelessInterfaces()
        }

        WifiDetailsView {}
        PreferenceView {}

    }

    SystemTrayIcon {
        id: systemTray
        visible: true
        tooltip: qsTr("QWi-Fi, The linux hotspot")
        iconSource: "qrc:/resources/wifi.svg"

        menu: Menu {

            MenuItem {
                text: qsTr("Stop Wi-Fi")
                enabled: starting || running
                onTriggered: qwifiapp.stop()
            }

            MenuItem {
                id:restoreItem
                text: qsTr("Restore")
                enabled: !minimizeItem.enabled
                onTriggered: restoreWindow()
            }

            MenuItem {
                id: minimizeItem
                text: qsTr("Minimize")
                enabled: qwifiWindow.visibility == 2
                onTriggered: {
                    qwifiWindow.showMinimized()
                }
            }

            MenuItem {
                separator: true
            }

            MenuItem {
                text: qsTr("Exit")
                onTriggered: {
                    if(starting || running){
                        qwifiapp.stop()
                        delayStoppingTimer.start()
                    }else{
                        Qt.quit()
                    }
                }
            }

        }

        onActivated: {
            if(reason === 3 || reason === 2){
                if(qwifiWindow.visibility == 3 || qwifiWindow.visibility == 0){
                    qwifiWindow.show()
                    qwifiWindow.raise()
                    qwifiWindow.requestActivate()
                }else{
                    qwifiWindow.showMinimized()
                }
            }
        }
    }

    onClosing: {
        close.accepted = false
        if(starting || running){
            qwifiWindow.hide()
            systemTray.showMessage(qsTr("QWi-Fi"),qsTr("La aplicación continuara ejecutándose."+
                                                       " Si desea terminar presione Salir en el menu contextual."))
        }else{
            Qt.quit()
        }
    }

}
