/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:27 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/02 23:08:55 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_islong(const char *str)
{
	while (*str != '\0')
	{
		if (!ft_isdigit((int)*str))
			return (1);
		str++;
	}
	return (0);
}

int	ft_isspace(char s1)
{
	return (s1 == '\t' || s1 == '\n' || s1 == '\v' || \
			s1 == '\f' || s1 == '\r' || s1 == ' ');
}

long	ft_atol(const char *str)
{
	long	ret;
	int		sign;

	ret = 0;
	sign = 1;
	while (ft_isspace(*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	while (ft_isdigit(*str))
	{
		ret *= 10;
		ret += *str - '0';
		++str;
	}
	return (ret * sign);
}

long	ft_now_microsec(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * THOUSAND * THOUSAND + time.tv_usec);
}
