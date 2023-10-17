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

#include "minitalk.h"

/**
 * @brief Counter for the number of bits received during a mini-talk session.
 */
static int	g_recieved = 0;

/**
 * @brief Ends the current mini-talk session, displaying the number of bits sent.
 *
 * @param info Information structure related to signals.
 */
void	ft_end_minitalk(siginfo_t *info)
{
	ft_printf("\n\x1b[34m[%i] sended %i bits\n", info->si_pid, g_recieved);
	ft_printf("------------------------------------\x1b[0m\n");
	g_recieved = 0;
}

/**
 * @brief Handles received signals, converting the signals to characters and
 *        outputting the resultant string.
 *
 * @param signo The received signal.
 * @param info Information structure related to signals.
 * @param context Unused parameter. It's present for compatibility with signal
 * handlers.
 */
void	ft_handler(int signo, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	rst = 0;

	if (g_recieved == 0)
		ft_printf("\x1b[35m[%i says]: \x1b[0m", info->si_pid);
	(void)context;
	g_recieved++;
	rst |= (signo == SIGUSR1);
	if (++i == 8)
	{
		if (rst == 0)
		{
			rst = 0;
			i = 0;
			ft_end_minitalk(info);
		}
		write(1, &rst, 1);
		rst = 0;
		i = 0;
	}
	else
		rst <<= 1;
}

/**
 * @brief Main function for the mini-talk server. It displays the server's
 * PID and waits for signals from clients to print out messages.
 *
 * @return int Returns 0 when the server exits.
 */
int	main(void)
{
	struct sigaction	s_sig;

	ft_printf("\x1b[32m[PID-server: %i]\x1b[0m\n", getpid());
	ft_printf("\x1B[38;2;176;174;174mIntructions:\n");
	ft_printf("Run: ./client [PID-server] \"message to send\"\x1b[0m\n");
	s_sig.sa_sigaction = ft_handler;
	s_sig.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sig.sa_mask);
	sigaddset(&s_sig.sa_mask, SIGUSR1);
	sigaddset(&s_sig.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &s_sig, NULL);
	sigaction(SIGUSR2, &s_sig, NULL);
	while (1)
		pause();
	return (0);
}
