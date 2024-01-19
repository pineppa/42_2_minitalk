/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:45:17 by jsala             #+#    #+#             */
/*   Updated: 2024/01/18 18:02:06 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_byte(int server_pid, unsigned char c)
{
	unsigned char	temp_char;
	int		i;

	i = 8; //This later on will conflict with the idea of UNICODES in int
	// Pass a message that can either be a classical char or a UNICODE
	// Structure -> Kill is used to send a signal to a process kill(pid, signal)
	while (--i > 0)
	{
		temp_char = c >> i;
		if (temp_char % 2 != 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(50); // To be tuned based on the computer architecture
	}
}

void	send_message(int server_pid, char *str)
{
	// Transform the message into its bit version instead of this
	while (*str)
	{
		send_byte(server_pid, *str);
		str++;
	}
	// When done it should send a termination signal
	send_byte(server_pid, '\0');
}

int main(int argc, char **argv)
{
	int	server_pid;
	char	*msg;

	if (argc != 3)
		return (0);
	server_pid = argv[1];
	msg = argv[2];
	struct sigaction    sa = { 0 };
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_sigusr2;
   
	return (0);
}
