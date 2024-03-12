/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:37 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/12 15:08:26 by sunghwki         ###   ########.fr       */
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
	if (flag == SLEEP)
		msg.msg = SLEEP_MSG;
	else if (flag == EAT)
	{
		msg.msg = EAT_MSG;
		count_up(ph);
		pthread_mutex_lock(ph->count_mutex);
		if (ph->info.num_must_eat && *(ph->count_eat) >= ph->info.num_must_eat)
		{
			msg_philo(ph, &msg);
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
		msg_philo(ph, &msg);
		*(ph->flag) = DIE;
		return (FUN_FAIL);
	}
	return (FUN_SUC);
}

int	odd_philo(t_thread *ph, long start_eating)
{
	while (1)
	{
		if (*ph->left_f == FALSE)
		{
			lock_fork(ph->left_fork, ph->left_f, TRUE);
			if (*ph->right_f == FALSE)
			{
				lock_fork(ph->right_fork, ph->right_f, TRUE);
				break ;
			}
			else
				lock_fork(ph->left_fork, ph->left_f, FALSE);
		}
		if (check_status(ph, start_eating, NOT_CHECK) == FUN_FAIL)
			return (FUN_FAIL);
		usleep(100);
	}
	return (FUN_SUC);
}

int	even_philo(t_thread *ph, long start_eating)
{
	while (1)
	{
		if (*ph->right_f == FALSE)
		{
			lock_fork(ph->right_fork, ph->right_f, TRUE);
			if (*ph->left_f == FALSE)
			{
				lock_fork(ph->left_fork, ph->left_f, TRUE);
				break ;
			}
			else
				lock_fork(ph->right_fork, ph->right_f, FALSE);
		}
		if (check_status(ph, start_eating, NOT_CHECK) == FUN_FAIL)
			return (FUN_FAIL);
		usleep(100);
	}
	return (FUN_SUC);
}

void	sleep_philo(t_thread *ph, long start_eating, long cmp_time)
{
	long	microsec;

	while (1)
	{
		microsec = ft_microsec_now() - start_eating;
		if (microsec >= cmp_time || microsec >= ph->info.time_to_die
			|| *(ph->flag) == DIE)
			break ;
		else if (cmp_time - microsec >= THOUSAND)
			usleep(THOUSAND / 2);
		else
			usleep(100);
	}
}

int	eating_philo(t_thread *ph, long start_eating)
{
	if (ph->ph_name % 2 == 0)
	{
		if (even_philo(ph, start_eating) == FUN_FAIL)
			return (FUN_FAIL);
	}
	else
	{
		if (odd_philo(ph, start_eating) == FUN_FAIL)
			return (FUN_FAIL);
	}
	return (FUN_SUC);
}

void	*philo(void *input)
{
	t_thread	ph;
	long		start_eating;

	ph = *(t_thread *)input;
	if (ph.ph_name % 2 == 0)
		usleep(200);
	start_eating = ft_microsec_now();
	while (1)
	{
		if (eating_philo(&ph, start_eating) == FUN_FAIL)
			return (NULL);
		start_eating = ft_microsec_now();
		if (check_status(&ph, start_eating, EAT) == FUN_FAIL)
			return (NULL);
		sleep_philo(&ph, start_eating, ph.info.time_to_eat);
		lock_fork(ph.left_fork, ph.left_f, FALSE);
		lock_fork(ph.right_fork, ph.right_f, FALSE);
		if (check_status(&ph, start_eating, SLEEP) == FUN_FAIL)
			return (NULL);
		sleep_philo(&ph, start_eating, ph.info.time_to_sleep
			+ ph.info.time_to_eat);
		if (check_status(&ph, start_eating, THINK) == FUN_FAIL)
			return (NULL);
	}
}
