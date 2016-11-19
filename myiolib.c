#include "myiolib.h"

/**
 * @brief 
 *
 * @param[in] ifname
 * @param[out] addr_out
 *
 * @return 0 succ
 *        -1 socket error
 *        -2 ioctl error
 *        -3 fail to find
 */
int get_iface_inet_addr(const char *ifname, char *addr_out)
{
    int ret, sock;
    struct ifreq ifr;
    char sa_data[14];
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);

    ret = ioctl(sock, SIOCGIFADDR, &ifr);
    if (ret < 0) {
        perror("ioctl");
        return -2;
    }

    if (ifr.ifr_addr.sa_family == AF_INET) {
        struct sockaddr_in *val = (struct sockaddr_in*) &(ifr.ifr_addr);
        inet_ntop(AF_INET, (void *) &val->sin_addr, addr_out, INET_ADDRSTRLEN);
        return 0;
    } else if (ifr.ifr_addr.sa_family = AF_INET6) {
        struct sockaddr_in6 *val = (struct sockaddr_in6*) &(ifr.ifr_addr);
        inet_ntop(AF_INET6, (void *) &val->sin6_addr, addr_out, INET6_ADDRSTRLEN);
        return 0;
    }

    return -3;
}


/**
 * @brief get netmastk.
 *
 * @param[in] ifname
 * @param[out] addr_out
 *
 * @return 0 succ
 *        -1 socket fail
 *        -2 ioctl fail
 */
int get_iface_netmask(const char *ifname, char *addr_out)
{
    int ret, sock;
    struct ifreq ifr;
    char sa_data[14];
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);

    ret = ioctl(sock, SIOCGIFNETMASK, &ifr);
    if (ret < 0) {
        perror("ioctl");
        return -2;
    }

    if (ifr.ifr_addr.sa_family == AF_INET) {
        struct sockaddr_in *val = (struct sockaddr_in*) &(ifr.ifr_addr);
        inet_ntop(AF_INET, (void *) &val->sin_addr, addr_out, INET_ADDRSTRLEN);
        return 0;
    } else if (ifr.ifr_addr.sa_family = AF_INET6) {
        struct sockaddr_in6 *val = (struct sockaddr_in6*) &(ifr.ifr_addr);
        inet_ntop(AF_INET6, (void *) &val->sin6_addr, addr_out, INET6_ADDRSTRLEN);
        return 0;
    }
    return -3;
}


/**
 * @brief get broadcast addr
 *
 * @param[in] ifname
 * @param[out] addr_out
 *
 * @return 0 succ
 *        -1 socket fail
 *        -2 ioctl fail
 *        -3 fail to find
 */
int get_iface_bcast_addr(const char *ifname, char *addr_out)
{
    int ret, sock;
    struct ifreq ifr;
    char sa_data[14];
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);

    ret = ioctl(sock, SIOCGIFBRDADDR, &ifr);
    if (ret < 0) {
        perror("ioctl");
        return -2;
    }

    if (ifr.ifr_addr.sa_family == AF_INET) {
        struct sockaddr_in *val = (struct sockaddr_in*) &(ifr.ifr_addr);
        inet_ntop(AF_INET, (void *) &val->sin_addr, addr_out, INET_ADDRSTRLEN);
        return 0;
    } else if (ifr.ifr_addr.sa_family = AF_INET6) {
        struct sockaddr_in6 *val = (struct sockaddr_in6*) &(ifr.ifr_addr);
        inet_ntop(AF_INET6, (void *) &val->sin6_addr, addr_out, INET6_ADDRSTRLEN);
        return 0;
    }
    return -3;
}

/**
 * @brief get maximum transmission unit.
 *
 * @param[in] ifname
 * @param[out] mtu_out
 *
 * @return 0 in succ
 *        -1 socket error
 *        -2 ioctl error
 */
int get_iface_mtu(const char *ifname, int *mtu_out)
{
    int ret, sock;
    struct ifreq ifr;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);

    ret = ioctl(sock, SIOCGIFMTU, &ifr);
    if (ret < 0) {
        perror("ioctl");
        return -2;
    }

    *mtu_out = ifr.ifr_mtu;
    return 0;
}

/**
 * @brief get active flag words of device.
 *
 * @param[in] ifname
 * @param[out] flags_out
 * @param[out] num_flags
 *
 * @return -1 socket fail
 *         -2 ioctl fail
 *          0 succ
 *
 */
int get_iface_flags(const char *ifname,
        char *flags_out, int *num_flags)
{
    int ret, sock;
    struct ifreq ifr;
    short flags;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);

    ret = ioctl(sock, SIOCGIFFLAGS, &ifr);
    if (ret < 0) {
        perror("ioctl");
        return -1;
    }

    flags = ifr.ifr_flags;

    ADD_SIOC_FLAG(flags, IFF_UP, "[IFF_UP]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_BROADCAST, "[IFF_BROADCAST]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_DEBUG, "[IFF_DEBUG]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_LOOPBACK, "[IFF_LOOPBACK]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_POINTOPOINT, "[IFF_POINTTOPOINT]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_RUNNING, "[IFF_RUNNING]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_NOARP, "[IFF_NOARP]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_PROMISC, "[IFF_PROMISC]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_NOTRAILERS, "[IFF_NOTRAILERS]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_ALLMULTI, "[IFF_ALLMULTI]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_MASTER, "[IFF_MASTER]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_SLAVE, "[IFF_SLAVE]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_MULTICAST, "[IFF_MULTICAST]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_PORTSEL, "[IFF_PORTSEL]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_AUTOMEDIA, "[IFF_AUTOMEDIA]", num_flags, flags_out);
    ADD_SIOC_FLAG(flags, IFF_DYNAMIC, "[IFF_DYNAMIC]", num_flags, flags_out);
}

/**
 * @brief whether ifname available.
 *
 * @param[in] ifname
 * @param[out] ifr_out
 * @param[in] is_print
 *
 * @return  1 succ
 *         -1 fail in socket
 *         -2 fail to ioctl
 *         -3 fail to find iface name
 *
 */
int has_interf(const char *ifname, struct ifreq *ifr_out, bool is_print)
{
    int i, num_ifaces, ret, sock;
    bool has_interf = false;
    char mac_out[ETH_ALEN] = {0};
    struct ifconf conf;
    struct ifreq req[10];
    struct ifreq *ifr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    conf.ifc_len = sizeof(req);
    conf.ifc_buf = (__caddr_t) req;
    ret = ioctl(sock, SIOCGIFCONF, &conf);
    if (ret < 0) {
        perror("ioctl");
        return -2;
    }

    num_ifaces = conf.ifc_len/sizeof(struct ifreq);
    for (i = 0; i < num_ifaces; i++) {
        ifr = &conf.ifc_req[i];
        if (is_print) {
            printf("%d - %s\n", i, ifr->ifr_name);
        }
        if (strcmp(ifname, ifr->ifr_name) == 0) {
            memcpy(ifr_out, ifr, sizeof(struct ifreq));
            has_interf = true;
        }
    }

    if (has_interf) {
        return 1;
    }

    return -3;
}

/**
 * @brief get mac address of interface.
 *
 * @param[in] ifname
 * @param[out] mac_out
 *
 * @return 0 succ
 *        -1 socket error
 *        -2 ioctl error
 */
int get_iface_mac(const char *ifname, char *mac_out)
{
    struct ifreq ifr;
    int ret, sock;

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket error");
        return -1;
    }

    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);

    ret = ioctl(sock, SIOCGIFHWADDR, &ifr);
    close(sock);

    if (ret < 0) {
        perror("ioctl error");
        return -2;
    }

    memcpy(mac_out, ifr.ifr_hwaddr.sa_data, ETH_ALEN);
    return ret;
}
