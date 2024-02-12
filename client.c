/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:45:17 by jsala             #+#    #+#             */
/*   Updated: 2024/02/12 10:58:12 by jsala            ###   ########.fr       */
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

int main(int argc, char **argv)
{
	int	pid_server;

	if (argc != 3)
		return (0);
	pid_server = ft_atoi(argv[1]);
	if (pid_server == -1)
		ft_handle_errors("Please insert a valid server PID value");
	send_message(pid_server, argv[2]);
	return (0);
}
