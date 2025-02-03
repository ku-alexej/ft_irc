/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:07 by akurochk          #+#    #+#             */
/*   Updated: 2025/02/03 13:28:54 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <vector>
# include <sstream>
# include "Client.hpp"

class Channel {
	public:
		// --- constructors ---
		Channel();
		Channel(const Channel &src);
		Channel(std::string name, Client *client, bool firstConnection);

		// --- operators ---
		Channel &operator=(const Channel &src);

		// --- destructors ---
		~Channel();
		// --- getters ---
		int						getL();
		bool					getI();
		bool					getT();
		std::string				getK();
		std::string				getPass();
		std::string				getTopicText();
		std::vector<Client *>	getClients();
		std::vector<Client *>	getOperators();
		Client					*getClientByFd(int fd);
		Client					*getOperatorByFd(int fd);
		std::string 			getName();
		// --- setters ---
		void	setL(int newL);
		void	setI(bool isI);
		void	setT(bool isT);
		void	setK(std::string newK);
		void	setTopicText(std::string newTopicText);

		// --- member functions ---
		void	addClient(Client *newClient);
		void	deleteClient(Client *toDelete);
		void	clearClients();
		void	addOperator(Client *newOperator);
		void	deleteOperator(Client *toDelete);
		void	clearOperators();
		void 	broadcastJoinMessage(Client *joiningClient) ;

		std::string	getModes();
		std::string	getModesArgs(bool isOnChannel);

	private:
		int						_l;
		bool					_i;
		bool					_t;
		std::string				_k;
		std::string 			_name;
		std::string				_tText;
		std::string 			_password;
		std::vector<std::string> _all_members;
		std::vector<Client *>	_clients;
		std::vector<Client *>	_operators;
};

bool isValidChannelName(const std::string &channel);

#endif
