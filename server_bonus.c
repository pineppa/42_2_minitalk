/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:45:23 by jsala             #+#    #+#             */
/*   Updated: 2024/02/12 09:11:01 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_sigusr_server(int sig, siginfo_t *info, void *context)
{
	static int				bit_pos;
	static unsigned char	c;
	static int				client_pid;

	(void) context;
	if (!info && !(info->si_pid))
		ft_handle_errors("Failed to retrieve the client PID\n");
	client_pid = info->si_pid;
	kill(client_pid, SIGUSR2);
	c |= (sig == SIGUSR2);
	if (++bit_pos == 8)
	{
		handle_char_print(client_pid, c);
		bit_pos = 0;
		c = 0;
	}
	else
		c <<= 1;
}

void	handle_char_print(int client_pid, char c)
{
	if (c == 0)
	{
		if ((write(1, "\n", 1) == -1) || (kill(client_pid, SIGUSR2) == -1))
		{
			kill(client_pid, SIGUSR1);
			ft_handle_errors("Failed to conclude the message\n");
		}
	}
	else
		if (write(1, &c, 1) == -1)
			ft_handle_errors("Failed to write the character\n");
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = 0;
	sigemptyset(&(sa.sa_mask));
	sigaddset(&(sa.sa_mask), SIGUSR1);
	sigaddset(&(sa.sa_mask), SIGUSR2);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &handle_sigusr_server;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_handle_errors("SIGUSR1 Signal assignment was faulty\n");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_handle_errors("SIGUSR2 Signal assignment was faulty\n");
	ft_printf("PID: %i\n", getpid());
	while (1)
		pause();
	return (0);
}
