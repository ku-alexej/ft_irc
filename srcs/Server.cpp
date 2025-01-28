/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:17 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/28 15:51:56 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// --- constructors ---
Server::Server() {

}

Server::Server(const Server &src) {
	(void) src;
}

Server::Server(int port, std::string password) {
	_port = port;
	_password = password;
	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_addr.s_addr = INADDR_ANY;
	_serverAddress.sin_port = htons(_port);
	_fd = socket(AF_INET, SOCK_STREAM, 0);
}

// --- operators ---
Server	&Server::operator=(const Server &src) {
	(void) src;
	return (*this);
}

// --- destructors ---
Server::~Server() {

}

// --- getters ---

// --- setters ---

// --- reply ---
// static size_t	reply(std::string msg, int fd) {
// 	if (msg[msg.size() - 1] != '\n')
// 		msg += "\n";

// 	ssize_t	sent_size = send(fd, msg.c_str(), msg.length(), 0);
// 	if(sent_size != (ssize_t) msg.length())
// 		std::cout << "[ERROR]: The message has not been sent entirely." << std::endl;
// 	return (sent_size);
// }

void showMsg(int fd) {
	char buff[512]; 
	memset(buff, 0, sizeof(buff)); 

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1 , 0); 

	if(bytes < 0) {
		std::cout << RED << "[ERROR]: Client fd=" << fd << ": recv error" << RES << std::endl;
		// Kick off the client from the server
	} else if (bytes == 0) {
		std::cout << RED << "[WARN]: Client fd=" << fd << ": empty buffer" << RES << std::endl;
	} else {
		buff[bytes] = '\0';
		std::cout << YEL << "Client <" << fd << "> Data:\n" << RES << buff << std::endl;
	}
}

// --- handle new client ---
void	Server::connectNewClient() {
	int					fdIn;
	struct pollfd		clientIn;
	struct sockaddr_in	clientAddress;
	socklen_t			len;
	Client				newClient;

	std::cout << "[INFO]: Connect new client" << std::endl;
	len = sizeof(clientAddress);
	fdIn = accept(_fd, (sockaddr *)&(clientAddress), &len);
	
	if (fdIn == -1) {
		std::cout << RED << "[ERROR]: connectNewClient: can't create fd" << RES << std::endl; 
		return ;
	}

	if (fcntl(fdIn, F_SETFL, O_NONBLOCK) == -1) {
		std::cout << RED << "[ERROR]: connectNewClient: can't set unblock flag" << RES << std::endl;
		return ;
	}

	clientIn.fd = fdIn;
	clientIn.events = POLLIN;
	clientIn.revents = 0;

	newClient.setFd(fdIn);
	newClient.setIp(inet_ntoa((clientAddress.sin_addr)));
	
	_clients.push_back(newClient);
	_fds.push_back(clientIn);

	std::cout << "[INFO]: Client fd=" << fdIn << " connected" << std::endl;
}
// void	Server::deleteClient(int fd) {
// 	for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
// 		if (it->getFd() == toDelete.getFd())
// 			this->_clients.erase(it);
// }


Client* Server::getClientByFd(int fd) {
    for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); it++) {
        if (it->getFd() == fd) {
            return &(*it); 
        }
    }
    return NULL;  
}
// --- handle new input ---
std::vector<std::string> Server::splitIrssiCommandinToken(std::string cmd)
{
    std::vector<std::string> result;
    std::istringstream iss(cmd);
    std::string token;

    while (iss >> token) {
        result.push_back(token);
		token.clear();
    }
    return result;
}

std::vector<std::string> Server::parse_input(std::string buffer)
{
	std::vector<std::string> commands;
	std::istringstream stm(buffer);
	std::string line;
	while(std::getline(stm, line))
	{
		size_t find = line.find_first_of("\r\n");
		if(find != std::string::npos)
			line = line.substr(0,find);
		commands.push_back(line);
		
	}
	for (size_t i = 0; i < commands.size(); ++i)
    {
        std::cout << "Command " << i << ": " << commands[i] << "\n";
    }
	return commands;
}	

int Server::exec(std::string cmd,int fd)
{
	std::vector<std::string> tokens;
	(void) fd;
	tokens = splitIrssiCommandinToken(cmd);
	for (size_t i = 0; i < tokens.size(); ++i)
    {
        std::cout << "Command V2 -> " << i << ": " << tokens[i] << "\n";
    }

	return (0);
}
void	Server::handleNewInput(int fd) {
	//std::cout << "You are the dancing bear" << std::endl;
	char buff[1024]; 
	memset(buff, 0, sizeof(buff));
	Client *client = getClientByFd(fd);
	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1 , 0); //-> receive the data
	std::cout << "fd" << fd << std::endl;
	if(bytes <= 0){
		std::cout << RED << "Client <" << client->getFd() << "> Disconnected" << std::endl;
		//deleteClient(fd); 
		// define cleaning
		close(fd); 
	}

	else{ //-> print the received data
		client -> setBuffer(buff);
		std::cout << client->getBuffer() << std::endl;	
		//todo verify buffer is not empty
		//std::cout << YEL << "Client <" << fd << "> Data: " << buff;
		std::vector<std::string> cmds = parse_input(client->getBuffer());
		for(size_t i = 0; i < cmds.size(); i++)
			exec(cmds[i], fd);
			
	}
}

// --- turn on/off ---
void	Server::startListening() {
	int optval = 1;

	if(_fd == -1)
		throw (std::runtime_error("Error: server socket: can't create socket"));
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		throw (std::runtime_error("Error: server socket: can't set reuse option for address and port"));
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
		throw (std::runtime_error("Error: server socket: can't set unblock flag"));
	if (bind(_fd, (struct sockaddr *)&_serverAddress, sizeof(_serverAddress) ) == -1)
		throw (std::runtime_error("Error: server socket: can't assign a specific address and port to a socket"));
	if (listen(_fd, SOMAXCONN) == -1)
		throw (std::runtime_error("Error: server socket: can't listen"));
	_clientIn.fd = _fd;
	_clientIn.revents = 0;
	_clientIn.events = POLLIN;
	_fds.push_back(_clientIn);
}

void	Server::turnOn() {
	startListening();
	std::cout << GRN << "[INFO]: the server fd=" << _fd << " was opened" << RES << std::endl;
	std::cout << "[INFO]: Waiting for connections ..." << std::endl;

	while (Server::_stayTurnedOn) {
		if ((poll(&_fds[0], _fds.size(), -1) == -1) && Server::_stayTurnedOn)
			throw (std::runtime_error("Error: poll()"));
		for (size_t i = 0; i < _fds.size(); i++)
			if (_fds[i].revents & POLLIN)
				(_fds[i].fd == _fd) ? connectNewClient() : handleNewInput(_fds[i].fd);
	}

	turnOff();
}

void	Server::turnOff() {
	std::cout << GRN << "[INFO]: turning off the server" << RES << std::endl;
	for (size_t i = 0; i < _clients.size(); i++) {
		close(_clients[i].getFd());
		std::cout << "[INFO]: client fd=" << _clients[i].getFd() << " disconnected" << std::endl;
	}
	if (_fd != -1) {
		close(_fd);
		std::cout << GRN << "[INFO]: the server fd=" << _fd << " was turned off" << RES << std::endl;
	}
}

// --- signal ---
bool	Server::_stayTurnedOn = true;
void	Server::signalHandler(int signum) {
	std::cout << YEL << "[WARN]: signal received: " << signum << RES << std::endl;
	_stayTurnedOn = false;
}
