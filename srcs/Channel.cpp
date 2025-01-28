/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:14 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/28 16:41:28 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

// --- constructors ---
Channel::Channel() {
	this->_l		= 0;		// 0		= unlimited number of clients
	this->_i		= false;	// false	= invite mot necessary
	this->_t		= true;		// true		= possible to change topic
	this->_k		= "";		// ""		= no password to join channel
	this->_tText	= "";
}

Channel::Channel(const Channel &src) {
	*this			= src;
}

// --- operators ---
Channel & Channel::operator=(const Channel &src) {
	if (this != &src) {
		this->_l			= src._l;
		this->_i			= src._i;
		this->_t			= src._t;
		this->_k			= src._k;
		this->_tText		= src._tText;
		this->_clients		= src._clients;
		this->_operators	= src._operators;
	}
	return (*this);
}

// --- destructors ---
Channel::~Channel() {}

// --- getters ---
int					Channel::getL()			{return (this->_l);}
bool				Channel::getI()			{return (this->_i);}
bool				Channel::getT()			{return (this->_t);}
std::string			Channel::getK()			{return (this->_k);}
std::string			Channel::getTopicText()	{return (this->_tText);}
std::vector<Client>	Channel::getClients()	{return (this->_clients);}
std::vector<Client>	Channel::getOperators()	{return (this->_operators);}

Client	Channel::getClientByFd(int fd) {
	Client client;
	for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		if (it->getFd() == fd) {
			client = *it;
			return (client);
		}
	return (client);
}

Client	Channel::getOperatorByFd(int fd) {
	Client op;
	for (std::vector<Client>::iterator it = _operators.begin(); it != _operators.end(); it++)
		if (it->getFd() == fd) {
			op = *it;
			return (op);
		}
	return (op);
}

// --- setters ---
void	Channel::setL(int newL)							{this->_l		= newL;}
void	Channel::setI(bool isI)							{this->_i		= isI;}
void	Channel::setT(bool isT)							{this->_t		= isT;}
void	Channel::setK(std::string newK)					{this->_k		= newK;}
void	Channel::setTopicText(std::string newTopicText)	{this->_tText	= newTopicText;}

// --- member functions ---
void	Channel::addClient(Client newClient) {
	for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		if (it->getFd() == newClient.getFd())
			return ;
	this->_clients.push_back(newClient);
}

void	Channel::deleteClient(Client toDelete) {
	for (std::vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
		if (it->getFd() == toDelete.getFd()) {
			this->_clients.erase(it);
			return ;
		}
}

void	Channel::clearClients() {
	this->_clients.clear();
}

void	Channel::addOperators(Client newOperator) {
	for (std::vector<Client>::iterator it = this->_operators.begin(); it != this->_operators.end(); it++)
		if (it->getFd() == newOperator.getFd())
			return ;
	this->_operators.push_back(newOperator);
}

void	Channel::deleteOperator(Client toDelete) {
	for (std::vector<Client>::iterator it = this->_operators.begin(); it != this->_operators.end(); it++)
		if (it->getFd() == toDelete.getFd()) {
			this->_operators.erase(it);
			return ;
		}
}

void	Channel::clearOperators() {
	this->_operators.clear();
}
