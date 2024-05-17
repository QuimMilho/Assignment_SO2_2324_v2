#pragma 

#include "macros.h"

struct SO2_API WindowsRegistryKey {
	[[nodiscard]] static WindowsRegistryKey* openKey(const _TSTRING& path, const _TSTRING& name, 
		const _TSTRING& value, const long access = KEY_ALL_ACCESS);
	[[nodiscard]] static WindowsRegistryKey* openKey(const _TSTRING& path, const _TSTRING& name, 
		const _TSTRING& value, const int defaultValue, const long access = KEY_ALL_ACCESS);
	[[nodiscard]] static WindowsRegistryKey* openKey(const _TSTRING& path, const _TSTRING& name, 
		const _TSTRING& value, const double defaultValue, const long access = KEY_ALL_ACCESS);
	[[nodiscard]] static WindowsRegistryKey* openKey(const _TSTRING& path, const _TSTRING& name, 
		const _TSTRING& value, const _TSTRING& defaultValue, const long access = KEY_ALL_ACCESS);

	virtual ~WindowsRegistryKey();

	[[nodiscard]] int readInt();
	[[nodiscard]] _TSTRING readString(const int maxSize);
	[[nodiscard]] double readDouble();

	[[nodiscard]] int setRegistry(_TSTRING str);
	[[nodiscard]] int setRegistry(int n);
	[[nodiscard]] int setRegistry(double d);

private:
	HKEY key;
	_TSTRING path, name, value;
	int error;
	bool newKey;

	[[nodiscard]] int openRegistry(long access = KEY_ALL_ACCESS);
	[[nodiscard]] int createRegistry(long access = KEY_ALL_ACCESS);

	WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const long access = KEY_ALL_ACCESS);
	WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value, const int defaultValue,
		const long access = KEY_ALL_ACCESS);
	WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value, const double defaultValue,
		const long access = KEY_ALL_ACCESS);
	WindowsRegistryKey(const _TSTRING& path, const _TSTRING& name, const _TSTRING& value,
		const _TSTRING& defaultValue, const long access = KEY_ALL_ACCESS);
};
