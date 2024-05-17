#include "pch/so2pch.h"

#include "NumberFormatter.h"

TCHAR* NumberFormatter::format(TCHAR* str, const int max_size, const double d, const int casasDecimais) {
	TCHAR buf[512];
	long b = (long)d;
	long c = (long)(d * pow(10, casasDecimais) - b * pow(10, casasDecimais));
	_TSTRINGSTREAM ss;
	ss << _T("%d.%") << casasDecimais << _T("d");
	_TSPRINTF(buf, ss.str().c_str(), b, c);

	int p;
	for (int i = 0; i < 512; i++) {
		if (buf[i] == _T('.')) {
			p = i;
			break;
		}
	}

	for (int i = p + 1; i < p + casasDecimais; i++) {
		if (buf[i] != _T(' '))
			break;
		buf[i] = _T('0');
	}

	_TSTRCPY_S(str, max_size - 1, buf);

	return str;
}

TCHAR* NumberFormatter::format(TCHAR* str, const int max_size, const float d, const int casasDecimais) {
	return NumberFormatter::format(str, max_size, (double) d, casasDecimais);
}

TCHAR* NumberFormatter::format(TCHAR* str, const int max_size, const double d, const int dezenas,
		const int casasDecimais) {
	TCHAR buf[512];
	long b = (long)d;
	long c = (long)(d * pow(10, casasDecimais) - b * pow(10, casasDecimais));
	_TSTRINGSTREAM ss;
	ss << _T("%") << dezenas << _T("d.%") << casasDecimais << _T("d");
	_TSPRINTF(buf, ss.str().c_str(), b, c);

	int p;
	for (int i = 0; i < 512; i++) {
		if (buf[i] == _T('.')) {
			p = i;
			break;
		}
	}

	for (int i = p + 1; i < p + casasDecimais; i++) {
		if (buf[i] != _T(' '))
			break;
		buf[i] = _T('0');
	}

	_TSTRCPY_S(str, max_size - 1, buf);

	return str;
}

TCHAR* NumberFormatter::format(TCHAR* str, const int max_size, const float d, const int dezenas,
		const int casasDecimais) {
	return NumberFormatter::format(str, max_size, (double)d, dezenas, casasDecimais);
}

TCHAR* NumberFormatter::format(TCHAR* str, const int max_size, const int d, const int dezenas) {
	TCHAR buf[512];
	long b = (long)d;
	_TSTRINGSTREAM ss;
	ss << _T("%") << dezenas << _T("d");
	_TSPRINTF(buf, ss.str().c_str(), b);

	_TSTRCPY_S(str, max_size - 1, buf);

	return str;
}

TCHAR* NumberFormatter::format(TCHAR* str, const int max_size, const long d, const int dezenas) {
	TCHAR buf[512];
	long b = (long)d;
	_TSTRINGSTREAM ss;
	ss << _T("%") << dezenas << _T("d");
	_TSPRINTF(buf, ss.str().c_str(), b);

	_TSTRCPY_S(str, max_size - 1, buf);

	return str;
}