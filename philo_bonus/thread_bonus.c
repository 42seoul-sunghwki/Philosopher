/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:29:21 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/20 16:58:34 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_msg(t_philo *ph, long usec, int flag)
{
	sem_wait(ph->sem->print);
	sem_wait(ph->sem->die);
	sem_post(ph->sem->die);
	if (flag == SLEEP)
		printf("%lld %d is sleeping\n", usec, ph->info->philo_num);
	else if (flag == EAT)
		printf("%lld %d is eating\n", usec, ph->info->philo_num);
	else if (flag == THINK)
		printf("%lld %d is thinking\n", usec, ph->info->philo_num);
	else if (flag == TAKE)
		printf("%lld %d has taken a fork\n", usec, ph->info->philo_num);
	else if (flag == UNTAKE)
		printf("%lld %d has untaken a fork\n", usec, ph->info->philo_num);
	else if (flag == DIE)
	{
		printf("%lld %d died\n", usec, ph->info->philo_num);
		sem_wait(ph->sem->die);
	}
	sem_post(ph->sem->print);
}

void	*th_eating(void *in)
{
	
}

//void	*th_sleeping(void *in)
//{
	
//}

//void	*th_thinking(void *in)
//{
	
//}
