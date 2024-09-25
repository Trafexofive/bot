/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 03:59:35 by mlamkadm          #+#    #+#             */
/*   Updated: 2024/09/25 03:59:35 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLL_HPP
#define POLL_HPP

#include <iostream>
#include <string>
#include <vector>

class Poll {
private:
  std::string _question;
  std::vector<int> _votes;

public:
  // canonical form

  Poll();
  Poll(const Poll &other);
  ~Poll();
  Poll &operator=(const Poll &other);

  Poll(const std::string &question, const std::vector<std::string> &answers);

  // GETTERS & SETTERS

  std::string getQuestion() const;
  std::vector<std::string> getAnswers() const;
  std::vector<int> getVotes() const;

  void setQuestion(const std::string &question);
  void setVotes(const std::vector<int> &votes);

  // poll specific methodes
  void displayPoll();
  void vote(int index);
};

#endif
