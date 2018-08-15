pragma Singleton
import QtQuick 2.6
import QuickFlux 1.1
import "./"

ActionCreator {

	signal setStarting(bool value)

    signal setRunning(bool value)


    signal setSSID(string value)

    signal setPassword(string value)

    signal setGateway(string value)

    signal setChannel(int value)

    signal setInIface(string value)

    signal setOutIface(string value)

    signal setDevicesCount(int value)

    signal setHidden(bool value)

    signal setIsolation(bool value)


    signal setMinimizeOnStart(bool value)

    signal setStoreCredentials(bool value)

    signal setLanguage(string value)

}

