#pragma once
#include "afxwin.h"


// SimResult ��ȭ �����Դϴ�.

class SimResult : public CDialog
{
	DECLARE_DYNAMIC(SimResult)

public:
	SimResult(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~SimResult();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Result };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int Static_Time;
	// �ùķ��̼� ���� �� ���� ������
	double Static_infection_rate;
	// �ùķ��̼� ����� ���� ȸ����
	double Static_Rcov_rate;
	// 10�� ���� ��� ������
	double Static_child_rate;
	// 10�� ������
	double Static_10s_rate;
	// 20�� ������
	double Static_20s_rate;
	// 30�� ������
	double Static_30s_rate;
	// 40�� ������
	double Static_40s_rate;
	// 50�� ������
	double Static_50s_rate;
	// 60�� ������
	double Static_60s_rate;
	// 70�� ������
	double Static_70s_rate;
	// 80�� ������
	double Static_80s_rate;
	// 90�� ������
	double Static_90s_rate;
};
