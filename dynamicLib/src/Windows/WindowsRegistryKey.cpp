#include "pch/so2pch.h"

#include "WindowsRegistryKey.h"

#define KEY_PATH _T("Software\\BolsaApp")
#define KEY_NAME _T("BolsaValoresSettings")
#define KEY_VALUE _T("NCLIENTES")

WindowsRegistryKey* WindowsRegistryKey::openKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const long access) {
	return new WindowsRegistryKey(path, name, value, access);
}

WindowsRegistryKey* WindowsRegistryKey::openKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const int defaultValue, const long access) {
	return new WindowsRegistryKey(path, name, value, defaultValue, access);
}

WindowsRegistryKey* WindowsRegistryKey::openKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const double defaultValue, const long access) {
	return new WindowsRegistryKey(path, name, value, defaultValue, access);
}

WindowsRegistryKey* WindowsRegistryKey::openKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const _TSTRING& defaultValue, const long access) {
	return new WindowsRegistryKey(path, name, value, defaultValue, access);
}

WindowsRegistryKey::WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value, 
		const long access) : path(path), name(name), value(value), newKey(false) {
	int s = openRegistry(access);
	LOG_INFO("Pedido para abrir chave efetuado!");
	if (s) {
		LOG_ERRO("Erro ao abrir chave: %d:%d", s, error);
		s = createRegistry(access);
		LOG_INFO("Pedido para criar chave efetuado!");
		if (s) {
			LOG_ERRO("Erro ao criar chave: %d:%d", s, error);
			delete this;
			return;
		}
		newKey = true;
	}
}

WindowsRegistryKey::WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const int defaultValue, const long access) : path(path), name(name), value(value), newKey(false) {
	int s = openRegistry(access);
	LOG_INFO("Pedido para abrir chave efetuado");
	if (s) {
		LOG_ERRO("Erro ao abrir chave: %d:%d", s, error);
		s = createRegistry(access);
		LOG_INFO("Pedido para criar chave efetuado!");
		if (s) {
			LOG_ERRO("Erro ao criar chave: %d:%d", s, error);
			delete this;
			return;
		}
		newKey = true;
		s = setRegistry(defaultValue);
		error = GetLastError();
		LOG_INFO("Valor default inserido! Valor: %d", defaultValue);
	}
}

WindowsRegistryKey::WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const double defaultValue, const long access) : path(path), name(name), value(value), newKey(false) {
	int s = openRegistry(access);
	LOG_INFO("Pedido para abrir chave efetuado!");
	if (s) {
		LOG_ERRO("Erro ao abrir chave: %d:%d", s, error);
		s = createRegistry(access);
		LOG_INFO("Pedido para criar chave efetuado!");
		if (s) {
			LOG_ERRO("Erro ao criar chave: %d:%d", s, error);
			delete this;
			return;
		}
		newKey = true;
		s = setRegistry(defaultValue);
		error = GetLastError();
		LOG_INFO("Valor default inserido! Valor: %lf", defaultValue);
	}
}
WindowsRegistryKey::WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const _TSTRING& defaultValue, const long access) : path(path), name(name), value(value), newKey(false) {
	int s = openRegistry(access);
	LOG_INFO("Pedido para abrir chave efetuado!");
	if (s) {
		LOG_ERRO("Erro ao abrir chave: %d:%d", s, error);
		s = createRegistry(access);
		LOG_INFO("Pedido para criar chave efetuado!");
		if (s) {
			LOG_ERRO("Erro ao criar chave: %d:%d", s, error);
			delete this;
			return;
		}
		newKey = true;
		s = setRegistry(defaultValue);
		error = GetLastError();
		LOG_INFO("Valor default inserido! Valor: %s", defaultValue.c_str());
	}
}

WindowsRegistryKey::~WindowsRegistryKey() {
	RegCloseKey(key);
}

int WindowsRegistryKey::openRegistry(long access) {
	int s = RegOpenKeyEx(HKEY_CURRENT_USER, path.c_str(), 0, access, &key);
	error = GetLastError();
	return s;
}

int WindowsRegistryKey::createRegistry(long access) {
	long a = access | KEY_WRITE;
	int s = RegCreateKeyEx(HKEY_CURRENT_USER, path.c_str(), 0, (_TLPSTR) name.c_str(), REG_OPTION_NON_VOLATILE,
		access, NULL, &key, NULL);
	error = GetLastError();
	return s;
}

int WindowsRegistryKey::readInt() {
	int valor;
	DWORD k = sizeof(int);
	int s = RegGetValue(key, name.c_str(), value.c_str(), RRF_RT_DWORD, NULL, &valor, &k);
	error = GetLastError();
	return valor;
}

_TSTRING WindowsRegistryKey::readString(const int maxSize) {
	std::unique_ptr<TCHAR> str = std::unique_ptr<TCHAR>(new TCHAR[maxSize]);
	DWORD k = maxSize;
	int s = RegGetValue(key, name.c_str(), value.c_str(), RRF_RT_REG_SZ, NULL, str.get(), &k);
	error = GetLastError();
	return _TSTRING(str.get());
}

double WindowsRegistryKey::readDouble() {
	double valor;
	DWORD k = sizeof(double);
	int s = RegGetValue(key, name.c_str(), value.c_str(), RRF_RT_QWORD, NULL, &valor, &k);
	error = GetLastError();
	return valor;
}

int WindowsRegistryKey::setRegistry(_TSTRING str) {
	int s = RegSetKeyValue(key, name.c_str(), value.c_str(), REG_SZ, str.c_str(), str.length()
			* sizeof(TCHAR));
	error = GetLastError();
	return s;
}

int WindowsRegistryKey::setRegistry(int n) {
	int s = RegSetKeyValue(key, name.c_str(), value.c_str(), REG_DWORD, &n, sizeof(int));
	error = GetLastError();
	return s;
}

int WindowsRegistryKey::setRegistry(double d) {
	int s = RegSetKeyValue(key, name.c_str(), value.c_str(), REG_QWORD, &d, sizeof(double));
	error = GetLastError();
	return s;
}
