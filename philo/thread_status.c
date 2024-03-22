/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:39:03 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/22 17:27:49 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	odd_philo_right_fork(t_thread *ph, long start_eating)
{
	pthread_mutex_lock(ph->right_fork);
	if (*ph->right_f == FALSE)
	{
		*ph->right_f = TRUE;
		pthread_mutex_unlock(ph->right_fork);
		//lock_fork(ph->right_fork, ph->right_f, TRUE);
		if (check_status(ph, start_eating, TAKE) == FUN_FAIL)
			return (FUN_FAIL);
		if (check_status(ph, start_eating, TAKE) == FUN_FAIL)
			return (FUN_FAIL);
		return (-1);
	}
	else
	{
		pthread_mutex_unlock(ph->right_fork);
		lock_fork(ph->left_fork, ph->left_f, FALSE);
		return (FUN_SUC);
	}
}

int	odd_philo(t_thread *ph, long start_eating)
{
	int	ret;

	while (1)
	{
		pthread_mutex_lock(ph->left_fork);
		if (*ph->left_f == FALSE)
		{
			*ph->left_f = TRUE;
			pthread_mutex_unlock(ph->left_fork);
			//lock_fork(ph->left_fork, ph->left_f, TRUE);
			ret = odd_philo_right_fork(ph, start_eating);
			if (ret == FUN_FAIL)
				return (FUN_FAIL);
			else if (ret == -1)
				break ;
		}
		else
			pthread_mutex_unlock(ph->left_fork);
		if (check_status(ph, start_eating, NOT_CHECK) == FUN_FAIL)
			return (FUN_FAIL);
		usleep(100);
	}
	return (FUN_SUC);
}

static int	even_philo_left_fork(t_thread *ph, long start_eating)
{
	pthread_mutex_lock(ph->left_fork);
	if (*ph->left_f == FALSE)
	{
		*ph->left_f = TRUE;
		pthread_mutex_unlock(ph->left_fork);
		//lock_fork(ph->left_fork, ph->left_f, TRUE);
		if (check_status(ph, start_eating, TAKE) == FUN_FAIL)
			return (FUN_FAIL);
		if (check_status(ph, start_eating, TAKE) == FUN_FAIL)
			return (FUN_FAIL);
		return (-1);
	}
	else
	{
		pthread_mutex_unlock(ph->left_fork);
		lock_fork(ph->right_fork, ph->right_f, FALSE);
		return (FUN_SUC);
	}
}

int	even_philo(t_thread *ph, long start_eating)
{
	int	ret;

	while (1)
	{
		pthread_mutex_lock(ph->right_fork);
		if (*ph->right_f == FALSE)
		{
			*ph->right_f = TRUE;
			pthread_mutex_unlock(ph->right_fork);
			//lock_fork(ph->right_fork, ph->right_f, TRUE);
			ret = even_philo_left_fork(ph, start_eating);
			if (ret == FUN_FAIL)
				return (FUN_FAIL);
			else if (ret == -1)
				break ;
		}
		else
			pthread_mutex_unlock(ph->right_fork);
		if (check_status(ph, start_eating, NOT_CHECK) == FUN_FAIL)
			return (FUN_FAIL);
		usleep(100);
	}
	return (FUN_SUC);
}
