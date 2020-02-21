#include "Libraries.h"

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		bool isIn = false,
			isOut = false,
			isLog = false,
			isLex = false,
			isSin = false;

		PARM parmStruct;
		wchar_t* tempString;											// ������� ������, ����� ��� ����������� ����������� �� �������, �������� 2 �����
		for (int i = 1; i < argc; i++) {								// ������ � 1, ������ ��� ������� �������� ��� SAA.exe
			if (wcslen(argv[i]) >= PARM_MAX_SIZE)						// �������� �� ����� i-���� ���������
			{
				throw ERROR_THROW(101);
			}

			if (tempString = wcsstr(argv[i], PARM_IN))					// wcsstr - �������, ������� ������� ����� � ������ ��������� ���������, ���� ��� - �� NULL.
			{															// �������� ����� � i-��� ��������� ������� -in:
				wcscpy_s(parmStruct.in, tempString + wcslen(PARM_IN));	// �������� � parm.in ������, ������ ��������� �� ������ ����� �������� -in:
				isIn = true;											// ���� �����, ������ - true
			}

			if (tempString = wcsstr(argv[i], PARM_OUT))
			{
				wcscpy_s(parmStruct.out, tempString + wcslen(PARM_OUT));
				isOut = true;
			}

			if (tempString = wcsstr(argv[i], PARM_LOG))
			{
				wcscpy_s(parmStruct.log, tempString + wcslen(PARM_LOG));
				isLog = true;
			}

			if (tempString = wcsstr(argv[i], PARM_LEX))
			{
				wcscpy_s(parmStruct.lex, tempString + wcslen(PARM_LEX));
				isLex = true;
			}

			if (tempString = wcsstr(argv[i], PARM_SIN))
			{
				wcscpy_s(parmStruct.sin, tempString + wcslen(PARM_SIN));
				isSin = true;
			}
		}
		if (isIn == false)										// ���� ��������� -in: ����, ���������� ����������, ��� ��� �� ����������� ������ ���� ������
		{
			throw ERROR_THROW(100);
		}
		if (isOut == false)										// ��� ���� ��������� ����������, ���� �� ��� - �������� � �� ��� ��� ������ -in: �����, ��� ��� ����
		{
			wcscpy_s(parmStruct.out, parmStruct.in);			// �������� � parm.out �������� parm.in, ���� �������� -out: �� ������
			wcsncat_s(parmStruct.out, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT));				// ��������� � parm.out ���������� �����, � ������ ������ .asm
		}
		if (isLog == false)
		{
			wcscpy_s(parmStruct.log, parmStruct.in);
			wcsncat_s(parmStruct.log, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));
			
		}

		if (isLex == false)
		{
			wcscpy_s(parmStruct.lex, parmStruct.in);
			wcsncat_s(parmStruct.lex, PARM_LEX_DEFAULT_EXT, wcslen(PARM_LEX_DEFAULT_EXT));
		}
		if (isSin == false)
		{
			wcscpy_s(parmStruct.sin, parmStruct.in);
			wcsncat_s(parmStruct.sin, PARM_SIN_DEFAULT_EXT, wcslen(PARM_SIN_DEFAULT_EXT));
		}
		return parmStruct;
	}
};