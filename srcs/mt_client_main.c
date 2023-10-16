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

/**
 * @brief Converts a character to its binary representation and sends it to the
 *        given PID using signals.
 *
 * @param pid Process ID to send signals.
 * @param c Character to convert and send.
 * @return int Returns 1 if the character is successfully sent.
 */
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
				printf("\x1b[31mKill function error (SIGUSR1).\x1b[0m\n");
				exit (0);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				printf("\x1b[31mKill function error (SIGUSR2).\x1b[0m\n");
				exit (0);
			}
		}
		usleep(500);
	}
	return (1);
}

/**
 * @brief Sends a string message to the specified PID by converting each
 *        character to binary and signaling the conversion.
 *
 * @param pid Process ID to send the message to.
 * @param message Message string to send.
 * @return int Returns the number of characters successfully sent.
 */
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

/**
 * @brief Main function for the mini-talk client. It takes a PID and a message
 *        as arguments, sends the message to the PID using signals, and outputs
 *        the result.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return int Returns 0 if the message is successfully sent or if there's an
 * error 1.
 */
int	main(int argc, char *argv[])
{
	int	pid;
	int	sended;

	if (argc != 3)
	{
		printf("\x1b[31mError\x1b[0m\n");
		printf("\x1B[38;2;176;174;174mIntructions:\n");
		printf("Run: ./client [PID-server] \"message to send\"\x1b[0m\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 1)
	{
		printf("\x1b[31mPID Error\x1b[0m\n");
		return (1);
	}
	sended = ft_messenger(pid, argv[2]);
	printf("\x1b[34mchars sended %i\x1b[0m\n", sended);
	return (0);
}
