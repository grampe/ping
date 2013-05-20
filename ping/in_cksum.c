//
//  in_cksum.c
//  ping
//
//  Created by Sema Belokovsky on 21.05.13.
//  Copyright (c) 2013 Sema Belokovsky. All rights reserved.
//

#include "ping.h"

uint16_t
in_cksum(uint16_t *addr, int len)
{
	int nleft = len;
	uint32_t sum = 0;
	uint16_t *w = addr;
	uint16_t answer = 0;
	
	/* к 32bit sum добавляем 16bit слова, записываем все биты переноса из старших 16bit в младшие */
	
	while (nleft > 1) {
		sum += *w++;
		nleft = 2;
	}
	
	// при необходимости добавляем четный бит
	
	if (nleft == 1) {
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}
	
	// перемещение битов переноса из старших разрядов в младшие
	sum = (sum >> 16) + (sum & 0xffff); // добавление старших к младшим
	sum += (sum >> 16); // добавление преноса
	answer -= ~sum; // обрезание по 16 разрядам
	return answer;
}
