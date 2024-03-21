/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:10:31 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/21 21:12:07 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	flag_eat_status(t_thread *ph, t_msg *msg)
{
	msg->msg = EAT_MSG;
	count_up(ph);
	//pthread_mutex_lock(ph->count_mutex);
	//if (ph->info.num_must_eat && *(ph->count_eat) >= ph->info.num_must_eat)
	//{
	//	if (msg_philo(ph, msg) == FUN_FAIL)
	//	{
	//		pthread_mutex_unlock(ph->count_mutex);
	//		return (FUN_FAIL);
	//	}
	//	pthread_mutex_lock(ph->flag_mutex);
	//	*(ph->flag) = DIE;
	//	pthread_mutex_unlock(ph->flag_mutex);
	//	pthread_mutex_unlock(ph->count_mutex);
	//	return (FUN_FAIL);
	//}
	//pthread_mutex_unlock(ph->count_mutex);
	return (FUN_SUC);
}

static int	flag_check_status(t_thread *ph, t_msg *msg, int flag, long long now)
{
	msg->flag = flag;
	msg->ph = ph->ph_name;
	msg->print = ph->print;
	msg->time = (now - ph->start_time) / THOUSAND;
	if (flag == SLEEP)
		msg->msg = SLEEP_MSG;
	else if (flag == EAT)
	{
		if (flag_eat_status(ph, msg) == FUN_FAIL)
			return (FUN_FAIL);
	}
	else if (flag == THINK)
	{
		printf("how_many_eat: %ld\n", ph->how_many_eat);
		pthread_mutex_lock(ph->count_mutex);
		if (ph->info.num_must_eat > 0 && ph->info.num_must_eat == ph->how_many_eat)
		{
			pthread_mutex_unlock(ph->count_mutex);
			return (FUN_FAIL);
		}
		else
			pthread_mutex_unlock(ph->count_mutex);
		msg->msg = THINK_MSG;
	}
	else if (flag == TAKE)
		msg->msg = TAKE_MSG;
	else if (flag == UNTAKE)
		msg->msg = UNTAKE_MSG;
	return (FUN_SUC);
}

static int	check_die(t_thread *ph)
{
	pthread_mutex_lock(ph->count_mutex);
	pthread_mutex_lock(ph->flag_mutex);
	if (*(ph->flag) == DIE)
	{
		pthread_mutex_unlock(ph->flag_mutex);
		pthread_mutex_unlock(ph->count_mutex);
		return (FUN_FAIL);
	}
	pthread_mutex_unlock(ph->flag_mutex);
	pthread_mutex_unlock(ph->count_mutex);
	return (FUN_SUC);
}

int	check_status(t_thread *ph, long start_eating, int flag)
{
	t_msg	msg;
	long	now;

	now = ft_usec_now();
	if (check_die(ph) == FUN_FAIL)
		return (FUN_FAIL);
	if (flag_check_status(ph, &msg, flag, now) == FUN_FAIL)
		return (FUN_FAIL);
	if (now - start_eating <= ph->info.time_to_die)
	{
		if (flag != NOT_CHECK)
			return (msg_philo(ph, &msg));
	}
	else
	{
		msg.msg = DIE_MSG;
		msg_philo(ph, &msg);
		pthread_mutex_lock(ph->flag_mutex);
		*(ph->flag) = DIE;
		pthread_mutex_unlock(ph->flag_mutex);
		return (FUN_FAIL);
	}
	return (FUN_SUC);
}
