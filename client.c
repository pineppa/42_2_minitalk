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

void    handle_sigusr2(int client_pid)
{
    ft_printf("Message");
}

int main(int argc, char **argv)
{
    struct sigaction    sa;

    sa.sa_handler = &handle_sigusr2;
    if (argc != 3)
        return (0);
    ft_printf("PID: %i\nMessage:%s", argv[1], argv[2]); //Most probably it will need to be changed
    return (0);
}
