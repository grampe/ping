//
//  main.c
//  ping
//
//  Created by Sema Belokovsky on 13.05.13.
//  Copyright (c) 2013 Sema Belokovsky. All rights reserved.
//


#include "ping.h"

struct proto proto_icmp = {NULL, NULL, 0, IPPROTO_ICMP};

int main(int argc, const char * argv[])
{
	struct addrinfo *ai;
	char *h;
	
	datalen = 56;
	
	pid = getpid() & 0xffff;
	
	signal(SIGALRM, sig_alrm);
	
	ai = Host_serv("google.com", NULL, 0, 0);
	h = Sock_ntop_host(ai->ai_addr, ai->ai_addrlen);
	
	printf("PING %s (%s): %d data bytes\n", ai->ai_canonname ? ai->ai_canonname : h, h, datalen);
	
	if (ai->ai_family == AF_INET) {
		pr = &proto_icmp;
	} else {
		err_quit("uknown adress family %d", ai->ai_family);
	}
	
	pr->sasend = ai->ai_addr;
	pr->sarecv = calloc(1, ai->ai_addrlen);
	pr->salen = ai->ai_addrlen;
	
	readloop();
	
    return 0;
}

