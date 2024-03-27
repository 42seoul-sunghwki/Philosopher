/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:10:16 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/27 11:15:20 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_philo(t_thread *ph, long start_eating, long cmp_time)
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
			usleep(500);
		else
			usleep(100);
	}
}

static int	eating_philo_right_fork(t_thread *ph, long start_eating)
{
	pthread_mutex_lock(ph->right_fork);
	if (*ph->right_f)
	{
		pthread_mutex_unlock(ph->right_fork);
		if (check_status(ph, start_eating, TAKE) == FUN_FAIL)
			return (FUN_FAIL);
		if (check_status(ph, start_eating, TAKE) == FUN_FAIL)
			return (FUN_FAIL);
		return (FUN_SUC);
	}
	else
		pthread_mutex_unlock(ph->right_fork);
	return (-1);
}

int	eating_philo(t_thread *ph, long *start_eating)
{
	int	ret;

	while (1)
	{
		pthread_mutex_lock(ph->left_fork);
		if (!(*ph->left_f))
		{
			pthread_mutex_unlock(ph->left_fork);
			ret = eating_philo_right_fork(ph, *start_eating);
			if (ret == FUN_SUC)
				break ;
			if (ret == FUN_FAIL)
				return (FUN_FAIL);
		}
		else
			pthread_mutex_unlock(ph->left_fork);
		if (check_status(ph, *start_eating, NOT_CHECK) == FUN_FAIL)
			return (FUN_FAIL);
		usleep(100);
	}
	*start_eating = ft_usec_now();
	if (check_status(ph, *start_eating, EAT) == FUN_FAIL)
		return (FUN_FAIL);
	stop_philo(ph, *start_eating, ph->info.time_to_eat);
	return (FUN_SUC);
}

int	sleeping_philo(t_thread *ph, long start_eating)
{
	change_lock_fork(ph->left_fork, ph->left_f);
	change_lock_fork(ph->right_fork, ph->right_f);
	if (check_status(ph, start_eating, SLEEP) == FUN_FAIL)
		return (FUN_FAIL);
	stop_philo(ph, start_eating, ph->info.time_to_sleep
		+ ph->info.time_to_eat);
	return (FUN_SUC);
}

int	thinking_philo(t_thread *ph, long start_eating)
{
	if (check_status(ph, start_eating, THINK) == FUN_FAIL)
		return (FUN_FAIL);
	return (FUN_SUC);
}
