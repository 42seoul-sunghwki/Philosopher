/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:25:16 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 15:05:59 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		if (sleeping_philo(&ph, &start_usec) == FUN_FAIL)
			exit (FUN_FAIL);
		if (thinking_philo(&ph) == FUN_FAIL)
			exit (FUN_FAIL);
	}
	exit (FUN_SUC);
}
