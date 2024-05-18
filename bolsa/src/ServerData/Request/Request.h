#pragma once

#include "ServerData/User/User.h"

struct Request {
	Request(User& user, const int n_acoes, const double preco_acoes);
	~Request();



private:
	int n_acoes;
	double preco_acoes;
	User& user;
};