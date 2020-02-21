#include "Libraries.h"
namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "������������ ��� ������"),
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "|IN|: �������� -in ������ ���� �����"),
		ERROR_ENTRY(101, "|IN|: ��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(102),	ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110, "|IN|: ������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "|IN|: ������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112, "|IN|: ������ ��� �������� ����� ���������(-log)"),
		ERROR_ENTRY(113, "|IN|: �������� ������������ ������ ��������� ����"),
		ERROR_ENTRY(114, "|IN|: �������� ������������ ������ ���������� �������� "),
		ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),

		ERROR_ENTRY(120, "|LA|: ������� �������� �� ���������"),
		ERROR_ENTRY(121, "|LA|: ������� ������ �����������"),
		ERROR_ENTRY(122, "|LA|: ������� ��������������� �����������"),
		ERROR_ENTRY(123, "|LA|: ������������ ��������������"),
		ERROR_ENTRY(124, "|LA|: ������������ �������������� ��������"),
		ERROR_ENTRY(125, "|LA|: ���������� ����������� �������� ����"),
		ERROR_ENTRY_NODEF(126),ERROR_ENTRY_NODEF(127),ERROR_ENTRY_NODEF(128), ERROR_ENTRY_NODEF(129),

		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY(600, "|SA|: �������� ��������� ���������"),
		ERROR_ENTRY(601, "|SA|: ��������� ��������"),
		ERROR_ENTRY(602, "|SA|: �������� ���������"),
		ERROR_ENTRY(603, "|SA|: ������ � ���������� ������� ��� ��������� ����������"),
		ERROR_ENTRY(604, "|SA|: ������ � ��������� ���������� ������� strton ����������� ����������"),
		ERROR_ENTRY(605, "|SA|: ���� �������� �������� ������������"),
		ERROR_ENTRY(606, "|SA|: ������ � ��������� ���������� ������� strl ����������� ����������"),
		ERROR_ENTRY(607, "|SA|: ������ � ���������� ���������� �������"),
		ERROR_ENTRY(608, "|SA|: ������ ��������������� ���������"),

		ERROR_ENTRY(609, "|SA|: �������� ��������� ���������. � ����� IIO-2019 �� ������������� ���������� ���������� ��� �������"), ERROR_ENTRY_NODEF(610),

		ERROR_ENTRY(611, "|SA|: �� ������ ����� �������"),
		ERROR_ENTRY(612, "|SA|: ������� ��������� �� ��������� (���� �� ������)"),
		ERROR_ENTRY(613, "|SA|: ����� ����� � ��������� �� ������"),
		ERROR_ENTRY_NODEF(614),	ERROR_ENTRY_NODEF(615), ERROR_ENTRY_NODEF(616),
		ERROR_ENTRY_NODEF(617), ERROR_ENTRY_NODEF(618), ERROR_ENTRY_NODEF(619),
		ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650), ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),

		ERROR_ENTRY(700, "|SMA|: ��������� ���������� ��������������"),
		ERROR_ENTRY(701, "|SMA|: ������ � ���� ��������������"),
		ERROR_ENTRY(702, "|SMA|: ������ � ������������ ��������� � �������"),
		ERROR_ENTRY(703, "|SMA|: � ������� �� �������� ���������"),
		ERROR_ENTRY(704, "|SMA|: ��� ������ ���������� ��������� �� ������������� �������������� ��������������"),
		ERROR_ENTRY(705, "|SMA|: ������ � ��������� ���������� ������� strton ����������� ����������"),
		ERROR_ENTRY(706, "|SMA|: ������������� �������������"),
		ERROR_ENTRY(707, "|SMA|: �������������� ����� � ��������� ������������"),
		ERROR_ENTRY(708, "|SMA|: �������� ��������� ���������"),
		ERROR_ENTRY(709, "|SMA|: �������� ������������ ������ ��������������"),
		ERROR_ENTRY(710,"|SMA|: ��������� ���������� ����� �����"),ERROR_ENTRY_NODEF10(720),ERROR_ENTRY_NODEF10(730),ERROR_ENTRY_NODEF10(740),
		ERROR_ENTRY_NODEF10(750),ERROR_ENTRY_NODEF10(760),ERROR_ENTRY_NODEF10(770),ERROR_ENTRY_NODEF10(780),
		ERROR_ENTRY_NODEF10(790),
		ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR getError(int id)
	{
		if (id > ERROR_MAX_ENTRY || id < 0)
		{
			return errors[0];
		}
		return errors[id];
	}

	ERROR getErrorIn(int id, int line = -1, int col = -1)
	{
		if (id > ERROR_MAX_ENTRY || id < 0)
		{
			return errors[0];
		}
		errors[id].inText.line = line;
		errors[id].inText.positionInTheString = col;
		return errors[id];
	}
}