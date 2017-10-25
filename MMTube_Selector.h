
const unsigned _SORTAMENT_SIZE = 255;		//	размер таблицы сортамента
const unsigned _ROD_QUANTITY = 15;			//	максимальное количество стержней в конструкции
const unsigned _PARAM_LEN = 10;					//	Длина поля параметра труб в сортаменте
const unsigned _MAX_LINE_LEN = 255;			//	Максимальная длина строки
const unsigned _MAX_LINE_FILE_LEN = 37;	//	максимальная длина строки файла
const unsigned _NMI_LEN = 48;						//	максимальная длина файла nmi
const unsigned _STD_FILE_LEN = 17;			//	максимальная длина файла std

struct TTube_SelectorIn
{
	//	Параметры констркции
	float GivenArea[_ROD_QUANTITY];			//	Заданные площади
	float NesMoment[_ROD_QUANTITY];			//	Потребные моменты
	//	Сортамент
	char ParamMassive[_SORTAMENT_SIZE][_PARAM_LEN];	//	Параметры труб из сортамента	
	float Area[_SORTAMENT_SIZE];										//	Площади из сортамента
	float Moment[_SORTAMENT_SIZE];									//	Моменты из сортамента

	int TotalRod;																	//	Количество стержней
	int TotalKnot;																//	Количество узлов
	char OpenFileName[_MAX_LINE_LEN];							//	Имя файла на входе
	char OpenFile[_MAX_LINE_LEN][_MAX_LINE_LEN];	//	Файл на входе
	int FileLen;																	//	Длина файла
	int LoadCase;																	//	Количество случаев нагружения

	//	Изменение параметров стержня
	int i_Rod_Num;			//	индекс стержня в сортаменте
	int i_Last_Num;			//	Предыдущий индекс стержня в сортаменте
};

struct TTube_SelectorOut
{
	char ParamMassiveOut[_ROD_QUANTITY][_PARAM_LEN];	//	Параметры труб  
	float AreaOut[_ROD_QUANTITY];											//	стандарнтые площади  
	float MomentOut[_ROD_QUANTITY];										//	стандартные моменты  

	char CloseFileName[_MAX_LINE_LEN];								//	Имя файла на выходе
	char CloseFile[_MAX_LINE_LEN][_MAX_LINE_LEN];			//	Файл на выходе
	char CloseSortFileName[_MAX_LINE_LEN];						//	имя файла на выходе с таблицей подобранных труб из сортамента
};

struct TTube_SelectorDebug
{
	char OpenFileShortName[_MAX_LINE_FILE_LEN];				//	имя файла, не содержащее путь
	char SortamentFileName[_MAX_LINE_LEN];						//	имя файла сортамента (.txt)
	char SortamentShortFileName[_MAX_LINE_FILE_LEN];	//	имя файла сортамента, не содержащее путь
	char SortamentName[_MAX_LINE_FILE_LEN];						//	название сортамента
	float NMIfile[_NMI_LEN - 3];											//	необходимые моменты инерции для всех стержней из файла nmi
	char NMIfileName[_MAX_LINE_LEN];									//	имя файла nmi
	int Lambda;																				//	Лямбда
	char STDfileName[_MAX_LINE_LEN];									//	имя файла std
	char STDfile[_STD_FILE_LEN][_MAX_LINE_FILE_LEN];	//	файл std
	float OldMomentOut[_ROD_QUANTITY];								//	массив предыдущих значений стандартных моментов
};

class CTube_Selector
{
private:
TTube_SelectorIn Tube_SelectorIn;
TTube_SelectorOut Tube_SelectorOut;
TTube_SelectorDebug Tube_SelectorDebug;
	//	Сортамент
	int IndexMassive[_ROD_QUANTITY];											//	Массив индексов итоговых стержней в сортаменте
	int MinMomentMassive[_ROD_QUANTITY];									//	Массив индексов минимумов моментов инерции, >= потребным
	int MinAreaMassive[_ROD_QUANTITY];										//	Массив индексов минимумов площадей
	int HelpIndex[_ROD_QUANTITY];													//	Массив вспомогательных индексов
	int IndexMassiveOld[_ROD_QUANTITY];										//	Массив индексов подобранных стержней из сортамента
	int IndexMassiveNew[_ROD_QUANTITY];										//	Массив индексов новых подобраных стержней из сортамента
	int LastIndexMassive[_ROD_QUANTITY][_SORTAMENT_SIZE];	//	Массив индексов бывших подобранных стержней

	int i_TimeStep;							//	Шаг по времени (мс)
	int i_Temp;									//	Вспомогательная переменная (счетчик цикла)
	int j_Temp;									//	Вспомогательная переменная (счетчик цикла)

	//	Поиск минимума в массиве, начиная с элемента k и до конца массива
	int FindMin(float * p, int k, int massivelen);
	//	Поиск минимума (больше или равного некоторому числу x)в массиве, начиная с элемента k и до конца массива
	int FindLimitMin(float * p, int k, int massivelen, float x);
	//	Поиск первого элемента больше или равного данному в массиве, упорядоченному по возрастанию
	int FindElement(float * p, float elemin, int massivelen);
	//	Поиск индекса стержня в массиве сортамента
	int FindIndex(float area, float moment);
	//	Поиск индекса максимума в массиве сортамента
	int FindMax(float * p, int massivelen);
	//	Поиск минимума (больше некоторого числа x)в массиве, начиная с элемента k и до конца массива
	int FindBiggerLimitMin(float * p, int k, int massivelen, float x);

public:

	CTube_Selector();
	~CTube_Selector();

	TTube_SelectorIn PreTube_SelectorIn;

	//	Установка шага по времени (мс)
	void SetTimeStep(int Step) { i_TimeStep = Step; }

	//	Инициализация модели
	void Init();

	//	Ввод входных данных модели
	void SetInputData(TTube_SelectorIn InputData) { Tube_SelectorIn = InputData; }

	//	Вывод выходных данных модели
	TTube_SelectorOut GetOutputData() { return Tube_SelectorOut; }

	//	Подбор стержня из сортамента
	bool FirstSelection(int rodindex);

	//	Подбор стержня из сортамента большей толщины
	bool NewSelection(int rodindex);

	//	Подбор стержня из сортамента меньшей толщины
	bool SubstractSelection(int rodindex);
 };


