/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 21:24:15 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 15:13:52 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_pf_plus_for_round(char *round, char *nbr)
{
	int i;
	int sum;

	i = 1;
	sum = 0;
	if (*nbr >= '5')
	{
		if ((*round - '0') % 2 == 1 || *nbr > '5')
			return (1);
		while (nbr[i])
		{
			sum = sum + (nbr[i] - '0');
			i++;
		}
		return (sum > 0 == 1 ? 1 : 0);
	}
	return (0);
}

static void	ft_pf_round_ld_a(t_pf *pf, int plus_val)
{
	char	tmp[PF_LDWITH];
	int		i_e;

	ft_pf_init_str(tmp, PF_LDWITH);
	i_e = PF_LDWITH - 2;
	while (pf->lda[i_e] == '\0')
		i_e--;
	if (plus_val < 0)
		tmp[i_e] = ft_pf_plus_for_round(&pf->lda[i_e], pf->ldb) + '0';
	else
		tmp[i_e] = plus_val + '0';
	if (tmp[i_e] != '0')
		ft_pf_plus_to_s_a(pf->lda, tmp);
}

static void	ft_pf_plus_to_ld_b(t_pf *pf, char *s_b)
{
	int i;
	int rem;
	int cur_sum;

	i = PF_LDWITH - 2;
	rem = 0;
	while (i >= 0)
	{
		cur_sum = (ft_isdigit(pf->ldb[i]) ? pf->ldb[i] - '0' : 0)
		+ (ft_isdigit(s_b[i]) ? s_b[i] - '0' : 0) + rem;
		if (cur_sum < 10 && cur_sum != 0)
			pf->ldb[i] = cur_sum + '0';
		else if (cur_sum != 0)
			pf->ldb[i] = (cur_sum % 10) + '0';
		rem = cur_sum < 10 ? 0 : cur_sum / 10;
		if (rem > 0 && i == 0)
		{
			ft_pf_round_ld_a(pf, rem);
			break ;
		}
		i--;
	}
}

void		ft_pf_round_ld_b(t_pf *pf, int prec)
{
	char tmp[PF_LDWITH];

	ft_pf_init_str(tmp, PF_LDWITH);
	if (prec <= 0)
	{
		ft_pf_round_ld_a(pf, -1);
		ft_pf_init_str(pf->ldb, PF_LDWITH);
		return ;
	}
	if (prec >= PF_LDWITH - 2)
		return ;
	tmp[prec - 1] = ft_pf_plus_for_round(&pf->ldb[prec - 1],
	&pf->ldb[prec]) + '0';
	if (tmp[prec - 1] != '0')
		ft_pf_plus_to_ld_b(pf, tmp);
	while (pf->ldb[prec])
	{
		pf->ldb[prec] = '\0';
		prec++;
	}
}
