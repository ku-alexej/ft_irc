/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:15 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/24 14:45:36 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

// --- constructors ---
Client::Client() {
	this->_fd			= -1;
	this->_online		= false;
	this->_operator		= false;
	this->_registred	= false;
	this->_buffer		= "";
	this->_ip			= "";
	this->_username		= "";
	this->_nickname		= "";
}

Client::Client(const Client &src) {
	*this				= src;
}

Client::Client(int fd, std::string username, std::string nickname) {
	this->_fd			= fd;
	this->_online		= false;
	this->_operator		= false;
	this->_registred	= false;
	this->_buffer		= "";
	this->_ip			= "";
	this->_username		= username;
	this->_nickname		= nickname;
}

// --- operators ---
Client	&Client::operator=(const Client &src) {
	if (this != &src) {
		this->_fd			= src._fd;
		this->_online		= src._online;
		this->_operator		= src._operator;
		this->_registred	= src._registred;
		this->_buffer		= src._buffer;
		this->_ip			= src._ip;
		this->_username		= src._username;
		this->_nickname		= src._nickname;
		this->_invites		= src._invites;
	}
	return (*this);
}

// --- destructors ---
Client::~Client() {}

// --- getters ---
int							Client::getFd()			{return (this->_fd);}
bool						Client::getOnline()		{return (this->_online);}
bool						Client::getOperator()	{return (this->_operator);}
bool						Client::getRegistred()	{return (this->_registred);}
std::string					Client::getBuffer()		{return (this->_buffer);}
std::string					Client::getIp()			{return (this->_ip);}
std::string					Client::getUsername()	{return (this->_username);}
std::string					Client::getNickname()	{return (this->_nickname);}
std::vector<std::string>	Client::getInvites()	{return (this->_invites);}

// --- setters ---
void	Client::setFd(int newFd)						{this->_fd			= newFd;}
void	Client::setOnline(bool isOnline)				{this->_online		= isOnline;}
void	Client::setOperator(bool isOperator)			{this->_operator	= isOperator;}
void	Client::setRegistred(bool isRegistred)			{this->_registred	= isRegistred;}
void	Client::setBuffer(std::string newBuffer)		{this->_buffer		= newBuffer;}
void	Client::setIp(std::string newIp)				{this->_ip			= newIp;}
void	Client::setUsername(std::string newUsername)	{this->_username	= newUsername;}
void	Client::setNickname(std::string newNickname)	{this->_nickname	= newNickname;}

// --- member functions ---
void	Client::clearBuffer() {
	this->_buffer.clear();
}

void	Client::addInvite(std::string newInvite) {
	for (std::vector<std::string>::iterator it = this->_invites.begin(); it != this->_invites.end(); it++) {
		if (*it == newInvite)
			return ;
	}
	this->_invites.push_back(newInvite);
}

void	Client::deleteInvite(std::string toDelete) {
	for (std::vector<std::string>::iterator it = this->_invites.begin(); it != this->_invites.end(); it++) {
		if (*it == toDelete) {
			this->_invites.erase(it);
		}
	}
}

void	Client::clearInvites() {
	this->_invites.clear();
}
