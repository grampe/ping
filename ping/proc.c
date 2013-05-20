//
//  proc.c
//  ping
//
//  Created by Sema Belokovsky on 21.05.13.
//  Copyright (c) 2013 Sema Belokovsky. All rights reserved.
//

#include "ping.h"

void
proc(char *ptr, ssize_t len, struct msghdr *msg, struct timeval *tvrecv)
{
	int hlenl, icmplen;
	double rtt;
	struct ip *ip;
	struct icmp *icmp;
	struct timeval *tvsend;
	
	ip = (struct ip *)ptr; // начало IP-заголовка
	hlenl = ip->ip_hl << 2; // длина IP-заголовка
	if (ip->ip_p != IPPROTO_ICMP)
		return; // не ICMP
	
	icmp = (struct icmp *)(ptr + hlenl); // начало ICMP-заголовка
	
	if ((icmplen = (int)len - hlenl) < 8)
		return; // плохой пакет
	
	if (icmp->icmp_type == ICMP_ECHOREPLY) {
		if (icmp->icmp_id != pid)
			return; // это не ответ на наш ECHO_REQUEST
		if (icmplen < 16)
			return; // недостаточно данных
		
		tvsend = (struct timeval *)icmp->icmp_data;
		tv_sub(tvrecv, tvsend);
		rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec * 1000.0;
		
		printf("%d bytes from %s: seq=%u, ttl=%d, rtt=%.3f ms\n",
			   icmplen,
			   Sock_ntop_host(pr->sarecv, pr->salen),
			   icmp->icmp_seq,
			   ip->ip_ttl,
			   rtt);
	
	} else if (verbose) {
		printf(" %d bytes from %s: type = %d, code = %d\n",
			   icmplen,
			   Sock_ntop_host(pr->sarecv, pr->salen),
			   icmp->icmp_type,
			   icmp->icmp_code);
	}
}