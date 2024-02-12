/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:45:17 by jsala             #+#    #+#             */
/*   Updated: 2024/02/12 10:58:40 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_byte(int server_pid, char c)
{
	char	temp_char;
	int	i;

	i = 8;
	while (i-- > 0)
	{
		temp_char = c >> i;
		if (temp_char % 2)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(50);
	}
}

void	send_message(int server_pid, char *str)
{
	while (*str)
	{
		send_byte(server_pid, *str);
		str++;
	}
	send_byte(server_pid, '\0');
}

void	handle_sigusr_client(int sig, siginfo_t *info, void *context)
{
	(void) context;
	(void) info;
	if (sig == SIGUSR1)
		write(1, "A fault has occured :(\n", 23);
	else if (sig == SIGUSR2)
		write(1, "Message received!\n", 18);
}

int main(int argc, char **argv)
{
	struct sigaction	sa_response;
	int					server_pid;

	if (argc != 3)
		ft_handle_errors("Wrong call. Use: './client < Server Process ID > < Message >'\n");
	server_pid = ft_atoi(argv[1]);
	if (!server_pid)
		ft_handle_errors("Wrong server PID\n");
	sa_response.sa_handler = 0;
	sigemptyset(&(sa_response.sa_mask));
	sigaddset(&(sa_response.sa_mask), SIGUSR1);
	sigaddset(&(sa_response.sa_mask), SIGUSR2);
	sa_response.sa_flags = SA_RESTART | SA_SIGINFO;
	sa_response.sa_sigaction = &handle_sigusr_client;
	if (sigaction(SIGUSR1, &sa_response, NULL) == -1)
		ft_handle_errors("SIGUSR1 Signal assignment was faulty\n");
	if (sigaction(SIGUSR2, &sa_response, NULL) == -1)
		ft_handle_errors("SIGUSR2 Signal assignment was faulty\n");
	send_message(server_pid, argv[2]);
	return (0);
}
