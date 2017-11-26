#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "myiolib.h"

static void usage();

int main(int argc, char *argv[])
{
    int ret, num_flags = 0, mtu_size = 0, in_addr_len = 0;
    struct ifreq *ifr = (struct ifreq*) malloc(sizeof(struct ifreq));

    char mac[IFNAMSIZ] = {0};
    char flags[MAX_STR_LEN] = {0};
    char in_addr[MAX_STR_LEN] = {0};
    char bcast_addr[MAX_STR_LEN] = {0};
    char netmask[MAX_STR_LEN] = {0};
    
    if (argc == 1) {
        ret = has_interf("", ifr, true);
        printf("./myfconfig interface [to see interface info]\n");
        free(ifr);
        return -1;
    } else if (argc != 2) {
        usage();
        free(ifr);
        return -2;
    }

    ret = has_interf(argv[1], ifr, false);
    if (ret != 1) {
        printf("interface %s is not found\n", argv[1]);
        return 2;
    }

    ret = get_iface_mac(argv[1], mac);
    if (!ret)
        fprintf(stdout, "mac: " MAC_STR  "\n", MAC_STR_ARGS(mac));

    ret = get_iface_flags(argv[1], flags, &num_flags);
    if (!ret)
        printf("flags: %s\n", flags);

    ret = get_iface_mtu(argv[1], &mtu_size);
    if (!ret)
        printf("MTU: %d\n", mtu_size);

    ret = get_iface_inet_addr(argv[1], in_addr);
    if (!ret)
        printf("inet_addr: %s\n", in_addr);

    ret = get_iface_bcast_addr(argv[1], bcast_addr);
    if (!ret)
        printf("Bcast: %s\n", bcast_addr);

    ret = get_iface_netmask(argv[1], netmask);
    if (!ret)
        printf("Mask: %s\n", netmask);

    free(ifr);
    return 0;
}

static void usage()
{
    printf("./myconfig [to see interfaces]\n");
    printf("./myfconfig interf [to see interface info]\n");
    printf("\n");
    printf("ex: ./myfconfig eth0\n");
}
