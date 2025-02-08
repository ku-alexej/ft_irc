/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:17 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/08 13:52:05 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

// --- constructors ---
Server::Server() {}

Server::Server(const Server &src) {
	(void) src;
}

void	Server::initCmdMap() {
	this->_cmdMap["CAP"]	= &Server::cmdCap;
	this->_cmdMap["PASS"]	= &Server::cmdPass;
	this->_cmdMap["NICK"]	= &Server::cmdNick;
	this->_cmdMap["USER"]	= &Server::cmdUser;
	this->_cmdMap["PING"]	= &Server::cmdPing;
	this->_cmdMap["WHOIS"]	= &Server::cmdWhois;
	this->_cmdMap["JOIN"]	= &Server::cmdJoin;
	this->_cmdMap["PART"]	= &Server::cmdPart;
	this->_cmdMap["TOPIC"]	= &Server::cmdTopic;
	this->_cmdMap["INVITE"]	= &Server::cmdInvite;
	this->_cmdMap["KICK"]	= &Server::cmdKick;
	this->_cmdMap["MODE"]	= &Server::cmdMode;
	this->_cmdMap["QUIT"]	= &Server::cmdQuit;
	this->_cmdMap["WHO"]	= &Server::cmdWho;
}

Server::Server(int port, std::string password, std::string serverName) {
	_port = port;
	_serverName = serverName;
	_password = password;
	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_addr.s_addr = INADDR_ANY;
	_serverAddress.sin_port = htons(_port);
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	this->initCmdMap();
}

// --- operators ---
Server	&Server::operator=(const Server &src) {
	(void) src;
	return (*this);
}

// --- destructors ---
Server::~Server() {}

// --- getters ---

// --- setters ---

void	Server::deleteClient(Client toDelete) {
	for (std::list<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		if (it->getFd() == toDelete.getFd()) {
			this->_clients.erase(it);
			std::cout << "[INFO]: client fd=" << toDelete.getFd() << " was deleted" << std::endl;
			return ;
		}
}

Client* Server::getClientByFd(int fd) {
	for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (it->getFd() == fd) {
			return &(*it);
		}
	}
	return (NULL);
}

Client* Server::getClientByNick(std::string nick) {
	for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (it->getNickname() == nick) {
			return &(*it);
		}
	}
	return (NULL);
}

void	Server::deleteFromFds(int fdsIndex) {
	std::vector<struct pollfd>::iterator it = _fds.begin();
	for (int i = 0; i < fdsIndex; i++)
		it++;
	if (it != _fds.end())
		_fds.erase(it);
}

// --- handle new client ---
void	Server::connectNewClient() {
	int					fdIn;
	struct pollfd		clientIn;
	struct sockaddr_in	clientAddress;
	socklen_t			len;
	Client				newClient;

	std::cout << UGRN << "[INFO]: Connect new client" << RES << std::endl;
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

	std::cout << UGRN << "[INFO]: Client fd=" << fdIn << " connected" << RES << std::endl;
}


// --- handle new input ---
std::vector<std::string>	Server::splitIrssiCommandinToken(std::string cmd) {
	std::vector<std::string> result;
	std::istringstream iss(cmd);
	std::string token;

	while (iss >> token) {
		result.push_back(token);
		token.clear();
	}

	return (result);
}

std::vector<std::string>	Server::parsCommands(std::string buffer) {
	std::vector<std::string>	commands;
	std::istringstream			stm(buffer);
	std::string					line;

	while (std::getline(stm, line)) {
		size_t find = line.find_first_of("\r\n");
		if(find != std::string::npos)
			line = line.substr(0,find);
		commands.push_back(line);
	}

	return (commands);
}

void	Server::handleNewInput(int fd, int fdsIndex) {
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	Client *client = getClientByFd(fd);
	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1 , 0);
	std::cout << YEL << "[INFO]: recived data from client fd=" << fd << RES << std::endl;

	if (bytes < 0) {
		std::cout << RED << "[INFO]: client fd=" << client->getFd() << " can't read data" << RES << std::endl;
		// define cleaning
		close(fd);
		deleteClient(*client);
		deleteFromFds(fdsIndex);
	} else if (bytes == 0) {
		std::cout << RED << "[INFO]: client fd=" << client->getFd() << " sent nothing" << RES << std::endl;
		// kick from the server if the client sent nothing several times
		close(fd);
		deleteClient(*client);
		deleteFromFds(fdsIndex);
	} else {						//-> print the received data
		client->setBuffer(buff);
		printClientBuffer(*client);
		//todo verify buffer is not empty
		std::vector<std::string> cmds = parsCommands(client->getBuffer());

		std::cout << "[INFO]: " << GRN << "vector=" << RES;
		printStringVector(cmds);

		for (size_t i = 0; i < cmds.size(); i++)
			exec(cmds[i], fd);
		sentReply(fd);
	}
}

void	Server::sentReply(int fd) {
	Client *client = getClientByFd(fd);

	if (client == NULL || client->getReplyBuffer().empty())
		return ;

	std::cout << CYN << "[INFO]: reply to client fd=" << client->getFd() << RES << std::endl;
	printBuffer(client->getReplyBuffer());

	send(client->getFd(), (client->getReplyBuffer()).c_str(), (client->getReplyBuffer()).size(), 0);
	client->clearReplyBuffer();
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

	// Client fox = Client(100, "akurochk", "akurochk");	// debug client
	// _clients.push_back(fox);								// debug client

	startListening();
	std::cout << GRN << "[INFO]: the server fd=" << _fd << " was opened" << RES << std::endl;
	std::cout << "[INFO]: Waiting for connections ..." << std::endl;

	while (Server::_stayTurnedOn) {
		if ((poll(&_fds[0], _fds.size(), -1) == -1) && Server::_stayTurnedOn)
			throw (std::runtime_error("Error: poll()"));

		this->printServer();

		for (size_t i = 0; i < _fds.size(); i++) {
			if (_fds[i].revents & POLLIN) {
				(_fds[i].fd == _fd) ? connectNewClient() : handleNewInput(_fds[i].fd, i);
			}
			for (size_t j = 0; j < _fds.size(); j++) {
				if (_fds[j].fd != _fd) {
					sentReply(_fds[j].fd);
				}
			}
		}

	}

	turnOff();
}

void	Server::turnOff() {
	std::cout << GRN << "[INFO]: turning off the server" << RES << std::endl;
	for (std::list<Client>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		// sent reply to client: SERVER OFF - or something same
		close(it->getFd());
		std::cout << "[INFO]: client fd=" << it->getFd() << " disconnected" << std::endl;
	}

	if (_fd != -1) {
		close(_fd);
		std::cout << GRN << "[INFO]: the server fd=" << _fd << " was turned off" << RES << std::endl;
	}
}

// --- signal ---
bool	Server::_stayTurnedOn = true;
void	Server::signalHandler(int signum) {
	std::cout << std::endl << YEL << "[WARN]: signal received: " << signum << RES << std::endl;
	_stayTurnedOn = false;
}

void Server::addChannel(Channel *newChannel, std::string name) {
	for (std::list<Channel>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it) {
		if (it->getName() == name) {
			std::cout << ">>>>>>> ARE WE HERE <<<<<<< " << std::endl;
			return ;
		}
	}

	this->_channels.push_back(*newChannel);
}

Channel* Server::getChannel(std::string chanName) {
	for (std::list<Channel>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it) {
		if (it->getName() == chanName) {
			return &(*it);
		}
	}

	return (NULL);
}

void	Server::deleteChannel(std::string toDelete) {
	for (std::list<Channel>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
		if (it->getName() == toDelete) {
			this->_channels.erase(it);
			std::cout << "[INFO]: channel name=" << toDelete << " was deleted" << std::endl;
			break;
		}
	}
}
