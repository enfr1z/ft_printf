/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:14:50 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 15:29:32 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_swap_char(char *c1, char *c2)
{
	char tmp;

	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

int		ft_pf_is_flag(char c)
{
	return (ft_strchr(PF_FLAGS, c) == NULL ? 0 : 1);
}

int		ft_pf_is_format(char c)
{
	return (ft_strchr(PF_FORMATS, c) == NULL ? 0 : 1);
}

t_pf	*ft_pf_set_max_spec(t_pf *pf)
{
	pf->s_hh = pf->s_hh == 1 &&
	pf->s_h + pf->s_l + pf->s_ll + pf->s_ld == 0 ? 1 : 0;
	pf->s_h = pf->s_h == 1 && pf->s_l + pf->s_ll + pf->s_ld == 0 ? 1 : 0;
	pf->s_l = pf->s_l == 1 && pf->s_ll + pf->s_ld == 0 ? 1 : 0;
	pf->s_ll = pf->s_ll == 1 && pf->s_ld == 0 ? 1 : 0;
	return (pf);
}
