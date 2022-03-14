/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:56:04 by mporras-          #+#    #+#             */
/*   Updated: 2022/02/08 22:48:33 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		rst;

	i = 0;
	rst = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			i++;
			rst += ft_input_to_tokens(&s[i], args, &i);
			continue ;
		}
		if (!s[i])
			break ;
		rst += write(1, &s[i], 1);
		i++;
	}
	va_end(args);
	return (rst);
}
