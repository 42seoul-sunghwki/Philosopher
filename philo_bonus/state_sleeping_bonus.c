/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_sleeping_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:50:08 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 18:50:28 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_philo_eating(t_philo *ph)
{
	pthread_t	pid;
	long		now_usec;

	sem_wait(ph->sem->count);
	pthread_create(&pid, NULL, th_philo_eating, (void *)ph);
	pthread_detach(pid);
	now_usec = ft_usec_now();
	while (TRUE)
	{
		sem_wait(ph->flag_sem);
		if (*(ph->flag) == TAKE)
		{
			*(ph->flag) = 0;
			sem_post(ph->flag_sem);
			break ;
		}
		else
			sem_post(ph->flag_sem);
		if (ft_usec_now() - now_usec >= 3 * THOUSAND)
			exit(FUN_FAIL);
		usleep(100);
	}
	return (FUN_SUC);
}

int	sleeping_philo(t_philo *ph, long *start_usec)
{
	long	now_usec;
	long	cmp_time;

	if (ph->info->num_must_eat > 0 && ph->info->eat_count
		== ph->info->num_must_eat)
	{
		if (check_philo_eating(ph) == FUN_FAIL)
			return (FUN_FAIL);
	}
	now_usec = ft_usec_now();
	cmp_time = ph->info->time_to_eat + ph->info->time_to_sleep;
	print_msg(ph, now_usec - ph->info->start_time, SLEEP);
	if (stop_philo(ph, start_usec, cmp_time) == FUN_FAIL)
		return (FUN_FAIL);
	return (FUN_SUC);
}
