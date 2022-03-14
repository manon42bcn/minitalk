/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:01:48 by mporras-          #+#    #+#             */
/*   Updated: 2022/02/01 12:01:54 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

static int	ft_print_format_hexa(t_token *token, char *base, char num)
{
	int	rst;

	rst = 0;
	if (token->hash == 1)
		token->width = token->width - 2;
	if (token->point == 1 && token->precision > 0)
		token->width = token->width - token->precision;
	if (token->hash == 1 && token->width > 0 && token->fill_c == '0')
		rst += write(1, &base[16], 1) + write(1, &base[17], 1);
	rst += ft_width_fill(token, 0);
	if (token->hash == 1 && (token->left == 1 || token->width < 1))
		rst += write(1, &base[16], 1) + write(1, &base[17], 1);
	rst += ft_width_fill(token, 1);
	if (token->space == 1)
		rst += write(1, " ", 1);
	if (num != 0)
		rst += write(1, &num, 1);
	return (rst);
}

static int	ft_print_hexa(unsigned long nbr, char *base, t_token *token)
{
	unsigned long	base_num;

	token->width--;
	token->precision--;
	base_num = 16;
	if (nbr >= base_num)
		return (ft_print_hexa(nbr / base_num, base, token)
			+ write(1, &base[nbr % base_num], 1));
	else
		return (ft_print_format_hexa(token, base, base[nbr]));
}

static int	ft_print_hexa_cases(unsigned long nbr, char *base, t_token *token)
{
	if (token->token != 'p' && nbr == 0 && token->hash == 1)
		token->hash = 0;
	if (nbr == 0 && token->token != 'p' && token->point == 1)
		return (ft_print_format_hexa(token, base, 0));
	else
		return (ft_print_hexa(nbr, base, token));
}

int	ft_process_hexa(va_list args, t_token *token)
{
	int	rst;

	rst = 0;
	if (token->token == 'p')
		rst += ft_print_hexa_cases(va_arg(args, unsigned long),
				"0123456789abcdef0x", token);
	else if (token->token == 'x')
		rst = ft_print_hexa_cases(va_arg(args, unsigned int),
				"0123456789abcdef0x", token);
	else if (token->token == 'X')
		rst = ft_print_hexa_cases(va_arg(args, unsigned int),
				"0123456789ABCDEF0X", token);
	return (rst + ft_fill_left(token));
}
