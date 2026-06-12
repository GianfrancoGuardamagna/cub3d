/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:08:19 by gguardam          #+#    #+#             */
/*   Updated: 2025/05/06 15:39:30 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	int		i;
	size_t	fst_len;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	fst_len = ft_strlen(s1);
	total_len = fst_len + ft_strlen(s2) + 1;
	new_str = malloc(total_len);
	if (!new_str)
		return (NULL);
	i = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	i = 0;
	while (s2[i])
	{
		new_str[fst_len + i] = s2[i];
		i++;
	}
	new_str[fst_len + i] = '\0';
	return (new_str);
}
