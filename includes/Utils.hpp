/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:02:24 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/14 16:50:57 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP
#include "Irc.hpp"


void splitMessage(std::vector<std::string> &cmds, std::string msg, std::string delimeter);

std::string	getChannelName(std::string msg_to_parse);


#endif