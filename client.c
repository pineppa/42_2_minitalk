/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:45:17 by jsala             #+#    #+#             */
/*   Updated: 2024/01/19 18:08:48 by jsala            ###   ########.fr       */
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
		usleep(250);
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
	if (argc != 3)
		return (0);
	send_message(ft_atoi(argv[1]), argv[2]);
	return (0);
}
