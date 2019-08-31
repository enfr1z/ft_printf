/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:14:44 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 15:14:10 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_join_to_buf(t_pf *pf, char *str)
{
	char *tmp;

	if (!pf->buf)
		if (!(pf->buf = ft_strnew(0)))
			exit(1);
	if (!(tmp = ft_strjoin(pf->buf, str)))
		exit(1);
	ft_cleaner((void**)&pf->buf, NULL, NULL);
	pf->buf = tmp;
}

void	ft_pf_join_width(t_pf *pf)
{
	char *tmp;

	if (!(tmp = ft_strnew(pf->width - pf->arg_len)))
		exit(1);
	ft_memset((void*)tmp, pf->minus == 0 && pf->zero == 1
					? '0' : ' ', pf->width - pf->arg_len);
	ft_pf_join_to_buf(pf, tmp);
	ft_cleaner((void**)&tmp, NULL, NULL);
}

void	ft_pf_check_space(t_pf *pf)
{
	if (pf->space == 1 && pf->plus == 0 && pf->is_neg == 0 &&
	((pf->width == 1 && pf->arg_len != 0) || pf->width > pf->arg_len ||
	pf->width == -1 || pf->width == 0) && pf->arg_str[0] != '-')
	{
		ft_pf_join_to_buf(pf, " ");
		pf->width--;
	}
}

void	ft_pf_check_space_f(t_pf *pf)
{
	if (pf->space == 1 && pf->plus == 0 && pf->is_neg == 0 &&
	((pf->width == 1 && pf->arg_len != 0) || pf->width > pf->arg_len ||
	pf->width == -1 || pf->width == 0 || pf->prec > pf->width ||
	pf->width > pf->prec) && pf->arg_str[0] != '-')
	{
		ft_pf_join_to_buf(pf, " ");
		pf->width--;
	}
}
