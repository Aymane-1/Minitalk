/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:37:07 by aechafii          #+#    #+#             */
/*   Updated: 2022/06/02 21:58:52 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_signal(int pid, char ch)
{
	int	i;
	int	check;

	i = 7;
	while (i >= 0)
	{
		if ((ch >> i) & 1)
			check = kill(pid, SIGUSR1);
		else
			check = kill(pid, SIGUSR2);
		i--;
		usleep(800);
	}
	if (check != 0)
	{	
		ft_putstr("\033[0;31mINVALID PID!");
		exit (0);
	}
	else
		return (0);
}

int	is_alldigit(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			return (0);
	return (1);
}

void	message_confirmation(int signal)
{
	if (signal == SIGUSR1)
		ft_putstr("\033[0;32mMessage received!");
}

int	main(int argc, char **argv)
{
	int					i;
	int					server_pid;
	struct sigaction	strct;

	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		i = 0;
		if (argv[1][0] == '0' || (!is_alldigit(argv[1])))
		{	
			ft_putstr("\033[0;31mINVALID PID!");
			exit (0);
		}
		strct.__sigaction_u.__sa_handler = &message_confirmation;
		sigaction(SIGUSR1, &strct, NULL);
		while (argv[2][i])
			send_signal(server_pid, argv[2][i++]);
		send_signal(server_pid, argv[2][i]);
	}
	else
		ft_putstr("\033[0;31mInvalid parameters!");
}
