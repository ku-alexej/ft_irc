/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:12 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 16:09:58 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <csignal>
# include <cstdlib>
# include <cstring>
# include <vector>
# include <netinet/in.h>
# include <poll.h>
# include <fcntl.h>
# include <arpa/inet.h>
#include <sstream>

// # include <sstream>
// # include <sys/socket.h>
// # include <sys/types.h>
// # include <unistd.h>
// # include <netdb.h>
// # include <fstream>
# include "Client.hpp"
# include "Channel.hpp"
# include "Colors.hpp"
# include "Replyes.hpp"

class Server {
	public:
		Server();
		Server(const Server &src);
		Server(int port, std::string password, std::string serverName);
		Server &operator=(const Server &src);
		~Server();

		void	connectNewClient();
		void	handleNewInput(int fd, int fdsIndex);
		void	sentReply(int fd);
		
		std::vector<std::string>	parsCommands(std::string buffer);
		std::vector<std::string>	splitIrssiCommandinToken(std::string cmd);

		void	exec(std::string cmd, int fd);
		void	cmdCap(std::vector<std::string> tokens, int fd);
		void	cmdPass(std::vector<std::string> tokens, int fd);
		void	cmdNick(std::vector<std::string> tokens, int fd);
		void	cmdUser(std::vector<std::string> tokens, int fd);
		void	cmdPing(std::vector<std::string> tokens, int fd);
		void	cmdWhois(std::vector<std::string> tokens, int fd);

		// void	cmdQuit();
		
		Client	*getClientByFd(int fd);
		Client	*getClientByNick(std::string nick);
		void	deleteClient(Client toDelete);
		void	deleteFromFds(int fdsIndex);
		
		void	startListening();
		void	turnOn();
		void	turnOff();
		static void	signalHandler(int signum);

		void	printStringVector(std::vector<std::string> v);
		void	printBuffer(std::string str);
		void	printClientBuffer(Client client);
		
	private:
		int							_fd;
		int							_port;
		static bool					_stayTurnedOn;
		std::string					_password;
		std::string					_serverName;
		struct sockaddr_in			_serverAddress;
		struct pollfd				_clientIn;
		std::vector<Client>			_clients;
		std::vector<Channel>		_channels;
		std::vector<struct pollfd>	_fds;
};

#endif
