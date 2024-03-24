/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:25:16 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 16:16:41 by sunghwki         ###   ########.fr       */
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

int	philo(t_info *info, t_sem *sem)
{
	int		flag;
	char	*flag_name;
	long	start_usec;
	t_philo	ph;

	flag = 0;
	ph.info = info;
	ph.sem = sem;
	ph.flag = &flag;
	flag_name = sem_flag_name(&ph);
	sem_unlink(flag_name);
	ph.flag_sem = sem_open(flag_name, O_CREAT, 0644, 1);
	free(flag_name);
	start_usec = ft_usec_now();
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
