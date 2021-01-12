
// COVID19_SimulatorView.cpp : COVID19_SimulatorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "COVID19_Simulator.h"
#endif

#include "COVID19_SimulatorDoc.h"
#include "COVID19_SimulatorView.h"

#include "Simulation.h"
#include "Simulator.h"
#include "SimResult.h"
#include "Person.h"
#include <time.h>
#include <cstdlib>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//��ü(���) ���� ���
#define MAX 1000 //��ü ���� �ִ� ġ
#define SIZE 10 //��ü ũ��
#define DivideRect 10 //Ȱ�� �ݰ� ������ ���� ���
#define SPEED 15 //��ü �̵� �ӵ�
#define  Disease_progression_rate 5 //�ẹ��� ȸ���� ���� ���� ��ġ Ÿ�̸� nȸ�� 1�ܰ辿 ����

//Ÿ�̸� ���� ���
#define ST 1000 //�ùķ��̼� ���� Ÿ�̸�
#define TIMER 1001 // �ð����� Ÿ�̸�
#define TERM 50 //Ÿ�̸� ȣ�� ���� (�ẹ�� -> ȸ���� �ܰ躰 ���� �ӵ� ����)
#define TIMECHECK 1000 //TIMECHECK �ʸ��� �ð� ����

// COVID19_SimulatorView

IMPLEMENT_DYNCREATE(COVID19_SimulatorView, CView)

BEGIN_MESSAGE_MAP(COVID19_SimulatorView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_MENU_SIMULATION, &COVID19_SimulatorView::OnMenuSimulation)
	ON_COMMAND(ID_MENU_SIMULATOR, &COVID19_SimulatorView::OnMenuSimulator)
	ON_COMMAND(ID_MENU_RESULT, &COVID19_SimulatorView::OnMenuResult)
	ON_COMMAND(ID_AC1, &COVID19_SimulatorView::OnAcceleratorresult)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// COVID19_SimulatorView ����/�Ҹ�

COVID19_SimulatorView::COVID19_SimulatorView()
	: m_stage(1)
	, m_area(2)
	, m_infected(1)
	, init_flag(0)
	, start_flag(0)
	, age(0)
	, direction(0)
	, dx(0)
	, dy(0)
	, count(0)
	, t_count(0)
	, Result_infected(0)
	, Result_Non(0)
	, Resulted_Rcov(0)
	, m_time(0)
	, infected_child(0)
	, infected_10s(0)
	, infected_20s(0)
	, infected_30s(0)
	, infected_40s(0)
	, infected_50s(0)
	, infected_60s(0)
	, infected_70s(0)
	, infected_80s(0)
	, infected_90s(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(ID_AC1));

}

COVID19_SimulatorView::~COVID19_SimulatorView()
{
}

BOOL COVID19_SimulatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// COVID19_SimulatorView �׸���


Person *Human = new Person[MAX]; //��� ��ü �ܺ� ����
CPoint *pot = new CPoint[MAX]; //��ǥ�� ������ ���� CPoint �ܺ� ����

void COVID19_SimulatorView::OnDraw(CDC* pDC)
{
	COVID19_SimulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	
	if (init_flag) //�ʱ�ȭ ������ ���� ���
	{
		//�ùķ��̼� ���� �� �����ü �ʱ�ȭ
		if (start_flag == 0)
		{
			CPen redPen;
			CPen* pOldPen;
			CBrush RBrush, BBrush, GBrush;
			CRect rect;
			if (m_area < m_infected)
			{
				MessageBox(_T("There should be more Social Population than Number of Infected."), _T("Warning!"), MB_ICONWARNING);
				return;
			}
			redPen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			RBrush.CreateSolidBrush(RGB(255, 0, 0));
			BBrush.CreateSolidBrush(RGB(0, 0, 255));
			GBrush.CreateSolidBrush(RGB(0, 255, 0));
			GetClientRect(&rect);
			pOldPen = pDC->SelectObject(&redPen);
			pDC->Rectangle((rect.right / DivideRect), (rect.bottom / DivideRect), (rect.right / DivideRect) * 9, (rect.bottom / DivideRect) * 9);
			pDC->SelectObject(pOldPen);
			//��ü ��ü ��ĵ
			for (int i = 0; i < m_area; i++)
			{
				//������ǥ �Ҵ�
				Human[i].x = (rand() % ((rect.right / DivideRect) * 9) - SIZE);
				Human[i].y = (rand() % ((rect.bottom / DivideRect) * 9) - SIZE);
				if (Human[i].x < (rect.right / DivideRect))
					Human[i].x += (rect.right / DivideRect) + SIZE;
				if (Human[i].y < (rect.bottom / DivideRect))
					Human[i].y += (rect.bottom / DivideRect) + SIZE;
				//��ü ���� ���� �Ҵ� (0~99��)
				Human[i].m_age = rand() % 100;
				//������ǥ�� pot�� ���� ����
				pot[i].x = Human[i].x;
				pot[i].y = Human[i].y;
				if (i < m_infected)
				{
					Human[i].m_status=-1; //�ʱ� ����
					Human[i].m_hiden = (rand()%13) +2; //�ẹ�� ���� �ʱ�ȭ
					Human[i].m_Rcov_Period = 0; //ȸ���� 0 
					pDC->SelectObject(&RBrush);
					pDC->Rectangle(pot[i].x, pot[i].y, pot[i].x + SIZE, pot[i].y + SIZE);
				}
				else if (i >= m_infected)
				{
					Human[i].m_status=0; //�ʱ� �񰨿�
					Human[i].m_hiden = 0; //�ẹ�� 0
					Human[i].m_Rcov_Period = 0; //ȸ���� 0 
					pDC->SelectObject(&BBrush);
					pDC->Rectangle(pot[i].x, pot[i].y, pot[i].x + SIZE, pot[i].y + SIZE);
				}
			}
		}
		//�ùķ��̼� ���� ��
		else if (start_flag == 1)
		{
			//�⺻ ȭ�� ����
			CPen redPen;
			CPen* pOldPen;
			CBrush RBrush, BBrush, GBrush;
			CRect rect;
			redPen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			RBrush.CreateSolidBrush(RGB(255, 0, 0));
			BBrush.CreateSolidBrush(RGB(0, 0, 255));
			GBrush.CreateSolidBrush(RGB(0, 255, 0));
			GetClientRect(&rect);
			pOldPen = pDC->SelectObject(&redPen);
			pDC->Rectangle((rect.right / DivideRect), (rect.bottom / DivideRect), (rect.right / DivideRect) * 9, (rect.bottom / DivideRect) * 9);
			pDC->SelectObject(pOldPen);
			//��迡 ���Ǵ� ��� ���� �ʱ�ȭ
			statistics_init();
			//��ü �ϳ��ϳ� ���¿� ���� ���� ���� ������:������ �񰨿���:�Ķ��� ȸ��:�ʷϻ�
			for (int i = 0; i < m_area; i++)
			{
				if (Human[i].m_status == -1)
				{
					pDC->SelectObject(&RBrush);
					Result_infected++;
				}
				else if (Human[i].m_status == 0)
				{
					pDC->SelectObject(&BBrush);
					Result_Non++;
				}
				else if (Human[i].m_status == 1)
				{
					pDC->SelectObject(&GBrush);
					Resulted_Rcov++;
				}
				//��ü�� �簢�� �׸���
				pDC->Rectangle(pot[i].x, pot[i].y, pot[i].x + SIZE, pot[i].y + SIZE);
			}
			//���̺� ������ �� �����ϱ�(���)
			Classification_by_age_group();
		}
		//�ùķ��̼� ���� ��� ��
		else if (start_flag == -1)
		{
			KillTimer(ST);
			KillTimer(TIMER);
			return;
		}

	}
}


// COVID19_SimulatorView �μ�

BOOL COVID19_SimulatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void COVID19_SimulatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void COVID19_SimulatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// COVID19_SimulatorView ����

#ifdef _DEBUG
void COVID19_SimulatorView::AssertValid() const
{
	CView::AssertValid();
}

void COVID19_SimulatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COVID19_SimulatorDoc* COVID19_SimulatorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COVID19_SimulatorDoc)));
	return (COVID19_SimulatorDoc*)m_pDocument;
}
#endif //_DEBUG


// COVID19_SimulatorView �޽��� ó����

//�ùķ��̼� �ʱ�ȭ ���� ��
void COVID19_SimulatorView::OnMenuSimulation()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Simulation sim;

	//��ȭ���� Ŭ���� ���� �� -> ��Ŭ���� ���� ��
	//�ʱ�ȭ �ϱ� ��..
	if (!init_flag)
	{
		sim.DoModal();
		m_stage = sim.m_stage;
		m_area = sim.m_area;
		m_infected = sim.m_infected;
		init_flag = sim.init_flag;
		start_flag = 0; //start_flag �ʱ�ȭ
		Invalidate(); //OnDraw() ȣ��
	}
	//�ʱ�ȭ ����
	else if (init_flag)
	{
		//�ùķ��̼� ������ Ȥ�� ���� ���� �ٽ� �ʱ�ȭ �Ҷ� ��� �÷��� off,Ÿ�̸� off
		init_flag = 0;
		start_flag = 0;
		KillTimer(ST);
		KillTimer(TIMER);

		//���� ������ �ʱ�ȭ ���� ����
		//��ȭ���� Ŭ���� ���� ��-> ��Ŭ���� ������
		sim.DoModal();
		m_stage = sim.m_stage;
		m_area = sim.m_area;
		m_infected = sim.m_infected;
		init_flag = sim.init_flag;
		start_flag = 0; //start_flag �ʱ�ȭ
		Invalidate(); //OnDraw() ȣ��
	}
}

//�ùķ����� ���� ���� ��
void COVID19_SimulatorView::OnMenuSimulator()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Simulator sim;
	//�ʱ�ȭ�� �Ǿ��ִٸ�
	if (init_flag)
	{
		//�ùķ����� ���� ��, �÷���on ���� Ÿ�̸�, �ð� ���� Ÿ�̸� on
		if (!start_flag)
		{
			sim.DoModal();
			start_flag = sim.start_flag;
			SetTimer(ST, TERM, NULL);
			SetTimer(TIMER,TIMECHECK,NULL);
			Invalidate();
		}
		//�̹� �ùķ��̼� ������ �ùķ����� ���� ����� ����
		else if (start_flag)
			return;
	}
}

//���â ���, Ctrl+XŰ �Է½� �Լ� ȣ��
void COVID19_SimulatorView::OnMenuResult()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//�ùķ��̼� �����߿��� ����
	if (start_flag)
	{
		KillTimer(ST); // �ùķ��̼� ���� Ÿ�̸� off
		KillTimer(TIMER); //�ð� ���� Ÿ�̸� off
		SimResult sim;
		sim.Static_Time = t_count; //1�ʸ��� ȣ��Ǵ� Ÿ�̸� ȣ�� Ƚ���� �ùķ��̼� ���� �ð��� ǥ��(�ð�ǥ��� �ʴ��� int������ ������ ����)
		t_count = 0;//t_count �ʱ�ȭ
		sim.Static_infection_rate = floor(((Result_infected * 100) / m_area) * 100) / 100; //��ü ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
		sim.Static_Rcov_rate = floor(((Resulted_Rcov * 100) / m_area) * 100) / 100; //��ü ȸ���� ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���� ������*100
		//���̺� ������ �� ����
		if (Result_infected != 0)
		{
			sim.Static_child_rate = floor(((infected_child * 100) / Result_infected) * 100) / 100; //���� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
			sim.Static_10s_rate = floor(((infected_10s * 100) / Result_infected) * 100) / 100; //10�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
			sim.Static_20s_rate = floor(((infected_20s * 100) / Result_infected) * 100) / 100; //20�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
			sim.Static_30s_rate = floor(((infected_30s * 100) / Result_infected) * 100) / 100; //30�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
			sim.Static_40s_rate = floor(((infected_40s * 100) / Result_infected) * 100) / 100; //40�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
			sim.Static_50s_rate = floor(((infected_50s * 100) / Result_infected) * 100) / 100; //50�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
			sim.Static_60s_rate = floor(((infected_60s * 100) / Result_infected) * 100) / 100; //60�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
			sim.Static_70s_rate = floor(((infected_70s * 100) / Result_infected) * 100) / 100; //70�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
			sim.Static_80s_rate = floor(((infected_80s * 100) / Result_infected) * 100) / 100; //80�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
			sim.Static_90s_rate = floor(((infected_90s * 100) / Result_infected) * 100) / 100; //90�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
		}
		else
		{
			//��� ȸ���ǰų� �����ڰ� ���� ���
			//��� ������ = 0
			sim.Static_child_rate = 0;
			sim.Static_10s_rate = 0;
			sim.Static_20s_rate = 0;
			sim.Static_30s_rate = 0;
			sim.Static_40s_rate = 0;
			sim.Static_50s_rate = 0;
			sim.Static_60s_rate = 0;
			sim.Static_70s_rate = 0;
			sim.Static_80s_rate = 0;
			sim.Static_90s_rate = 0;
		}
		//ī���ͺ��� �ʱ�ȭ
		count = 0;
		//��� �÷��� �ʱ�ȭ
		init_flag = 0;
		start_flag = 0;
		//���â ����
		sim.DoModal();
	}
}


void COVID19_SimulatorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnTimer(nIDEvent);
	if (nIDEvent == ST) //�ùķ����� ���� �� ȣ��...
	{
		int infect_rate = rand() % 9;
		for (int i = 0; i < m_area; i++)
		{
			CRect rect;
			GetClientRect(&rect);
			direction = (rand() % 4) + 1; // 4��и� ����.
			dx = rand() % SPEED;
			dy = rand() % SPEED;
			switch (direction)
			{
			case 1://1��и� ���� ++ 
					pot[i].x += dx;
					pot[i].y += dy;
				break;
			case 2://2��и� ���� -+
					pot[i].x -= dx;
					pot[i].y += dy;			
				break;
			case 3://3��и� ���� --
					pot[i].x -= dx;
					pot[i].y -= dy;
				break;
			case 4://4��и� ���� +-
					pot[i].x += dx;
					pot[i].y -= dy;
				break;
			}
		}
		SocailArea();
		Period_H();
		Period_Rcov();
		switch (m_stage)
		{
		case 0://10%
			if (infect_rate == 0)
				Contact();
			break;
		case 1://30%
			if (infect_rate >= 0 && infect_rate<=2)
				Contact();
			break;
		case 2://50%
			if (infect_rate >= 0 && infect_rate <= 4)
				Contact();
			break;
		case 3://90%
			if (infect_rate != 9)
				Contact();
			break;
		}
		if (Result_infected + Resulted_Rcov == m_area || Result_infected == 0 || t_count >= 30) //��� ����� �����ǰų� ���̻� ������ �ȵǰų� �ùķ��̼� 30�ʰ� ������ ���
		{
			KillTimer(ST); // �ùķ��̼� ���� Ÿ�̸� off
			KillTimer(TIMER); //�ð� ���� Ÿ�̸� off
			SimResult sim;
			sim.Static_Time = t_count; //1�ʸ��� ȣ��Ǵ� Ÿ�̸� ȣ�� Ƚ���� �ùķ��̼� ���� �ð��� ǥ��(�ð�ǥ��� �ʴ��� int������ ������ ����)
			t_count = 0;//t_count �ʱ�ȭ
			sim.Static_infection_rate = floor(((Result_infected * 100) / m_area) * 100) / 100; //��ü ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
			sim.Static_Rcov_rate = floor(((Resulted_Rcov * 100) / m_area) * 100) / 100; //��ü ȸ���� ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���� ������*100
																						//���̺� ������ �� ����
			if (Result_infected != 0)
			{
				sim.Static_child_rate = floor(((infected_child * 100) / Result_infected) * 100) / 100; //���� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
				sim.Static_10s_rate = floor(((infected_10s * 100) / Result_infected) * 100) / 100; //10�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
				sim.Static_20s_rate = floor(((infected_20s * 100) / Result_infected) * 100) / 100; //20�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
				sim.Static_30s_rate = floor(((infected_30s * 100) / Result_infected) * 100) / 100; //30�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
				sim.Static_40s_rate = floor(((infected_40s * 100) / Result_infected) * 100) / 100; //40�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
				sim.Static_50s_rate = floor(((infected_50s * 100) / Result_infected) * 100) / 100; //50�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
				sim.Static_60s_rate = floor(((infected_60s * 100) / Result_infected) * 100) / 100; //60�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
				sim.Static_70s_rate = floor(((infected_70s * 100) / Result_infected) * 100) / 100; //70�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
				sim.Static_80s_rate = floor(((infected_80s * 100) / Result_infected) * 100) / 100; //80�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
				sim.Static_90s_rate = floor(((infected_90s * 100) / Result_infected) * 100) / 100; //90�� ������ ��� floor �Լ����� �Ҽ��� ��° �ڸ��� �ݿø� �ϱ� ���� ���������� *100
			}
			else
			{
				//��� ȸ���ǰų� �����ڰ� ���� ���
				//��� ������ = 0
				sim.Static_child_rate = 0;
				sim.Static_10s_rate = 0;
				sim.Static_20s_rate = 0;
				sim.Static_30s_rate = 0;
				sim.Static_40s_rate = 0;
				sim.Static_50s_rate = 0;
				sim.Static_60s_rate = 0;
				sim.Static_70s_rate = 0;
				sim.Static_80s_rate = 0;
				sim.Static_90s_rate = 0;
			}
			//ī���ͺ��� �ʱ�ȭ
			count = 0;
			//��� �÷��� �ʱ�ȭ
			init_flag = 0;
			start_flag = 0;
			//���â ����
			sim.DoModal();
		}
		count++; //Ÿ�̸� ȣ�� �� ������ +1 , ��ü�� �ẹ��, ȸ���� ������ ���� �ʿ��� ����
		Invalidate();
	}
	else if (nIDEvent == TIMER)
	{
		t_count++; //�ð� Ȯ�� �ֱ⸶�� +1 
	}


}

//���� �� �̵�
void COVID19_SimulatorView::SocailArea()
{
	RECT rect;
	GetClientRect(&rect);
	//��ü ��ü ��ĵ
	for (int i = 0; i < m_area; i++)
	{
		//���� ���̵� ������ ��Ż�� ���
		if (pot[i].x - SIZE <= ((rect.right) / DivideRect))
		{
			pot[i].x += dx * 3; // x �࿡�� x���� 3�� ��ŭ ���������� �̵�
		}
		//������ ���̵� ������ ��Ż�� ���
		else if (pot[i].x + SIZE >= ((rect.right * 9) / DivideRect))
		{
			pot[i].x -= dx * 3; // x �࿡�� x���� 3�� ��ŭ �������� �̵�
		}
		//���� ���̵� ������ ��Ż�� ���
		else if (pot[i].y - SIZE <= ((rect.bottom) / DivideRect))
		{
			pot[i].y += dy * 3; //y �࿡�� y���� 3�� ��ŭ �Ʒ��� �̵�
		}
		//�Ʒ��� ���̵� ������ ��Ż�� ���
		else if (pot[i].y + SIZE >= ((rect.bottom * 9) / DivideRect))
		{
			pot[i].y -= dy * 3; //y�࿡�� y���� 3�� ��ŭ ���� �̵�
		}
	}

}

// �ẹ�� �Ⱓ..
void COVID19_SimulatorView::Period_H()
{
	for (int i = 0; i < m_area; i++)
	{
		//�ẹ���� ���
		if (count% Disease_progression_rate == 0 && Human[i].m_hiden >= 2)
		{
			// �ùķ��̼� ���� ȣ�� Disease_progression_rateȸ ���� �ѹ��� �ẹ�� ����
			Human[i].m_hiden++;
			if (Human[i].m_hiden >= 14)
			{
				Human[i].m_Rcov_Period = (rand()%5)+7; //ȸ���� ����(����, 7~11) ����
				Human[i].m_hiden = 0; //�ẹ�� 0 => ���� for�� ����
			}
		}
	}
}


// ȸ���� �Ⱓ..
void COVID19_SimulatorView::Period_Rcov()
{
	for (int i = 0; i < m_area; i++)
	{
		//ȸ������ ���
		if (count % Disease_progression_rate*2 == 0 && Human[i].m_Rcov_Period >= 7) //ȸ���� �ֱ⸦ �ẹ�� ���� 2�� �� �÷ȴ�.
		{
			// �ùķ��̼� ���� ȣ�� Disease_progression_rateȸ ���� �ѹ��� ȸ���� ����
			Human[i].m_Rcov_Period++;
			if (Human[i].m_Rcov_Period >= 21)
			{
				Human[i].m_Rcov_Period = 0; //���� for�� ����
				Human[i].m_hiden = 0; //�ẹ�� �ʱ�ȭ
				Human[i].m_status = 1; //ȸ���� ǥ��
			}

		}

	}

}

// ���� ���� �Ǵ� �Լ�
void COVID19_SimulatorView::Contact()
{

	for (int i = 0; i < m_area; i++)
	{
		int first_x = pot[i].x + (SIZE / 2); //��ü���� �߾� ��ǥ��(x)�� ����
		int first_y = pot[i].y + (SIZE / 2); //��ü���� �߾� ��ǥ��(y)�� ����
		for (int j = 0; j < m_area; j++)
		{
			int last_x = pot[j].x + (SIZE / 2); //��ü���� �߾� ��ǥ��(x)�� ����
			int last_y = pot[j].y + (SIZE / 2); //��ü���� �߾� ��ǥ��(y)�� ����
			//sqrt(a^2+b^2)=c ��Ÿ��� ���� 
			double distance_s = ((first_x - last_x)*(first_x - last_x)) + ((first_y - last_y)*(first_y - last_y)); 
			double distance = sqrt(distance_s);
			//���� �¿� 2��ŭ�� ������ �ξ���. (���� ������ ������.)
			if (distance < (double)(SIZE + 2))
			{
				if (i != j) //���� �ٸ� ��ü�� ���� ��
				{
					if (Human[i].m_status == 0 && Human[j].m_status == 0) //�񰨿��� & �񰨿��� ����
					{
						Human[i].m_status = 0;
					}
					else if (Human[i].m_status == 0 && Human[j].m_Rcov_Period >= 7) // �񰨿��� & ������ ����
					{
						//������ ���Ҿ� �ẹ�� ����
						Human[i].m_status = -1;
						Human[i].m_hiden = 2;
					}
					else if (Human[i].m_status == -1 && Human[j].m_Rcov_Period >= 7) //������ & ������ ����
					{
						Human[i].m_status = -1;
					}
					else if (Human[i].m_Rcov_Period >= 7 && Human[j].m_status == 0) //������ & �񰨿��� ����
					{
						//������ ���Ҿ� �ẹ�� ����
						Human[j].m_status = -1;
						Human[j].m_hiden = 2;
					}
				}
			}
		}
	}
}

// ��迡 ���Ǵ� ���� �ʱ�ȭ
void COVID19_SimulatorView::statistics_init()
{
	infected_child = 0;
	infected_10s = 0;
	infected_20s = 0;
	infected_30s = 0;
	infected_40s = 0;
	infected_50s = 0;
	infected_60s = 0;
	infected_70s = 0;
	infected_80s = 0;
	infected_90s = 0;
	Result_infected = 0; //������ �� (���) �ʱ�ȭ
	Result_Non = 0; //�� ������ �� (���) �ʱ�ȭ
	Resulted_Rcov = 0; //ȸ���� �� (���) �ʱ�ȭ
}


// ���̺� ������ �� ����
void COVID19_SimulatorView::Classification_by_age_group()
{
	for (int i = 0; i < m_area; i++)
	{
		switch (Human[i].m_age / 10)
		{
		case 0://���(0~9��)
			if (Human[i].m_status == -1) //�����ڶ��
				infected_child++; //��� ������ +1
			break;
		case 1://10��
			if (Human[i].m_status == -1) //�����ڶ��
				infected_10s++; //10�� ������ +1
			break;
		case 2://20��
			if (Human[i].m_status == -1) //�����ڶ��
				infected_20s++; //20�� ������ +1
			break;
		case 3://30��
			if (Human[i].m_status == -1) //�����ڶ��
				infected_30s++; //30�� ������ +1
			break;
		case 4://40��
			if (Human[i].m_status == -1) //�����ڶ��
				infected_40s++; //40�� ������ +1
			break;
		case 5://50��
			if (Human[i].m_status == -1) //�����ڶ��
				infected_50s++; //50�� ������ +1
			break;
		case 6://60��
			if (Human[i].m_status == -1) //�����ڶ��
				infected_60s++; //60�� ������ +1
			break;
		case 7://70��
			if (Human[i].m_status == -1) //�����ڶ��
				infected_70s++; //70�� ������ +1
			break;
		case 8://80��
			if (Human[i].m_status == -1) //�����ڶ��
				infected_80s++; //80�� ������ +1
			break;
		case 9://90��
			if (Human[i].m_status == -1) //�����ڶ��
				infected_90s++; //90�� ������ +1
			break;
		}
	}

}

//����Ű ���� �� Ctrl + X
void COVID19_SimulatorView::OnAcceleratorresult()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	OnMenuResult(); //���â ����
	Invalidate(); //ȭ�� �����
}
