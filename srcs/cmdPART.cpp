/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPART.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:11:12 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 18:30:54 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<std::string>	split_part(const std::string str, char delimiter) {
	std::vector<std::string>	v;
	std::stringstream			ss(str);
	std::string					element;

	while (std::getline(ss, element, delimiter)) {
		v.push_back(element);
	}

	return (v);
}

void	Server::cmdPart(std::vector<std::string> tokens, int fd) {
	std::vector<std::string>							channelsNames;
	std::vector<std::string>							channelsKeys;
	Channel *channel;
	std::stringstream msg;
	Client	*c = getClientByFd(fd);
	channelsNames = split_part(tokens[1], ',');
	std::cout << "PLS what is inside" << std::endl;
	printStringVector(tokens);
	if (tokens.size() > 2) {
		channelsKeys = split_part(tokens[2], ',');
		
		//printStringVector(channelsKeys);
	}
	std::cout << RED << "CHANS TO LEAVE:" << std::endl;
	printStringVector(channelsNames);
	 for (size_t i = 0; i < channelsNames.size(); i++)
	 {
		channel = getChannel(channelsNames[i]);
		if (!channel)
		{	
			c->setReplyBuffer(ERR_NOSUCHCHANNEL(c->getNickname(),channelsNames[i]));
			return ;
		}
			msg << c  -> getUserID() << " PART " << channelsNames[i];
			c -> deleteChannel(channelsNames[i]);
			channel -> deleteClient(c);
			channel -> setReplyBufferForAllChannelClients(msg.str());
			c -> setReplyBuffer(msg.str());
		}
	
	
}
