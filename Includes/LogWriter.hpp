#ifndef LOGWRITER_HPP
#define LOGWRITER_HPP

#include <fstream>
#include <iostream>
#include <string>

class LogWriter {

	public:

		LogWriter() = delete;
		LogWriter(const LogWriter &) = delete;
		LogWriter &operator=(const LogWriter &) = delete;

		LogWriter(const std::string filePath);
		~LogWriter();

		void write(const std::string data);
		void addRDBuf(std::ostream &stream);

	private:

		std::ofstream m_logFile;

		const bool m_canWrite;
};

LogWriter &operator<<(LogWriter &writer, const std::string data);

#endif