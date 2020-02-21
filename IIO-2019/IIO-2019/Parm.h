#pragma once

#define PARM_MAX_SIZE 100					// ������������ ����� ������ ���������

#define PARM_IN  L"-in:"					// ���� ��� ����� ��������� ����
#define PARM_OUT L"-out:"					// ���� ��� ����� ���������� ����	
#define PARM_LOG L"-log:"					// ���� ��� ����� ������� 

#define PARM_LEX L"-lex:"					// ���� ��� �����-��������� ������������ � �������������� �������
#define PARM_SIN L"-sin:"					// ���� ��� �����-��������� ��������������� �������

#define PARM_OUT_DEFAULT_EXT L".asm"		// ���������� ����� ���������� ���� �� ���������
#define PARM_LOG_DEFAULT_EXT L".log"		// ���������� ����� ��������� �� ���������
#define PARM_LEX_DEFAULT_EXT L".lx" 		// ���������� ����� ��������� ������������ �������
#define PARM_SIN_DEFAULT_EXT L".sin" 		// ���������� ����� ��������� ��������������� �������
#include <tchar.h>

namespace Parm
{
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE];			// -in:     ��� ����� ��������� ����
		wchar_t out[PARM_MAX_SIZE];			// -out:    ��� ����� ���������� ����
		wchar_t log[PARM_MAX_SIZE];			// -log:    ��� ����� ���������
		wchar_t lex[PARM_MAX_SIZE];			// -lex:	��� ����� ��������� ������������ �������
		wchar_t sin[PARM_MAX_SIZE];			// -sin:	��� ����� ��������� ��������������� �������
	};

	PARM getparm(int argc, _TCHAR* argv[]);
}
