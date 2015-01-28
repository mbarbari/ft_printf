/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlambert <rlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:37:18 by rlambert          #+#    #+#             */
/*   Updated: 2015/01/28 22:57:50 by rlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include "handle_funcs.h"

char	*parse_flags(char **format, t_arg *arg)
{
	if (**format == '#' || **format == '0' || **format == '-' || **format == '+'
		|| **format == ' ')
	{
		if (**format == '#')
			arg->force_prefix = 1;
		else if (**format == '0')
			arg->pad_zeroes = 1;
		else if (**format == '-')
			arg->right_pad = 1;
		else if (**format == '+')
			arg->force_sign = 1;
		else if (**format == ' ')
			arg->blank_sign = 1;
		(*format)++;
		if (arg->right_pad)
			arg->pad_zeroes = 0;
		return (parse_flags(format, arg));
	}
	else
		return (*format);
}

char	*parse_width(char **format, va_list *list, t_arg *arg)
{
	arg->width = 0;
	if (**format == '*')
	{
		(*format)++;
		arg->width = va_arg(*list, unsigned int);
		arg->got_width = 1;
		return (*format);
	}
	else if (ft_isdigit(**format))
	{
		arg->got_width = 1;
		while (ft_isdigit(**format))
			arg->width = arg->width * 10 + (*(*format)++ - '0');
		return (*format);
	}
	else
		return (*format);
}

char	*parse_precision(char **format, va_list *list, t_arg *arg)
{
	if (**format == '.')
	{
		arg->pad_zeroes = 0;
		(*format)++;
		if (**format == '*')
		{
			(*format)++;
			arg->got_precision = 1;
			arg->precision = va_arg(*list, unsigned int);
			return (*format);
		}
		else if (ft_isdigit(**format))
		{
			while (ft_isdigit(**format))
				arg->precision = arg->precision * 10 + (*(*format)++ - '0');
			arg->got_precision = 1;
			return (*format);
		}
		else
			return (*format);
	}
	else
		return (*format);
}

char	*parse_length(char **format, t_arg *arg)
{
	if (**format == 'h' && *(*format + 1) == 'h')
	{
		arg->length = hh;
		return (*format += 2);
	}
	else if (**format == 'l' && *(*format + 1) == 'l')
	{
		arg->length = ll;
		return (*format += 2);
	}
	else if (**format == 'h' || **format == 'l' || **format == 'j' ||
					**format == 'z')
	{
		if (**format == 'h')
			arg->length = h;
		else if (**format == 'l')
			arg->length = l;
		else if (**format == 'j')
			arg->length = j;
		else if (**format == 'z')
			arg->length = z;
		return ((*format)++);
	}
	else
		return (*format);
}
