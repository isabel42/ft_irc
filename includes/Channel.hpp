/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:03:14 by itovar-n          #+#    #+#             */
/*   Updated: 2024/04/18 17:08:41 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Irc.hpp"

class Channel
{
	private:
		std::string _name;

	public:
		Channel();
		Channel(std::string name);
		~Channel();
		
		
	
}

#endif