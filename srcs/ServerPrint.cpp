/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerPrint.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:53:20 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/28 17:54:17 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::printStringVector(std::vector<std::string> v) {
	for (size_t i = 0; i < v.size(); i++) {
		std::cout << "[" << v[i] << "]";
		if (i + 1 < v.size())
			std::cout << GRN << "->" << RES;
	}
	std::cout << std::endl;
}

void	Server::printBuffer(std::string str) {
	std::cout << CYN << "[INFO]: RECV buffer=[";
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '\n')
			std::cout << "\\n";
		else if (str[i] == '\r')
			std::cout << "\\r";
		else 
			std::cout << str[i];
	}
	std::cout << "]" << RES << std::endl;
}

void	Server::printClientBuffer(Client client) {
	std::string str = client.getBuffer();
	
	std::cout << YEL << "[INFO]: client fd=" << client.getFd() << "CLIENT buffer=[";
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '\n')
			std::cout << "\\n";
		else if (str[i] == '\r')
			std::cout << "\\r";
		else 
			std::cout << str[i];
	}
	std::cout << "]" << RES << std::endl;
}
