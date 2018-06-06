#include "LogWriter.hpp"

LogWriter::LogWriter(const std::string filePath):
	m_logFile{filePath},
	m_canWrite{m_logFile} {

		if(!m_canWrite) { std::cerr << "LogWriter Warning: can't write to file" << filePath << std::endl; }
	}

LogWriter::~LogWriter() { m_logFile.close(); }
	

void LogWriter::write(const std::string data) {

	if(m_canWrite) {

		try { m_logFile << data; }
		catch(const std::exception &e) { std::cerr << e.what(); }
	}
}

void LogWriter::addRDBuf(std::ostream &stream) {

	if(m_canWrite) { stream.rdbuf(m_logFile.rdbuf()); }
	else { stream.rdbuf(nullptr);}
}

LogWriter &operator<<(LogWriter &writer, const std::string data) {

	writer.write(data);
	return writer;
}

