/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:14:34 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 15:13:00 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_init_str(char *str, unsigned int len)
{
	ft_memset((void*)str, '0', len);
	str[len - 1] = '\0';
}

t_pf	*ft_pf_init_args(t_pf *pf)
{
	pf->type = 0;
	pf->okt = 0;
	pf->zero = 0;
	pf->minus = 0;
	pf->plus = 0;
	pf->space = 0;
	pf->width = -1;
	pf->prec = -1;
	pf->s_h = 0;
	pf->s_hh = 0;
	pf->s_j = 0;
	pf->s_z = 0;
	pf->s_l = 0;
	pf->s_ll = 0;
	pf->s_ld = 0;
	pf->arg_len = 0;
	pf->arg_str = NULL;
	pf->buf = NULL;
	pf->is_neg = 0;
	pf->ld.val = 0;
	ft_pf_init_str(pf->lda, PF_LDWITH);
	ft_pf_init_str(pf->ldb, PF_LDWITH);
	ft_pf_init_str(pf->tmp, PF_LDWITH);
	return (pf);
}

t_pf	*ft_pf_init(const char *format)
{
	t_pf *tmp;

	if (!(tmp = (t_pf*)malloc(sizeof(t_pf))))
		exit(1);
	tmp = ft_pf_init_args(tmp);
	tmp->i_s = 0;
	tmp->i_e = 0;
	tmp->is_arg = 0;
	tmp->str_len = 0;
	tmp->format = format;
	return (tmp);
}
