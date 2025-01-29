/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPASS.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:28 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/29 17:59:46 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdPass(std::vector<std::string> tokens, int fd) {
	// std::cout << "cmdPass - 0" << std::endl;
	Client *c = getClientByFd(fd);
	
	if(c->getPassOk()) {
		// std::cout << "cmdPass - 1" << std::endl; 
		c->setReplyBuffer(ERR_ALREADYREGISTERED(c->getNickname()));
		return ;
	}

	if(tokens.size() < 2 || tokens[1] == "") {
		// std::cout << "cmdPass - 2" << std::endl; 
		c->setReplyBuffer(ERR_NEEDMOREPARAMS(c->getNickname(), tokens[0]));
		return ;
	}

	if(tokens[1] != _password) {
		// std::cout << "cmdPass - 3" << std::endl; 
		c->setReplyBuffer(ERR_PASSWDMISMATCH(c->getNickname()));					// WE MUST KICK IT
		return ;
	}

	c->setPassOk(true);
	
	if(c->getPassOk() && c->getNickname() != "" && c->getUsername() != "", !c->getCapOn()) {
		// std::cout << "cmdPass - 4" << std::endl; 
		c->setReplyBuffer(RPL_WELCOME(c->getNickname(), c->getNickname(), c->getUsername(), c->getIp()));
	}
		
	std::cout << "cmdPass - X ok" << std::endl; 

}
