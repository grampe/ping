//
//  send_to.c
//  ping
//
//  Created by Sema Belokovsky on 21.05.13.
//  Copyright (c) 2013 Sema Belokovsky. All rights reserved.
//

#include "ping.h"

void
send_to(void)
{
	uint16_t len;
	struct icmp *icmp;
	
	icmp = (struct icmp *)sendbuf;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_id = pid;
	icmp->icmp_seq = nsend++;
	memset(icmp->icmp_data, 0x00, datalen);
	gettimeofday((struct timeval *)icmp->icmp_data, NULL);
	len = 8 + datalen;
	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = in_cksum((u_short *)icmp, len);
	sendto(sockfd, sendbuf, len, 0, pr->sasend, pr->salen);
}