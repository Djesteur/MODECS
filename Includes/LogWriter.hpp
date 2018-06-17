/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

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

		template<typename T>
		void write(const T data) {

			if(m_canWrite) {

				try { m_logFile << data << std::flush; }
				catch(const std::exception &e) { std::cerr << e.what(); }
			}
		}

		void addRDBuf(std::ostream &stream);

	private:

		std::ofstream m_logFile;

		const bool m_canWrite;
};

template<typename T>
LogWriter &operator<<(LogWriter &writer, const T data) {

	writer.write(data);
	return writer;
}



#endif