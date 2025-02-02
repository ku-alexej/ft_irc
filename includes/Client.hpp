/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:08 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/30 15:52:48 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <vector>
# include <iostream>		// dell after
# include "Colors.hpp"		// dell

class Client {
	public:
		// --- constructors ---
		Client();
		Client(const Client &src);
		Client(int fd, std::string username, std::string nickname);

		// --- operators ---
		Client &operator=(const Client &src);

		// --- destructors ---
		~Client();

		// --- getters ---
		int							getFd();
		bool						getCapOn();
		bool						getOnline();
		bool						getOperator();
		bool						getPassOk();
		bool						getRegistred();
		std::string					getReplyBuffer();
		std::string					getBuffer();
		std::string					getIp();
		std::string					getUsername();
		std::string					getHostname();
		std::string					getServername();
		std::string					getRealname();
		std::string					getNickname();
		std::vector<std::string>	getInvites();

		// --- setters ---
		void	setFd(int newFd);
		void	setCapOn(bool isCapOn);
		void	setOnline(bool isOnline);
		void	setOperator(bool isOperator);
		void	setPassOk(bool isPassOk);
		void	setRegistred(bool isRegistred);
		void	setReplyBuffer(std::string newReply);
		void	setBuffer(std::string newBuffer);
		void	setIp(std::string newIp);
		void	setUsername(std::string newUsername);
		void	setHostname(std::string newHostname);
		void	setServername(std::string newServername);
		void	setRealname(std::string newRealname);
		void	setNickname(std::string newNickname);

		// --- member functions ---
		void	clearReplyBuffer();
		void	clearBuffer();
		void	addInvite(std::string newInvite);
		void	deleteInvite(std::string toDelete);
		void	clearInvites();
		void	trimmReplyBuffer(size_t bytes);

	private:
		int							_fd;
		bool						_capOn;
		bool						_online;
		bool						_operator;
		bool						_passOk;
		bool						_registred;
		std::string					_replyBuffer;
		std::string					_buffer;
		std::string					_ip;
		std::string					_username;
		std::string					_hostname;
		std::string					_servername;
		std::string					_realname;
		std::string					_nickname;
		std::vector<std::string>	_invites;
};

#endif
