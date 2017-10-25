
const unsigned _SORTAMENT_SIZE = 255;		//	������ ������� ����������
const unsigned _ROD_QUANTITY = 15;			//	������������ ���������� �������� � �����������
const unsigned _PARAM_LEN = 10;					//	����� ���� ��������� ���� � ����������
const unsigned _MAX_LINE_LEN = 255;			//	������������ ����� ������
const unsigned _MAX_LINE_FILE_LEN = 37;	//	������������ ����� ������ �����
const unsigned _NMI_LEN = 48;						//	������������ ����� ����� nmi
const unsigned _STD_FILE_LEN = 17;			//	������������ ����� ����� std

struct TTube_SelectorIn
{
	//	��������� ����������
	float GivenArea[_ROD_QUANTITY];			//	�������� �������
	float NesMoment[_ROD_QUANTITY];			//	��������� �������
	//	���������
	char ParamMassive[_SORTAMENT_SIZE][_PARAM_LEN];	//	��������� ���� �� ����������	
	float Area[_SORTAMENT_SIZE];										//	������� �� ����������
	float Moment[_SORTAMENT_SIZE];									//	������� �� ����������

	int TotalRod;																	//	���������� ��������
	int TotalKnot;																//	���������� �����
	char OpenFileName[_MAX_LINE_LEN];							//	��� ����� �� �����
	char OpenFile[_MAX_LINE_LEN][_MAX_LINE_LEN];	//	���� �� �����
	int FileLen;																	//	����� �����
	int LoadCase;																	//	���������� ������� ����������

	//	��������� ���������� �������
	int i_Rod_Num;			//	������ ������� � ����������
	int i_Last_Num;			//	���������� ������ ������� � ����������
};

struct TTube_SelectorOut
{
	char ParamMassiveOut[_ROD_QUANTITY][_PARAM_LEN];	//	��������� ����  
	float AreaOut[_ROD_QUANTITY];											//	����������� �������  
	float MomentOut[_ROD_QUANTITY];										//	����������� �������  

	char CloseFileName[_MAX_LINE_LEN];								//	��� ����� �� ������
	char CloseFile[_MAX_LINE_LEN][_MAX_LINE_LEN];			//	���� �� ������
	char CloseSortFileName[_MAX_LINE_LEN];						//	��� ����� �� ������ � �������� ����������� ���� �� ����������
};

struct TTube_SelectorDebug
{
	char OpenFileShortName[_MAX_LINE_FILE_LEN];				//	��� �����, �� ���������� ����
	char SortamentFileName[_MAX_LINE_LEN];						//	��� ����� ���������� (.txt)
	char SortamentShortFileName[_MAX_LINE_FILE_LEN];	//	��� ����� ����������, �� ���������� ����
	char SortamentName[_MAX_LINE_FILE_LEN];						//	�������� ����������
	float NMIfile[_NMI_LEN - 3];											//	����������� ������� ������� ��� ���� �������� �� ����� nmi
	char NMIfileName[_MAX_LINE_LEN];									//	��� ����� nmi
	int Lambda;																				//	������
	char STDfileName[_MAX_LINE_LEN];									//	��� ����� std
	char STDfile[_STD_FILE_LEN][_MAX_LINE_FILE_LEN];	//	���� std
	float OldMomentOut[_ROD_QUANTITY];								//	������ ���������� �������� ����������� ��������
};

class CTube_Selector
{
private:
TTube_SelectorIn Tube_SelectorIn;
TTube_SelectorOut Tube_SelectorOut;
TTube_SelectorDebug Tube_SelectorDebug;
	//	���������
	int IndexMassive[_ROD_QUANTITY];											//	������ �������� �������� �������� � ����������
	int MinMomentMassive[_ROD_QUANTITY];									//	������ �������� ��������� �������� �������, >= ���������
	int MinAreaMassive[_ROD_QUANTITY];										//	������ �������� ��������� ��������
	int HelpIndex[_ROD_QUANTITY];													//	������ ��������������� ��������
	int IndexMassiveOld[_ROD_QUANTITY];										//	������ �������� ����������� �������� �� ����������
	int IndexMassiveNew[_ROD_QUANTITY];										//	������ �������� ����� ���������� �������� �� ����������
	int LastIndexMassive[_ROD_QUANTITY][_SORTAMENT_SIZE];	//	������ �������� ������ ����������� ��������

	int i_TimeStep;							//	��� �� ������� (��)
	int i_Temp;									//	��������������� ���������� (������� �����)
	int j_Temp;									//	��������������� ���������� (������� �����)

	//	����� �������� � �������, ������� � �������� k � �� ����� �������
	int FindMin(float * p, int k, int massivelen);
	//	����� �������� (������ ��� ������� ���������� ����� x)� �������, ������� � �������� k � �� ����� �������
	int FindLimitMin(float * p, int k, int massivelen, float x);
	//	����� ������� �������� ������ ��� ������� ������� � �������, �������������� �� �����������
	int FindElement(float * p, float elemin, int massivelen);
	//	����� ������� ������� � ������� ����������
	int FindIndex(float area, float moment);
	//	����� ������� ��������� � ������� ����������
	int FindMax(float * p, int massivelen);
	//	����� �������� (������ ���������� ����� x)� �������, ������� � �������� k � �� ����� �������
	int FindBiggerLimitMin(float * p, int k, int massivelen, float x);

public:

	CTube_Selector();
	~CTube_Selector();

	TTube_SelectorIn PreTube_SelectorIn;

	//	��������� ���� �� ������� (��)
	void SetTimeStep(int Step) { i_TimeStep = Step; }

	//	������������� ������
	void Init();

	//	���� ������� ������ ������
	void SetInputData(TTube_SelectorIn InputData) { Tube_SelectorIn = InputData; }

	//	����� �������� ������ ������
	TTube_SelectorOut GetOutputData() { return Tube_SelectorOut; }

	//	������ ������� �� ����������
	bool FirstSelection(int rodindex);

	//	������ ������� �� ���������� ������� �������
	bool NewSelection(int rodindex);

	//	������ ������� �� ���������� ������� �������
	bool SubstractSelection(int rodindex);
 };


