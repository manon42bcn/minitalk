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
 * @brief Sends signals to a specified PID and handles any signal sending errors.
 *
 * @param pid Process ID to send signals.
 * @param signo Signal number (1 for SIGUSR1, 2 for SIGUSR2).
 */
void	ft_kill_errors(int pid, int signo)
{
	usleep(20);
	if (signo == 1)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			ft_printf("\x1b[31mKill function error (SIGUSR1).\x1b[0m\n");
			exit (0);
		}
	}
	else if (signo == 2)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_printf("\x1b[31mKill function error (SIGUSR2).\x1b[0m\n");
			exit (0);
		}
	}
}

/**
 * @brief Concludes the current mini-talk session, acknowledges the client,
 *        and displays the number of bits received.
 *
 * @param info Information structure related to signals.
 */
void	ft_end_minitalk(siginfo_t *info)
{
	ft_kill_errors(info->si_pid, 2);
	ft_printf("\n\x1b[34m[%i sended] %i bits\n", info->si_pid, g_recieved);
	ft_printf("\x1b[35m------------------------------------------\x1b[0m\n");
	g_recieved = 0;
}

/**
 * @brief Handles received signals, converting the signals to characters,
 *        acknowledges the client and displays the resultant message.
 *
 * @param signo The received signal.
 * @param info Information structure related to signals.
 * @param context Unused parameter. It's present for compatibility with
 * signal handlers.
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
		ft_putchar_fd(rst, 1);
		rst = 0;
		i = 0;
	}
	else
		rst <<= 1;
	ft_kill_errors(info->si_pid, 1);
}

/**
 * @brief Main function for the mini-talk server bonus segment. It displays the
 *        server's PID and awaits signals from clients to display messages,
 *        sending acknowledgment after each received byte.
 *
 * @return int Returns 0 when the server exits.
 */
int	main(void)
{
	struct sigaction	s_sig;

	ft_printf("\x1b[32m[PID-server: %i]\x1b[0m\n", getpid());
	ft_printf("\x1B[38;2;176;174;174mIntructions:\n");
	ft_printf("Run: ./client [PID-server] \"message to send\"\x1b[0m\n");
	ft_printf("\x1b[35m------------------------------------------\x1b[0m\n");
	s_sig.sa_sigaction = ft_handler;
	s_sig.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sig.sa_mask);
	sigaddset(&s_sig.sa_mask, SIGUSR1);
	sigaddset(&s_sig.sa_mask, SIGUSR2);
	while (1)
	{
		sigaction(SIGUSR1, &s_sig, 0);
		sigaction(SIGUSR2, &s_sig, 0);
		pause();
	}
	return (0);
}
