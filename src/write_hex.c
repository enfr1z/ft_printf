/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 18:37:21 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 15:18:12 by pdiedra          ###   ########.fr       */
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
		pf->arg_str = ft_ulltoa_base(h, 16);
	}
	else if (pf->s_hh)
	{
		hh = va_arg(pf->vl, unsigned int);
		pf->arg_str = ft_ulltoa_base(hh, 16);
	}
	if (pf->s_l || pf->s_j)
	{
		l = va_arg(pf->vl, unsigned long int);
		pf->arg_str = ft_ulltoa_base(l, 16);
	}
	else if (pf->s_ll)
	{
		ll = va_arg(pf->vl, unsigned long long int);
		pf->arg_str = ft_ulltoa_base(ll, 16);
	}
}

static void	ft_pf_set_arg_str(t_pf *pf)
{
	int				iter;
	unsigned int	i;

	if (!pf->s_h && !pf->s_hh && !pf->s_l && !pf->s_ll && !pf->s_j)
	{
		i = va_arg(pf->vl, unsigned int);
		pf->arg_str = (i == 0 && pf->prec == 0) ?
		ft_strnew(0) : ft_ulltoa_base(i, 16);
	}
	else if (pf->s_h || pf->s_hh || pf->s_l || pf->s_ll || pf->s_j)
		ft_pf_set_arg_str_l_h(pf);
	if (pf->type == 'x')
	{
		iter = 0;
		while (pf->arg_str[iter])
		{
			pf->arg_str[iter] = ft_tolower(pf->arg_str[iter]);
			iter++;
		}
	}
}

static int	ft_pf_swap_x_zero(char *str, char sign)
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
			f_zero = i + 1;
		if (str[i] == sign && f_sign == -1)
			f_sign = i;
		if (f_zero >= 0 && f_sign >= 0)
			break ;
		i++;
	}
	if (f_zero >= 0 && f_sign >= 0)
	{
		str[f_zero] = sign;
		str[f_sign] = '0';
	}
	return (f_zero >= 0 && f_sign >= 0);
}

void		ft_pf_write_arg_hex(t_pf *pf)
{
	ft_pf_set_arg_str(pf);
	if (pf->prec >= 0 && pf->width >= 0 && pf->zero)
		pf->zero = 0;
	pf->arg_len = ft_strlen(pf->arg_str);
	if (pf->prec > pf->arg_len)
		ft_pf_join_prec_to_str(pf);
	ft_pf_check_okt_hex(pf);
	pf->arg_len = ft_strlen(pf->arg_str);
	if (pf->arg_len < pf->width && pf->minus == 0 && pf->width > pf->prec)
		ft_pf_join_width(pf);
	ft_pf_join_to_buf(pf, pf->arg_str);
	if (pf->arg_len < pf->width && pf->minus == 1)
		ft_pf_join_width(pf);
	if (pf->zero == 1 || pf->prec != -1)
		ft_pf_swap_sign_zero(pf->buf, pf->is_neg ? '-' : '+');
	if (pf->width > pf->arg_len && pf->zero == 1 && pf->minus == 0)
		ft_pf_swap_x_zero(pf->buf, pf->type == 'x' ? 'x' : 'X');
	pf->str_len += ft_pf_write(pf->buf, ft_strlen(pf->buf));
	ft_cleaner((void**)&pf->buf, NULL, NULL);
	ft_cleaner((void**)&pf->arg_str, NULL, NULL);
}
