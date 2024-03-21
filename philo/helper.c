/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:27 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/21 21:13:22 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	msg_philo(t_thread *ph, t_msg *msg)
{
	int	ret;

	ret = pthread_mutex_lock(ph->print);
	pthread_mutex_lock(ph->flag_mutex);
	if (ret || *(ph->flag) == DIE)
	{
		pthread_mutex_unlock(ph->flag_mutex);
		return (ret);
	}
	pthread_mutex_unlock(ph->flag_mutex);
	printf("%ld %ld %s\n", msg->time, msg->ph, msg->msg);
	ret = pthread_mutex_unlock(ph->print);
	return (ret);
}

int	count_up(t_thread *ph)
{
	ph->how_many_eat++;
	if (ph->info.num_must_eat && ph->how_many_eat == ph->info.num_must_eat)
	{
		pthread_mutex_lock(ph->count_mutex);
		*(ph->count_eat) = *(ph->count_eat) + 1;
		pthread_mutex_unlock(ph->count_mutex);
	}
	return (FUN_SUC);
}

int	lock_fork(pthread_mutex_t *fork, long *flag, int fork_flag)
{
	int	ret;

	ret = FUN_SUC;
	ret = pthread_mutex_lock(fork);
	*flag = fork_flag;
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
