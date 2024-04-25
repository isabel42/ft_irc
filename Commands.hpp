/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:16:18 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/25 15:21:01 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

struct cmd_struct
{
	std::string	prefix;
	std::string	name;
	std::string	message;
};

int			parseCommand(std::string cmd_line, cmd_struct &cmd_infos);

#endif