#include "stdafx.h"
#include "System.h"

CSystem g_sSystem;


CSystem::~CSystem()
{


}

void CSystem::InitMember() 
{
	::ZeroMemory(m_nBlockNumber, sizeof(m_nBlockNumber));
	::ZeroMemory(m_nBlockType, sizeof(m_nBlockType));

	m_nRJigFileNum = -1;
	m_nSystemType = -1;

	InitCalData();
	//TRACE("CSystem::InitMember(): sizeof(m_nBlockNumber)=%d\n", sizeof(m_nBlockNumber));
	//TRACE("CSystem::InitMember(): sizeof(m_nBlockType)=%d\n", sizeof(m_nBlockType));
}





// "D:\log4w\" 디렉토리에 날짜별폴더 -> 시간별 Net Sample Raw data를  로드
BOOL 	CSystem::Load_4wRawData()
{
	FILE *fp; 
	char  fName[200]; 
	int i; 
	BOOL bRetVal = TRUE;


	::ZeroMemory(&fName, sizeof(fName));
	strcat(fName , g_sFile.ACE400_TestConditionPath);		// "C:\ACE400\SETUP\\SysSet21_ACE400.ini"

	if(!FileExists(fName)) 
	{ 	ERR.Set(FLAG_FILE_NOT_FOUND, fName); return FALSE; }

	fp=fopen(fName,"rt");
	if(fp == NULL)
	{ 	ERR.Set(FLAG_FILE_CANNOT_OPEN, fName); return FALSE; }

	int Num;

	// 파일 헤더 Read 
	for (i=0; i < 16; i++)
		fscanf(fp, "%10d", &Num);	// 파일 헤더는 저장하지 말자.  Skip
	fscanf(fp, "\n");

	// 파일 데이터 Read
	for (i=0; i < MAX_TEST_MODE; i++)
	{

		fscanf(fp, "%10d", &Num); 	// 첫 컬럼 Num 은 저장하지 말자. (i+1값과 같아서 불필요)
		fscanf(fp, "%10d", &g_saTestCondition[i].nCC);
		fscanf(fp, "%10d", &g_saTestCondition[i].nVBSrc);
		fscanf(fp, "%10d", &g_saTestCondition[i].nVSet);
		fscanf(fp, "%10d", &g_saTestCondition[i].nIRng);
		fscanf(fp, "%10d", &g_saTestCondition[i].nISet);
		fscanf(fp, "%10d", &g_saTestCondition[i].nDelay);
		fscanf(fp, "%10d", &g_saTestCondition[i].nAdCnt);

		fscanf(fp, "%10d", &g_saTestCondition[i].nFilter);
		fscanf(fp, "%10d", &g_saTestCondition[i].nIFilter);
		fscanf(fp, "%10d", &g_saTestCondition[i].nHvOffset);
		fscanf(fp, "%10d", &g_saTestCondition[i].nHVGain);
		fscanf(fp, "%10d", &g_saTestCondition[i].nIGain);
		fscanf(fp, "%10d", &g_saTestCondition[i].n4WGain);
		fscanf(fp, "%10d", &g_saTestCondition[i].sCount);
		fscanf(fp, "%10d", &g_saTestCondition[i].nTest);
		fscanf(fp, "\n");
	}
	fclose(fp);


	// Load한  calMode, TestCondtion의 Range를 체크한다.
	CString strTemp("");
	CString title=""; CString state=""; CString sol="";

	for (i=0; i < MAX_TEST_MODE; i++)
	{
		if (Check_TestCondtionRange(15, g_saTestCondition[i].nTest) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		// Test를 수행하지 않는 케이스라면 range 체크 필요 없이 다음 케이스 진행
		if(	g_saTestCondition[i].nTest == TEST_NOT_USE)
			continue;

		if (Check_TestCondtionRange(1, g_saTestCondition[i].nCC) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d:\n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
		
		if (Check_TestCondtionRange(2, g_saTestCondition[i].nVBSrc) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(3, g_saTestCondition[i].nVSet) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(4, g_saTestCondition[i].nIRng) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(5, g_saTestCondition[i].nISet) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(6, g_saTestCondition[i].nDelay) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(7, g_saTestCondition[i].nAdCnt) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(8, g_saTestCondition[i].nFilter) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(9, g_saTestCondition[i].nIFilter) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(10, g_saTestCondition[i].nHvOffset) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(11, g_saTestCondition[i].nHVGain) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(12, g_saTestCondition[i].nIGain) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(13, g_saTestCondition[i].n4WGain) == FALSE)
		{ 	strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
		if (Check_TestCondtionRange(14, g_saTestCondition[i].sCount) == FALSE)
		{ strTemp.Format("Load_TestCondtionData: CalMode=%d: \n%s", i, ERR.m_strState);
			ERR.Set(RANGE_OVER, strTemp);
			ErrMsg(); ERR.Reset(); 
			bRetVal = FALSE;
			continue; 
		}
	
	}
	return bRetVal;
}

// "C:\ACE400\SETUP\\SysSet21_ACE400.ini"에 g_saTestCondition[MAX_TEST_MODE] 데이터 Save
BOOL CSystem::Save_TestCondtionData()
{
	FILE *fp; 
	char  fName[200]; 
	int i; 

	::ZeroMemory(&fName, sizeof(fName));
	
	// Test 후에 실제 ini 파일 Path 로 바꾼다.=> 테스트 완료.
	//strcat(fName , ".\\Parameter\\SysSet21_ACE400.ini"); 
	
	strcat(fName , g_sFile.ACE400_TestConditionPath);		// "C:\ACE400\SETUP\\SysSet21_ACE400.ini"

	
	//if(!FileExists(fName)) 
	//{ 	ERR.Set(FLAG_FILE_NOT_FOUND, fName); return FALSE; }

	fp=fopen(fName,"wt");
	if(fp == NULL)
	{ 	
		TRACE("%s", strerror( errno ));
		ERR.Set(FLAG_FILE_CANNOT_OPEN, fName); return FALSE; 
	}

	// 파일 헤더 출력
	for (i=0; i < 14; i++)
		fprintf(fp, "%10d", i);	
	fprintf(fp, "%10d", 0);
	fprintf(fp, "%10d", 0);
	fprintf(fp, "\n");

	// 파일 데이터 출력: TestCondtion Data
	for (i=0; i < MAX_TEST_MODE; i++)
	{

		fprintf(fp, "%10d", i+1);	
		fprintf(fp, "%10d", g_saTestCondition[i].nCC);			// 1
		fprintf(fp, "%10d", g_saTestCondition[i].nVBSrc);		// 2
		fprintf(fp, "%10d", g_saTestCondition[i].nVSet);		// 3
		fprintf(fp, "%10d", g_saTestCondition[i].nIRng);		// 4
		fprintf(fp, "%10d", g_saTestCondition[i].nISet);		// 5
		fprintf(fp, "%10d", g_saTestCondition[i].nDelay);		// 6
		fprintf(fp, "%10d", g_saTestCondition[i].nAdCnt);		// 7
			
		fprintf(fp, "%10d", g_saTestCondition[i].nFilter);		// 8
		fprintf(fp, "%10d", g_saTestCondition[i].nIFilter);		// 9
		fprintf(fp, "%10d", g_saTestCondition[i].nHvOffset);	// 10
		fprintf(fp, "%10d", g_saTestCondition[i].nHVGain);		// 11
		fprintf(fp, "%10d", g_saTestCondition[i].nIGain);		// 12
		fprintf(fp, "%10d", g_saTestCondition[i].n4WGain);		// 13
		fprintf(fp, "%10d", g_saTestCondition[i].sCount);		// 14
		fprintf(fp, "%10d", g_saTestCondition[i].nTest);		// 15

		fprintf(fp, "\n");

	}

	fclose(fp);
	return TRUE;
}

