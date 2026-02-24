/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	rt_parse_fraction(const char *str, char **endptr, int *i)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 10.0;
	(*i)++;
	while (ft_isdigit(str[*i]))
	{
		fraction += (str[*i] - '0') / divisor;
		divisor *= 10.0;
		(*i)++;
	}
	*endptr = (char *)(str + *i);
	return (fraction);
}

double	rt_atof(const char *str, char **endptr)
{
	double	result;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	result = 0.0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		result += rt_parse_fraction(str, endptr, &i);
	else
		*endptr = (char *)(str + i);
	return (result * sign);
}

void	rt_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
