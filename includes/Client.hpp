/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:28:08 by akurochk          #+#    #+#             */
/*   Updated: 2025/01/28 18:23:06 by akurochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <vector>

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
		bool						getOnline();
		bool						getOperator();
		bool						getPassOk();
		bool						getRegistred();
		std::string					getReplyBuffer();
		std::string					getBuffer();
		std::string					getIp();
		std::string					getUsername();
		std::string					getNickname();
		std::vector<std::string>	getInvites();

		// --- setters ---
		void	setFd(int newFd);
		void	setOnline(bool isOnline);
		void	setOperator(bool isOperator);
		void	setPassOk(bool isPassOk);
		void	setRegistred(bool isRegistred);
		void	setReplyBuffer(std::string newReply);
		void	setBuffer(std::string newBuffer);
		void	setIp(std::string newIp);
		void	setUsername(std::string newUsername);
		void	setNickname(std::string newNickname);

		// --- member functions ---
		void	clearReplyBuffer();
		void	clearBuffer();
		void	addInvite(std::string newInvite);
		void	deleteInvite(std::string toDelete);
		void	clearInvites();

	private:
		int							_fd;
		bool						_online;
		bool						_operator;
		bool						_passOk;
		bool						_registred;
		std::string					_replyBuffer;
		std::string					_buffer;
		std::string					_ip;
		std::string					_username;
		std::string					_nickname;
		std::vector<std::string>	_invites;
};

#endif
