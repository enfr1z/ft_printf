/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 15:29:15 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 15:21:57 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_pf_set_arg_str_l_h(t_pf *pf)
{
	unsigned short			h;
	unsigned char			hh;
	unsigned long int		l;
	unsigned long long int	ll;

	if (pf->s_h && pf->type != 'U')
	{
		h = va_arg(pf->vl, unsigned int);
		pf->arg_str = ft_utoa(h);
	}
	else if (pf->s_hh && pf->type != 'U')
	{
		hh = va_arg(pf->vl, unsigned int);
		pf->arg_str = ft_utoa(hh);
	}
	if (pf->s_l || pf->s_j || pf->s_z)
	{
		l = va_arg(pf->vl, unsigned long int);
		pf->arg_str = ft_ulltoa(l);
	}
	else if (pf->s_ll && pf->type != 'U')
	{
		ll = va_arg(pf->vl, unsigned long long int);
		pf->arg_str = ft_ulltoa(ll);
	}
}

static void	ft_pf_set_arg_str(t_pf *pf)
{
	unsigned int	i;

	if (pf->type == 'U')
		pf->s_l = 1;
	if (!pf->s_h && !pf->s_hh && !pf->s_l && !pf->s_ll && !pf->s_j && !pf->s_z)
	{
		i = va_arg(pf->vl, unsigned int);
		pf->arg_str = (i == 0 && pf->prec == 0) ? ft_strnew(0) : ft_utoa(i);
	}
	else if (pf->s_h || pf->s_hh || pf->s_l || pf->s_ll || pf->s_j || pf->s_z)
		ft_pf_set_arg_str_l_h(pf);
}

void		ft_pf_write_arg_unsigned(t_pf *pf)
{
	ft_pf_set_arg_str(pf);
	if (pf->prec >= 0 && pf->width >= 0 && pf->zero)
		pf->zero = 0;
	pf->arg_len = ft_strlen(pf->arg_str);
	if (pf->prec > pf->arg_len)
		ft_pf_join_prec_to_str(pf);
	pf->arg_len = ft_strlen(pf->arg_str);
	if (pf->arg_len < pf->width && pf->minus == 0 && pf->width > pf->prec)
		ft_pf_join_width(pf);
	ft_pf_join_to_buf(pf, pf->arg_str);
	if (pf->arg_len < pf->width && pf->minus == 1)
		ft_pf_join_width(pf);
	if (pf->zero == 1 || pf->prec != -1)
		ft_pf_swap_sign_zero(pf->buf, pf->is_neg ? '-' : '+');
	pf->str_len += ft_pf_write(pf->buf, ft_strlen(pf->buf));
	ft_cleaner((void**)&pf->buf, NULL, NULL);
	ft_cleaner((void**)&pf->arg_str, NULL, NULL);
}
