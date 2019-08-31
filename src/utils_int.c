/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:51:39 by pdiedra           #+#    #+#             */
/*   Updated: 2019/07/01 15:16:46 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_join_sign_to_str(t_pf *pf, char *str)
{
	char *tmp;

	if (!(tmp = ft_strjoin(str, pf->arg_str)))
		exit(1);
	free(pf->arg_str);
	pf->arg_str = tmp;
}

int		ft_pf_swap_sign_zero(char *str, char sign)
{
	int f_zero;
	int f_sign;
	int i;

	f_zero = -1;
	f_sign = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '0' && f_zero == -1)
			f_zero = i;
		if (str[i] == sign && f_sign == -1)
			f_sign = i;
		if (f_zero >= 0 && f_sign >= 0)
			break ;
		i++;
	}
	if (f_zero >= 0 && f_sign >= 0 && f_zero < f_sign)
	{
		str[f_zero] = sign;
		str[f_sign] = '0';
	}
	return (f_zero >= 0 && f_sign >= 0);
}

void	ft_pf_join_prec_to_str(t_pf *pf)
{
	char *prec;
	char *tmp;

	if (!(prec = ft_strnew(pf->prec - pf->arg_len)))
		exit(1);
	ft_memset(prec, '0', pf->prec - pf->arg_len > 0 ?
	pf->prec - pf->arg_len : pf->prec);
	if (!(tmp = ft_strjoin(prec, pf->arg_str)))
		exit(1);
	free(prec);
	free(pf->arg_str);
	pf->arg_str = tmp;
}

void	ft_pf_size_t_d(t_pf *pf)
{
	size_t	z;

	z = va_arg(pf->vl, ssize_t);
	pf->arg_str = ft_ltoa(z);
}

void	ft_pf_check_spec(t_pf *pf)
{
	if (pf->s_ll == 1)
	{
		pf->s_z = 0;
		pf->s_l = 0;
		pf->s_h = 0;
		pf->s_hh = 0;
	}
	if (pf->s_z == 1 || pf->s_l == 1 || pf->s_j == 1)
	{
		pf->s_h = 0;
		pf->s_hh = 0;
	}
	if (pf->s_h == 1)
		pf->s_hh = 0;
}
