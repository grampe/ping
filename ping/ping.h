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
int nsend; // send_to() count
pid_t pid; // pid
int sockfd;

int verbose;
int waittime;

int nrecv; // recieved count
int nwrecv; // recieved in wait time count
float ttotal; // total time
int twait; // wait time

bool stop;

void proc(char *, ssize_t, struct msghdr *, struct timeval *);
void send_to(void);
void readloop(void);

void sig_alrm(int);
void intHandler(int);
void tv_sub(struct timeval *, struct timeval *);

struct proto {
	struct sockaddr* sasend;
	struct sockaddr* sarecv;
	socklen_t salen;
	int icmp_proto;
} *pr;

#endif
