/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:45:23 by jsala             #+#    #+#             */
/*   Updated: 2024/01/18 19:47:43 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_sigusr(int sig)
{
	static int	bit_pos = 0;
	static char	c;

	// Based on the signal received and on the current position, either add 1 or pass
	// Add 1 position to last_bit before doing anything, so that is possible to add info to last char
	//
	// Should this be filled left to right or right to left? Best left to right with atoi algo idea
	c |= (sig == SIGUSR2);
	// Assignment is done, we can move the bit_pos of a pos
	bit_pos++;
	// We don't know if the char is finished or in the middle. We keep track of this via last_bit;
	// This has added the 0 or 1 to the last bit. At each cycle / call we need to shift it left
	if (bit_pos == 8)
	{
		if (c == 0)
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		// Reset values;
		bit_pos = 0;
		c = 0;
	}
	else
		c <<= 1;
}

int main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				client_pid;

	client_pid = fork(); // Used to create an additional child process... But... is this needeD?
	if (client_pid == -1) //errno is set to indicate the error
		return (1);
	sa.sa_handler = &handle_sigusr1; //function to be called when the SIGUSR1 signal is trigger
	sigaction(SIGUSR1, &sa, NULL); // Bounds SIG to sa which has been handled
	sigaction(SIGUSR2, &sa, NULL);

	ft_printf("%i", getpid()); // Prints the current process id of the server process
	pause();
	return (0);
}
