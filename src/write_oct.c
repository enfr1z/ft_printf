/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_oct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:53:04 by pdiedra           #+#    #+#             */
/*   Updated: 2019/07/01 15:19:08 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_pf_set_arg_str_l_h(t_pf *pf)
{
	unsigned short			h;
	unsigned char			hh;
	unsigned long int		l;
	unsigned long long int	ll;

	if (pf->s_h)
	{
		h = va_arg(pf->vl, unsigned int);
		pf->arg_str = ft_ulltoa_base(h, 8);
	}
	else if (pf->s_hh)
	{
		hh = va_arg(pf->vl, unsigned int);
		pf->arg_str = ft_ulltoa_base(hh, 8);
	}
	if (pf->s_l || pf->s_j)
	{
		l = va_arg(pf->vl, unsigned long int);
		pf->arg_str = ft_ulltoa_base(l, 8);
	}
	else if (pf->s_ll)
	{
		ll = va_arg(pf->vl, unsigned long long int);
		pf->arg_str = ft_ulltoa_base(ll, 8);
	}
}

static void	ft_pf_set_arg_str(t_pf *pf)
{
	unsigned int	i;

	if (!pf->s_h && !pf->s_hh && !pf->s_l && !pf->s_ll && !pf->s_j && !pf->s_z)
	{
		i = va_arg(pf->vl, unsigned int);
		pf->arg_str = (i == 0 && (pf->width == -1 || pf->width >= 0) &&
		pf->okt == 0 && pf->prec == 0 ? ft_strnew(0) : ft_ulltoa_base(i, 8));
	}
	else if (pf->s_h || pf->s_hh || pf->s_l || pf->s_ll || pf->s_j || pf->s_z)
		ft_pf_set_arg_str_l_h(pf);
}

void		ft_pf_write_arg_oct(t_pf *pf)
{
	ft_pf_set_arg_str(pf);
	if (pf->prec >= 0 && pf->width >= 0 && pf->zero)
		pf->zero = 0;
	pf->arg_len = ft_strlen(pf->arg_str);
	if (pf->prec > pf->arg_len)
		ft_pf_join_prec_to_str(pf);
	pf->arg_len = ft_strlen(pf->arg_str);
	ft_pf_check_okt_oct(pf);
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
