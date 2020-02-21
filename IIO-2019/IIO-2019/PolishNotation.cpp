#include "Libraries.h"
#include <stack>
#include "LexicalAnalysis.h"
using namespace std;

void CallPolishNotation(LT::LexTable* lextable, IT::IdTable* idtable)
{
	for (int i = 0; i < lextable->size; i++) {
		if (lextable->table[i].lexema == LEX_EQUAL)
		{
			PolishNotation(++i, lextable, idtable);
		}
	}
}

void AddToResult(IT::IdTable* idtable, LT::Entry* result, LT::Entry elementLT, int *pos, int *flag, int lenout, int lextable_pos)
{
	if (idtable->table[elementLT.indexTI].idFirstInLT >= lextable_pos && idtable->table[elementLT.indexTI].idFirstInLT < (lextable_pos + lenout))
	{
		idtable->table[elementLT.indexTI].idFirstInLT = lextable_pos + *flag;
	}
	*flag += 1;
	result[*pos] = elementLT;
	*pos += 1;
}

void AddToResult(stack<LT::Entry>* stk, IT::IdTable* idtable, LT::Entry* result, int *pos, int *flag, int lenout, int lextable_pos)
{
	if (idtable->table[stk->top().indexTI].idFirstInLT >= lextable_pos && idtable->table[stk->top().indexTI].idFirstInLT < (lextable_pos + lenout))
	{
		idtable->table[stk->top().indexTI].idFirstInLT = lextable_pos + *flag;
	}
	*flag += 1;
	result[*pos] = stk->top();
	*pos += 1;
	stk->pop();
}

bool PolishNotation(int lextable_pos, LT::LexTable* lextable, IT::IdTable* idtable)
{
	stack<LT::Entry> stackLTelements;
	LT::Entry* elementsLT = new LT::Entry[lextable->size];
	int ncomma = 0,
		flag = 0,
		waste = 0,
		funcPositionTI = -1,
		lenght = 0,							//����� �����
		lenout = 0,							//����� �������� ������
		semicolonid;						//�� ��� �������� ������� � ������ � �������
	LT::Entry tempLTEntry, bufEntry;

	for (int i = lextable_pos; lextable->table[i].lexema != LEX_SEMICOLON; i++) {
		lenout = i + 1;
		semicolonid = i + 1;
	}

	for (int i = lextable_pos; i < lenout; i++) {
		tempLTEntry = lextable->table[i];
		if (tempLTEntry.lexema == LEX_ID || tempLTEntry.lexema == LEX_NUM || tempLTEntry.lexema == LEX_STR ||
			tempLTEntry.lexema == LEX_STRTON || tempLTEntry.lexema == LEX_STRLN)
		{
			if (idtable->table[tempLTEntry.indexTI].idType == IT::IDTYPE_FUN)
			{
				funcPositionTI = tempLTEntry.indexTI;
				continue;
			}
			AddToResult(idtable, elementsLT, tempLTEntry, &lenght, &flag, lenout, lextable_pos);
		}
		else {
			if (tempLTEntry.lexema == LEX_ACTION)
			{
				while (!stackLTelements.empty() && stackLTelements.top().priority >= tempLTEntry.priority)
				{
					if (stackLTelements.top().lexema != LEX_LEFTHESIS)
					{
						AddToResult(&stackLTelements, idtable, elementsLT, &lenght, &flag, lenout, lextable_pos);
					}
					else break;
				}
				stackLTelements.push(tempLTEntry);
			}
			if (tempLTEntry.lexema == LEX_COMMA)
			{
				ncomma++;
				while (stackLTelements.top().lexema == LEX_ACTION) {
					AddToResult(&stackLTelements, idtable, elementsLT, &lenght, &flag, lenout, lextable_pos);
				}
			}
			else if (tempLTEntry.lexema != LEX_RIGHTHESIS)
			{
				if (stackLTelements.empty() || stackLTelements.top().lexema == LEX_LEFTHESIS || tempLTEntry.lexema == LEX_LEFTHESIS)
				{
					stackLTelements.push(tempLTEntry);
				}
			}
			if (tempLTEntry.lexema == LEX_RIGHTHESIS && tempLTEntry.priority != 4)
			{
				waste += 2;
				while (stackLTelements.top().lexema != LEX_LEFTHESIS) {
					AddToResult(&stackLTelements, idtable, elementsLT, &lenght, &flag, lenout, lextable_pos);
				}
				stackLTelements.pop();
			}
			if (tempLTEntry.lexema == LEX_RIGHTHESIS && tempLTEntry.priority == 4)
			{
				bufEntry.lexema = LEX_SUBST;
				bufEntry.indexTI = funcPositionTI;
				bufEntry.lineNo = elementsLT[lenght - 1].lineNo;
				bufEntry.priority = ncomma + 1; //����� �������� ���-�� ���������� � �������
				elementsLT[lenght++] = bufEntry;
				if (ncomma != 0)
				{
					waste += ncomma;
					ncomma = 0;
				}
				while (stackLTelements.top().lexema != LEX_LEFTHESIS) {
					AddToResult(&stackLTelements, idtable, elementsLT, &lenght, &flag, lenout, lextable_pos);
				}
				stackLTelements.pop();
				waste += 2;
			}
		}
	}
	while (!stackLTelements.empty()) {
		AddToResult(&stackLTelements, idtable, elementsLT, &lenght, &flag, lenout, lextable_pos);
	}

	for (int i = lextable_pos, k = 0; i < lextable_pos + lenght; i++, k++) {
		lextable->table[i] = elementsLT[k];												//������ � ������� �������� ������
	}
	lextable->table[lextable_pos + lenght] = lextable->table[semicolonid];			//������� �������� � ������ � �������

	for (int i = 0; i < waste; i++) {
		lextable->size--;
		for (int j = lextable_pos + lenght + 1; j < lextable->size; j++) {  // �������� �� �������� ��������
			lextable->table[j] = lextable->table[j + 1];
			if (lextable->table[j].indexTI != LT_TI_NULLIDX && idtable->table[lextable->table[j].indexTI].idFirstInLT == (j + 1))
			{
				idtable->table[lextable->table[j].indexTI].idFirstInLT -= 1;
			}
		}
	}
	return true;
}
