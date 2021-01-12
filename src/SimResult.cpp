// SimResult.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "COVID19_Simulator.h"
#include "SimResult.h"
#include "afxdialogex.h"


// SimResult ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(SimResult, CDialog)

SimResult::SimResult(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_Result, pParent)
	, Static_Time(0)
	, Static_infection_rate(0)
	, Static_Rcov_rate(0)
	, Static_10s_rate(0)
	, Static_20s_rate(0)
	, Static_30s_rate(0)
	, Static_40s_rate(0)
	, Static_50s_rate(0)
	, Static_60s_rate(0)
	, Static_70s_rate(0)
	, Static_80s_rate(0)
	, Static_90s_rate(0)
	, Static_child_rate(0)
{

}

SimResult::~SimResult()
{
}

void SimResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_Time, Static_Time);
	DDX_Text(pDX, IDC_STATIC_Infected, Static_infection_rate);
	DDX_Text(pDX, IDC_STATIC_Rcov, Static_Rcov_rate);
	DDX_Text(pDX, IDC_STATIC0_10, Static_10s_rate);
	DDX_Text(pDX, IDC_STATIC0_20, Static_20s_rate);
	DDX_Text(pDX, IDC_STATIC0_30, Static_30s_rate);
	DDX_Text(pDX, IDC_STATIC0_40, Static_40s_rate);
	DDX_Text(pDX, IDC_STATIC0_50, Static_50s_rate);
	DDX_Text(pDX, IDC_STATIC0_60, Static_60s_rate);
	DDX_Text(pDX, IDC_STATIC0_70, Static_70s_rate);
	DDX_Text(pDX, IDC_STATIC0_80, Static_80s_rate);
	DDX_Text(pDX, IDC_STATIC0_90, Static_90s_rate);
	DDX_Text(pDX, IDC_STATIC0, Static_child_rate);
}


BEGIN_MESSAGE_MAP(SimResult, CDialog)
END_MESSAGE_MAP()


// SimResult �޽��� ó�����Դϴ�.


BOOL SimResult::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.


	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
