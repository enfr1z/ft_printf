/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:14:58 by vsanta            #+#    #+#             */
/*   Updated: 2019/06/28 20:19:52 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_write(const char *str, int len)
{
	if (len > 0)
		return (write(1, str, len));
	else
		return (len);
}

void	ft_pf_write_args(t_pf *pf)
{
	if (pf->type == 's')
		ft_pf_write_arg_str(pf);
	else if (pf->type == 'i' || pf->type == 'd')
		ft_pf_write_arg_int(pf);
	else if (pf->type == '%')
		ft_pf_write_arg_percent(pf);
	else if (pf->type == 'c')
		ft_pf_write_arg_char(pf);
	else if (pf->type == 'u' || pf->type == 'U')
		ft_pf_write_arg_unsigned(pf);
	else if (pf->type == 'x' || pf->type == 'X')
		ft_pf_write_arg_hex(pf);
	else if (pf->type == 'f')
		ft_pf_write_arg_float(pf);
	else if (pf->type == 'o')
		ft_pf_write_arg_oct(pf);
	else if (pf->type == 'p')
		ft_pf_write_arg_pointer(pf);
}

void	ft_pf_write_str(t_pf *pf)
{
	pf->str_len = pf->str_len +
		ft_pf_write(&pf->format[pf->i_s], pf->i_e - pf->i_s + 1);
}
