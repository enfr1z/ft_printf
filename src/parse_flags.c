/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:14:38 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 14:31:17 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_pf	*ft_pf_set_spec(t_pf *pf)
{
	if (pf->format[pf->i_e] == 'h' && pf->format[pf->i_e + 1] == 'h')
		pf->s_hh = 1;
	if (pf->format[pf->i_e] == 'h' &&
	pf->format[pf->i_e - 1] != 'h' && pf->format[pf->i_e + 1] != 'h')
		pf->s_h = 1;
	if (pf->format[pf->i_e] == 'l' &&
	pf->format[pf->i_e - 1] != 'l' && pf->format[pf->i_e + 1] != 'l')
		pf->s_l = 1;
	if (pf->format[pf->i_e] == 'l' && pf->format[pf->i_e + 1] == 'l')
		pf->s_ll = 1;
	if (pf->format[pf->i_e] == 'L')
		pf->s_ld = 1;
	if (pf->format[pf->i_e] == 'j')
		pf->s_j = 1;
	if (pf->format[pf->i_e] == 'z')
		pf->s_z = 1;
	return (pf);
}

static t_pf	*ft_pf_set_flags(t_pf *pf)
{
	if (pf->format[pf->i_e] == '#')
		pf->okt = 1;
	else if (pf->format[pf->i_e] == '0' && pf->format[pf->i_e - 1] != '.' &&
	pf->width == -1)
		pf->zero = 1;
	else if (pf->format[pf->i_e] == '-')
		pf->minus = 1;
	else if (pf->format[pf->i_e] == '+')
		pf->plus = 1;
	else if (pf->format[pf->i_e] == ' ')
		pf->space = 1;
	else if (pf->format[pf->i_e] == '.')
		pf->prec = 0;
	return (pf);
}

static t_pf	*ft_pf_set_width(t_pf *pf)
{
	pf->width = ft_atoi(&pf->format[pf->i_e]);
	return (pf);
}

static t_pf	*ft_pf_set_prec(t_pf *pf)
{
	pf->prec = ft_atoi(&pf->format[pf->i_e]);
	return (pf);
}

t_pf		*ft_pf_parse_flags(t_pf *pf)
{
	pf = ft_pf_set_flags(pf);
	pf = ft_pf_set_spec(pf);
	if (pf->format[pf->i_e - 1] != '.' && ft_isdigit(pf->format[pf->i_e]) &&
	!ft_isdigit(pf->format[pf->i_e - 1]))
		pf = ft_pf_set_width(pf);
	else if (pf->format[pf->i_e - 1] == '.' && ft_isdigit(pf->format[pf->i_e]))
		pf = ft_pf_set_prec(pf);
	return (pf);
}
