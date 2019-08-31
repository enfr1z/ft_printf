/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 18:28:09 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 15:15:59 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_str_move_right(char *str, char c)
{
	int		i;
	char	tmp;

	i = 1;
	while (i < PF_LDWITH - 1)
	{
		tmp = str[i];
		str[i] = str[0];
		str[0] = tmp;
		i++;
	}
	str[0] = c;
}

void	ft_pf_add_zero(char *s, int pow)
{
	int i;

	i = 0;
	while (s[i] != '*' && s[i] != '\0')
		i++;
	if (i < pow)
		while (pow - i)
		{
			ft_str_move_right(s, '0');
			i++;
		}
}

void	ft_pf_set_ld_val(t_pf *pf)
{
	if (pf->s_ld)
		pf->ld.val = (long double)va_arg(pf->vl, long double);
	else
		pf->ld.val = (long double)va_arg(pf->vl, double);
}

void	ft_pf_reverse_lda(t_pf *pf)
{
	int i_s;
	int i_e;

	i_s = 0;
	i_e = PF_LDWITH - 2;
	while (pf->lda[i_e] == '0' && i_e != 0)
	{
		pf->lda[i_e] = '\0';
		i_e--;
	}
	while (i_e > i_s)
	{
		ft_swap_char(&pf->lda[i_s], &pf->lda[i_e]);
		i_s++;
		i_e--;
	}
}
