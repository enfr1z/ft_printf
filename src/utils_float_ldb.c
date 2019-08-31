/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_float_ldb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 18:27:46 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 15:15:35 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_pf_plus_to_s_a(char *s_a, char *s_b)
{
	int i;
	int rem;
	int cur_sum;

	i = PF_LDWITH - 2;
	rem = 0;
	while (i >= 0)
	{
		cur_sum = (ft_isdigit(s_a[i]) ? s_a[i] - '0' : 0)
		+ (ft_isdigit(s_b[i]) ? s_b[i] - '0' : 0) + rem;
		if (cur_sum < 10 && cur_sum != 0)
			s_a[i] = cur_sum + '0';
		else if (cur_sum != 0)
			s_a[i] = (cur_sum % 10) + '0';
		rem = cur_sum < 10 ? 0 : cur_sum / 10;
		if (rem > 0 && i == 0)
		{
			ft_str_move_right(s_a, '0');
			continue;
		}
		i--;
	}
}

static void	ft_pf_mult_s_by_c(char *s, char c)
{
	int i;
	int rem;
	int cur_mult;

	i = PF_LDWITH - 2;
	rem = 0;
	while (i >= 0)
	{
		cur_mult = (s[i] == '*' ? 0 : s[i] - '0') * (c - '0') + rem;
		if (cur_mult < 10 && cur_mult != 0)
			s[i] = cur_mult + '0';
		else if (cur_mult != 0)
			s[i] = (cur_mult % 10) + '0';
		rem = cur_mult < 10 ? 0 : cur_mult / 10;
		if (rem > 0 && i == 0)
		{
			ft_str_move_right(s, '0');
			continue;
		}
		i--;
	}
}

static void	ft_pf_5_by_pow(char *s, int pow)
{
	int i;

	i = 0;
	while (s[i])
		s[i++] = '*';
	s[0] = pow == 0 ? '1' : '5';
	i = 1;
	while (i < pow)
	{
		ft_pf_mult_s_by_c(s, '5');
		i++;
	}
	ft_pf_add_zero(s, pow);
}

void		ft_pf_set_ldb(t_pf *pf)
{
	t_ld ld;

	ld.i = (PF_SIZE_MANT - 1);
	ld.first_pow = 0;
	ld.mask = 1;
	ld.cur_pow = pf->ld.b.e - PF_TRUEEXP;
	while (ld.i >= 0)
	{
		if (ld.cur_pow < 0 && ld.first_pow == 0)
		{
			ft_pf_5_by_pow(pf->tmp, ft_abs(ld.cur_pow));
			ld.first_pow = 1;
		}
		else if (ld.cur_pow < 0)
		{
			ft_pf_mult_s_by_c(pf->tmp, '5');
			ft_pf_add_zero(pf->tmp, ft_abs(ld.cur_pow));
		}
		if (pf->ld.b.m & (ld.mask << ld.i) && ld.cur_pow < 0)
			ft_pf_plus_to_s_a(pf->ldb, pf->tmp);
		ld.i--;
		ld.cur_pow--;
	}
}
