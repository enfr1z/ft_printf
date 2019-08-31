/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:59:22 by pdiedra           #+#    #+#             */
/*   Updated: 2019/07/01 15:22:36 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_pf_put_prec(t_pf *pf)
{
	char *tmp;
	char *prec;

	if (!(prec = ft_strnew(pf->prec - pf->arg_len)))
		exit(1);
	ft_memset(prec, '0', pf->prec - pf->arg_len);
	prec[pf->prec - pf->arg_len] = '\0';
	tmp = pf->arg_str;
	if (!(pf->arg_str = ft_strjoin(prec, pf->arg_str)))
		exit(1);
	free(tmp);
	free(prec);
}

static int	ft_pf_swap_x_zero(char *str, char sign)
{
	int f_zero;
	int f_sign;
	int i;

	f_zero = -1;
	f_sign = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '0' && f_zero == -1)
			f_zero = i + 1;
		if (str[i] == sign && f_sign == -1)
			f_sign = i;
		if (f_zero >= 0 && f_sign >= 0)
			break ;
		i++;
	}
	if (f_zero >= 0 && f_sign >= 0 && f_zero < f_sign)
	{
		str[f_zero] = sign;
		str[f_sign] = '0';
	}
	return (f_zero >= 0 && f_sign >= 0);
}

void		ft_pf_write_arg_pointer(t_pf *pf)
{
	int		iter;
	size_t	i;
	char	*tmp;

	i = va_arg(pf->vl, size_t);
	pf->arg_str = !i && pf->prec >= 0 ? ft_strnew(0) : ft_ulltoa_base(i, 16);
	iter = -1;
	while (pf->arg_str[++iter])
		pf->arg_str[iter] = ft_tolower(pf->arg_str[iter]);
	if (pf->prec > (pf->arg_len = ft_strlen(pf->arg_str)))
		ft_pf_put_prec(pf);
	tmp = pf->arg_str;
	if (!(pf->arg_str = ft_strjoin("0x", pf->arg_str)))
		exit(1);
	free(tmp);
	if (((pf->arg_len = ft_strlen(pf->arg_str)) < pf->width) && pf->minus == 0)
		ft_pf_join_width(pf);
	ft_pf_join_to_buf(pf, pf->arg_str);
	if (((pf->arg_len = ft_strlen(pf->arg_str)) < pf->width) && pf->minus == 1)
		ft_pf_join_width(pf);
	if (pf->zero == 1 && pf->width >= 0)
		ft_pf_swap_x_zero(pf->buf, 'x');
	pf->str_len += ft_pf_write(pf->buf, ft_strlen(pf->buf));
	ft_cleaner((void**)&pf->buf, NULL, NULL);
	ft_cleaner((void**)&pf->arg_str, NULL, NULL);
}
