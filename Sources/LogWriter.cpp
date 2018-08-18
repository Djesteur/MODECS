#include "LogWriter.hpp"

LogWriter::LogWriter(const std::string filePath):
	m_logFile{filePath},
	m_canWrite{m_logFile} {

		if(!m_canWrite) { std::cerr << "LogWriter Warning: can't write to file " << filePath << std::endl; }
	}

LogWriter::~LogWriter() { m_logFile.close(); }

void LogWriter::addRDBuf(std::ostream &stream) {

	if(m_canWrite) { stream.rdbuf(m_logFile.rdbuf()); }
	else { stream.rdbuf(nullptr);}
}