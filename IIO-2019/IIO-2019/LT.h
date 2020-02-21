#pragma once
#include "Log.h"
#define LT_NOPRIORITY 0xffffffff		//��� ����������
#define LEXEMA_FIXZISE 1				//������������� ������ �������
#define LT_MAXSIZE 4096			//������������ ���-�� ����� � ������� ������   
#define LT_TI_NULLIDX 0xffffffff		//��� �������� ������� ���������������
#define LEX_T			't'				
#define LEX_NUM			'n'				//	digital
#define LEX_STR			's'				//	string
#define LEX_RC			'r'				//	var
#define LEX_FUNC		'f'				//	function
#define LEX_ENTRY		'm'				//	start
#define LEX_COMEBACK	'c'				//	ret
#define LEX_LITERAL		'l'				//	�������
#define LEX_READ		'w'				//	show
#define LEX_STRTON		'j'				//	strton
#define LEX_STRLN		'k'				//	strlen
#define LEX_ID			'i'				//	�������������
#define LEX_ACTION		'v'
#define LEX_SEMICOLON	';'				//	;
#define LEX_COLON		':'				//	:
#define LEX_COMMA		','				//	,
#define LEX_LEFTHESIS	'('				//	(
#define LEX_RIGHTHESIS	')'				//	)
#define LEX_EQUAL		'='				//  =
#define LEX_LEFTBRACE	'{'				//	{
#define LEX_RIGHTBRACE	'}'				//	}
#define LEX_LESS		'<'
#define LEX_MORE		'>'
#define LEX_AND			'A'
#define LEX_OR			'O'
#define LEX_NOT			'~'
#define LEX_PLUS		'+'				//	+
#define LEX_MINUS		'-'				//	-
#define LEX_MULTIPLY	'*'				//	*
#define LEX_STRLIT		'"'				//  "
#define LEX_SUBST		'@'
#define LEX_L			'L'				//  L
#define LEX_SEP			'|'				// ������ ����� ������
#define LEX_CYCLE		'b'				// ����

namespace LT
{										// ������� ������
	struct Entry
	{
		char lexema;						// �������
		int lineNo;							// ����� ������ � �������� ����
		int indexTI;						// ������ � ������� ��������������� 
		short priority;						// ��������� ��� ��������
	};

	struct LexTable
	{
		int maxize;							// ������� ������� ������ 
		int size;							// ������� ������ ������� ������
		Entry* table;						// ������ ����� ������� ������	
	};

	LexTable Create(int size);
	Entry GetEntry(LexTable& lextable, int n);
	Entry Add(LexTable& lextable, Entry entry);
	void ShowTable(LexTable& lexTable);
	void Write(Log::LOG log, LexTable& lexTable);
}