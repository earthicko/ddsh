/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:19 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:42:29 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_COMMANDS_H
# define BUILTIN_COMMANDS_H

int	builtin_echo(char **argv);
int	builtin_cd(char **argv);
int	builtin_pwd(char **argv);
int	builtin_export(char **argv);
int	builtin_unset(char **argv);
int	builtin_env(char **argv);
int	builtin_exit(char **argv);

int	builtin_getindex(char *name);
int	builtin_exec_by_name(char *name, char **argv);

#endif
