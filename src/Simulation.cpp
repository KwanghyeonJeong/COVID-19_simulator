// Simulation.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "COVID19_Simulator.h"
#include "Simulation.h"
#include "afxdialogex.h"


// Simulation ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Simulation, CDialog)

Simulation::Simulation(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SimulationInit, pParent)
	, m_stage(0)
	, m_area(2)
	, m_infected(1)
	, init_flag(0)
{

}

Simulation::~Simulation()
{
}

void Simulation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOX, combox);
	DDX_Text(pDX, IDC_EDIT1, m_area);
	DDX_Text(pDX, IDC_EDIT2, m_infected);
	DDX_Text(pDX, IDC_EDIT1, m_area);
	DDV_MinMaxInt(pDX, m_area, 2, 1000);
	DDX_Text(pDX, IDC_EDIT2, m_infected);
	DDV_MinMaxInt(pDX, m_infected, 1, 999);
}


BEGIN_MESSAGE_MAP(Simulation, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBOX, &Simulation::OnCbnSelchangeCombox)
	ON_BN_CLICKED(IDOK, &Simulation::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Simulation::OnBnClickedCancel)
END_MESSAGE_MAP()


// Simulation �޽��� ó�����Դϴ�.

BOOL Simulation::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	combox.AddString(_T("Strong social distance(10%)"));
	combox.AddString(_T("Relaxed social distance(30%)"));
	combox.AddString(_T("Distance in life(50%)"));
	combox.AddString(_T("Everyday life(90%)"));
	combox.SetCurSel(0);
	m_area = 1;
	m_infected = 1;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void Simulation::OnCbnSelchangeCombox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_stage = combox.GetCurSel();
}



void Simulation::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	init_flag = 1;
	CDialog::OnOK();
}


void Simulation::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	init_flag = 0;
	CDialog::OnCancel();
}
