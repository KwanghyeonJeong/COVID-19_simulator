// Simulator.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "COVID19_Simulator.h"
#include "Simulator.h"
#include "afxdialogex.h"


// Simulator ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Simulator, CDialog)

Simulator::Simulator(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_Simulator, pParent)
	, start_flag(0)
{

}

Simulator::~Simulator()
{
}

void Simulator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Simulator, CDialog)
	ON_BN_CLICKED(IDOK, &Simulator::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Simulator::OnBnClickedCancel)
END_MESSAGE_MAP()


// Simulator �޽��� ó�����Դϴ�.


void Simulator::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	start_flag = 1;
	CDialog::OnOK();
}


void Simulator::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	start_flag = -1;
	CDialog::OnCancel();
}
