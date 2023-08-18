/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:42:19 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:42:29 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_COMMANDS_H
# define BUILTIN_COMMANDS_H

int	builtin_echo(char **argv);
int	builtin_cd(char **argv);
int	builtin_pwd(char **argv);
int	builtin_export(char **argv);
int	builtin_declare(char **argv);
int	builtin_unset(char **argv);
int	builtin_exit(char **argv);
int	builtin_dot(char **argv);

int	builtin_getindex(char *name);
int	builtin_exec_by_name(char *name, char **argv);

#endif
