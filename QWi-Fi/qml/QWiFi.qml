import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import Qt.labs.platform 1.0
import QWiFi 1.0
import "components"

ApplicationWindow {
    property bool starting: false
    property bool running: false
    property int currentViewIndex: 0
    id: qwifiWindow
    visible: true
    color: "#fff"
    minimumHeight: 450
    maximumHeight: 450
    maximumWidth: 340
    minimumWidth: 340
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    font.family: "Roboto Thin"
    font.letterSpacing : 0.6
    font.weight: Font.Bold
    title: qsTr("QWi-Fi")

    function restoreWindow(){
        qwifiWindow.show()
        qwifiWindow.raise()
        qwifiWindow.requestActivate()
    }


    QWiFiApp {
        id: qwifiapp
        onWifiAPStarted: {
            running = true
            starting  = false
            currentViewIndex = 1
            console.log('started')
        }
        onWifiAPStopped: {
            running = false
            currentViewIndex = 0
            console.log('stopped')
        }
        onNewMessage:{
            starting = false
            messageBox.messageText = msg
        }

    }

    NetworkUtility {
        id: networkUtlity
    }

    FontLoader {
        id: qwififont
        source: "qrc:/resources/fonts/Roboto-Thin.ttf"
    }

    Timer {
        id: delayStartingTimer
        interval:800;
        onTriggered: {
            if(starting){
                currentViewIndex = 1
                messageBox.messageText = ""
            }
            console.info("starting:"+starting)
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
            id:manageView
            startButton.onClicked: {
                starting = true
                qwifiapp.startWiFiAP(inIface.currentText, outIface.currentText, ssid.text, password.text)
                delayStartingTimer.start()
            }
            inIface.model: networkUtlity.getAllInterfaces()
            outIface.model: networkUtlity.getWirelessInterfaces()
        }

        WifiDetailsView {
            id:detailView
            _running: running
            _ssid: manageView.ssid.text
            _password: manageView.password.text
            _interface: manageView.outIface.currentText
            stopButton.onClicked: qwifiapp.stopWiFiAP()
        }

        PreferenceView {}

    }

    SystemTrayIcon {
        id: systemTray
        visible: true
        tooltip: qsTr("QWi-Fi, The linux hotspot")
        iconSource: "qrc:/resources/images/wifi.svg"

        menu: Menu {

            MenuItem {
                text: qsTr("Stop Wi-Fi")
                enabled: running
                onTriggered: qwifiapp.stopWiFiAP()
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
                    if(running){
                        qwifiapp.stopWiFiAP()
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
            systemTray.showMessage(qsTr("QWi-Fi"),qsTr("The program will keep running in the "+
                                                       "system tray. To terminate the program, "+
                                                       "choose Quit in the context menu "))
        }else{
            Qt.quit()
        }
    }

}
