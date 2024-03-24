/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:47:53 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 14:53:33 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;
	void	*ret;
	long	len;

	len = count * size;
	tmp = malloc(len);
	if (!tmp)
	{
		return (NULL);
	}
	ret = tmp;
	while (len > 0)
	{
		*(char *)tmp = 0;
		++tmp;
		--len;
	}
	return (ret);
}

static int	ft_int_len(int n)
{
	int			len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		++len;
		n /= 10;
	}
	return (len);
}

static void	ft_is_plus_minus(int *plus_minus, long *n_tmp)
{
	if (*n_tmp < 0)
	{
		*plus_minus = 1;
		*n_tmp *= -1;
	}
	else
		*plus_minus = 0;
}

static char	*ft_ret_char(char *string, int n, int plus_minus, int index)
{
	char		*ret;
	char		*ret_tmp;

	ret = (char *)ft_calloc(1, ft_int_len(n) + plus_minus + 1);
	if (ret == NULL)
		return (NULL);
	ret_tmp = ret;
	if (n == 0)
	{
		ret[0] = '0';
		ret[1] = '\0';
		return (ret);
	}
	if (plus_minus == 1)
		*ret_tmp++ = '-';
	while (--index >= 0)
	{
		*ret_tmp++ = string[index];
	}
	*ret_tmp = '\0';
	return (ret);
}

char	*ft_itoa(int n)
{
	char		string[12];
	int			index;
	int			plus_minus;
	long		n_tmp;
	char		*ret_tmp;

	index = 12;
	while (--index >= 0)
		string[index] = 0;
	index = 0;
	n_tmp = n;
	ft_is_plus_minus(&plus_minus, &n_tmp);
	while (n_tmp != 0)
	{
		string[index++] = n_tmp % 10 + '0';
		n_tmp /= 10;
	}
	ret_tmp = ft_ret_char(string, n, plus_minus, index);
	if (ret_tmp == NULL)
		return (NULL);
	return (ret_tmp);
}
