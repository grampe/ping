//
//  in_cksum.c
//  ping
//
//  Created by Sema Belokovsky on 21.05.13.
//  Copyright (c) 2013 Sema Belokovsky. All rights reserved.
//

#include "ping.h"

uint16_t
in_cksum(uint16_t *addr, uint16_t len)
{
	unsigned long cksum = 0;
    while (len > 1)
    {
        cksum+=*addr++;
        len -= sizeof(uint16_t);
    }
    if (len)
    {
		cksum += *(unsigned char*)addr;
    }
    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >>16);
    return (uint16_t)(~cksum);
}
