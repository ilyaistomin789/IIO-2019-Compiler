#include "Libraries.h"
#include "Log.h"
namespace Log
{
	LOG GetLog(wchar_t logfile[])
	{
		LOG log;
		wcscpy_s(log.logfile, logfile);					// �������� ��� ����� � ���������
		log.stream = new ofstream;						// ������� ��������� ������ ����� ������
		log.stream->open(logfile, ios_base::out);		// ofstream - ��� ������ � ����, ���� ����� ���, �� ����� ������
		if (!log.stream->is_open()) {
			throw ERROR_THROW(112);
		}
		return log;
	}

	void WriteLine(LOG log, char* c, ...)
	{
		char** logparm = &c;
		while (strcmp(*logparm, "")) {
			*(log.stream) << *logparm;
			logparm++;
		}
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t** logparm = &c;
		char buf[PARM_MAX_SIZE];
		while (wcscmp(*logparm, L"")) {
			wcstombs(buf, *logparm, PARM_MAX_SIZE);
			*(log.stream) << buf;
			logparm++;
		}
	}

	void WriteLog(LOG log)								// ���������� � ��� ����������
	{
		char buffer[PARM_MAX_SIZE];
		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, PARM_MAX_SIZE, "����: %d.%m.%y %H:%M:%S", timeinfo);
		(*log.stream) << "----------�������� " << buffer << "----------" << endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char buf[PARM_MAX_SIZE];
		*(log.stream) << "---- ��������� --------" << endl;
		wcstombs(buf, parm.in, PARM_MAX_SIZE);
		*(log.stream) << "-in:  " << buf << endl;
		wcstombs(buf, parm.out, PARM_MAX_SIZE);
		*(log.stream) << "-out: " << buf << endl;
		wcstombs(buf, parm.log, PARM_MAX_SIZE);
		*(log.stream) << "-log: " << buf << endl;
		wcstombs(buf, parm.lex, PARM_MAX_SIZE);
		*(log.stream) << "-lex: " << buf << endl;
		wcstombs(buf, parm.sin, PARM_MAX_SIZE);
		*(log.stream) << "-sin: " << buf << endl;
	}

	void WriteIn(LOG log, IN::IN in)
	{
		*(log.stream) << "---- �������� ������ ------" << endl;
		*(log.stream) << "���������� ��������:" << in.size << endl;
		*(log.stream) << "���������� �����   :" << in.lines << endl;
		*(log.stream) << "���������� ����������������� ��������: " << in.ignor << endl;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		if (log.stream != 0) {
			*log.stream << "\n������ " << error.id << ": " << error.message;
			if (error.inText.line != -1) {
				*log.stream << ", ������ " << error.inText.line;
			}
			if (error.inText.positionInTheString != -1) {
				*log.stream << ", ������� " << error.inText.positionInTheString << endl << endl;
			}
		}

		cout << "\n������ " << error.id << ": " << error.message;
		if (error.inText.line != -1) {
			cout << " ������ " << error.inText.line;
		}
		if (error.inText.positionInTheString != -1) {
			cout << ", ������� " << error.inText.positionInTheString << endl << endl;
		}
		cout << endl;
	}

	void Close(LOG log)
	{
		if (log.stream != 0) {
			log.stream->close();
		}
	}
}