/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:29:21 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/21 15:12:44 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_msg(t_philo *ph, long usec, int flag)
{
	long	msec;
	
	sem_wait(ph->sem->print);
	printf("before die semaphore\n");
	sem_wait(ph->sem->die);
	sem_post(ph->sem->die);
	printf("after die semaphore\n");
	msec = usec / THOUSAND;
	if (flag == SLEEP)
		printf("%ld %ld is sleeping\n", msec, ph->info->name);
	else if (flag == EAT)
		printf("%ld %ld is eating\n", msec, ph->info->name);
	else if (flag == THINK)
		printf("%ld %ld is thinking\n", msec, ph->info->name);
	else if (flag == TAKE)
		printf("%ld %ld has taken a fork\n", msec, ph->info->name);
	else if (flag == UNTAKE)
		printf("%ld %ld has untaken a fork\n", msec, ph->info->name);
	else if (flag == DIED)
	{
		printf("%ld %ld died\n", msec, ph->info->name);
		sem_wait(ph->sem->die);
	}
	sem_post(ph->sem->print);
}

void	*th_eating(void *in)
{
	t_philo	*ph;

	ph = (t_philo *)in;
	printf("before wating\n");
	sem_wait(ph->sem->fork);
	printf("after waiting\n");
	print_msg(ph, ft_usec_now() - ph->info->start_time, TAKE);
	sem_wait(ph->sem->fork);
	print_msg(ph, ft_usec_now() - ph->info->start_time, TAKE);
	*(ph->flag) = EAT;
	if (ph->info->num_must_eat != -1)
		sem_wait(ph->sem->count);
	return (NULL);
}

//void	*th_sleeping(void *in)
//{
	
//}

//void	*th_thinking(void *in)
//{
	
//}
