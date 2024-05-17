/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:03:03 by itovar-n          #+#    #+#             */
/*   Updated: 2024/05/17 16:34:26 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Utils.hpp"

void splitMessage(std::vector<std::string> &cmds, std::string msg, std::string delimeter)
{
	int pos = 0;
	std::string substr;
	
	if ((pos = msg.find(delimeter)) == static_cast<int>(std::string::npos))
		cmds.push_back(msg);

	while ((pos = msg.find(delimeter)) != static_cast<int>(std::string::npos))
	{
		substr = msg.substr(0, pos);
		cmds.push_back(substr);
		msg.erase(0, pos + delimeter.length());
	}
}