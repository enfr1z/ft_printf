/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:00:03 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 14:49:30 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_write_arg_char(t_pf *pf)
{
	int c;

	c = va_arg(pf->vl, int);
	pf->arg_len = 1;
	if (pf->width > 1 && pf->minus == 0)
	{
		ft_pf_join_width(pf);
		pf->str_len += ft_pf_write(pf->buf, ft_strlen(pf->buf));
	}
	pf->str_len += write(1, &c, 1);
	if (pf->width > 1 && pf->minus == 1)
	{
		ft_pf_join_width(pf);
		pf->str_len += ft_pf_write(pf->buf, ft_strlen(pf->buf));
	}
	ft_cleaner((void**)&pf->buf, NULL, NULL);
}

void	ft_pf_write_arg_str(t_pf *pf)
{
	char *tmp;

	if (!(pf->arg_str = ft_strjoin(va_arg(pf->vl, char *), "\0")))
		if (!(pf->arg_str = ft_strjoin("(null)", "\0")))
			exit(1);
	tmp = NULL;
	pf->plus = 0;
	pf->space = 0;
	if (pf->prec < (pf->arg_len = ft_strlen(pf->arg_str)) && pf->prec >= 0)
	{
		if (!(tmp = ft_strsub(pf->arg_str, 0, pf->prec)))
			exit(1);
		ft_cleaner((void**)&pf->arg_str, NULL, NULL);
		pf->arg_str = tmp;
		pf->arg_len = ft_strlen(tmp);
	}
	if (pf->width > pf->arg_len && pf->minus == 0)
		ft_pf_join_width(pf);
	ft_pf_join_to_buf(pf, pf->arg_str);
	if (pf->width > pf->arg_len && pf->minus == 1)
		ft_pf_join_width(pf);
	pf->str_len += ft_pf_write(pf->buf, ft_strlen(pf->buf));
	ft_cleaner((void**)&pf->buf, NULL, NULL);
	ft_cleaner((void**)&pf->arg_str, NULL, NULL);
}
