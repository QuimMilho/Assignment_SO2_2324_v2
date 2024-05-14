#include "pch/so2pch.h"

#include "User.h"

User::User(const _TSTRING& name, const _TSTRING& password, const double balance): username(name),
		password(password), balance(balance), wallet() {}

_TSTRING User::getName() const {
	return username;
}