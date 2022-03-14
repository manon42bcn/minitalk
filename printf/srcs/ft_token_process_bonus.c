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

#include "../includes/ft_printf_bonus.h"

int	ft_process_tokens(t_token *token, va_list args)
{
	int	rst;

	rst = 0;
	if (token->token == 'p' || token->token == 'x' || token->token == 'X')
		rst = ft_process_hexa(args, token);
	if (token->token == 'c' || token->token == 's' || token->token == '%')
		rst = ft_process_strings(args, token);
	if (token->token == 'd' || token->token == 'i' || token->token == 'u')
		rst = ft_process_numbers(args, token);
	return (rst);
}

void	ft_fix_flags_conditions(t_token	*token)
{
	if (token->fill_c == ' ' && token->width == 0)
		token->space = 1;
	if (token->fill_c == 0 || token->point == 1)
		token->fill_c = ' ';
	if (token->token == 'p')
		token->hash = 1;
	if ((token->token == 'x' || token->token == 'x') && token->fill_c == 0)
		token->fill_c = '0';
}

int	ft_get_token_sizes(const char *input, t_token *token)
{
	int	i;

	i = 0;
	while (input[0] == '.' && input[++i] && ft_isdigit(input[i]) == 1)
		token->precision = (token->precision * 10) + (input[i] - 48);
	while (ft_is_width_flag(input[0]) == 1 && input[++i]
		&& ft_isdigit(input[i]) == 1)
		token->width = (token->width * 10) + (input[i] - 48);
	while (input[i] && ft_isdigit(input[i]) == 1)
	{
		token->width = (token->width * 10) + (input[i] - 48);
		i++;
	}
	if (i > 0)
		i--;
	return (i);
}

int	ft_get_tokens(const char *input, t_token *token)
{
	int		k;

	k = 0;
	while (input[k] && ft_is_flag(input[k]) == 1)
	{
		if (input[k] == '-')
			token->left = 1;
		if (input[k] == '.')
			token->point = 1;
		if (input[k] == ' ' || input[k] == '0')
			token->fill_c = input[k];
		if (ft_flag_with_values(input[k]) == 1)
			k += ft_get_token_sizes(&input[k], token);
		if (input[k] == '#')
			token->hash = 1;
		if (input[k] == '+')
			token->sign = 1;
		k++;
	}
	if (ft_is_token(input[k]) == 1)
	{
		token->token = input[k];
		k++;
	}
	return (k);
}

int	ft_input_to_tokens(const char *input, va_list args, int *i)
{
	t_token	*token;
	int		k;
	int		rst;

	if (input[0] == '%')
	{
		*(i) = *(i) + 1;
		return (write(1, "%", 1));
	}
	token = ft_start_token();
	k = ft_get_tokens(input, token);
	ft_fix_flags_conditions(token);
	*(i) = *(i) + k;
	rst = ft_process_tokens(token, args);
	free(token);
	return (rst);
}
