/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:14:26 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 15:12:36 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_pf	*ft_pf_is_arg(t_pf *pf)
{
	if (pf->format[pf->i_e] == '%' && pf->is_arg == 0)
	{
		pf = ft_pf_init_args(pf);
		pf->is_arg = 1;
		return (NULL);
	}
	if (ft_pf_is_format(pf->format[pf->i_e]))
	{
		pf->type = pf->format[pf->i_e];
		pf->is_arg = 0;
		pf->i_s = pf->i_e + 1;
		ft_pf_write_args(pf);
	}
	else if (ft_pf_is_flag(pf->format[pf->i_e]))
		ft_pf_parse_flags(pf);
	else
	{
		pf->is_arg = 0;
		pf->i_s = pf->i_e;
	}
	return (NULL);
}

static void	ft_pf_is_str(t_pf *pf)
{
	if (pf->format[pf->i_e + 1] == '%' || pf->format[pf->i_e + 1] == '\0')
	{
		ft_pf_write_str(pf);
		pf->i_s = pf->i_e;
	}
}

static void	ft_pf_parse(t_pf *pf)
{
	while (pf->format[pf->i_e])
	{
		if (pf->format[pf->i_e] == '%' || pf->is_arg == 1)
			ft_pf_is_arg(pf);
		if (pf->is_arg == 0)
			ft_pf_is_str(pf);
		pf->i_e++;
	}
}

int			ft_printf(const char *format, ...)
{
	t_pf	*pf;
	int		len;

	pf = NULL;
	pf = ft_pf_init(format);
	va_start(pf->vl, format);
	ft_pf_parse(pf);
	va_end(pf->vl);
	len = pf->str_len;
	free(pf);
	return (len);
}
