#pragma once
#include "Libraries.h"
#include "In.h"

namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];		// ��� ����� ���������
		ofstream* stream;					// �������� �����
	};

	static const LOG INITLOG = { L"", NULL };		// ��������� ��� ��������� ������������� LOG

	LOG  GetLog(wchar_t logfile[]);					// ������������ ��������� LOG
	void WriteLine(LOG log, char* c, ...);			// ������� � �������� ������������ �����
	void WriteLine(LOG log, wchar_t* c, ...);		// ������� � �������� ������������ �����
	void WriteLog(LOG log);							// ������� � �������� ���������
	void WriteParm(LOG log, Parm::PARM parm);		// ������� � �������� ���������� � ������� ����������
	void WriteIn(LOG log, IN::IN in);				// ������� � �������� ���������� � ������� ������
	void WriteError(LOG log, Error::ERROR error);	// ������� � ������ ���������� �� ������
	void Close(LOG log);							// ������� ��������
}