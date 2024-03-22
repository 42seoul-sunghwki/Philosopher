/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:10:31 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/22 21:09:54 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	flag_think_status(t_thread *ph, t_msg *msg)
{
	if (ph->info.num_must_eat > 0 && ph->info.num_must_eat == ph->how_many_eat)
	{
		pthread_mutex_lock(ph->count_mutex);
		*(ph->count_eat) = *(ph->count_eat) + 1;
		if (*(ph->count_eat) == ph->info.num_philo)
		{
			pthread_mutex_lock(ph->flag_mutex);
			*(ph->flag) = DIE;
			pthread_mutex_unlock(ph->flag_mutex);
		}
		pthread_mutex_unlock(ph->count_mutex);
		return (FUN_FAIL);
	}
	else
	{
		msg->msg = THINK_MSG;
		return (FUN_SUC);
	}
}

static int	flag_check_status(t_thread *ph, t_msg *msg, int flag)
{
	msg->flag = flag;
	msg->ph = ph->ph_name;
	msg->print = ph->print;
	if (flag == SLEEP)
		msg->msg = SLEEP_MSG;
	else if (flag == EAT)
	{
		msg->msg = EAT_MSG;
		ph->how_many_eat++;
	}
	else if (flag == THINK)
	{
		if (flag_think_status(ph, msg) == FUN_FAIL)
			return (FUN_FAIL);
	}
	else if (flag == TAKE)
		msg->msg = TAKE_MSG;
	else if (flag == UNTAKE)
		msg->msg = UNTAKE_MSG;
	return (FUN_SUC);
}

static int	check_die(t_thread *ph)
{
	pthread_mutex_lock(ph->flag_mutex);
	if (*(ph->flag) == DIE)
	{
		pthread_mutex_unlock(ph->flag_mutex);
		return (FUN_FAIL);
	}
	else
	{
		pthread_mutex_unlock(ph->flag_mutex);
		return (FUN_SUC);
	}
}

int	check_status(t_thread *ph, long start_eating, int flag)
{
	t_msg	msg;

	if (check_die(ph) == FUN_FAIL)
		return (FUN_FAIL);
	if (flag_check_status(ph, &msg, flag) == FUN_FAIL)
		return (FUN_FAIL);
	if (ft_usec_now() - start_eating <= ph->info.time_to_die)
	{
		if (flag != NOT_CHECK)
			return (msg_philo(ph, &msg));
	}
	else
	{
		pthread_mutex_lock(ph->flag_mutex);
		if (*(ph->flag) != DIE)
		{
			*(ph->flag) = DIE;
			printf("%ld %ld %s\n", (ft_usec_now() - ph->start_time)
				/ THOUSAND, ph->ph_name, DIE_MSG);
		}
		pthread_mutex_unlock(ph->flag_mutex);
		return (FUN_FAIL);
	}
	return (FUN_SUC);
}
