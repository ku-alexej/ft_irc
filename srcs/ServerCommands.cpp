/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:52:12 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/29 16:18:35 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string	toLower(std::string str) {
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = std::tolower(str[i]);
		else if (str[i] == '[')
			str[i] = '{';
		else if (str[i] == ']')
			str[i] = '}';
		else if (str[i] == '~')
			str[i] = '^';
	}
	return (str);
}

void    Server::exec(std::string cmd, int fd) {
	std::vector<std::string> tokens;
	tokens = splitIrssiCommandinToken(cmd);
	
	std::cout << "[INFO]: " << GRN << "token=" << RES;
	printStringVector(tokens);
	
	std::cout << "[INFO]: try to handle \'" << YEL << tokens[0] << RES << "\'" << std::endl;
	if (tokens[0] == "CAP")
		cmdCap(tokens, fd);
	if (tokens[0] == "PASS")
		cmdPass(tokens, fd);
	if (tokens[0] == "NICK")
	    cmdNick(tokens, fd);
	if (tokens[0] == "USER")
	    cmdUser(tokens, fd);
	if (tokens[0] == "PING")
		cmdPing(tokens,fd);
}

void	Server::cmdPing(std::vector<std::string> tokens, int fd) {
	Client *client = getClientByFd(fd);
	(tokens.size() > 1) ? client->setReplyBuffer("PONG " + tokens[1]) : client->setReplyBuffer("PONG");
}

void	Server::cmdCap(std::vector<std::string> tokens, int fd) {

	std::cout << "cmdCap - 0" << std::endl;
	Client *client = getClientByFd(fd);
	
	if (tokens.size() < 2) {
		return ;
	}
	
	if (tokens[1] == "LS") {
		client->setCapOn(true);
		client->setReplyBuffer("CAP * LS :");
		return ;
	}
	
	if (tokens[1] == "END") {
		client->setCapOn(false);		
		if (client->getPassOk() && client->getNickname() != "" && client->getUsername() != "")
				client->setReplyBuffer(RPL_WELCOME(client->getNickname(), client->getNickname(), client->getUsername(), client->getIp()));	
	}
	
	std::cout << "cmdCap - X [" << client->getUsername() << "]" << std::endl;
}

void	Server::cmdNick(std::vector<std::string> tokens, int fd) {
	
	// std::cout << "cmdNick - 0" << std::endl;
	//check the name/nick is set
	Client *client = getClientByFd(fd);
	
	if (tokens.size() < 2 || tokens[1].empty()) {
		// std::cout << "cmdNick - 1" << std::endl;
		client->setReplyBuffer(ERR_NONICKNAMEGIVEN(client->getNickname()));
		// std::cout << "[NICK] is not defined" << std::endl;
		return ;
	}
	
	if (tokens[1].find_first_not_of("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ~[]{}^") != std::string::npos) {
		// std::cout << "cmdNick - 2" << std::endl;
		client->setReplyBuffer(ERR_ERRONEUSNICKNAME(client->getNickname(), tokens[1]));
		return ;
	}

	for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (toLower(tokens[1]) == toLower(it->getNickname())) {
			// std::cout << "cmdNick - 3" << std::endl;
			client->setReplyBuffer(ERR_NICKNAMEINUSE(client->getNickname(), tokens[1]));
			return ;
		}
	}
		
	client->setNickname(tokens[1]);
	if(client->getPassOk() && client->getNickname() != "" && client->getUsername() != "", !client->getCapOn()) {
		// std::cout << "cmdNick - 4" << std::endl;
		client->setReplyBuffer(RPL_WELCOME(client->getNickname(), client->getNickname(), client->getUsername(), client->getIp()));
	}
	std::cout << "cmdNick - X nick=[" << client->getNickname() << "]" << std::endl;
}

void 	Server::cmdUser(std::vector<std::string> tokens, int fd) {

	std::cout << "cmdUser - 0" << std::endl;
	Client *client = getClientByFd(fd);
	
	//check the name/nick is set
	if (tokens.size() < 5) {
		// std::cout << "cmdUser - 1" << std::endl;
		client->setReplyBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), tokens[0]));
		return ;
	}

	if (client->getUsername() != "") {
		// std::cout << "cmdUser - 2" << std::endl;
		client->setReplyBuffer(ERR_ALREADYREGISTERED(client->getNickname()));
		return ;
	}

	if(tokens[4][0] == ':')
		tokens[4].erase(tokens[4].begin());

	std::string user = tokens[4];
	for (size_t i = 5; i < tokens.size(); i++)
		user = user + " " + tokens[i];
	
	client -> setUsername(user);
	if(client->getPassOk() && client->getNickname() != "" && client->getUsername() != "", !client->getCapOn()) {
		// std::cout << "cmdUser - 3" << std::endl;
		client->setReplyBuffer(RPL_WELCOME(client->getNickname(), client->getNickname(), client->getUsername(), client->getIp()));
	}
	
	std::cout << "cmdUser - X user=[" << client->getUsername() << "]" << std::endl;
}

void	Server::cmdPass(std::vector<std::string> tokens, int fd) {
	// std::cout << "cmdPass - 0" << std::endl;
	Client *client = getClientByFd(fd);
	
	if(client->getPassOk()) {
		// std::cout << "cmdPass - 1" << std::endl; 
		client->setReplyBuffer(ERR_ALREADYREGISTERED(client->getNickname()));
		return ;
	}

	if(tokens.size() < 2 || tokens[1] == "") {
		// std::cout << "cmdPass - 2" << std::endl; 
		client->setReplyBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), tokens[0]));
		return ;
	}

	if(tokens[1] != _password) {
		// std::cout << "cmdPass - 3" << std::endl; 
		client->setReplyBuffer(ERR_PASSWDMISMATCH(client->getNickname()));					// WE MUST KICK IT
		return ;
	}

	client->setPassOk(true);
	
	if(client->getPassOk() && client->getNickname() != "" && client->getUsername() != "", !client->getCapOn()) {
		// std::cout << "cmdPass - 4" << std::endl; 
		client->setReplyBuffer(RPL_WELCOME(client->getNickname(), client->getNickname(), client->getUsername(), client->getIp()));
	}
		
	std::cout << "cmdPass - X ok" << std::endl; 

}
