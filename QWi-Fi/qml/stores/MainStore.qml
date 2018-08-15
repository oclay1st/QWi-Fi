pragma Singleton
import QtQuick 2.6
import QuickFlux 1.1
import "../actions"

Store {
    property bool isStarting: false
    property bool isRunning: false

    property string ssid : ""
    property string password : ""
    property string gateway : "192.168.12.1"
    property int channel : 1
    property string inIface : ""
    property string outIface : ""
    property bool hidden : false
    property bool isolation : false
    property int devicesCount : 0

    property bool minimizeOnStart: false
    property bool storeCredentials: false
    property string language: ""

    property bool canStartAp: inIface != "" && outIface != "" && ssid.trim() != ""
                              && password.trim() != "" && password.length >= 8

    bindSource: AppDispatcher

    Filter {
        type: ActionTypes.setRunning
        onDispatched: {
            isRunning = message.value
            if(isRunning){
                isStarting = false
            }
        }
    }
    Filter {
        type: ActionTypes.setStarting
        onDispatched: {
            isStarting = message.value
            if(isStarting){
                isRunning = false
            }
        }
    }

    Filter {
        type: ActionTypes.setSSID
        onDispatched: {
            ssid = message.value
        }
    }
    Filter {
        type: ActionTypes.setPassword
        onDispatched: {
            password = message.value
        }
    }
    Filter {
        type: ActionTypes.setGateway
        onDispatched: {
            gateway = message.value
        }
    }
    Filter {
        type: ActionTypes.setChannel
        onDispatched: {
            channel = message.value
        }
    }
    Filter {
        type: ActionTypes.setInIface
        onDispatched: {
            inIface = message.value
        }
    }
    Filter {
        type: ActionTypes.setOutIface
        onDispatched: {
            outIface = message.value
        }
    }
    Filter {
        type: ActionTypes.setDevicesCount
        onDispatched: {
            devicesCount = message.value
        }
    }
    Filter {
        type: ActionTypes.setHidden
        onDispatched: {
            hidden = message.value
        }
    }
    Filter {
        type: ActionTypes.setIsolation
        onDispatched: {
            isolation = message.value
        }
    }
    Filter {
        type: ActionTypes.setMinimizeOnStart
        onDispatched: {
            minimizeOnStart = message.value
        }
    }
    Filter {
        type: ActionTypes.setStoreCredentials
        onDispatched: {
            storeCredentials = message.value
        }
    }
    Filter {
        type: ActionTypes.setLanguage
        onDispatched: {
            language = message.value
        }
    }

}
