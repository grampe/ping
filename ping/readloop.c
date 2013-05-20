//
//  readloop.c
//  ping
//
//  Created by Sema Belokovsky on 21.05.13.
//  Copyright (c) 2013 Sema Belokovsky. All rights reserved.
//

#include "ping.h"

void
readloop(void)
{
	int size;
	char recvbuf[BUFFSIZE];
	char controlbuf[BUFFSIZE];
	struct msghdr msg;
	struct iovec iov;
	ssize_t n;
	struct timeval tval;
	
	sockfd = socket(pr->sasend->sa_family, SOCK_RAW, pr->icmp_proto);
//	setuid(getuid());
	
	size = 60 * 1024;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)); // WTF?!
	
	sig_alrm(SIGALRM);
	
	iov.iov_base = recvbuf;
	iov.iov_len = sizeof(recvbuf);
	
	msg.msg_name = pr->sarecv;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = controlbuf;
	
	for ( ; ; ) {
		msg.msg_namelen = pr->salen;
		msg.msg_controllen = sizeof(controlbuf);
		n = recvmsg(sockfd, &msg, 0);
		
		if (n < 0) {
			if (errno == EINTR)
				continue;
			else
				err_sys("recvmsg");
		}
		
		gettimeofday(&tval, NULL);
		proc(recvbuf, n, &msg, &tval);
	}
}