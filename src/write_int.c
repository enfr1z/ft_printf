/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:19:44 by pdiedra           #+#    #+#             */
/*   Updated: 2019/07/01 15:18:56 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_pf_set_arg_str_l_h(t_pf *pf)
{
	short			h;
	signed char		hh;
	long int		l;
	long long int	ll;

	if (pf->s_h)
	{
		h = (short)va_arg(pf->vl, int);
		pf->arg_str = h == 0 && pf->prec == 0 ? ft_strnew(0) : ft_itoa(h);
	}
	else if (pf->s_hh)
	{
		hh = (signed char)va_arg(pf->vl, int);
		pf->arg_str = hh == 0 && pf->prec == 0 ? ft_strnew(0) : ft_itoa(hh);
	}
	if (pf->s_l || pf->s_j)
	{
		l = va_arg(pf->vl, long int);
		pf->arg_str = l == 0 && pf->prec == 0 ? ft_strnew(0) : ft_ltoa(l);
	}
	else if (pf->s_ll)
	{
		ll = va_arg(pf->vl, long long int);
		pf->arg_str = ll == 0 && pf->prec == 0 ? ft_strnew(0) : ft_lltoa(ll);
	}
}

static void	ft_pf_set_arg_str(t_pf *pf)
{
	int i;

	if (!pf->s_h && !pf->s_hh && !pf->s_l && !pf->s_ll && !pf->s_j)
	{
		if ((pf->s_z == 0 && pf->type == 'd') || pf->type == 'i')
		{
			i = va_arg(pf->vl, int);
			if (i < 0)
			{
				i = ft_abs(i);
				pf->is_neg = 1;
			}
			pf->arg_str = i == 0 && pf->prec == 0 ? ft_strnew(0) : ft_itoa(i);
		}
		else if (pf->s_z == 1 && pf->type == 'd')
			ft_pf_size_t_d(pf);
	}
	else if (pf->s_h || pf->s_hh || pf->s_l || pf->s_ll || pf->s_j)
		ft_pf_set_arg_str_l_h(pf);
}

void		ft_pf_check_swap(t_pf *pf)
{
	if (pf->width >= 0 || pf->prec >= 0 || pf->zero == 1)
	{
		if (pf->is_neg == 1 || pf->arg_str[0] == '-'
		|| pf->arg_str[pf->prec - (pf->arg_len - pf->prec)] == '-' ||
		pf->arg_str[pf->prec > pf->width ? pf->prec - pf->width :
		pf->width - pf->prec] == '-' || pf->plus == 0)
			ft_pf_swap_sign_zero(pf->buf, '-');
		else
			ft_pf_swap_sign_zero(pf->buf, '+');
	}
}

void		ft_pf_write_arg_int(t_pf *pf)
{
	ft_pf_check_spec(pf);
	ft_pf_set_arg_str(pf);
	if (pf->prec >= 0 && pf->width >= 0 && pf->zero)
		pf->zero = 0;
	pf->arg_len = pf->arg_str[0] == '-' ?
	ft_strlen(pf->arg_str) - 1 : ft_strlen(pf->arg_str);
	if (pf->is_neg == 1 && pf->arg_str[0] != '-')
		ft_pf_join_sign_to_str(pf, "-");
	else if ((pf->is_neg == 0) && pf->plus == 1 && pf->arg_str[0] != '-')
		ft_pf_join_sign_to_str(pf, "+");
	ft_pf_check_space(pf);
	if (pf->prec > pf->arg_len)
		ft_pf_join_prec_to_str(pf);
	pf->arg_len = ft_strlen(pf->arg_str);
	if (pf->arg_len < pf->width && pf->minus == 0 && pf->width > pf->prec)
		ft_pf_join_width(pf);
	ft_pf_join_to_buf(pf, pf->arg_str);
	if (pf->arg_len < pf->width && pf->minus == 1)
		ft_pf_join_width(pf);
	ft_pf_check_swap(pf);
	pf->str_len += ft_pf_write(pf->buf, ft_strlen(pf->buf));
	ft_cleaner((void**)&pf->buf, NULL, NULL);
	ft_cleaner((void**)&pf->arg_str, NULL, NULL);
}
