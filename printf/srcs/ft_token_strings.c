/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 23:50:12 by mporras-          #+#    #+#             */
/*   Updated: 2022/02/08 22:51:14 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_print_strings(char *str)
{
	int		len;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	return (write(1, str, len));
}

static int	ft_print_chars(int c)
{
	return (write(1, &c, 1));
}

int	ft_process_strings(va_list args, char token)
{
	int	rst;

	if (token == 'c')
		rst = ft_print_chars((unsigned char)(va_arg(args, int)));
	if (token == '%')
		rst = ft_print_chars('%');
	if (token == 's')
		rst = ft_print_strings(va_arg(args, char *));
	return (rst);
}
