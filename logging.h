
#ifndef _LOGGING_
#define _LOGGING_
//#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>


#ifdef WIDE_MODE
typedef std::wstring SiString;
#else
typedef std::string SiString;
#endif

/*
#ifdef Log
#undef Log
#undef LogLine
#endif
*/

class Logging {
	public:
		enum LOG_LEVEL {LOG_DEBUG,
						LOG_INFO,
						LOG_ERROR };
				

private:
		Logging(LOG_LEVEL logLevel, bool toConsole , bool toFile ,std::string filename )
				:m_toConsole(toConsole), m_toFile(toFile),m_logLevel(logLevel),m_filename(filename),m_status(0)
		{
#ifdef _WIN
			if (toConsole)
				setupConsoleLog();
#endif
			if (toFile)
				setupFileLog();
		}

public:

		~Logging() {
			if (m_toFile)
				m_fileLog.close();
		}



		// Singleton setup
		static void init(LOG_LEVEL level, bool toConsole = false, bool toFile = false,std::string filename = "") {
			if (m_instance)
				return;
			m_instance = new Logging(level,toConsole,toFile,filename);
		}

		static void destroy() {
			if (!m_instance)
				return;
			delete m_instance;
			m_instance = NULL;
		}

		static bool good() {
			return (m_instance) ? m_instance->m_status == 0 : false;
		}

		bool setupFileLog();
		bool setupConsoleLog( int numLines = 200);

		void log(const SiString& input, const LOG_LEVEL level) {
			if (level < m_logLevel)
				return;
			if (m_toConsole)
				std::cout << input;
			if (m_toFile)
				m_fileLog << input;
		}

		void logLine(const SiString& input, LOG_LEVEL level) {
			log(input + "\n",level);
		}

		void log(const char* input,LOG_LEVEL level) {
			if (level < m_logLevel)
				return;
			if (m_toConsole)
				std::cout << input;
			if (m_toFile)
				m_fileLog << input;
		}

		void logLine(const char* input,LOG_LEVEL level) {
			log(input ,level);
			log("\n",level);
		}

		static void Log(const SiString& input,LOG_LEVEL level) {
			if (m_instance)
				m_instance->log(input,level);
		}

		static void LogLine(const SiString& input,LOG_LEVEL level) {
			if (m_instance)
				m_instance->logLine(input,level);
		}

		static void Log(const char* input,LOG_LEVEL level) {
			if (m_instance)
				m_instance->log(input,level);
		}


		static void LogLine(const char* input,LOG_LEVEL level) {
			if (m_instance)
				m_instance->logLine(input,level);
		}

	private:
		const bool m_toConsole;
		const bool m_toFile;
		const LOG_LEVEL m_logLevel;
		const std::string m_filename;

		int m_status;
		std::ofstream m_fileLog;

		static Logging* m_instance;



};
#ifndef Log
#define Log Logging::Log
#define LogLine Logging::LogLine
#endif

#endif
