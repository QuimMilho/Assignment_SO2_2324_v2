#include "pch/so2pch.h"

#include "Request.h"

Request::Request(User& user, const int n_acoes, const double preco_acoes) : 
		user(user), n_acoes(n_acoes), preco_acoes(preco_acoes) {}

Request::~Request() {}

