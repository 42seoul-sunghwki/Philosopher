/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:25:16 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/20 17:04:18 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	eating_philo(t_philo *ph, long *start_usec)
{
	pid_t	pid;
	long	now_usec;

	pthread_create(&pid, NULL, th_eating, &ph);
	pthread_detach(pid);
	while (TRUE)
	{
		now_usec = ft_usec_now();
		if (ph->flag == EAT)
		{
			print_msg(ph, now_usec, EAT);
			*start_usec = now_usec;
			return (FUN_SUC);
		}
		if (now_usec - *start_usec >= ph->info->time_to_die)
		{
			print_msg(ph, now_usec, DIE);
			return (FUN_FAIL);
		}
		usleep(100);
	}
}

static int	thinking_philo(t_philo *ph, long *start_usec)
{
	long	now_usec;

	now_usec = ft_usec_now();
	print_msg(ph, now_usec - *start_usec, THINK);
	while (TRUE)
	{
		now_usec = ft_usec_now();
		if (now_usec - *start_usec >= ph->info->time_to_die)
		{
			print_msg(ph, now_usec - *start_usec, DIE);
			return (FUN_FAIL);
		}
		else if (now_usec - *start_usec >= ph->info->time_to_sleep)
		{
			return (FUN_SUC);
		}
		usleep(100);
	}
}

static int	sleeping_philo(t_philo *ph, long *start_usec)
{
	long	now_usec;

	now_usec = ft_usec_now();
	print_msg(ph, now_usec - *start_usec, THINK);
	while (TRUE)
	{
		now_usec = ft_usec_now();
		if (now_usec - *start_usec >= ph->info->time_to_die)
		{
			print_msg(ph, now_usec - *start_usec, DIE);
			return (FUN_FAIL);
		}
		else if (now_usec - *start_usec >= ph->info->time_to_sleep)
		{
			return (FUN_SUC);
		}
		usleep(100);
	}
}

int	philo(t_info *info, t_sem *sem)
{
	int		flag;
	long	start_usec;
	t_philo	ph;

	flag = 0;
	ph.info = info;
	ph.sem = sem;
	ph.flag = &flag;
	start_usec = ft_usec_now();
	while (TRUE)
	{
		if (eating_philo(&ph, &start_usec) == FUN_FAIL)
			exit (FUN_FAIL);
		if (thinking_philo(&ph, &start_usec) == FUN_FAIL)
			exit (FUN_FAIL);
		if (sleeping_philo(&ph, &start_usec) == FUN_FAIL)
			exit (FUN_FAIL);
	}
	exit (FUN_SUC);
}
