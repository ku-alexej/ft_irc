/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:12 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/28 18:14:58 by akurochk         ###   ########.fr       */
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
		Server(int port, std::string password);
		Server &operator=(const Server &src);
		~Server();

		void	connectNewClient();
		void	handleNewInput(int fd, int fdsIndex);
		void	exec(std::string cmd, int fd);
		void 	cmdNick(std::vector<std::string> tokens, int fd);
		void 	cmdName(std::vector<std::string> tokens, int fd);
		//void 	deleteClient(int fd);
		std::vector<std::string>	parsCommands(std::string buffer);
		std::vector<std::string>	splitIrssiCommandinToken(std::string cmd);

		void	cmdPass(std::vector<std::string> tokens, int fd);
		// void	cmdNick();
		// void	cmdUser();
		// void	cmdQuit();
		// void	cmdPing();

		
		Client	*getClientByFd(int fd);
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
		struct sockaddr_in			_serverAddress;
		// struct sockaddr_in			_clientAddress;
		struct pollfd				_clientIn;
		std::vector<Client>			_clients;
		std::vector<Channel>		_channels;
		std::vector<struct pollfd>	_fds;
};

#endif
