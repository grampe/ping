//
//  main.c
//  ping
//
//  Created by Sema Belokovsky on 13.05.13.
//  Copyright (c) 2013 Sema Belokovsky. All rights reserved.
//


#include "ping.h"

int str2int(const char *str)
{
	int num = 0;
	int i;
	
	for (i = 0; i < strlen(str); i++) {
		if (48 <= str[i] <= 57) {
			num = num*10 + str[i]-48;
		} else
			break;
	}
	
	return num;
}

struct proto proto_icmp = {NULL, NULL, 0, IPPROTO_ICMP};

int main(int argc, const char * argv[])
{
	struct addrinfo *ai;
	char *h;
	int i;
	
	datalen = 56;
	stop = false;
	twait = 100;
	
	pid = getpid() & 0xffff;
	
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-v") == 0) {
			verbose = 1;
		} else if (strcmp(argv[i], "-w") == 0) {
			if (argc > i+1) {
				waittime = str2int(argv[i+1]);
				if (waittime) {
					twait = waittime;
				}
			}
		}
	}
	
	signal(SIGALRM, sig_alrm);
	signal(SIGINT, intHandler);
	
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
	
	printf("--- %s ping statistics---\n%d packets transmitted, %d packets received, %.1f%% packet loss\navr rtt %.2f",
		   ai->ai_canonname ? ai->ai_canonname : h,
		   nsend,
		   nrecv,
		   (float)(nsend-nrecv)/(nsend)*100,
		   ttotal/nrecv);
	if (waittime && (nrecv > nwrecv)) {
		printf(", %d packets out of wait time\n", (nrecv - nwrecv));
	} else {
		printf("\n");
	}
    return 0;
}

void intHandler(int signo)
{
	stop = true;
}
