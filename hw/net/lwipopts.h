#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#define NO_SYS	1
#define LWIP_SOCKET 0
#define LWIP_NETCONN 0


#define MEM_ALIGNMENT 4
#define MEM_SIZE 1024*30

#define TCP_SND_BUF 4000
#define TCP_MSS	1000

#define ETHARP_DEBUG LWIP_DBG_ON
#define ICMP_DEBUG LWIP_DBG_ON

#endif
