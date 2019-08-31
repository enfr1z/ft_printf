/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanta <vsanta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:16:58 by vsanta            #+#    #+#             */
/*   Updated: 2019/07/01 16:07:12 by vsanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_join_prec_to_str_float(t_pf *pf)
{
	char *prec;
	char *tmp;

	pf->prec = pf->prec - PF_LDWITH + 1;
	if (pf->prec > 0)
	{
		if (!(prec = ft_strnew(pf->prec)))
			exit(1);
		ft_memset(prec, '0', pf->prec);
		if (!(tmp = ft_strjoin(pf->arg_str, prec)))
			exit(1);
		free(prec);
		free(pf->arg_str);
		pf->arg_str = tmp;
	}
}

int		ft_pf_set_ld_nan_inf_str(t_pf *pf)
{
	if (EXP_MAX(pf->ld.b.e))
	{
		if (MANT_MAX(pf->ld.b.m))
		{
			pf->zero = 0;
			if (!(pf->arg_str = ft_strjoin("inf\0", "\0")))
				exit(1);
		}
		else if (pf->ld.b.m > 0)
		{
			pf->plus = 0;
			pf->zero = 0;
			pf->space = 0;
			if (!(pf->arg_str = ft_strjoin("nan\0", "\0")))
				exit(1);
		}
		return (1);
	}
	return (0);
}

void	ft_pf_set_ld_str(t_pf *pf)
{
	char *tmp;

	if (ft_pf_set_ld_nan_inf_str(pf) == 0)
	{
		if (pf->ld.b.m + pf->ld.b.e > 0)
		{
			ft_pf_set_lda(pf);
			ft_pf_set_ldb(pf);
		}
		ft_pf_reverse_lda(pf);
		ft_pf_round_ld_b(pf, pf->prec < 0 ? 6 : pf->prec);
		if (!(pf->arg_str = ft_strjoin(pf->lda, pf->prec == 0 &&
		pf->okt == 0 ? "\0" : ".\0")))
			exit(1);
		if (pf->prec != 0)
		{
			tmp = pf->arg_str;
			if (!(pf->arg_str = ft_strjoin(pf->arg_str, pf->ldb)))
				exit(1);
			free(tmp);
		}
	}
}

void	ft_pf_write_arg_float(t_pf *pf)
{
	ft_pf_set_ld_val(pf);
	ft_pf_set_ld_str(pf);
	pf->arg_len = pf->ld.b.s == 1 ?
	ft_strlen(pf->arg_str) - 1 : ft_strlen(pf->arg_str);
	if (pf->ld.b.s == 1)
		ft_pf_join_sign_to_str(pf, "-");
	else if ((pf->ld.b.s == 0) && pf->plus == 1)
		ft_pf_join_sign_to_str(pf, "+");
	ft_pf_check_space_f(pf);
	if (pf->prec > PF_LDWITH - 1)
		ft_pf_join_prec_to_str_float(pf);
	pf->arg_len = ft_strlen(pf->arg_str);
	if (pf->arg_len < pf->width && pf->minus == 0)
		ft_pf_join_width(pf);
	ft_pf_join_to_buf(pf, pf->arg_str);
	if (pf->arg_len < pf->width && pf->minus == 1)
		ft_pf_join_width(pf);
	ft_pf_check_swap(pf);
	pf->str_len += ft_pf_write(pf->buf, ft_strlen(pf->buf));
	ft_cleaner((void**)&pf->buf, NULL, NULL);
	ft_cleaner((void**)&pf->arg_str, NULL, NULL);
}
