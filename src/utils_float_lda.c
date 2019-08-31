/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_float_lda.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 18:27:38 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 15:14:50 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_pf_plus_to_s_a_rev(char *s_a, char *s_b)
{
	int i;
	int rem;
	int cur_sum;
	int last_s_b;

	i = 0;
	rem = 0;
	last_s_b = 0;
	while (last_s_b == 0 || rem > 0)
	{
		if (s_b[i] == '\0')
			last_s_b = 1;
		if (s_a[i] == '\0')
			break ;
		cur_sum = (s_a[i] - '0') + ((last_s_b == 0 ? s_b[i] : '0') - '0') + rem;
		if (cur_sum < 10)
			s_a[i] = cur_sum + '0';
		else
			s_a[i] = (cur_sum % 10) + '0';
		rem = cur_sum < 10 ? 0 : cur_sum / 10;
		i++;
	}
}

static void	ft_pf_mult_s_by_c_rev(char *s, char c)
{
	int i;
	int rem;
	int cur_mult;

	i = 0;
	rem = 0;
	while (s[i] != '\0')
	{
		cur_mult = (s[i] - '0') * (c - '0') + rem;
		if (cur_mult < 10)
			s[i] = cur_mult + '0';
		else
			s[i] = (cur_mult % 10) + '0';
		rem = cur_mult < 10 ? 0 : cur_mult / 10;
		i++;
	}
}

static void	ft_pf_2_by_pow_rev(char *s, int pow)
{
	int i;

	i = 0;
	while (s[i])
		s[i++] = '0';
	s[0] = pow == 0 ? '1' : '2';
	i = 1;
	while (i < pow)
	{
		ft_pf_mult_s_by_c_rev(s, '2');
		i++;
	}
}

void		ft_pf_set_lda(t_pf *pf)
{
	t_ld ld;

	ld.i = 0;
	ld.first_pow = 0;
	ld.mask = 1;
	ld.cur_pow = pf->ld.b.e - PF_TRUEEXP - (PF_SIZE_MANT - 1);
	while (ld.i < PF_SIZE_MANT)
	{
		if (ld.cur_pow > 0 && ld.first_pow == 0)
		{
			ft_pf_2_by_pow_rev(pf->tmp, ld.cur_pow);
			ld.first_pow = 1;
		}
		else if (ld.cur_pow > 0)
			ft_pf_mult_s_by_c_rev(pf->tmp, '2');
		if (pf->ld.b.m & (ld.mask << ld.i))
		{
			ft_pf_plus_to_s_a_rev(pf->lda, pf->tmp);
			if (ld.cur_pow == 0)
				ft_pf_plus_to_s_a_rev(pf->lda, "1");
		}
		ld.i++;
		ld.cur_pow++;
	}
}
