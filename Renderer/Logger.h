#include <string>
#include <ostream>

#pragma once
#ifndef _LOGGER_H
#define _LOGGER_H

class ConsoleLogger {
public:
	std::ostream& operator<<(char *s);

};
class Logger {
	
public:
	static Logger* Instance();
	ConsoleLogger& getCL();

private:
	
	Logger();  // Private so that it can  not be called
	Logger(Logger const&){};             // copy constructor is private
	Logger& operator=(Logger const&){};  // assignment operator is private
	static Logger* m_pInstance;
	ConsoleLogger _cl;
};



#endif