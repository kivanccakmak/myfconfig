# myfconfig

User Space application to gather network interface information.  

## compile

`make`

## run

`./myconfig` <to see available interfaces >   
`./myconfig eth0` <to see interface info>  

# related

`strace ifconfig` <where ioctl() funcs in this repository were collected>

[man netdevice](http://man7.org/linux/man-pages/man7/netdevice.7.html)  
[man ioctl](http://man7.org/linux/man-pages/man2/ioctl.2.html)  
[man strace](https://linux.die.net/man/1/strace)  
[man ifconfig](https://linux.die.net/man/8/ifconfig)
