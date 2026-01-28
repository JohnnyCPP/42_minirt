/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mr_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+        */
/*       igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:03:00 by igenez-y          #+#    #+#             */
/*   Updated: 2026/01/26 02:49:28 by igenez-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	mr_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static int	mr_count_tokens(char *str)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	while (*str)
	{
		if (!mr_is_whitespace(*str) && !in_token)
		{
			in_token = 1;
			count++;
		}
		else if (mr_is_whitespace(*str))
			in_token = 0;
		str++;
	}
	return (count);
}

static char	*mr_extract_token(char *str, int *i)
{
	int		start;
	int		len;
	char	*token;

	while (str[*i] && mr_is_whitespace(str[*i]))
		(*i)++;
	start = *i;
	while (str[*i] && !mr_is_whitespace(str[*i]))
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (NULL);
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, &str[start], len + 1);
	return (token);
}

char	**mr_tokenize(char *str)
{
	char	**tokens;
	int		count;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	count = mr_count_tokens(str);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		tokens[j] = mr_extract_token(str, &i);
		if (!tokens[j])
		{
			mr_free_split(tokens);
			return (NULL);
		}
		j++;
	}
	tokens[j] = NULL;
	return (tokens);
}
