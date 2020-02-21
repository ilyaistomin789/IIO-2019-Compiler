#include "Libraries.h"
#include "FST.h"
#include "LT.h"

namespace FST
{
	bool step(FST& fst, short*& rstates)	//���� ��� ��������
	{
		bool rc = false;
		swap(rstates, fst.rstates);
		//�� ���������� ���������
		for (short i = 0; i < fst.nstates; i++) {
			//���� �������� � ������� ����� ������� ������� �������
			if (rstates[i] == fst.position)
			{
				//��������� �� ���� ����� ������� �������
				for (short j = 0; j < fst.nodes[i].n_relation; j++) {
					//���� ������ �������� ��������� � �������� � ������
					if (fst.nodes[i].relations[j].symbol == fst.str[fst.position])
					{
						//�� ��������� � �������� ������ ��������
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					};
				};
			}
		};
		return rc;
	};

	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];//�������� ������
		memset(rstates, 0xff, sizeof(short) * fst.nstates);//� ������� ����� ������� ������� ��� -1
		short lstring = fst.str.size();//������ �������
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++) {
			fst.position++;				//���������� �������
			rc = step(fst, rstates);	//���� ��� ��������
		};
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	}

	RELATION::RELATION(char c, short nn)
	{
		symbol = c;
		nnode = nn;
	};

	NODE::NODE()	//�� ���������
	{
		n_relation = 0;
		RELATION* relations = NULL;
	};

	NODE::NODE(short n, RELATION rel, ...)	//� �����������
	{
		n_relation = n;
		RELATION* p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++) {
			relations[i] = p[i];
		}
	};

	FST::FST(char c, LEX_TYPE l_t, string s, short ns, NODE n, ...)
	{
		lexema = c;
		str = s;
		nstates = ns;
		lex_type = l_t;
		nodes = new NODE[ns];
		NODE* p = &n;
		for (int k = 0; k < ns; k++) nodes[k] = p[k];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1;
	};

	FST::FST() {}

	FST* arr_of_fst_op()
	{
		FST fstAriph(LEX_ACTION, SYMB_ACTION, "", 2,
			NODE(5, RELATION('+', 1), RELATION('-', 1), RELATION('*', 1),RELATION('A',1), RELATION('O', 1)), \
			NODE()
		);
		FST fstInversion(LEX_NOT, SYMB_ACTION, "", 2,
			NODE(1,RELATION('N',1), \
			NODE())
			);
		FST fstLeftHesis(LEX_LEFTHESIS, SYMB_NEED_PRIORITY, "", 2,
			NODE(1, RELATION('(', 1)), \
			NODE()
		);
		FST fstRightHesis(LEX_RIGHTHESIS, SYMB_NEED_PRIORITY, "", 2,
			NODE(1, RELATION(')', 1)), \
			NODE()
		);
		FST fstEqual(LEX_EQUAL, SYMB_LEXEMS, "", 2,
			NODE(1, RELATION('=', 1)), \
			NODE()
		);
		FST fstLeftBrace(LEX_LEFTBRACE, SYMB_LEXEMS, "", 2,
			NODE(1, RELATION('{', 1)), \
			NODE()
		);
		FST fstRightBrace(LEX_RIGHTBRACE, SYMB_LEXEMS, "", 2,
			NODE(1, RELATION('}', 1)), \
			NODE()
		);
		FST fstSemicolon(LEX_SEMICOLON, SYMB_LEXEMS, "", 2,
			NODE(1, RELATION(';', 1)), \
			NODE()
		);

		FST fstComma(LEX_COMMA, SYMB_NEED_PRIORITY, "", 2,
			NODE(1, RELATION(',', 1)), \
			NODE()
		);

		FST fstNumLit(LEX_NUM, SYMB_LITERAL, "", 2,
			NODE(10,
				RELATION('0', 1), RELATION('1', 1), RELATION('2', 1),
				RELATION('3', 1), RELATION('4', 1), RELATION('5', 1),
				RELATION('6', 1), RELATION('7', 1), RELATION('8', 1),
				RELATION('9', 1)),
			NODE()
		);
		FST fstId(LEX_ID, SYMB_TABLE_ID, "", 2,
			NODE(26, RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1),
				RELATION('e', 1), RELATION('f', 1), RELATION('g', 1), RELATION('h', 1),
				RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),
				RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1),
				RELATION('q', 1), RELATION('r', 1), RELATION('s', 1), RELATION('t', 1),
				RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),
				RELATION('y', 1), RELATION('z', 1)),
			NODE()
		);
		
		FST* result = new FST[ARR_OF_FST_OP_SIZE];
		result[0] = fstAriph;				//
		result[1] = fstSemicolon;			//
		result[2] = fstComma;				//
		result[3] = fstLeftHesis;			//
		result[4] = fstRightHesis;			//
		result[5] = fstEqual;				//
		result[6] = fstLeftBrace;			//	
		result[7] = fstRightBrace;			//
		result[8] = fstNumLit;
		result[9] = fstInversion;
		result[10] = fstId;
		return result;
	}
	FST* arr_of_fst_word()
	{
		FST fstDig(LEX_NUM, SYMB_LEXEMS, "", 4,
			NODE(1, RELATION('n', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('m', 3)),
			NODE()
		);
		FST fstStr(LEX_STR, SYMB_LEXEMS, "", 4,
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('t', 2)),
			NODE(1, RELATION('r', 3)),
			NODE()
		);
		FST fstFunc(LEX_FUNC, SYMB_LEXEMS, "", 5,
			NODE(1, RELATION('f', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('n', 3)),
			NODE(1, RELATION('c', 4)),
			NODE()
		);
		FST fstVar(LEX_RC, SYMB_LEXEMS, "", 3,
			NODE(1, RELATION('r', 1)),
			NODE(1, RELATION('c', 2)),
			NODE()
		);
		FST fstStart(LEX_ENTRY, SYMB_LEXEMS, "", 6,
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('t', 2)),
			NODE(1, RELATION('a', 3)),
			NODE(1, RELATION('r', 4)),
			NODE(1, RELATION('t', 5)),
			NODE()
		);

		FST fstRead(LEX_READ, SYMB_LEXEMS, "", 5,
			NODE(1, RELATION('r', 1)), \
			NODE(1, RELATION('e', 2)), \
			NODE(1, RELATION('a', 3)), \
			NODE(1, RELATION('d', 4)),
			NODE()
		);
		FST fstComeback(LEX_COMEBACK, SYMB_LEXEMS, "", 9,
			NODE(1, RELATION('c', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('m', 3)),
			NODE(1, RELATION('e', 4)),
			NODE(1, RELATION('b', 5)),
			NODE(1, RELATION('a', 6)),
			NODE(1, RELATION('c', 7)),
			NODE(1, RELATION('k', 8)),
			NODE()
		);
		FST fstNumLit(LEX_NUM, SYMB_LITERAL, "", 2, NODE(20, RELATION('0', 0), RELATION('1', 0), RELATION('2', 0),
			RELATION('3', 0), RELATION('4', 0), RELATION('5', 0),
			RELATION('6', 0), RELATION('7', 0), RELATION('8', 0),
			RELATION('9', 0),
			RELATION('0', 1), RELATION('1', 1), RELATION('2', 1),
			RELATION('3', 1), RELATION('4', 1), RELATION('5', 1),
			RELATION('6', 1), RELATION('7', 1), RELATION('8', 1),
			RELATION('9', 1)),
			NODE()
		);
		FST fstId(LEX_ID, SYMB_TABLE_ID, "", 2,
			NODE(52, RELATION('a', 0), RELATION('b', 0), RELATION('c', 0), RELATION('d', 0),
				RELATION('e', 0), RELATION('f', 0), RELATION('g', 0), RELATION('h', 0),
				RELATION('i', 0), RELATION('j', 0), RELATION('k', 0), RELATION('l', 0),
				RELATION('m', 0), RELATION('n', 0), RELATION('o', 0), RELATION('p', 0),
				RELATION('q', 0), RELATION('r', 0), RELATION('s', 0), RELATION('t', 0),
				RELATION('u', 0), RELATION('v', 0), RELATION('w', 0), RELATION('x', 0),
				RELATION('y', 0), RELATION('z', 0),
				RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1),
				RELATION('e', 1), RELATION('f', 1), RELATION('g', 1), RELATION('h', 1),
				RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),
				RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1),
				RELATION('q', 1), RELATION('r', 1), RELATION('s', 1), RELATION('t', 1),
				RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),
				RELATION('y', 1), RELATION('z', 1)),
			NODE()
		);
		FST fstStrLit(LEX_STR, SYMB_LITERAL, "", 4,
			NODE(2, RELATION('"', 1), RELATION('"', 2)), \
			NODE(276, \
				RELATION('A', 1), RELATION('B', 1), RELATION('C', 1), RELATION('D', 1), RELATION('E', 1), RELATION('F', 1), \
				RELATION('G', 1), RELATION('H', 1), RELATION('I', 1), RELATION('J', 1), RELATION('K', 1), RELATION('L', 1), \
				RELATION('M', 1), RELATION('N', 1), RELATION('O', 1), RELATION('P', 1), RELATION('Q', 1), RELATION('R', 1), \
				RELATION('S', 1), RELATION('T', 1), RELATION('U', 1), RELATION('V', 1), RELATION('W', 1), RELATION('X', 1), \
				RELATION('Y', 1), RELATION('Z', 1), \
				RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1), RELATION('f', 1), \
				RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1), \
				RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), RELATION('q', 1), RELATION('r', 1), \
				RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1), \
				RELATION('y', 1), RELATION('z', 1), RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), \
				RELATION('5', 1), RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1), \
				\
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), \
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), \
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), \
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), \
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), \
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), \
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), \
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), \
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), \
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), \
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), \
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION(' ', 1), RELATION('.', 1), RELATION(',', 1), \
				RELATION('?', 1), RELATION('!', 1), RELATION(';', 1), RELATION(':', 1), RELATION('-', 1), RELATION(')', 1), \
				RELATION('(', 1), \
				\
				RELATION('A', 2), RELATION('B', 2), RELATION('C', 2), RELATION('D', 2), RELATION('E', 2), RELATION('F', 2), \
				RELATION('G', 2), RELATION('H', 2), RELATION('I', 2), RELATION('J', 2), RELATION('K', 2), RELATION('L', 2), \
				RELATION('M', 2), RELATION('N', 2), RELATION('O', 2), RELATION('P', 2), RELATION('Q', 2), RELATION('R', 2), \
				RELATION('S', 2), RELATION('T', 2), RELATION('U', 2), RELATION('V', 2), RELATION('W', 2), RELATION('X', 2), \
				RELATION('Y', 2), RELATION('Z', 2), \
				RELATION('a', 2), RELATION('b', 2), RELATION('c', 2), RELATION('d', 2), RELATION('e', 2), RELATION('f', 2), \
				RELATION('g', 2), RELATION('h', 2), RELATION('i', 2), RELATION('j', 2), RELATION('k', 2), RELATION('l', 2), \
				RELATION('m', 2), RELATION('n', 2), RELATION('o', 2), RELATION('p', 2), RELATION('q', 2), RELATION('r', 2), \
				RELATION('s', 2), RELATION('t', 2), RELATION('u', 2), RELATION('v', 2), RELATION('w', 2), RELATION('x', 2), \
				RELATION('y', 2), RELATION('z', 2), RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2), \
				RELATION('5', 2), RELATION('6', 2), RELATION('7', 2), RELATION('8', 2), RELATION('9', 2), RELATION('0', 2), \
				\
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), \
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), \
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), \
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), \
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), \
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), \
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), \
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), \
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), \
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), \
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), \
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION(' ', 2), RELATION('.', 2), RELATION(',', 2), \
				RELATION('?', 2), RELATION('!', 2), RELATION(';', 2), RELATION(':', 2), RELATION('-', 2), RELATION(')', 2), \
				RELATION('(', 2)), \
			\
			NODE(1, RELATION('"', 3)), \
			NODE()
		);

			
		FST fstStrToN(LEX_STRTON, SYMB_STATIC_LIB, "", 7,
			NODE(1, RELATION('s', 1)), \
			NODE(1, RELATION('t', 2)), \
			NODE(1, RELATION('r', 3)), \
			NODE(1, RELATION('t', 4)), \
			NODE(1, RELATION('o', 5)), \
			NODE(1, RELATION('n', 6)), \
			NODE()
		);
		FST fstStrl(LEX_STRLN, SYMB_STATIC_LIB, "", 6,
			NODE(1, RELATION('s', 1)), \
			NODE(1, RELATION('t', 2)), \
			NODE(1, RELATION('r', 3)), \
			NODE(1, RELATION('l', 4)), \
			NODE(1, RELATION('n', 5)),
			NODE()
		);
		FST fstCycle(LEX_CYCLE,SYMB_LEXEMS,"",6,
			NODE(1,RELATION('c',1)), \
			NODE(1, RELATION('y', 2)), \
			NODE(1, RELATION('c', 3)), \
			NODE(1, RELATION('l', 4)), \
			NODE(1, RELATION('e', 5)), 
			NODE()
		);
		FST* result = new FST[ARR_OF_FST_WORD_SIZE];
		result[0] = fstDig;
		result[1] = fstStr;
		result[2] = fstVar;
		result[3] = fstFunc;
		result[4] = fstStart;
		result[5] = fstComeback;
		result[6] = fstNumLit;
		result[7] = fstStrLit;
		result[8] = fstRead;
		result[9] = fstStrToN;
		result[10] = fstStrl;
		result[11] = fstCycle;
		result[12] = fstId;
		
		return result;
	}
}