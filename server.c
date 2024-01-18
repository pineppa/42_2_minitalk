/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:45:23 by jsala             #+#    #+#             */
/*   Updated: 2024/01/18 17:47:47 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    print_pid(pid_t client_pid) //PID as entry
{
	ft_print("%i", client_pid);
}

void	handle_sigusr1(int sig)
{
	
}

int main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				client_pid;

	client_pid = fork();
	if (client_pid == -1) //errno is set to indicate the error
		return (1);
	sa.sa_handler = &handle_sigusr1; //function to be called when the SIGUSR1 signal is trigger
	sigaction(SIGUSR1, &sa, NULL);
	
	return (0);
}
