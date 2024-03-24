/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_eating_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:45:26 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 19:39:21 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	take_fork_philo(t_philo *ph, long *start_usec)
{
	long		now_usec;

	while (TRUE)
	{
		now_usec = ft_usec_now();
		sem_wait(ph->flag_sem);
		if (*(ph->flag) == EAT)
		{
			*(ph->flag) = 0;
			sem_post(ph->flag_sem);
			print_msg(ph, now_usec - ph->info->start_time, EAT);
			*start_usec = now_usec;
			break ;
		}
		sem_post(ph->flag_sem);
		if (now_usec - *start_usec >= ph->info->time_to_die)
		{
			print_msg(ph, now_usec - ph->info->start_time, DIED);
			return (FUN_FAIL);
		}
		usleep(100);
	}
	return (FUN_SUC);
}

int	eating_philo(t_philo *ph, long *start_usec)
{
	pthread_t	pid;

	pthread_create(&pid, NULL, th_eating, (void *)ph);
	pthread_detach(pid);
	if (take_fork_philo(ph, start_usec) == FUN_FAIL)
		return (FUN_FAIL);
	if (stop_philo(ph, start_usec, ph->info->time_to_eat) == FUN_FAIL)
		return (FUN_FAIL);
	sem_post(ph->sem->fork);
	sem_post(ph->sem->fork);
	if (ph->info->num_must_eat > 0)
		ph->info->eat_count++;
	return (FUN_SUC);
}
