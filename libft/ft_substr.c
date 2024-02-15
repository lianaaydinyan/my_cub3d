/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:20:23 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/12 21:16:13 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*sub;
	int		i;
	int		slen;

	i = 0;
	slen = ft_strlen(s);
	if (start > (unsigned)slen)
		return (ft_strdup(""));
	if (len > slen)
		len = slen;
	if (!s)
		return (0);
	sub = (char *)malloc((len + 1) * sizeof(char));
	slen = ft_strlen(s);
	if (!sub)
		return (0);
	while (i < len && s[start] != '\0')
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
