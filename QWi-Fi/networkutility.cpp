#include "networkutility.h"
#include <unistd.h>
#include <ifaddrs.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/wireless.h>

NetworkUtility::NetworkUtility(QObject *parent) : QObject(parent)
{

}

bool NetworkUtility::isWireless(const char* ifname, char* protocol) {
    int sock = -1;
    struct iwreq pwrq;
    memset(&pwrq, 0, sizeof(pwrq));
    strncpy(pwrq.ifr_name, ifname, IFNAMSIZ);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return false;
    }

    if (ioctl(sock, SIOCGIWNAME, &pwrq) != -1) {
        if (protocol) strncpy(protocol, pwrq.u.name, IFNAMSIZ);
        close(sock);
        return true;
    }

    close(sock);
    return false;
}

QStringList NetworkUtility::getWirelessInterfaces(){
    QStringList interfaces;
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
    }
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        char protocol[IFNAMSIZ]  = {0};
        if (ifa->ifa_addr == NULL ||
                ifa->ifa_addr->sa_family != AF_PACKET ||
                !!(ifa->ifa_flags & IFF_LOOPBACK)) continue;

        if (isWireless(ifa->ifa_name, protocol)) {
            interfaces << ifa->ifa_name;
        }
    }
    freeifaddrs(ifaddr);
    return interfaces;
}


QStringList NetworkUtility::getAllInterfaces(){
    QStringList interfaces;
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
    }
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL ||
                ifa->ifa_addr->sa_family != AF_PACKET ||
                !!(ifa->ifa_flags & IFF_LOOPBACK)) continue;

        interfaces << ifa->ifa_name;
    }

    freeifaddrs(ifaddr);
    return interfaces;

}
