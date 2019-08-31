/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hex_oct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:49:34 by pdiedra           #+#    #+#             */
/*   Updated: 2019/07/01 15:23:05 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_pf_check_zero(t_pf *pf)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (pf->arg_str[++i])
		if (pf->arg_str[i] == '0')
			j++;
	if ((pf->arg_str[0] == '0' && j == pf->prec) ||
	(pf->arg_str[0] == '0' && i == 1) || (pf->arg_str[0] == '\0'))
		return (0);
	return (1);
}

void		ft_pf_check_okt_hex(t_pf *pf)
{
	char *tmp;

	if (pf->okt == 1 && ft_pf_check_zero(pf))
	{
		tmp = pf->arg_str;
		if (!(pf->arg_str = (pf->type == 'x') ?
		ft_strjoin("0x", tmp) : ft_strjoin("0X", tmp)))
			exit(1);
		free(tmp);
		pf->arg_len += 2;
	}
}

void		ft_pf_check_okt_oct(t_pf *pf)
{
	char *tmp;

	if (pf->okt == 1 && pf->arg_str[0] != '0' && pf->arg_str[1] != '\0')
	{
		tmp = pf->arg_str;
		if (!(pf->arg_str = ft_strjoin("0", tmp)))
			exit(1);
		free(tmp);
		pf->arg_len += 1;
	}
}
