/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdUSER.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:31 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/29 17:59:27 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void 	Server::cmdUser(std::vector<std::string> tokens, int fd) {

	std::cout << "cmdUser - 0" << std::endl;
	Client *c = getClientByFd(fd);
	
	//check the name/nick is set
	if (tokens.size() < 5) {
		// std::cout << "cmdUser - 1" << std::endl;
		c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
		return ;
	}

	if (c->getUsername() != "") {
		// std::cout << "cmdUser - 2" << std::endl;
		c->setReplyBuffer(ERR_ALREADYREGISTERED(c->getNickname()));
		return ;
	}

	if(tokens[4][0] == ':')
		tokens[4].erase(tokens[4].begin());

	std::string user = tokens[4];
	for (size_t i = 5; i < tokens.size(); i++)
		user = user + " " + tokens[i];
	
	c -> setUsername(user);
	if(c->getPassOk() && c->getNickname() != "" && c->getUsername() != "", !c->getCapOn()) {
		// std::cout << "cmdUser - 3" << std::endl;
		c->setReplyBuffer(RPL_WELCOME(c->getNickname(), c->getNickname(), c->getUsername(), c->getIp()));
	}
	
	std::cout << "cmdUser - X user=[" << c->getUsername() << "]" << std::endl;
}
