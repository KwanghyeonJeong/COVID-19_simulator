
// COVID19_Simulator.h : COVID19_Simulator ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// COVID19_SimulatorApp:
// �� Ŭ������ ������ ���ؼ��� COVID19_Simulator.cpp�� �����Ͻʽÿ�.
//

class COVID19_SimulatorApp : public CWinApp
{
public:
	COVID19_SimulatorApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COVID19_SimulatorApp theApp;
