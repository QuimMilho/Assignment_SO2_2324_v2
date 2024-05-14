#pragma 

#include "macros.h"

struct SO2_API WindowsRegistryKey {
	static WindowsRegistryKey* openKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const long access = KEY_ALL_ACCESS);
	static WindowsRegistryKey* openKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value, 
		const int defaultValue, const long access = KEY_ALL_ACCESS);
	static WindowsRegistryKey* openKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value, 
		const double defaultValue, const long access = KEY_ALL_ACCESS);
	static WindowsRegistryKey* openKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const _TSTRING& defaultValue, const long access = KEY_ALL_ACCESS);

	virtual ~WindowsRegistryKey();

	int readInt();
	_TSTRING readString(const int maxSize);
	double readDouble();

	int setRegistry(_TSTRING str);
	int setRegistry(int n);
	int setRegistry(double d);

private:
	HKEY key;
	_TSTRING path, name, value;
	int error;
	bool newKey;

	int openRegistry(long access = KEY_ALL_ACCESS);
	int createRegistry(long access = KEY_ALL_ACCESS);

	WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const long access = KEY_ALL_ACCESS);
	WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value, const int defaultValue,
		const long access = KEY_ALL_ACCESS);
	WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value, const double defaultValue,
		const long access = KEY_ALL_ACCESS);
	WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const _TSTRING& defaultValue, const long access = KEY_ALL_ACCESS);
};
