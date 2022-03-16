/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_client_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:48:54 by mporras-          #+#    #+#             */
/*   Updated: 2022/03/12 18:48:58 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

int	ft_to_bin(int pid, char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		if (c >> i & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_printf("\x1b[31mKill function error (SIGUSR1).\x1b[0m\n");
				exit (0);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_printf("\x1b[31mKill function error (SIGUSR2).\x1b[0m\n");
				exit (0);
			}
		}
		usleep(200);
	}
	return (1);
}

int	ft_messenger(int pid, char *message)
{
	int	i;
	int	sended;

	i = 0;
	sended = 0;
	while (message[i])
	{
		sended += ft_to_bin(pid, message[i]);
		i++;
	}
	sended += ft_to_bin(pid, '\0');
	return (sended);
}

int	main(int argc, char *argv[])
{
	int	pid;
	int	sended;

	if (argc != 3)
	{
		ft_printf("\x1b[31mError\x1b[0m\n");
		ft_printf("\x1B[38;2;176;174;174mIntructions:\n");
		ft_printf("Run: ./client [PID-server] \"message to send\"\x1b[0m\n");
		return (0);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 1)
	{
		ft_printf("\x1b[31mPID Error\x1b[0m\n");
		return (0);
	}
	sended = ft_messenger(pid, argv[2]);
	ft_printf("\x1b[34mchars sended %i\x1b[0m\n", sended);
	return (0);
}
