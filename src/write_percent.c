/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 20:16:22 by vsanta            #+#    #+#             */
/*   Updated: 2019/06/28 18:36:22 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_write_arg_percent(t_pf *pf)
{
	pf->arg_str = "%";
	pf->arg_len = 1;
	pf->plus = 0;
	pf->space = 0;
	if (pf->width > pf->arg_len && pf->minus == 0)
		ft_pf_join_width(pf);
	ft_pf_join_to_buf(pf, pf->arg_str);
	if (pf->width > pf->arg_len && pf->minus == 1)
		ft_pf_join_width(pf);
	pf->str_len += ft_pf_write(pf->buf, ft_strlen(pf->buf));
	ft_cleaner((void**)&pf->buf, NULL, NULL);
}
