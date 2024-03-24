/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:29:21 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 18:30:48 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*th_eating(void *in)
{
	t_philo	*ph;

	ph = (t_philo *)in;
	sem_wait(ph->sem->be_fork);
	sem_wait(ph->sem->fork);
	print_msg(ph, ft_usec_now() - ph->info->start_time, TAKE);
	sem_wait(ph->sem->fork);
	print_msg(ph, ft_usec_now() - ph->info->start_time, TAKE);
	sem_post(ph->sem->be_fork);
	sem_wait(ph->flag_sem);
	*(ph->flag) = EAT;
	sem_post(ph->flag_sem);
	return (NULL);
}

void	*th_philo_eating(void *in)
{
	t_philo	*ph;

	ph = (t_philo *)in;
	sem_wait(ph->sem->print);
	sem_wait(ph->sem->count);
	sem_wait(ph->flag_sem);
	*(ph->flag) = TAKE;
	sem_post(ph->flag_sem);
	sem_post(ph->sem->count);
	sem_post(ph->sem->print);
	return (NULL);
}
