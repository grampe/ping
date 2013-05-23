//
//  utils.h
//  ping
//
//  Created by Sema Belokovsky on 21.05.13.
//  Copyright (c) 2013 Sema Belokovsky. All rights reserved.
//

#ifndef ping_utils_h
#define ping_utils_h

#include <errno.h>

#include <stdarg.h>		/* ANSI C header file */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <string.h>
#include <strings.h>

#include <syslog.h>		/* for syslog() */
#include <sys/signal.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <netdb.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include <arpa/inet.h>

// host_serv
struct addrinfo *
Host_serv(const char *host, const char *serv, int family, int socktype);

// error
void
err_quit(const char *fmt, ...);

void
err_sys(const char *fmt, ...);

//sock_ntop_host

char *
Sock_ntop_host(const struct sockaddr *sa, socklen_t salen);

// in_cksum

uint16_t
in_cksum(uint16_t *addr, uint16_t len);

#endif
