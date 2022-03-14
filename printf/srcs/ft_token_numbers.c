/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:15:45 by mporras-          #+#    #+#             */
/*   Updated: 2022/02/08 22:50:01 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_print_int(long int nbr, char sign)
{
	char	c;

	if (nbr < 0)
	{
		nbr = nbr * -1;
		sign = '-';
	}
	c = (nbr % 10) + '0';
	if (nbr >= 10)
		return (ft_print_int(nbr / 10, sign)
			+ write(1, &c, 1));
	else
	{
		if (sign == '-')
			return (write(1, &sign, 1) + write(1, &c, 1));
		else
			return (write(1, &c, 1));
	}
}

int	ft_process_numbers(va_list args, char token)
{
	int	rst;

	rst = 0;
	if (token == 'i' || token == 'd')
		rst += ft_print_int((long int)(va_arg(args, int)), 0);
	if (token == 'u')
		rst += ft_print_int((long int)
				(va_arg(args, unsigned int)), 0);
	return (rst);
}

static int	ft_print_hexa(unsigned long nbr, char *base, char token)
{
	unsigned long	base_num;

	base_num = 16;
	if (nbr >= base_num)
		return (ft_print_hexa(nbr / base_num, base, token)
			+ write(1, &base[nbr % base_num], 1));
	else
	{
		if (token == 'p')
			return (write(1, &base[16], 1)
				+ write(1, &base[17], 1)
				+ write(1, &base[nbr % base_num], 1));
		else
			return (write(1, &base[nbr % base_num], 1));
	}
}

static int	ft_print_hexa_cases(unsigned long nbr, char *base, char token)
{
	if (nbr == 0 && token != 'p')
		return (write(1, "0", 1));
	else
		return (ft_print_hexa(nbr, base, token));
}

int	ft_process_hexa(va_list args, char token)
{
	int	rst;

	rst = 0;
	if (token == 'p')
		rst += ft_print_hexa_cases(va_arg(args, unsigned long),
				"0123456789abcdef0x", token);
	else if (token == 'x')
		rst = ft_print_hexa_cases(va_arg(args, unsigned int),
				"0123456789abcdef0x", token);
	else if (token == 'X')
		rst = ft_print_hexa_cases(va_arg(args, unsigned int),
				"0123456789ABCDEF0X", token);
	return (rst);
}
