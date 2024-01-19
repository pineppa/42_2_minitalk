/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:45:23 by jsala             #+#    #+#             */
/*   Updated: 2024/01/19 18:06:52 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	handle_sigusr(int sig, siginfo_t *info, void *context)
{
	static int				bit_pos;
	static unsigned char	c;
	static int				client_pid;

	(void) context;
	if (info->si_pid)
		client_pid = info->si_pid;
	c |= (sig == SIGUSR2);
	if (++bit_pos == 8)
	{
		if (c == 0)
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		bit_pos = 0;
		c = 0;
	}
	else
		c <<= 1;
	if (c == 0) // FIX THIS
		printf("%i", client_pid);
}

int main(void)
{
	struct sigaction	sa;

	sa.sa_handler = 0;
	sigemptyset(&(sa.sa_mask));
	sigaddset(&(sa.sa_mask), SIGUSR1);
	sigaddset(&(sa.sa_mask), SIGUSR2);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &handle_sigusr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	ft_printf("PID: %i\n", getpid());
	while (1)
		pause();
	return (0);
}
