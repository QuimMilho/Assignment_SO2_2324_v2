#pragma once

#include "exceptions/Exception.h"

struct SO2_API CompanyNotFound : public Exception {
	CompanyNotFound(const _TSTRING& name) : name(name) {}

	[[nodiscard]] _TSTRING what() override;

private:
	_TSTRING name;

};
