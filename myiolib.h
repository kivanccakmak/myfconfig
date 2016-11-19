#ifndef MY_IO_LIB_H
#define MY_IO_LIB_H

#include <net/if.h>
#include <net/ethernet.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>

#include <netpacket/packet.h>
#include <arpa/inet.h>

#define MAX_STR_LEN 4096

#define MAC_STR "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx"
#define MAC_STR_ARGS(m) m[0], m[1], m[2], m[3], m[4], m[5]

#define ADD_SIOC_FLAG(flags, type, str, num_flags, flags_out) \
    do { \
        if (flags & type) { \
            flags_out += sprintf(flags_out, str); \
            *num_flags += 1; \
        } \
    } while(0); \

int has_interf(const char *ifname, struct ifreq *ifr_out, bool is_print);
int get_iface_mac(const char *ifname, char *mac_out);
int get_iface_flags(const char *ifname, char *flags_out, int *num_flags);
int get_iface_mtu(const char *ifname, int *mtu_out);
int get_iface_inet_addr(const char *ifname, char *addr_out);
int get_iface_bcast_addr(const char *ifname, char *addr_out);
int get_iface_netmask(const char *ifname, char *addr_out);

#endif
