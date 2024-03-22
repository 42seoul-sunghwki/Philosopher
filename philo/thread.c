/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:37 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/22 20:15:47 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_philo(t_thread *ph, long start_eating, long cmp_time)
{
	long	usec;

	while (1)
	{
		pthread_mutex_lock(ph->flag_mutex);
		if (*(ph->flag) == DIE)
		{
			pthread_mutex_unlock(ph->flag_mutex);
			return ;
		}
		else
			pthread_mutex_unlock(ph->flag_mutex);
		usec = ft_usec_now() - start_eating;
		if (usec >= cmp_time || usec >= ph->info.time_to_die)
			return ;
		if (cmp_time - usec > THOUSAND)
			usleep(800);
		else
			usleep(100);
	}
}

int	eating_philo(t_thread *ph, long start_eating)
{
	while (1)
	{
		pthread_mutex_lock(ph->left_fork);
		if (!(*ph->left_f))
		{
			*ph->left_f = ~(*ph->left_f);
			pthread_mutex_unlock(ph->left_fork);
			pthread_mutex_lock(ph->right_fork);
			if (*ph->right_f)
			{
				*ph->right_f = ~(*ph->right_f);
				pthread_mutex_unlock(ph->right_fork);
				if (check_status(ph, start_eating, TAKE) == FUN_FAIL)
					return (FUN_FAIL);
				if (check_status(ph, start_eating, TAKE) == FUN_FAIL)
					return (FUN_FAIL);
				break ;
			}
			else
			{
				pthread_mutex_unlock(ph->right_fork);
				pthread_mutex_lock(ph->left_fork);
				*ph->left_f = ~(*ph->left_f);
				pthread_mutex_unlock(ph->left_fork);
			}
		}
		else
			pthread_mutex_unlock(ph->left_fork);
		if (check_status(ph, start_eating, NOT_CHECK) == FUN_FAIL)
			return (FUN_FAIL);
		usleep(100);
	}
	return (FUN_SUC);
}

void	*philo(void *input)
{
	t_thread	ph;
	long		start_eating;

	ph = *(t_thread *)input;
	while (1)
	{
		start_eating = ft_usec_now();
		if (start_eating >= ph.start_time)
			break ;
		usleep(5);
	}
	while (1)
	{
		if (eating_philo(&ph, start_eating) == FUN_FAIL)
			return (NULL);
		start_eating = ft_usec_now();
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
