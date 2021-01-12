#pragma once
#include "afxwin.h"


// Simulation ��ȭ �����Դϴ�.

class Simulation : public CDialog
{
	DECLARE_DYNAMIC(Simulation)

public:
	Simulation(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Simulation();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SimulationInit };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// �޺��ڽ� ��Ʈ�� ����
	CComboBox combox;
	// �濪�ܰ� �������
	int m_stage;
	// ��ȸ �ο� �� �������
	int m_area;
	// ������ �� �������
	int m_infected;
	afx_msg void OnCbnSelchangeCombox();
	virtual BOOL OnInitDialog();
	int init_flag;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
