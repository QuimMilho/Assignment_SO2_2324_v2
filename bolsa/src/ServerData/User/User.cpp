#include "pch/so2pch.h"

#include "User.h"

User::User(const _TSTRING& name, const _TSTRING& password, const double balance): username(name),
		password(password), balance(balance), wallet(), loggedIn(false){}

_TSTRING User::getName() const {
	return username;
}

_TOSTREAM& operator<<(_TOSTREAM& o, User& c) {
	return o << _T("Username: ") << c.username << _T(" - Saldo: ") << c.balance;
}
