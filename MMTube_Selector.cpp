#include "MMTube_Selector.h"
#include <memory.h>
#include <stdio.h>

//--------------------------------------------------------------------------------------------------------------------------
//	Конструктор
//--------------------------------------------------------------------------------------------------------------------------
CTube_Selector::CTube_Selector()
{
	//	инициализация переменных
	memset(&Tube_SelectorIn, 0, sizeof(TTube_SelectorIn));
	memset(&Tube_SelectorOut, 0, sizeof(TTube_SelectorOut));
	memset(&PreTube_SelectorIn, 0, sizeof(TTube_SelectorIn));
	memset(&Tube_SelectorDebug, 0, sizeof(TTube_SelectorDebug));

	for (i_Temp = 0; i_Temp < _ROD_QUANTITY; i_Temp++) {IndexMassive[i_Temp] = 0;}
	for (i_Temp = 0; i_Temp < _ROD_QUANTITY; i_Temp++) {MinMomentMassive[i_Temp] = 0;}
	for (i_Temp = 0; i_Temp < _ROD_QUANTITY; i_Temp++) {MinAreaMassive[i_Temp] = 0;}
	for (i_Temp = 0; i_Temp < _ROD_QUANTITY; i_Temp++) {HelpIndex[i_Temp] = 0;}
	for (i_Temp = 0; i_Temp < _ROD_QUANTITY; i_Temp++) {IndexMassiveOld[i_Temp] = 0;}
	for (i_Temp = 0; i_Temp < _ROD_QUANTITY; i_Temp++) {IndexMassiveNew[i_Temp] = 0;}
	for (i_Temp = 0; i_Temp < _ROD_QUANTITY; i_Temp++) {for (j_Temp = 0; j_Temp < _SORTAMENT_SIZE; j_Temp++){LastIndexMassive[i_Temp][j_Temp] = 0;}}

	i_TimeStep = 0;
	i_Temp = 0;
	j_Temp = 0;
}

//--------------------------------------------------------------------------------------------------------------------------
//	Деструктор
//--------------------------------------------------------------------------------------------------------------------------
CTube_Selector::~CTube_Selector()
{
}
//--------------------------------------------------------------------------------------------------------------------------
//	Инициализация 
//--------------------------------------------------------------------------------------------------------------------------
void CTube_Selector::Init()
{
}
//--------------------------------------------------------------------------------------------------------------------------
//	Поиск индекса минимума в массиве p, начиная с элемента k и до конца массива длиной massivelen
//--------------------------------------------------------------------------------------------------------------------------
int CTube_Selector::FindMin(float * p, int k, int massivelen)
{
	int indexmin = 0;
	float min = 0.0f;
	int i = 0;
	min = p[k];
	indexmin = k;
	for(i = k; i < massivelen; i++)
	{
		if((p[i] < min) && (p[i] != 0))
		{
			min = p[i];
			indexmin = i;
			i = massivelen;
		}
	}
	return indexmin;
}
//--------------------------------------------------------------------------------------------------------------------------
//	Поиск индекса максимума в массиве сортамента
//--------------------------------------------------------------------------------------------------------------------------
int CTube_Selector::FindMax(float * p, int massivelen)
	{
		int indexmax = 0;
		float max = 0.0f;
		int i = 0;
		max = p[0];
		for(i = 0; i < massivelen; i++)
		{
			if(p[i] > max)
			{
				max = p[i];
				indexmax = i;
			}
		}
		return indexmax;
	}
//--------------------------------------------------------------------------------------------------------------------------
//	Поиск индекса первого элемента больше или равного данному в массиве, упорядоченному по возрастанию
//--------------------------------------------------------------------------------------------------------------------------
int CTube_Selector::FindElement(float * p, float elemin, int massivelen)
	{
		int indexelemout = 0;
		float elemout = 0.0f;
		int i = 0;
		for (i = 0; i < massivelen; i++)
		{
			if (p[i] >= elemin)
			{
				elemout = p[i];
				indexelemout = i;
				i = massivelen;
			}
		}
		if((indexelemout == 0) && (elemout < elemin))	{ return NULL; }
		return indexelemout;
	}

//--------------------------------------------------------------------------------------------------------------------------
//	Поиск индекса минимума (больше или равного некоторому числу x) в массиве p, начиная с элемента k и до конца массива длиной massivelen
//--------------------------------------------------------------------------------------------------------------------------
int CTube_Selector::FindLimitMin(float * p, int k, int massivelen, float x)
{
	int indexmin = 0;
	float min = 0.0f;
	int i = 0;
	if(FindElement(p, x, massivelen) > k)
	{ 
		indexmin = FindElement(p, x, massivelen);
			min = p[indexmin];
	}
	else 
	{
		indexmin = FindMax(p, massivelen);
		min = p[indexmin];
	}
	for(i = k; i < massivelen; i++)
	{
		if((p[i] != 0) && (p[i] >= x) && (p[i] <= min))
		{
			min = p[i];
			indexmin = i;
		}
	}
	if((indexmin == 0) && (min < x))	{ return NULL; }
	return indexmin;
}
//--------------------------------------------------------------------------------------------------------------------------
//	Поиск индекса минимума (больше некоторого числа x) в массиве p, начиная с элемента k до конца массива длиной massivelen
//--------------------------------------------------------------------------------------------------------------------------
int CTube_Selector::FindBiggerLimitMin(float * p, int k, int massivelen, float x)
{
	int indexmin = 0;
	float min = 0.0f;
	int i = 0;
	indexmin = FindMax(p, massivelen);
	min = p[indexmin];
	for(i = k; i < massivelen; i++)
	{
		if((p[i] != 0) && (p[i] > x) && (p[i] < min) && (p[i] > p[FindLimitMin(p, 0, massivelen, x)]))
		{
			min = p[i];
			indexmin = i;
		}
	}
	if((indexmin == 0) && (min < x))	{ return NULL; }
	return indexmin;
}
//--------------------------------------------------------------------------------------------------------------------------
//	Поиск индекса стержня в массиве сортамента
//--------------------------------------------------------------------------------------------------------------------------
int CTube_Selector::FindIndex(float area, float moment)
	{
		int i = 0;
		for(i = 0; i < _SORTAMENT_SIZE; i++)
		{
			if(moment == PreTube_SelectorIn.Moment[i])
			{
				if(area == PreTube_SelectorIn.Area[i]) { return i; }
			}
		}
		return NULL;
	}

//--------------------------------------------------------------------------------------------------------------------------
//	Подбор стержня из сортамента
//--------------------------------------------------------------------------------------------------------------------------
bool CTube_Selector::FirstSelection(int rodindex)
{
	//	Ищем индекс стержня с минимальным моментом инерции из сортамента
	MinMomentMassive[rodindex] = FindElement(PreTube_SelectorIn.Moment, PreTube_SelectorIn.NesMoment[rodindex], _SORTAMENT_SIZE);
	//	Ищем индекс стержня с минимальной площадью из сортамента (больший индекса стержня с минимальным моментом инерции)
	MinAreaMassive[rodindex] = FindLimitMin(PreTube_SelectorIn.Area, MinMomentMassive[rodindex], _SORTAMENT_SIZE, PreTube_SelectorIn.GivenArea[rodindex]);

	//	Подбираем подходящие стержни из сортамента
	if((MinMomentMassive[rodindex] >= MinAreaMassive[rodindex]) && (PreTube_SelectorIn.GivenArea[rodindex] <= PreTube_SelectorIn.Area[MinMomentMassive[rodindex]]) && PreTube_SelectorIn.NesMoment[rodindex] <= PreTube_SelectorIn.Moment[MinMomentMassive[rodindex]]) 
	{IndexMassive[rodindex] = MinMomentMassive[rodindex];}
	else if ((MinMomentMassive[rodindex] < MinAreaMassive[rodindex]) && (PreTube_SelectorIn.GivenArea[rodindex] <= PreTube_SelectorIn.Area[MinAreaMassive[rodindex]]) && PreTube_SelectorIn.NesMoment[rodindex] <= PreTube_SelectorIn.Moment[MinAreaMassive[rodindex]])
	{ IndexMassive[rodindex] = MinAreaMassive[rodindex]; }
	else 
	{
	//	Сортамент не удовлетворяет размерам стержня
	Tube_SelectorOut.AreaOut[rodindex] = 0;
	Tube_SelectorOut.MomentOut[rodindex] = 0;
		for(i_Temp = 0; i_Temp < _PARAM_LEN; i_Temp++)
	{
		Tube_SelectorOut.ParamMassiveOut[rodindex][i_Temp] = NULL;
	}
	return true;
	}

	//	Получение выходных данных
	Tube_SelectorOut.AreaOut[rodindex] = PreTube_SelectorIn.Area[IndexMassive[rodindex]];
	Tube_SelectorOut.MomentOut[rodindex] = PreTube_SelectorIn.Moment[IndexMassive[rodindex]];
	for(i_Temp = 0; i_Temp < _PARAM_LEN; i_Temp++)
	{
		Tube_SelectorOut.ParamMassiveOut[rodindex][i_Temp] = PreTube_SelectorIn.ParamMassive[IndexMassive[rodindex]][i_Temp];
	}
	return true;
}

//--------------------------------------------------------------------------------------------------------------------------
//	Подбор стержня из сортамента большей толщины
//--------------------------------------------------------------------------------------------------------------------------
bool CTube_Selector::NewSelection(int rodindex)
	{
		if(Tube_SelectorOut.ParamMassiveOut[rodindex][0] == 0) {return false;}
		//	Находим индекс используемого стержня в массиве сортамента
		IndexMassiveOld[rodindex] = FindIndex(Tube_SelectorOut.AreaOut[rodindex], Tube_SelectorOut.MomentOut[rodindex]);
		// Записываем индекс используемого стержня в массив бывших индексов
				for(i_Temp = 0; i_Temp < _SORTAMENT_SIZE; i_Temp++)
		{
			if(LastIndexMassive[rodindex][i_Temp] == 0)
			{
				LastIndexMassive[rodindex][i_Temp] = IndexMassiveOld[rodindex];
				break;
			}
		}
		//	Находим минимальную площадь стержня, большую используемой и удовлетворяющую начальным условиям
		MinAreaMassive[rodindex] = FindBiggerLimitMin(PreTube_SelectorIn.Area, MinMomentMassive[rodindex], _SORTAMENT_SIZE, Tube_SelectorOut.AreaOut[rodindex]);

		//	Подбираем подходящие стержни из сортамента
		if((MinMomentMassive[rodindex] >= MinAreaMassive[rodindex]) && (PreTube_SelectorIn.GivenArea[rodindex] <= PreTube_SelectorIn.Area[MinMomentMassive[rodindex]]) && (PreTube_SelectorIn.NesMoment[rodindex] <= PreTube_SelectorIn.Moment[MinMomentMassive[rodindex]])) 
		{IndexMassive[rodindex] = MinMomentMassive[rodindex];}
		else if ((MinMomentMassive[rodindex] < MinAreaMassive[rodindex]) && (PreTube_SelectorIn.GivenArea[rodindex] <= PreTube_SelectorIn.Area[MinAreaMassive[rodindex]]) && (PreTube_SelectorIn.NesMoment[rodindex] <= PreTube_SelectorIn.Moment[MinAreaMassive[rodindex]]))
		{ IndexMassive[rodindex] = MinAreaMassive[rodindex]; }

		//	Получение выходных данных
		Tube_SelectorOut.AreaOut[rodindex] = PreTube_SelectorIn.Area[IndexMassive[rodindex]];
		Tube_SelectorOut.MomentOut[rodindex] = PreTube_SelectorIn.Moment[IndexMassive[rodindex]];
		for(i_Temp = 0; i_Temp < _PARAM_LEN; i_Temp++)
		{
			Tube_SelectorOut.ParamMassiveOut[rodindex][i_Temp] = PreTube_SelectorIn.ParamMassive[IndexMassive[rodindex]][i_Temp];
		}
			return true;
	}

//--------------------------------------------------------------------------------------------------------------------------
//	Подбор стержня из сортамента меньшей толщины
//--------------------------------------------------------------------------------------------------------------------------

	bool CTube_Selector::SubstractSelection (int rodindex)
	{
		if(Tube_SelectorOut.ParamMassiveOut[rodindex][0] == 0) {return false;}
		int lastind = 0;
		//	Находим индекс предыдущего используемого стержня
		for (i_Temp = 0; i_Temp < _SORTAMENT_SIZE; i_Temp++)
		{
			if((LastIndexMassive[rodindex][i_Temp] == 0) && (i_Temp >= 0))
			{
				lastind = LastIndexMassive[rodindex][i_Temp - 1];
				LastIndexMassive[rodindex][i_Temp - 1] = 0; 
				break;
			}
		}
		if(lastind < 0){return false;}
//		if(lastind == 0) {lastind = FindIndex(Tube_SelectorOut.AreaOut[rodindex], Tube_SelectorOut.MomentOut[rodindex]);}
		if(lastind == 0) {lastind = FindIndex(PreTube_SelectorIn.GivenArea[rodindex],PreTube_SelectorIn.NesMoment[rodindex]);}

		//	Получение выходных данных
		Tube_SelectorOut.AreaOut[rodindex] = PreTube_SelectorIn.Area[lastind];
		Tube_SelectorOut.MomentOut[rodindex] = PreTube_SelectorIn.Moment[lastind];
		for(i_Temp = 0; i_Temp < _PARAM_LEN; i_Temp++)
		{
			Tube_SelectorOut.ParamMassiveOut[rodindex][i_Temp] = PreTube_SelectorIn.ParamMassive[lastind][i_Temp];
		}
		return true;
	}