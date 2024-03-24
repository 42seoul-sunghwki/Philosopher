/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:04:32 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/24 15:23:06 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_simulation(t_info *info, t_sem *sem)
{
	int	*pid;
	int	num;

	pid = (int *)malloc(sizeof(int) * info->philo_num);
	if (!pid)
		return ;
	num = 0;
	info->start_time = ft_usec_now();
	while (num < info->philo_num)
	{
		info->name = num + 1;
		pid[num] = fork();
		if (pid[num] == 0)
			philo(info, sem);
		num++;
	}
	if (waitpid(0, NULL, 0))
	{
		while (--(info->philo_num))
		{
			kill(pid[info->philo_num], SIGKILL);
		}
	}
	free(pid);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_sem	*sem;

	if (ft_init_info(&info, argc, argv) == FUN_FAIL)
		return (FUN_FAIL);
	sem = ft_init_sem(&info);
	if (sem == NULL)
		return (FUN_FAIL);
	start_simulation(&info, sem);
	ft_unlink_sem(&sem);
	return (0);
}
