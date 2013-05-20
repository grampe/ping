//
//  sig_alrm.c
//  ping
//
//  Created by Sema Belokovsky on 21.05.13.
//  Copyright (c) 2013 Sema Belokovsky. All rights reserved.
//

#include "ping.h"

void
sig_alrm(int signo)
{
	send_to();
	
	alarm(1);
	return;
}