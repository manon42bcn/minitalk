/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 01:55:20 by mporras-          #+#    #+#             */
/*   Updated: 2022/02/05 01:55:25 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_is_token(int c)
{
	return (c == 'c' || c == 's' || c == 'i'
		|| c == 'p' || c == 'x' || c == 'X'
		|| c == 'd' || c == 'u' || c == '%');
}

static int	ft_process_tokens(char token, va_list args)
{
	int	rst;

	rst = 0;
	if (token == 'p' || token == 'x' || token == 'X')
		rst = ft_process_hexa(args, token);
	if (token == 'c' || token == 's' || token == '%')
		rst = ft_process_strings(args, token);
	if (token == 'd' || token == 'i' || token == 'u')
		rst = ft_process_numbers(args, token);
	return (rst);
}

int	ft_input_to_tokens(const char *input, va_list args, int *i)
{
	int		rst;

	if (ft_is_token(input[0]) == 1)
	{
		*(i) = *(i) + 1;
		rst = ft_process_tokens(input[0], args);
	}
	else
		rst = 0;
	return (rst);
}
