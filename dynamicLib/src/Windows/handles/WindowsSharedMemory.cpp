#include "pch/so2pch.h"

#include "WindowsSharedMemory.h"
#include "Data/Data.h"

WindowsSharedMemory::WindowsSharedMemory(const _TSTRING& name, const int size) :
		WindowsHandle(NULL), name(name), size(size), access(0), created(false) {}

WindowsSharedMemory::~WindowsSharedMemory() {}

int WindowsSharedMemory::createFile(const int access) {
	this->access = access;
	this->created = true;
	handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, access, 0, size, name.c_str());
	error = GetLastError();
	LOG_INFO(_T("Criado ficheiro de memória partilhada! P: %p"), handle);
	if (!handle)
		return 1;
	return 0;
}

int WindowsSharedMemory::openFile(const int access) {
	this->access = access;
	handle = OpenFileMapping(access, FALSE, name.c_str());
	error = GetLastError();
	LOG_INFO(_T("Aberto ficheiro de memória partilhada! P: %p"), handle);
	if (!handle)
		return 1;
	return 0;
}

int WindowsSharedMemory::map() {
	int a = access;
	if (created) {
		switch (access) {
		case PAGE_WRITECOPY:
			a = FILE_MAP_COPY;
			break;
		case PAGE_READONLY:
			a = FILE_MAP_READ;
			break;
		default:
			a = FILE_MAP_ALL_ACCESS;
			break;
		}
	}
	data = MapViewOfFile(handle, a, 0, 0, size);
	error = GetLastError();
	LOG_INFO(_T("Mapeada memória partilhada! P: %p"), data);
	if (data == nullptr)
		return 1;
	return 0;
}

void WindowsSharedMemory::unmap() {
	UnmapViewOfFile(data);
	error = GetLastError();
	LOG_INFO(_T("Memória partilhada desmapeada!"));
}

void WindowsSharedMemory::write(void* e, const int size) {
	int k = size;
	if (size <= 0 || size > k)
		k = this->size;
	memcpy(data, e, k);
	LOG_DEBUG(_T("Foram copiados %d bytes!"), k);
}

int WindowsSharedMemory::read(void* e, const int size) {
	int k = size;
	if (size <= 0 || size > k)
		k = this->size;
	memcpy(e, data, k);
	LOG_DEBUG(_T("Foram copiados %d bytes!"), k);
	return k;
}

bool WindowsSharedMemory::create(const int access) {
	int r = createFile(access);
	if (r) {
		return false;
	}
	r = map();
	if (r) {
		return false;
	}
	return true;
}

bool WindowsSharedMemory::open(const int access) {
	int r = openFile(access);
	if (r) {
		return false;
	}
	r = map();
	if (r) {
		return false;
	}
	return true;
}