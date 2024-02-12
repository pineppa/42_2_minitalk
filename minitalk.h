/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:46:00 by jsala             #+#    #+#             */
/*   Updated: 2024/02/12 09:05:53 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <sys/types.h>

int		ft_putchar(int c);
int		ft_putstr(char *s);
int		ft_atoi(const char *str);
int		ft_putnbr(int nb);
int		ft_putunbr(int n);
size_t	ft_strlen(const char *s);
int		ft_puthex(unsigned int nbr, char x);
int		ft_putlonghex(unsigned long int nbr, char x);
int		ft_putpointer(void *p);
int		ft_printf(const char *str, ...);
void	send_byte(int server_pid, char c);
void	send_message(int server_pid, char *str);
void	ft_handle_errors(char *err_msg);
void	handle_char_print(int client_pid, char c);

#endif

