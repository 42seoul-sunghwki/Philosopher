/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:10:31 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/12 23:10:39 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_status(t_thread *ph, long start_eating, int flag)
{
	t_msg	msg;
	long	now;

	now = ft_microsec_now();
	msg.flag = flag;
	msg.ph = ph->ph_name;
	msg.print = ph->print;
	msg.time = (now - ph->start_time) / THOUSAND;
	pthread_mutex_lock(ph->count_mutex);
	if (*(ph->flag) == DIE)
	{
		pthread_mutex_unlock(ph->count_mutex);
		return (FUN_FAIL);
	}
	pthread_mutex_unlock(ph->count_mutex);
	if (flag == SLEEP)
		msg.msg = SLEEP_MSG;
	else if (flag == EAT)
	{
		msg.msg = EAT_MSG;
		count_up(ph);
		pthread_mutex_lock(ph->count_mutex);
		if (ph->info.num_must_eat && *(ph->count_eat) >= ph->info.num_must_eat)
		{
			if (msg_philo(ph, &msg) == FUN_FAIL)
			{
				pthread_mutex_unlock(ph->count_mutex);
				return (FUN_FAIL);
			}
			*(ph->flag) = DIE;
			pthread_mutex_unlock(ph->count_mutex);
			return (FUN_FAIL);
		}
		pthread_mutex_unlock(ph->count_mutex);
	}
	else if (flag == THINK)
		msg.msg = THINK_MSG;
	if (now - start_eating <= ph->info.time_to_die)
	{
		if (flag != NOT_CHECK)
			return (msg_philo(ph, &msg));
	}
	else
	{
		msg.msg = DIE_MSG;
		if (msg_philo(ph, &msg) == FUN_FAIL)
			return (FUN_FAIL);
		*(ph->flag) = DIE;
		return (FUN_FAIL);
	}
	return (FUN_SUC);
}
