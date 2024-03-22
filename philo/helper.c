/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:27 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/22 20:35:25 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	msg_philo(t_thread *ph, t_msg *msg)
{
	pthread_mutex_lock(ph->flag_mutex);
	if (*(ph->flag) == DIE)
	{
		pthread_mutex_unlock(ph->flag_mutex);
		return (FUN_FAIL);
	}
	else
	{
		pthread_mutex_lock(ph->print);
		msg->time = (ft_usec_now() - ph->start_time) / THOUSAND;
		printf("%ld %ld %s\n", msg->time, msg->ph, msg->msg);
		pthread_mutex_unlock(ph->print);
		pthread_mutex_unlock(ph->flag_mutex);
		return (FUN_SUC);
	}
}

int	lock_fork(pthread_mutex_t *fork, long *flag, int fork_flag)
{
	int	ret;

	ret = FUN_SUC;
	(void)fork_flag;
	ret = pthread_mutex_lock(fork);
	*flag = ~(*flag);
	ret = pthread_mutex_unlock(fork);
	return (ret);
}

int	check_atol(const char *input, long *output)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isdigit(input[i++]))
		{
			printf("NOT INTEGER!\n");
			return (1);
		}
	}
	*output = ft_atol(input);
	if (*output < 0)
	{
		printf("NOT POSITIVE NUMBER!\n");
		return (1);
	}
	if (*output > INT_MAX || i > 12)
	{
		printf("INVALID INT SIZE!\n");
		return (1);
	}
	return (0);
}
