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

static int sended = 0;

void ft_confirm(int signo)
{
	static int confirmed = 0;

	confirmed++;
	if (signo == SIGUSR2)
	{
		ft_printf("bits sended %i - bits confirmed %i",sended, confirmed);
		if (sended == confirmed)
			ft_printf(" - \x1b[34mOK\x1b[0m\n");
		else
			ft_printf(" - \x1b[31mKO\x1b[0m\n");
		exit(0);
	}
}

int	ft_to_bin(int pid, char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		sended++;
		if (c >> i & 1) 
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		//pause();
		usleep(100);
	}
	return (1);
}

int ft_messenger(int pid, char *message)
{
	int	i;
	int rst;

	i = 0;
	rst = 0;
	while (message[i])
	{
		rst += ft_to_bin(pid, message[i]);
		i++;
	}
	ft_to_bin(pid, '\0');
	return (rst);
}

int main(int argc, char *argv[])
{
	int	to_send;

	if (argc == 1)
		return (0);
	to_send = ft_strlen(argv[2]);
	signal(SIGUSR1, &ft_confirm);
	signal(SIGUSR2, &ft_confirm);
	ft_messenger(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return 0;
}