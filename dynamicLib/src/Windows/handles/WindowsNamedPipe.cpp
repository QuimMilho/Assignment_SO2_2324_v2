#include "pch/so2pch.h"

#include "WindowsNamedPipe.h"

WindowsNamedPipe::WindowsNamedPipe(const _TSTRING& name) : WindowsHandle(NULL) {

}

WindowsNamedPipe::~WindowsNamedPipe() {

}

int WindowsNamedPipe::createFile() {
	return 0;
}

int WindowsNamedPipe::openFile() {
	return 0;
}

int WindowsNamedPipe::unmap() {
	return 0;
}

template<typename T>
int WindowsNamedPipe::write(Envelope<T>* e) {
	return 0;
}

template<typename T>
int WindowsNamedPipe::read(Envelope<T>* e) {
	return 0;
}