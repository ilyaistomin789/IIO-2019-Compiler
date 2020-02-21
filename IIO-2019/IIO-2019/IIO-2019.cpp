// IIO-2019.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Libraries.h"
#include "LexicalAnalysis.h"
#include "MFST.h"
#include "Generation.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;										// Инициализировали переменную, отвечающую за вывод в .log файл
	try																	// Блок проверки на исключения, в catch заносится первое попавшееся исключение
	{
		Parm::PARM parm = Parm::getparm(argc, argv);					// Инициализируем переменную типа PARM значениями, введенными при запуске проекта через консоль
		log = Log::GetLog(parm.log);									// Задаем значение переменной log, передавая ей имя файла, указанного с консоли
		Log::WriteLog(log);												// Записываем оглавление лог файла
		Log::WriteParm(log, parm);

		IN::IN in = IN::GetIn(parm.in);								// Считываем файл и при встрече любого сепаратора, разделяем слова, записывая их в отдельную структуру
		Log::WriteIn(log, in);

		log = Log::GetLog(parm.lex);
		char header[] = "Lexical and sintaxis analisis\n";
		Log::WriteLine(log, header, "");
		Lex::LEX lex = Lex::Lexer(in, log);								// Лексический анализ. В соответствии со словами, полученными на пред. этапе, составляем таблицу лексем по этим словам. И табл. идент.

		log = Log::GetLog(parm.sin);
		MFST_TRACE_START(log);
		MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start(log);
		mfst.savededucation(); //для дерева разбора
		mfst.printrules(log);

		CallPolishNotation(&lex.lextable, &lex.idtable);
		LT::Write(log, lex.lextable);
		IT::WriteTable(log, lex.idtable);
		cout << endl << "-------------------После вызова польской нотации-------------------------- " << endl;
		LT::ShowTable(lex.lextable);

		log = Log::GetLog(parm.out);
		Generation::Generation(lex, log);

		cout << "\nSuccessfully complete.\n";
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
