#include "logging.h"
#include <stdio.h>
#include <fcntl.h>
#include <ios>
Logging* Logging::m_instance(0);
#ifdef _WIN
#include <io.h>
#include <Windows.h>
bool Logging::setupConsoleLog( int numLines) {
	if (!AllocConsole()) {
		/*
		If Alloc console fails the program already has a console
		m_status |= 1;
		return false;
		*/
		return true;
	}
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&conInfo);
	conInfo.dwSize.Y = numLines;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),conInfo.dwSize);

	//stdout
	long lStdHandle((long)GetStdHandle(STD_OUTPUT_HANDLE));
	int hConsole (_open_osfhandle(lStdHandle,_O_TEXT));
	FILE *fp = _fdopen(hConsole,"w");
	*stdout = *fp;
	setvbuf(stdout,NULL, _IONBF,0);

	//stdin
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConsole = _open_osfhandle(lStdHandle,_O_TEXT);
	fp = _fdopen(hConsole,"r");
	*stdin = *fp;
	setvbuf(stdin,NULL, _IONBF,0);

	//sterr
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConsole = _open_osfhandle(lStdHandle,_O_TEXT);
	fp = _fdopen(hConsole,"w");
	*stderr = *fp;
	setvbuf(stderr,NULL, _IONBF,0);

	//resync c++ operators
	std::ios_base::sync_with_stdio();
	return true;
}
#endif


bool Logging::setupFileLog() {
	m_fileLog.open(m_filename,std::ofstream::app | std::ofstream::out);
	if (m_fileLog.good())
		return true;
	m_status |= 2;
	return false;
}
