// GageDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ACE400Gage.h"
#include "GageDialog.h"
#include "chartdir.h"
#include "FileSysInfo.h"

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
	m_edit_nRef = m_edit_nRefInput;
	m_edit_nTol = m_edit_nTolInput;
	//}}AFX_DATA_INIT
	
}


void CGageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGageDialog)
	DDX_Control(pDX, IDC_COMBO_MEAS_TYPE, 	m_comboMeasType);
	DDX_Control(pDX, IDC_GRID, 				m_gridCtrl);
	DDX_Text   (pDX, IDC_EDIT_4W_FILE_PATH, m_editMeasDataPath);
	DDX_Text   (pDX, IDC_EDIT_REF_INPUT, 	m_edit_nRefInput);
	DDX_Text   (pDX, IDC_EDIT_TOL_INPUT, 	m_edit_nTolInput);
	DDV_MinMaxInt(pDX, m_edit_nTolInput, 1, 3);
	DDX_Text(	pDX, IDC_EDIT_REF, 			m_edit_nRef);
	DDX_Text(pDX, IDC_EDIT_TOL, m_edit_nTol);
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
	
	if (InitMember() == FALSE)
		return FALSE;

	if (InitView() == FALSE)
		return FALSE;

	
	g_sFile.Init();

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

	// ���� raw data ������ read�Ѵ�.

	return TRUE;
}


BOOL CGageDialog::InitView()
{
	UpdateData(TRUE);


	//-------------------------
	// 4W Meas data �ε�
	// ACE400�� 4W_Setup_A.txt ���� ��ġ�� ã�´�.   ex) "C:\ACE400\QC-JIG-S100-BHFlex\4W\"
	FileSysInfo01.LoadSaveView01(DATA_LOAD);		// Load	SysInfoView01.m_pStrFilePathBDL

	// 4W_Setup_A.txt ������ �ε��Ѵ�.
	Load_4W_MeasData();

	//----------------------------
	// mohm grid �ʱ�ȭ 

	m_gridCtrl.SetEditable(m_bEditable);
	//m_gridCtrl.SetListMode(m_bListMode);
	//m_gridCtrl.EnableDragAndDrop(TRUE);
	m_gridCtrl.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));		// ������� back ground


	TRY {
		m_gridCtrl.SetRowCount(m_nRows);
		m_gridCtrl.SetColumnCount(m_nCols);
		m_gridCtrl.SetFixedRowCount(m_nFixRows);
		m_gridCtrl.SetFixedColumnCount(m_nFixCols);
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


	//--------------------------
	// combo box init

	// mohm_75000 ������ combo�� �Է��Ѵ�.
	for (int type = 0; type < (MAX_MEAS_TYPE -1); type++)
		m_comboMeasType.InsertString( -1, g_MeasInfoTable[type].strMeas);

	// ���� combo���� ���õ� type#
	m_nCombo_CurrType = mohm_1;			// 0
	m_comboMeasType.SetCurSel(mohm_1);	// 0 = mohm_1

	SetGridBule(m_nCombo_CurrType);	// ���� ���õ� type column�� ����� Ǫ�������� ����.

	m_edit_nRefInput = g_MeasInfoTable[m_nCombo_CurrType].nMeasRef;
	m_edit_nRef = m_edit_nRefInput;


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

// â�� ���� ���϶� ������ �ʱ�ȭ�ؾ� �ϴ� ������� ������ 
// OnShowWindow()�� TOTO �ؿ� �ʱ�ȭ�Ѵ�. 
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

	// ���õ� type�� ���� 'type1 gage study' ����� ���? 
	// => ���� ����  'OK' ��ư�� ������ �� �����ϱ�� �Ѵ�.  ���� ���⼭ �ϰ� �� ���� ����.
	

	SetGridBule(m_nCombo_CurrType);	// ���� ���õ� type column�� ����� Ǫ�������� ����.

	
	// ��ȭ������ Edit��Ʈ�ѿ� m_edit_nRefInput �� ���.
	m_edit_nRefInput = g_MeasInfoTable[m_nCombo_CurrType].nMeasRef;
	m_edit_nRef = m_edit_nRefInput;
	UpdateData(FALSE); 
	Invalidate(TRUE);		// ȭ�� ���� ����. UpdateData(False)������ Grid ȭ�� ������ ���� �ʾƼ� �߰���.

}


// ���� ���õ� type�� ����� Ǫ�������� ����.
void CGageDialog::SetGridBule(int type)
{
	// ���� ����� ��� ��������� ���󺹱�
	ClearGrid_BackGround();			

	//  ���õ� mohm�� Grid cell���� Ǫ�� ������� ǥ��
	for (int meas=0; meas < m_nMeasCount; meas++)
		m_gridCtrl.SetItemBkColour(meas+1, (GRID_COL_MOHM_BASE + type), 	// row, col
									RGB(0x00, 0xbf, 0xff));					// deep skyblue : £�� �ϴ��Ķ� 

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

	m_edit_nTol = m_edit_nTolInput;
	
	UpdateData(FALSE);
}

void CGageDialog::OnButtonDoStudy() 
{
	// TODO: Add your control notification handler code here
	
}
