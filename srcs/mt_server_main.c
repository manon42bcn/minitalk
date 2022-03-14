/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_server_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:10:44 by mporras-          #+#    #+#             */
/*   Updated: 2022/03/12 18:10:49 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static int recieved = 0;

void	ft_end_minitalk(siginfo_t *info)
{
	kill(info->si_pid, SIGUSR2);
	ft_printf("\n\x1b[34m[%i] has sended %i bits\n", info->si_pid, recieved);
	ft_printf("------------------------------------\x1b[0m\n");
	recieved = 0;
}

void 	ft_handler(int signo, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	rst = 0;

if (recieved == 0)
		ft_printf("\x1b[35m[%i says]: \x1b[0m", info->si_pid);
	(void)context;
	recieved++;
	rst |= (signo == SIGUSR1);
	//kill(info->si_pid, SIGUSR1);
	if (++i == 8)
	{
		if (rst == 0)
		{
			rst = 0;
			i = 0;
			ft_end_minitalk(info);
		}
		ft_putchar_fd(rst, 1);
		//write(1, &rst, 1);
		rst = 0;
		i = 0;
	}
	else
		rst <<= 1;
	//kill(info->si_pid, SIGUSR1);
}

int main(void)
{
	struct sigaction s_sig;

	ft_printf("\x1b[32m[PID-server: %i]\x1b[0m\n", getpid());
	ft_printf("\x1B[38;2;176;174;174mIntructions:\n");
	ft_printf("Run: ./client [PID-server] \"message to send\"\x1b[0m\n");
	s_sig.sa_sigaction = ft_handler;
	s_sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sig, 0);
	sigaction(SIGUSR2, &s_sig, 0);
	while (1)
		pause();
	return (0);
}
