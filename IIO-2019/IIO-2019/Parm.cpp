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
		wchar_t* tempString;											// Широкая строка, нужна для корректного отображения на консоли, размером 2 байта
		for (int i = 1; i < argc; i++) {								// Начало с 1, потому что нулевой аргумент это SAA.exe
			if (wcslen(argv[i]) >= PARM_MAX_SIZE)						// Проверка на длину i-того аргумента
			{
				throw ERROR_THROW(101);
			}

			if (tempString = wcsstr(argv[i], PARM_IN))					// wcsstr - функция, которая пробует найти в строке указанную подстроку, если нет - то NULL.
			{															// Пытаемся найти в i-том аргументе префикс -in:
				wcscpy_s(parmStruct.in, tempString + wcslen(PARM_IN));	// Копируем в parm.in строку, смещая указатель на размер длины префикса -in:
				isIn = true;											// Если нашли, флажок - true
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
		if (isIn == false)										// Если параметра -in: нету, генерируем исключение, так как он обязательно должен быть указан
		{
			throw ERROR_THROW(100);
		}
		if (isOut == false)										// Для всех остальных параметров, если их нет - копируем в их имя имя твоего -in: файла, что был выше
		{
			wcscpy_s(parmStruct.out, parmStruct.in);			// Копируем в parm.out значение parm.in, если аргумент -out: не указан
			wcsncat_s(parmStruct.out, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT));				// Добавляем к parm.out расширение файла, в данном случае .asm
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