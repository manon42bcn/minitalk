/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:59:56 by mporras-          #+#    #+#             */
/*   Updated: 2022/02/01 11:00:04 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft/libft.h"

typedef struct s_token
{
	int	token;
	int	fill_c;
	int	width;
	int	hash;
	int	sign;
	int	left;
	int	point;
	int	precision;
	int	space;

}	t_token;

int		ft_printf(const char *s, ...);
int		ft_process_tokens(t_token *token, va_list args);
void	ft_fix_flags_conditions(t_token	*token);
int		ft_get_token_sizes(const char *input, t_token *token);
int		ft_get_tokens(const char *input, t_token *token);
int		ft_input_to_tokens(const char *input, va_list args, int *i);
t_token	*ft_start_token(void);
void	ft_free_token(t_token *token);
int		ft_fill_left(t_token *token);
int		ft_is_token(int c);
int		ft_is_flag(int c);
int		ft_width_fill(t_token *token, int l_r);
int		ft_flag_with_values(int c);
int		ft_is_width_flag(int c);
int		ft_process_hexa(va_list arg, t_token *token);
int		ft_process_strings(va_list args, t_token *token);
int		ft_process_numbers(va_list args, t_token *token);

#endif
