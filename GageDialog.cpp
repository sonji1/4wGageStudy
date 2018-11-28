// GageDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ACE400Gage.h"
#include "GageDialog.h"
#include "chartdir.h"
#include "FileSysInfo.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGageDialog dialog


CGageDialog::CGageDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGageDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGageDialog)
	m_editMeasDataPath = _T("");
	m_edit_nRefInput = 0;
	m_edit_nTolInput = 1;

	//}}AFX_DATA_INIT
	
	m_nRef = m_edit_nRefInput;
	m_nTol = m_edit_nTolInput;
	m_dAvg = 0.0;
	m_d6StDev = 0.0;
	m_dStDev = 0.0;
	m_dBias = 0.0;
	m_dT = 0.0;
	m_dPValue = 0.0;
	m_dCg = 0.0;
	m_dCgk = 0.0;
	m_dVarRept = 0.0;
	m_dVarReptBias = 0.0;
}


void CGageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGageDialog)
	DDX_Control(pDX, IDC_COMBO_MEAS_TYPE, 	m_comboMeasType);
	DDX_Control(pDX, IDC_GRID, 				m_gridCtrl);

	DDX_Text   (pDX, IDC_EDIT_4W_FILE_PATH, m_editMeasDataPath);
	DDX_Control(pDX, IDC_CHART, 			m_ChartViewer);
	DDX_Text   (pDX, IDC_EDIT_REF_INPUT, 	m_edit_nRefInput);
	DDX_Text   (pDX, IDC_EDIT_TOL_INPUT, 	m_edit_nTolInput);
	DDV_MinMaxInt(pDX, m_edit_nTolInput, 1, 3);

	DDX_Control(pDX, IDC_GRID_STAT, 		m_gridStat);
	DDX_Control(pDX, IDC_GRID_BIAS, 		m_gridBias);
	DDX_Control(pDX, IDC_GRID_CAPABILITY, 	m_gridCapability);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGageDialog, CDialog)
	//{{AFX_MSG_MAP(CGageDialog)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_MEAS_TYPE, OnSelchangeComboMeasType)
	ON_BN_CLICKED(	 IDC_BUTTON_DO_STUDY, OnButtonDoStudy)
	ON_EN_CHANGE(IDC_EDIT_TOL_INPUT, OnChangeEditTolInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGageDialog message handlers

BOOL CGageDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	g_sFile.Init();

	if (InitMember() == FALSE)
		return FALSE;

	if (InitView() == FALSE)
		return FALSE;

	

	MyTrace(PRT_BASIC, "\"4W GageStudy SW\" Started...\n" );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CGageDialog::InitMember()
{

	// Meas Data ���� ��� ���� �ʱ�ȭ
	m_nTypeCount = 0;
	m_nMeasCount = 0;
	::ZeroMemory(m_daMeasData, sizeof(m_daMeasData));


	// Grid ���� ��� ���� �ʱ�ȭ
	m_nFixCols = 1;
	m_nFixRows = 1;
	m_nCols = (MAX_MEAS_TYPE + 1);
	m_nRows = (MAX_MEAS_COUNT + 1);
	m_bEditable = TRUE;

	m_nFixCols_Out = 1;
	m_nFixRows_Out = 0;
	m_nCols_Out = 2;
	m_nRows_Out = MAX_STAT_ENUM;
/*
	m_bHorzLines = TRUE;
	m_bListMode = FALSE;
	m_bVertLines = TRUE;
	m_bSelectable = TRUE;
	m_bAllowColumnResize = TRUE;
	m_bAllowRowResize = TRUE;
	m_bHeaderSort = TRUE;
	m_bReadOnly = TRUE;
	m_bItalics = TRUE;
	m_btitleTips = TRUE;
	m_bSingleSelMode = FALSE;
*/

	m_dAvg = 0.0;
	m_d6StDev = 0.0;
	m_dStDev = 0.0;
	m_dBias = 0.0;
	m_dT = 0.0;
	m_dPValue = 0.0;
	m_dCg = 0.0;
	m_dCgk = 0.0;
	m_dVarRept = 0.0;
	m_dVarReptBias = 0.0;

	
	return TRUE;
}


BOOL CGageDialog::InitView()
{
	UpdateData(TRUE);


	//-------------------------
	// 4W Meas data �ε�
	
	// ACE400�� 4W_Setup_A.txt ���� ��ġ�� ã�´�.   ex) "C:\ACE400\QC-JIG-S100-BHFlex\4W\"
	FileSysInfo01.LoadSaveView01(DATA_LOAD);		// Load	SysInfoView01.m_pStrFilePathBDL

	// 4W_Setup_A.txt ������ �ε��Ѵ�.  : 4W Meas data
	Load_4W_MeasData();


	//----------------------------
	// Grid �ʱ�ȭ 
	//  : SetGridBkBlue()�� combo�ʱ�ȭ�� �� �ؾ��ϹǷ� Grid�� Combo���� ���� �ʱ�ȭ�Ѵ�.

	m_gridCtrl.SetEditable(m_bEditable);
	//m_gridCtrl.SetListMode(m_bListMode);
	//m_gridCtrl.EnableDragAndDrop(TRUE);
	m_gridCtrl.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));		// ������� back ground

	m_gridStat.SetEditable(m_bEditable);
	m_gridStat.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));		// ������� back ground

	m_gridBias.SetEditable(m_bEditable);
	m_gridBias.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));		// ������� back ground

	m_gridCapability.SetEditable(m_bEditable);
	m_gridCapability.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));		// ������� back ground

	TRY {
		m_gridCtrl.SetRowCount(m_nRows);
		m_gridCtrl.SetColumnCount(m_nCols);
		m_gridCtrl.SetFixedRowCount(m_nFixRows);
		m_gridCtrl.SetFixedColumnCount(m_nFixCols);

		m_gridStat.SetRowCount(MAX_STAT_ENUM);
		m_gridStat.SetColumnCount(m_nCols_Out);
		m_gridStat.SetFixedRowCount(m_nFixRows_Out);
		m_gridStat.SetFixedColumnCount(m_nFixCols_Out);

		m_gridBias.SetRowCount(MAX_BIAS_ENUM);
		m_gridBias.SetColumnCount(m_nCols_Out);
		m_gridBias.SetFixedRowCount(m_nFixRows_Out);
		m_gridBias.SetFixedColumnCount(m_nFixCols_Out);

		m_gridCapability.SetRowCount(MAX_CAPABILITY_ENUM);
		m_gridCapability.SetColumnCount(m_nCols_Out);
		m_gridCapability.SetFixedRowCount(m_nFixRows_Out);
		m_gridCapability.SetFixedColumnCount(m_nFixCols_Out);
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}
    END_CATCH	

	Display_mohmGridHeader();		// Grid Header ����.
	Display_mohmGridData();			// Grid Data  ���

	Display_OutputGridFixCol();		// Output Grid Fixed Col (name) ���


	//--------------------------
	// combo box init

	// mohm_75000 ������ combo�� �Է��Ѵ�.
	for (int type = 0; type < (MAX_MEAS_TYPE -1); type++)
		m_comboMeasType.InsertString( -1, g_MeasInfoTable[type].strMeas);

	// ���� combo���� ���õ� type#
	m_nCombo_CurrType = mohm_1;			// 0
	m_comboMeasType.SetCurSel(mohm_1);	// 0 = mohm_1

	SetGridBkBlue(m_nCombo_CurrType);	// ���� ���õ� type column�� ����� Ǫ�������� ����.

	m_edit_nRefInput = g_MeasInfoTable[m_nCombo_CurrType].nMeasRef;
	m_nRef = m_edit_nRefInput;
	

	// ���õ� type�� ���� 'type1 gage study' ����� ��� 
	OnButtonDoStudy();

	UpdateData(FALSE);
	Invalidate(TRUE);		// ȭ�� ���� ����. UpdateData(False)������ Grid ȭ�� ������ ���� �ʾƼ� �߰���.

	return TRUE;
}


// mohm Grid header ����
#define		GRID_COL_NO			0
#define		GRID_COL_MOHM_BASE	1
void CGageDialog::Display_mohmGridHeader()
{

	// 0     1      2        3     4      5      6       7         8         9       10      
	// No,  1mohm, 2mohm,  3mohm, 4mohm, 5mohm, 10mhom,  20mohm,   30mohm,  40mohm,  50mohm, 
	// 11       12        13       14     15       				.... 24 
	// 100mohm  200mohm 500mohm  750mohm  1000mohm				   75000mohm  


    m_gridCtrl.SetItemText(0, GRID_COL_NO, "No");
	m_gridCtrl.SetColumnWidth(GRID_COL_NO, 40);


	for (int type=0; type < (MAX_MEAS_TYPE -1); type++)
	{
		m_gridCtrl.SetItemText(0, (GRID_COL_MOHM_BASE + type), g_MeasInfoTable[type].strMeas);
		m_gridCtrl.SetColumnWidth((GRID_COL_MOHM_BASE + type), 82);

	}

	
	//m_gridCtrl.SetRowHeight(0, 40);	// ����� ���� ���� ǥ�ø� ���� ���� ����
}


void CGageDialog::Display_mohmGridData()
{
	CString	strTemp;

	for (int meas=0; meas < m_nMeasCount; meas++)
	{
		// No ���
		strTemp.Format("%d", (meas+1) );
    	m_gridCtrl.SetItemText(meas+1, GRID_COL_NO, strTemp);

    	// �ش� No�� mohm(MeasType)�� �ش��ϴ� ������ ���.
		for (int type=0; type < (MAX_MEAS_TYPE -1); type++)
		{
			strTemp.Format("%.2f",  m_daMeasData[type][meas]);		// ���μ��θ� �ٲپ ���.
			m_gridCtrl.SetItemText(meas+1, (GRID_COL_MOHM_BASE + type), strTemp);
		}

	}

}


void CGageDialog::Display_OutputGridFixCol()
{

	int row;

	m_gridStat.SetColumnWidth(0, 100);
	m_gridStat.SetColumnWidth(1, 80);
	for (row = 0; row < MAX_STAT_ENUM; row++)
		m_gridStat.SetRowHeight(row, 25);

    m_gridStat.SetItemText(STAT_REF, 		0, "Reference");
    m_gridStat.SetItemText(STAT_MEAN, 		0, "Mean");
    m_gridStat.SetItemText(STAT_STDEV, 		0, "StDev");
    m_gridStat.SetItemText(STAT_6xSTDEV, 	0, "6 x StDev (SV)");
    m_gridStat.SetItemText(STAT_TOL, 		0, "Tolerance (TOL)");

	m_gridBias.SetColumnWidth(0, 100);
	m_gridBias.SetColumnWidth(1, 80);
	for (row = 0; row < MAX_BIAS_ENUM; row++)
		m_gridBias.SetRowHeight(row, 25);
    m_gridBias.SetItemText(BIAS_BIAS, 		0, "Bias");
    m_gridBias.SetItemText(BIAS_T, 			0, "T");
    m_gridBias.SetItemText(BIAS_PVALUE, 	0, "PValue");


	m_gridCapability.SetColumnWidth(0, 170);
	m_gridCapability.SetColumnWidth(1, 80);
	for (row = 0; row < MAX_CAPABILITY_ENUM; row++)
		m_gridCapability.SetRowHeight(row, 25);
    m_gridCapability.SetItemText(CAPABILITY_CG, 			0, "Cg");
    m_gridCapability.SetItemText(CAPABILITY_CGK, 			0, "Cgk");
    m_gridCapability.SetItemText(CAPABILITY_VAR_REPT, 		0, "%Var (Repeatablility)");
    m_gridCapability.SetItemText(CAPABILITY_VAR_REPT_BIAS, 	0, "%Var (Repeatability and Bias)");

	
	//m_gridCtrl.SetRowHeight(0, 40);	// ����� ���� ���� ǥ�ø� ���� ���� ����
}


// â�� ���� ���϶� ������ �ʱ�ȭ�ؾ� �ϴ� ������� ������ 
// OnShowWindow()�� TODO �ؿ� �ʱ�ȭ�Ѵ�. 
void CGageDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if(bShow == TRUE)
	{
		// ��� �ʱ�ȭ


		// View �ʱ�ȭ 

	}
	
}


#define		MAX_LINE_STR		2048
void CGageDialog::Load_4W_MeasData()
{

	FILE *fp; 
	char  fName[200];  
	CString /*str,*/ strTemp;

	// Meas Data ���� ��� ���� �ʱ�ȭ
	m_nTypeCount = 0;
	m_nMeasCount = 0;
	::ZeroMemory(m_daMeasData, sizeof(m_daMeasData));

    ::ZeroMemory(&fName, sizeof(fName));
 	//str.Format("%s", SysInfoView01.m_pStrFilePathBDL);//SYLEE121202
   	strcat( fName ,SysInfoView01.m_pStrFilePathBDL);
 	//strcat( fName , "\\4W_Setup_A.txt" );
 	strcat( fName , "\\4W_Setup_A-H-10.txt" );

 	m_editMeasDataPath = fName;
	UpdateData(FALSE); // ��ȭ������ Edit��Ʈ�ѿ� m_editMeasDataPath �� ���.


	fp=fopen(fName,"rt");
	if(fp==NULL) 
		return;


	fscanf(fp, "%d, %d,  \n", &m_nMeasCount, &m_nTypeCount);		 
	if (m_nTypeCount > MAX_MEAS_TYPE)
	{
		strTemp.Format("Load_4W_MeasData(): %s m_nTypeCount=%d Range(<%d) Over Error!\n", 
					fName, m_nTypeCount, MAX_MEAS_TYPE);
		ERR.Set(RANGE_OVER, strTemp); 
		ErrMsg();  ERR.Reset(); 
		return;
	}

	if (m_nMeasCount > MAX_MEAS_COUNT)
	{
		strTemp.Format("Load_4W_MeasData(): %s m_nMeasCount=%d Range(<%d) Over Error!\n", 
					fName, m_nMeasCount, MAX_MEAS_COUNT);
		ERR.Set(RANGE_OVER, strTemp); 
		ErrMsg();  ERR.Reset(); 
		return;
	}


	char str[MAX_LINE_STR];
	::ZeroMemory(str, sizeof(str));
	fgets((char*)str, MAX_LINE_STR, fp);	// ��������� ��°�� �о skip



	// Line�� �д� ������ �ݺ�
	char	strWord[3][200];
	int		pin[4];
	int		nMeasType;
	int  	row=0;
	while(!feof(fp))
	{
		if (row >= m_nTypeCount  || row >= MAX_MEAS_TYPE)		// Ż�� ����
			break;

		::ZeroMemory(str, sizeof(str));
		fgets((char*)str, MAX_LINE_STR, fp);	// ���� ��°�� �о� ����


		// �� ���� 'Net'���� �������� �ʴ´ٸ� line skip
		::ZeroMemory(strWord, sizeof(strWord));
		int ret = sscanf(str, "%s %s %d, %d, %d, %d", // ex) Read "Net1,  PIN,  1,  3,   130,  132, "
				strWord[0], strWord[1],  &pin[0], &pin[1], &pin[2], &pin[3]); // PIN ��ȣ read.  ��������� ����.
		if (strncmp(strWord[0],"Net", 3) != 0)		
		{
			row++;
			continue;	// line skip
		}

		// nMeasType�� range over�� ��� line skip
		nMeasType = -1;
		int length = strlen(strWord[0]);
		CString str1 = strWord[0];
		CString str2 = str1.Mid(3, (length-3));
		nMeasType = (atoi(str2) - 1); // nMeasType (Net��ȣ -1) ����
		if (nMeasType < 0 || nMeasType >= m_nTypeCount) 
		{
			strTemp.Format("Load_4W_MeasData(): %s row=%d nMeasType=%d Range(0 <= nMeasType < %d) Over!\n", 
						fName, row, nMeasType, m_nTypeCount);
			ERR.Set(SW_LOGIC_ERR, strTemp); 
			ErrMsg();  ERR.Reset(); 

			row++;		
			continue; // line skip
		}

		// Measurement data ��ġ ã��.  (6��° ',' ����)
		int dataLoc = 0;
		if (getMeasDataLoc(str, MAX_LINE_STR, dataLoc) < 0) 	// data loc ã�� ���ж�� line skip
		{
			strTemp.Format("Load_4W_MeasData(): %s nMeasType=%d getMeasDataLoc(dataLoc=%d) Error! \n", 
					fName, nMeasType, dataLoc);
			ERR.Set(SW_LOGIC_ERR, strTemp); 
			ErrMsg();  ERR.Reset(); 

			row++;
			continue;	// line skip
		}

		//-------------------------------------
		// m_nMeasCount ������ŭ data�� read
		char *pStr = &str[dataLoc];
		int loc;
		for (int meas=0; meas < m_nMeasCount; meas++)
		{
			loc = getMeasData(pStr, (MAX_LINE_STR-dataLoc), m_daMeasData[nMeasType][meas]);	
			if (loc < 0)
			{
				strTemp.Format("Load_4W_MeasData(): %s nMeasType=%d getMeasData(dataLoc=%d) Error!  meas=%d\n", 
						fName, nMeasType, dataLoc, meas);
				ERR.Set(SW_LOGIC_ERR, strTemp); 
				ErrMsg();  ERR.Reset(); 
				break;
			}

			dataLoc += (loc +1);	// read�� data�� ','�� ���� ��ġ�� ǥ���Ѵ�.
			pStr += (loc +1);
				
		}

		row++;
	}

	
	fclose(fp);
}

int CGageDialog::getMeasDataLoc(char *pStr, int strMax, int &rLoc) 
{
	// data ��ġ ã��.  (6��° ',' ����)
	int 	commaCnt = 0;
	for (int loc=0; loc < strMax; loc++)
	{
		if (pStr[loc] == ',')
			commaCnt++;

		if (commaCnt == 6)
		{
			rLoc = loc +1;
			return 0;		// OK : 6��° ',' ��ġ ����
		}
	}

	return -1;		// NOK : 6��° ',' ��ġ�� ���� ���� ���
}

int CGageDialog::getMeasData(char *pStr, int strMax, double &rdMeasData) 
{
	int loc;

	for (loc=0; loc < strMax; loc++)
	{
		if (pStr[loc] == ',')
			break;
	}
	if (loc == strMax)	// ',' ã�µ��� ����.
		return -1;

	// ',' ��ġ ã�� OK.
	CString str = pStr;
	CString strData = str.Left(loc);
	rdMeasData = (double)atof(strData);

	return loc;
}

BOOL CGageDialog::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}


void CGageDialog::OnSelchangeComboMeasType() 
{
	// TODO: Add your control notification handler code here
	CString strTemp;

	// ���� combo���� ���õ� type#.  enum������ access ������ (ex: mohm_1, mohm_2..)	
	int 	comboPrevType = m_nCombo_CurrType;
	m_nCombo_CurrType = m_comboMeasType.GetCurSel(); 

	// Range Check
	if ( m_nCombo_CurrType < 0 || m_nCombo_CurrType >= MAX_MEAS_TYPE )
	{

		strTemp.Format("OnSelchangeComboMeasType(): m_nCombo_CurrType=%d, Range(0 =< MeasType < %d) Over\n", 
					m_nCombo_CurrType, MAX_MEAS_TYPE );
		ERR.Set(RANGE_OVER, strTemp); 
		ErrMsg();  ERR.Reset(); 

		m_nCombo_CurrType = comboPrevType;
		return;
	}	


	SetGridBkBlue(m_nCombo_CurrType);	// ���� ���õ� type column�� ����� Ǫ�������� ����.

	
	// ��ȭ������ Edit��Ʈ�ѿ� m_edit_nRefInput �� ���.
	m_edit_nRefInput = g_MeasInfoTable[m_nCombo_CurrType].nMeasRef;
	m_nRef = m_edit_nRefInput;


	// ���õ� type�� ���� 'type1 gage study' ����� ��� 
	OnButtonDoStudy();
	
	UpdateData(FALSE); 
	Invalidate(TRUE);		// ȭ�� ���� ����. UpdateData(False)������ Grid ȭ�� ������ ���� �ʾƼ� �߰���.

}


// ���� ���õ� type�� ����� Ǫ�������� ����.
void CGageDialog::SetGridBkBlue(int type)
{
	// ���� ����� ��� ��������� ���󺹱�
	ClearGrid_BackGround();			

	//  ���õ� mohm�� Grid cell���� Ǫ�� ������� ǥ��
	for (int meas=0; meas < m_nMeasCount; meas++)
		m_gridCtrl.SetItemBkColour(meas+1, (GRID_COL_MOHM_BASE + type), 	// row, col
									RGB(0x00, 0xbf, 0xff));					// deep skyblue : £�� �ϴ��Ķ� 

	// type�� mhom_750�̻��̸� ���õ� mohm�� ���̵���, Grid�� ���� ��ũ�� ��ġ�� �ٲ۴�.
	if (type >= mohm_750)
		m_gridCtrl.SetScrollPos32(SB_HORZ, (mohm_750 * 82));

	// mohm_750�����̸� ���� ��ũ�� ���󺹱�
	else
		m_gridCtrl.SetScrollPos32(SB_HORZ, 0);	

}

void CGageDialog::ClearGrid_BackGround()
{

	for (int row = 1; row < m_gridCtrl.GetRowCount(); row++)		// ����� �����ϰ�
		for (int col = 0; col < m_gridCtrl.GetColumnCount(); col++)
		{
			// ����� ���󺹱� �Ѵ�.
			m_gridCtrl.SetItemBkColour(row, col, RGB(0xFF, 0xFF, 0xE0));	// ������� 
		}

}

void CGageDialog::ClearGrid_Data()
{

	// fill rows/cols with text
	for (int row = 1; row < m_gridCtrl.GetRowCount(); row++)		// ����� �����ϰ� Ŭ�����Ѵ�.
		for (int col = 0; col < m_gridCtrl.GetColumnCount(); col++)
		{
			m_gridCtrl.SetItemText(row, col, "                 ");


			// Ȥ�� ����� faultó���� cell�� �ִٸ� ������ display�� ���� ���󺹱� �Ѵ�.
			m_gridCtrl.SetItemBkColour(row, col, RGB(0xFF, 0xFF, 0xE0));	// ������� 
		}

	//m_gridCtrl.DeleteAllItems();  -> �̰͵� ������ �ӵ� �������� �ֽ� �ʱ�ȭ�� data �� ���ư�
	
	// Scroll Bar �ʱ�ȭ 
	m_gridCtrl.SetScrollPos32(SB_VERT, 0);
	m_gridCtrl.SetScrollPos32(SB_HORZ, 0);
	

//	m_gridCtrl.AutoSize(); -> �̰� ������ �ӵ� ������.

}
void CGageDialog::ClearGrid_Output()
{
	int row;

	// fill rows/cols with text :  �ι�° �÷��� �ʱ�ȭ.
	for (row = 0; row < m_gridStat.GetRowCount(); row++)		// ����� �����ϰ� Ŭ�����Ѵ�.
	{
		m_gridStat.SetItemText(row, 1, "                 ");

		// Ȥ�� ����� faultó���� cell�� �ִٸ� ������ display�� ���� ���󺹱� �Ѵ�.
		m_gridStat.SetItemBkColour(row, 1, RGB(0xFF, 0xFF, 0xE0));	// ������� 
	}

	for (row = 0; row < m_gridBias.GetRowCount(); row++)		
	{
		m_gridBias.SetItemText(row, 1, "                 ");

		// Ȥ�� ����� faultó���� cell�� �ִٸ� ������ display�� ���� ���󺹱� �Ѵ�.
		m_gridBias.SetItemBkColour(row, 1, RGB(0xFF, 0xFF, 0xE0));	// ������� 
	}

	for (row = 0; row < m_gridCapability.GetRowCount(); row++)		
	{
		m_gridCapability.SetItemText(row, 1, "                 ");

		// Ȥ�� ����� faultó���� cell�� �ִٸ� ������ display�� ���� ���󺹱� �Ѵ�.
		m_gridCapability.SetItemBkColour(row, 1, RGB(0xFF, 0xFF, 0xE0));	// ������� 
	}
}

void CGageDialog::OnChangeEditTolInput() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	//CString strTemp;	
	//GetDlgItemText(IDC_EDIT_TOL_INPUT, strTemp);
	
	UpdateData(TRUE);

	m_nTol = m_edit_nTolInput;



	// ������ Tol �� ���� 'type1 gage study' ����� ��� 
	OnButtonDoStudy();
	
	UpdateData(FALSE);
}

void CGageDialog::OnButtonDoStudy() 
{
	// TODO: Add your control notification handler code here
	
	DisplayGageStudyChart(m_nCombo_CurrType);
	CalcGageStudyOutput(m_nCombo_CurrType);
	DisplayGageStudyOutput(m_nCombo_CurrType);
	
}

void CGageDialog::DisplayGageStudyChart(int type) 
{

	//----------------------------------------------------------------------
	// Ref - 0.1 *Tol, Ref, Ref + 0.1*Tol, measData(type) �� �׷��� �׸��� 
	//
	// Draw Chart and set to CChartViewer
	

    // The data for the bar chart
    //double proportion[] = {0.08, 0.02, 0.06, 0.02, 0.04, 0.12, 0.06, 0.04, 0.06, 0, 0.25, 0.16666667, 0.14893617, 0.127659574, 0.130434783 };
    //double center[] = { 0.087, 0.087, 0.087, 0.087,0.087, 0.087,0.087, 0.087,0.087, 0.087,0.087, 0.087,0.087, 0.087, 0.087 };
    //double UCL[] = { 0.207, 0.207, 0.207, 0.207,0.207, 0.207,0.207, 0.207,0.207, 0.207,0.209, 0.209,0.210, 0.210, 0.210 };
	// The labels for the bar chart
    //const char *labels[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};

   	double ref[MAX_MEAS_COUNT];			// ref���� array�� �ƴϹǷ� ����� ���� array�� �����.
   	double ref_minus[MAX_MEAS_COUNT];	// ref - (0.1 * Tol)
   	double ref_plus[MAX_MEAS_COUNT];	// ref + (0.1 * Tol)
    double dataX0[MAX_MEAS_COUNT];		// X �� label�� ����� array 

    int nRef = g_MeasInfoTable[type].nMeasRef;
	for (int meas =0; meas < m_nMeasCount; meas++)
	{
		ref[meas] = nRef;
		ref_minus[meas] = nRef - (0.1 * m_nTol);
		ref_plus[meas]  = nRef + (0.1 * m_nTol);
		dataX0[meas] = meas;
	}


	// ��Ʈ ���� ------
    // Create an XYChart object of size 660 x 280 pixels, with a light blue (EEEEFF) background,
    // black border, 1 pxiel 3D border effect and rounded corners
    XYChart *c = new XYChart(660, 280, 0xeeeeff, 0x000000, 1);
    //c->setRoundedFrame();

    // Set the plotarea at (55:x, 58:y) and of size 580 x 175 pixels, with white background. Turn on
    // both horizontal and vertical grid lines with light grey color (0xcccccc)
    c->setPlotArea(55, 58, 580, 175, 0xffffff, -1, -1, 0xcccccc, 0xcccccc);


	// �������� ����  ------- 
    // Add a legend box at (250:x, 30:y) (top of the chart) with horizontal layout. Use 9pt Arial Bold
    // font. Set the background and border color to Transparent.
    c->addLegend(250, 30, false, "arialbd.ttf", 9)->setBackground(Chart::Transparent);



	// X��, Y �� Ÿ��Ʋ ���� ----------------
	
    // Add a title box to the chart using 12pt Arial Bold Italic font, on a light blue (CCCCFF)
    // background with glass effect. white (0xffffff) on a dark red (0x800000) background, with a 1
    // pixel 3D border.
    CString strTemp;
    strTemp.Format("Run Chart of %s", g_MeasInfoTable[type].strMeas);
	c->addTitle(strTemp, "arialbi.ttf", 12)->setBackground(0xccccff, 0x000000, Chart::glassEffect());


    // data�� ���� �ִ� ������ ��µǵ��� Scale �����ϱ�. 
    //   meas[0]�� 0���� �ִ� �ǹ̾��� data�� �־���. meas[0]�� �����ϰ� ������� �Ʒ� �ڵ� ���ʿ�.
    //c->yAxis()->setAutoScale(0.1, 0.1);			
    //c->yAxis()->setLinearScale(m_dMinYR, m_dMaxYR);
    //c->yAxis()->setMargin(10, 10);
    
    // Add a title to the y axis
 
    TextBox *textbox_Y = c->yAxis()->setTitle("mohm");
    textbox_Y->setFontAngle(0);					// Set the y axis title upright (font angle = 0)
    textbox_Y->setAlignment(Chart::TopLeft2);	// Put the y axis title on top of the axis


    // Add a title to the x axis
    TextBox *textbox_X = c->xAxis()->setTitle("Measure Count");
    textbox_X->setAlignment(Chart::BottomRight);

	// layer.setXData()�� ����ϰ� �Ʒ��ڵ�� �ڸ�Ʈó��
    // Set the labels on the x axis.
    //c->xAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));
    //c->xAxis()->setLabels(StringArray((const char * const *)&labels[1], g_sLotNetDate_Info.naLotNetCnt[nLot])); 
  	//c->xAxis()->setLabelStep(g_sLotNetDate_Info.naLotNetCnt[nLot] / 10);


	// XY LineChart ���� & �ɼ� ���� ----------------------


    // Add a line layer to the chart
    LineLayer *layer = c->addLineLayer();

    // Set the default line width to 2 pixels
    layer->setLineWidth(2);


    // Add the three data sets to the line layer. 
    									
    layer->addDataSet( DoubleArray(ref, m_nMeasCount), 
	   				0x008800, "Ref")->setDataSymbol(Chart::DiamondSymbol, 7, -1, 0x008800);		// �ʷϻ�

    layer->addDataSet( DoubleArray(&m_daMeasData[type][0], m_nMeasCount), 
	   				0x3333ff, "Data")->setDataSymbol(Chart::DiamondSymbol, 7, -1, 0x008800);		// ����

    layer->addDataSet( DoubleArray(ref_minus, m_nMeasCount), 
	   				0xff0000, "Ref - 0.10 x Tol")->setDataSymbol(Chart::DiamondSymbol, 7, -1, 0x008800);	// ������

    layer->addDataSet( DoubleArray(ref_plus, m_nMeasCount), 
	   				0xff0000, "Ref + 0.10 x Tol")->setDataSymbol(Chart::DiamondSymbol, 7, -1, 0x008800);	// ������


 /*   layer->addDataSet( DoubleArray(&m_daLCL[1], g_sLotNetDate_Info.naLotNetCnt[nLot]), 
    				//0xff0000, "LCL");				// ������ 
    				0xff00ff, "LCL")->setDataSymbol(Chart::DiamondSymbol, 4, -1, 0xff00ff);		// ���ֻ�

    // For demo purpose, we use a dash line color for the last line
    //layer->addDataSet(DoubleArray(m_daLCL, (int)(sizeof(m_daLCL) / sizeof(m_daLCL[0]))), 
    //				c->dashLineColor(0x3333ff, Chart::DashLine), "LCL");	// ���� ����
  */  
    // The x-coordinates for the line layer	 : X �� data label ����.
	layer->setXData(DoubleArray(dataX0, m_nMeasCount ));

/*
	// Track Net�� ������ ���, Track line�� �׷��ش�.
    if (nTrackNet != -1)
	{
    	//trackLineLegend(c, c->getPlotArea()->getRightX());
    	
    	// Include track line for the latest data values
	    trackLineLabel(c, nTrackNet);
	}
 */   

    // XY LineChart  ��� ----------------


    // Output the chart
    m_ChartViewer.setChart(c);
	
    // Include tool tip for the chart
    m_ChartViewer.setImageMap( c->getHTMLImageMap("", "", "title='{xLabel}: US${value}K'"));

	// In this sample project, we do not need to chart object any more, so we 
	// delete it now.
    delete c;

}

void CGageDialog::CalcGageStudyOutput(int type) 
{

	//---------------------
	// Calc Avg (Mean) 
	m_dAvg = 0.0;

	int meas;
	double dSum = 0;
	for (meas=0; meas < m_nMeasCount; meas++)
		dSum += m_daMeasData[type][meas]; 

	if (m_nMeasCount)		// check devide by zero : Average
		m_dAvg = dSum / (double) m_nMeasCount;



	//-----------------------------
	// Calc StDev & 6x Stdev 	
	
	m_dStDev = 0.0;
	m_d6StDev = 0.0;
	double dDiff = 0, dDiffPowerSum = 0, dVar = 0; 
	if (m_nMeasCount -1)	// check devide by zero : Variance
	{
		// Calc Variance
		for (meas=0; meas < m_nMeasCount; meas++)
		{
			dDiff = m_daMeasData[type][meas] - m_dAvg;
			dDiffPowerSum += (dDiff * dDiff);
		}

		// �л�     : (val-avg)�� ������ ������ (n - 1)���� ������.
		dVar = dDiffPowerSum / (double) (m_nMeasCount -1);

		// ǥ������ : �л��� ������
		m_dStDev = sqrt(dVar);
		m_d6StDev = 6 * m_dStDev;

	}
	
	//-------------
	// Calc Bias 
	m_dBias = 0.0;
	m_dBias = m_dAvg - g_MeasInfoTable[type].nMeasRef;
	
	//-------------
	// Calc T 
	m_dT = 0.0;
	if (m_nMeasCount)	// check devide by zero : for stdErr 
	{
		double stdErr = m_dStDev / sqrt(m_nMeasCount);
		m_dT = m_dBias / stdErr;
		if (m_dT < 0)
			m_dT = -m_dT;		// ���밪
	}
	
	//-------------
	// Calc PValue 
	m_dPValue = 0.0;
	int degFree = m_nMeasCount -1;		// degree of freedom (������) : n - 1 
	m_dPValue = p_tdist(m_dT, degFree);


	//-------------
	// Calc Cg	
	m_dCg = 0.0;
	if (m_d6StDev)	// check devide by zero
		m_dCg = (20/(double)100 * m_nTol) / (double)m_d6StDev;


	//--------------
	// Calc Cgk  
	m_dCgk = 0.0;
	if (m_dStDev)	// check devide by zero
	{
		double absBias = (m_dBias < 0) ? (-m_dBias) : m_dBias;		// ���밪
		m_dCgk = (20/(double)200 * m_nTol - absBias) / (double)(3 * m_dStDev);
	}

	
	//---------------------------
	// Calc %Var(Repeatability)  
	m_dVarRept = 0.0;
	if (m_dCg)		// check devide by zero
		m_dVarRept = 20 / m_dCg;

	
	//------------------------------------
	// Calc %Var(Repeatability and Bias) 
	m_dVarReptBias = 0.0;
	if (m_dCgk)
		m_dVarReptBias = 20 / m_dCgk;

	UpdateData(FALSE);
}

void CGageDialog::DisplayGageStudyOutput(int type) 
{
	UpdateData(TRUE);
	CString strTemp;

	ClearGrid_Output();

	// Stat Grid
	strTemp.Format("%d", m_nRef);
	m_gridStat.SetItemText(STAT_REF, 		1,	strTemp);

	strTemp.Format("%.2f", m_dAvg); 			
	m_gridStat.SetItemText(STAT_MEAN, 		1,	strTemp);

	strTemp.Format("%.3f", m_dStDev);
	m_gridStat.SetItemText(STAT_STDEV, 		1,	strTemp);

	strTemp.Format("%.3f", m_d6StDev); 
	m_gridStat.SetItemText(STAT_6xSTDEV, 	1,	strTemp);

	strTemp.Format("%d", m_nTol);
	m_gridStat.SetItemText(STAT_TOL, 		1,	strTemp);


	// Bias Grid
	strTemp.Format("%.2f", m_dBias);
	m_gridBias.SetItemText(BIAS_BIAS, 		1, strTemp);

	strTemp.Format("%.3f", m_dT);
	m_gridBias.SetItemText(BIAS_T, 			1, strTemp);

	strTemp.Format("%.3f", m_dPValue); 
	m_gridBias.SetItemText(BIAS_PVALUE, 	1, strTemp);

	// Capability Grid
	strTemp.Format("%.2f", m_dCg);
	m_gridCapability.SetItemText(CAPABILITY_CG, 			1, strTemp);

	strTemp.Format("%.2f", m_dCgk);
	m_gridCapability.SetItemText(CAPABILITY_CGK, 			1, strTemp);

	strTemp.Format("%.2f %%", m_dVarRept);
	m_gridCapability.SetItemText(CAPABILITY_VAR_REPT, 		1, strTemp);
	if (m_dVarRept >= VAR_REPT_LIMIT_MAJ)
		m_gridCapability.SetItemBkColour(CAPABILITY_VAR_REPT, 1,	// row, col
										RGB(0xff, 0x63, 0x47));		// tomato : ���� ��Ȳ
	if (m_dVarRept >= VAR_REPT_LIMIT_CRI)
		m_gridCapability.SetItemBkColour(CAPABILITY_VAR_REPT, 1,	// row, col
										RGB(0xdc, 0x24, 0x4c));		// crimson(0xdc143c)���� �ణ ���� ����

	strTemp.Format("%.2f %%", m_dVarReptBias);
	m_gridCapability.SetItemText(CAPABILITY_VAR_REPT_BIAS, 	1, strTemp);

	UpdateData(FALSE);
	Invalidate(TRUE);		// ȭ�� ���� ����. UpdateData(False)������ Grid ȭ�� ������ ���� �ʾƼ� �߰���.
}
