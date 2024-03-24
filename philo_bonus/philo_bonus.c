/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:25:16 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 19:02:21 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*sem_flag_name(t_philo *ph)
{
	char	*tmp;
	char	*fork_name;

	tmp = ft_itoa(ph->info->name);
	fork_name = ft_strjoin(FLAG, tmp);
	free(tmp);
	return (fork_name);
}

static void	philo_sem_flag_init(t_philo *ph)
{
	char	*flag_name;

	flag_name = sem_flag_name(ph);
	sem_unlink(flag_name);
	ph->flag_sem = sem_open(flag_name, O_CREAT, 0644, 1);
	free(flag_name);
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
	philo_sem_flag_init(&ph);
	while (TRUE)
	{
		if (eating_philo(&ph, &start_usec) == FUN_FAIL)
			break ;
		if (sleeping_philo(&ph, &start_usec) == FUN_FAIL)
			break ;
		if (thinking_philo(&ph) == FUN_FAIL)
			break ;
	}
	sem_close(ph.flag_sem);
	ft_unlink_sem(&sem);
	exit (FUN_SUC);
}
