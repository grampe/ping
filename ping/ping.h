//
//  ping.h
//  ping
//
//  Created by Sema Belokovsky on 13.05.13.
//  Copyright (c) 2013 Sema Belokovsky. All rights reserved.
//

#ifndef ping_ping_h
#define ping_ping_h

#include "utils.h"

#define BUFFSIZE 1500

char sendbuf[BUFFSIZE];

int datalen; // size of data after ICMP header
char *host;
int nsend; // sendto() count
pid_t pid; // pid
int sockfd;
int verbose;

void proc(char *, ssize_t, struct msghdr *, struct timeval *);
void send_to(void);
void readloop(void);

void sig_alrm(int);
void tv_sub(struct timeval *, struct timeval *);

struct proto {
	struct sockaddr* sasend;
	struct sockaddr* sarecv;
	socklen_t salen;
	int icmp_proto;
} *pr;

#endif
