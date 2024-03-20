/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:04:32 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/20 15:18:20 by sunghwki         ###   ########.fr       */
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
	while (num < info->philo_num)
	{
		pid[num] = fork();
		if (pid[num] == 0)
		{
			philo(info, sem);
			exit (FUN_SUC);
		}
		num++;
	}
	if (waitpid(-1, NULL, 0) == -1)
	{
		kill(-1, SIGKILL);
		free(pid);
	}
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
	ft_unlink_sem(sem);
	return (0);
}
