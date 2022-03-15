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

#include "../inc/minitalk_bonus.h"

static char	*g_message = NULL;

void	ft_prepare_to_exit(void)
{
	if (g_message)
		free(g_message);
	exit(0);
}

void	ft_kill_errors(int pid, int signo)
{
	if (signo == 1)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			ft_printf("\x1b[31mKill function error (SIGUSR1).\x1b[0m\n");
			ft_prepare_to_exit();
		}
	}
	else if (signo == 2)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_printf("\x1b[31mKill function error (SIGUSR2).\x1b[0m\n");
			ft_prepare_to_exit();
		}
	}
}

void	ft_messenger(int pid)
{
	static int	i = 0;
	static int	pid_to = 0;
	static int	bytes = 8;

	if (pid_to == 0)
		pid_to = pid;
	if (bytes <= 0)
		bytes = 8;
	if (g_message[i])
	{
		if (bytes--)
		{
			if (g_message[i] >> bytes & 1)
				ft_kill_errors(pid_to, 1);
			else
				ft_kill_errors(pid_to, 2);
		}
		if (bytes == 0)
			i++;
	}
	else
	{
		if (bytes--)
			ft_kill_errors(pid_to, 2);
	}
}

void	ft_handler(int signo)
{
	if (signo == SIGUSR1)
	{
		usleep(20);
		ft_messenger(0);
	}
	else if (signo == SIGUSR2)
		ft_prepare_to_exit();
}

int	main(int argc, char *argv[])
{
	int	pid;

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
	signal(SIGUSR1, &ft_handler);
	signal(SIGUSR2, &ft_handler);
	g_message = ft_strdup(argv[2]);
	ft_messenger(pid);
	while (1)
	{
		pause();
	}
	return (0);
}
