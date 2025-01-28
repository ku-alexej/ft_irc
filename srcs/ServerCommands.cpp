/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:12 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/28 19:05:42 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void    Server::exec(std::string cmd, int fd) {
	std::vector<std::string> tokens;
	(void) fd;
	tokens = splitIrssiCommandinToken(cmd);
	
	std::cout << "[INFO]: " << GRN << "token=" << RES;
	printStringVector(tokens);

	if (tokens[0] == "PASS")
		cmdPass(tokens, fd);
	// if (tokens[0] == "NAME")
	//     cmdName();
}


void	Server::cmdPass(std::vector<std::string> tokens, int fd) {
	std::cout << "cmdPass - 0" << std::endl;
	Client *client = getClientByFd(fd);
	
	if(client->getPassOk()) {
		std::cout << "cmdPass - 1" << std::endl; 
		client->setReplyBuffer(ERR_ALREADYREGISTERED(client->getNickname()));
		return ;
	}

	if(tokens.size() < 2 || tokens[1] == "") {
		std::cout << "cmdPass - 2" << std::endl; 
		client->setReplyBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), tokens[0]));
		return ;
	}

	if(tokens[1] != _password) {
		std::cout << "cmdPass - 3" << std::endl; 
		client->setReplyBuffer(ERR_PASSWDMISMATCH(client->getNickname()));					// WE MUST KICK IT
		return ;
	}

	client->setPassOk(true);
	
	if(client->getPassOk() && client->getNickname() != "" && client->getUsername() != "") {// we need to check is CAP command in progress or is done [&& !client->getCapOk()]
		std::cout << "cmdPass - 4" << std::endl;  // change to reply
		// getHostName - need to add function =(
		// client->setReplyBuffer(RPL_WELCOME(client->getNickname(), client->getNickname(), client->getUsername(), client->getHostName()));
	}
		
	std::cout << "cmdPass - X" << std::endl; 

}
