/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:07 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/28 15:57:42 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <vector>
# include "Client.hpp"

class Channel {
	public:
		// --- constructors ---
		Channel();
		Channel(const Channel &src);

		// --- operators ---
		Channel &operator=(const Channel &src);

		// --- destructors ---
		~Channel();

		// --- getters ---
		int					getL();
		bool				getI();
		bool				getT();
		std::string			getK();
		std::string			getTopicText();
		std::vector<Client>	getClients();
		std::vector<Client>	getOperators();
		Client				getClientByFd(int fd);
		Client				getOperatorByFd(int fd);

		// --- setters ---
		void	setL(int newL);
		void	setI(bool isI);
		void	setT(bool isT);
		void	setK(std::string newK);
		void	setTopicText(std::string newTopicText);

		// --- member functions ---
		void	addClient(Client newClient);
		void	deleteClient(Client toDelete);
		void	clearClients();
		void	addOperators(Client newOperator);
		void	deleteOperator(Client toDelete);
		void	clearOperators();


	private:
		int					_l;
		bool				_i;
		bool				_t;
		std::string			_k;
		std::string			_tText;
		std::vector<Client>	_clients;
		std::vector<Client>	_operators;
};

#endif
