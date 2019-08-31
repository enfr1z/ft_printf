/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdiedra <pdiedra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:27:01 by pdiedra           #+#    #+#             */
/*   Updated: 2019/07/01 15:29:07 by pdiedra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define PF_FORMATS "cspdiouUxXf%"
# define PF_FLAGS "1234567890. #-+hlLjz"

# define PF_LDWITH 4934
# define PF_SIZE_SIGN 1
# define PF_SIZE_EXP 15
# define PF_SIZE_MANT 64
# define PF_TRUEEXP 16383

# define EXP_MAX(E) E == 32767 ? 1 : 0
# define MANT_MAX(M) M == 9223372036854775808U ? 1 : 0

typedef struct			s_ld
{
	int					i;
	int					cur_pow;
	int					first_pow;
	unsigned long int	mask;
}						t_ld;

typedef struct			s_ldsem
{
	unsigned long int	m:PF_SIZE_MANT;
	unsigned			e:PF_SIZE_EXP;
	unsigned			s:PF_SIZE_SIGN;
}						t_ldsem;

typedef union			u_ldbits
{
	long double			val;
	t_ldsem				b;
}						t_ldbits;

typedef	struct			s_pf
{
	int					type;
	int					okt;
	int					zero;
	int					minus;
	int					plus;
	int					space;
	int					width;
	int					prec;
	int					s_h;
	int					s_j;
	int					s_z;
	int					s_hh;
	int					s_l;
	int					s_ll;
	int					s_ld;
	int					arg_len;
	char				*arg_str;
	char				*buf;
	int					is_neg;
	t_ldbits			ld;
	char				lda[PF_LDWITH];
	char				ldb[PF_LDWITH];
	char				tmp[PF_LDWITH];
	int					i_s;
	int					i_e;
	int					is_arg;
	int					str_len;
	va_list				vl;
	const char			*format;
}						t_pf;

int						ft_printf(const char *format, ...);
void					ft_pf_init_str(char *str, unsigned int len);
t_pf					*ft_pf_init_args(t_pf *pf);
t_pf					*ft_pf_init(const char *format);
t_pf					*ft_pf_parse_flags(t_pf *pf);
void					ft_pf_round_ld_b(t_pf *pf, int prec);
void					ft_pf_join_to_buf(t_pf *pf, char *str);
void					ft_pf_join_width(t_pf *pf);
void					ft_pf_check_space(t_pf *pf);
void					ft_pf_plus_to_s_a_rev(char *s_a, char *s_b);
void					ft_pf_set_lda(t_pf *pf);
void					ft_pf_plus_to_s_a(char *s_a, char *s_b);
void					ft_pf_set_ldb(t_pf *pf);
void					ft_str_move_right(char *str, char c);
void					ft_pf_add_zero(char *s, int pow);
void					ft_pf_set_ld_val(t_pf *pf);
void					ft_pf_reverse_lda(t_pf *pf);
void					ft_pf_write_arg_hex(t_pf *pf);
void					ft_pf_check_swap(t_pf *pf);
void					ft_pf_write_arg_int(t_pf *pf);
void					ft_pf_write_arg_oct(t_pf *pf);
void					ft_pf_write_arg_percent(t_pf *pf);
void					ft_pf_write_arg_pointer(t_pf *pf);
void					ft_pf_write_arg_unsigned(t_pf *pf);
int						ft_pf_write(const char *str, int len);
void					ft_pf_write_args(t_pf *pf);
void					ft_pf_write_str(t_pf *pf);
int						ft_pf_is_format(char c);
int						ft_pf_is_flag(char c);
void					ft_swap_char(char *c1, char *c2);
void					ft_pf_write_arg_str(t_pf *pf);
void					ft_pf_write_arg_char(t_pf *pf);
void					ft_pf_write_arg_float(t_pf *pf);
void					ft_pf_join_sign_to_str(t_pf *pf, char *str);
void					ft_pf_join_prec_to_str(t_pf *pf);
void					ft_pf_check_okt_hex(t_pf *pf);
int						ft_pf_swap_sign_zero(char *str, char sign);
void					ft_pf_size_t_d(t_pf *pf);
int						ft_pf_swap_sign_zero(char *str, char sign);
void					ft_pf_check_spec(t_pf *pf);
void					ft_pf_check_okt_oct(t_pf *pf);
void					ft_pf_check_space_f(t_pf *pf);

#endif
