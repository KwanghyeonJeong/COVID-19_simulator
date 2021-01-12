
// COVID19_SimulatorView.h : COVID19_SimulatorView Ŭ������ �������̽�
//

#pragma once


class COVID19_SimulatorView : public CView
{
protected: // serialization������ ��������ϴ�.
	COVID19_SimulatorView();
	DECLARE_DYNCREATE(COVID19_SimulatorView)

// Ư���Դϴ�.
public:
	COVID19_SimulatorDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~COVID19_SimulatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	// �濪�ܰ� �������
	int m_stage;
	// ��ȸ �ο��� �������
	int m_area;
	// ������ �� �������
	int m_infected;
	// �ùķ��̼� �ʱ�ȭ �÷���
	int init_flag;
	// �ùķ��̼� ���� �÷��� 0 / 1 / -1 :�ʱ�ȭ�� �Ǿ��ִ� ���� / �ùķ��̼� on / �ùķ��̼� off
	int start_flag;
	// ���� ����
	int age;
	// ������ ��Ÿ���� ����
	int direction;
	// x����
	int dx;
	// y����
	int dy;
	// ���� ���� �Ǵ� �Լ�	
	void Contact();
	// ���� ������ �̵�
	void SocailArea();
	// �ẹ�� �Ⱓ..
	void Period_H();
	// ȸ���� �Ⱓ..
	void Period_Rcov();
	//�ùķ��̼� Ÿ�̸� ȣ�� Ƚ��
	int count;
	// �ð� ���� ����
	int t_count;
	// �����ڼ�(���)
	double Result_infected;
	// �񰨿��� ��(���) 
	double Result_Non;
	// ȸ���� ��(���)
	double Resulted_Rcov;
	// �ð� �� ���� ����
	int m_time;
	// ��� ������(~9��)
	double infected_child;
	// 10�� ������ ��
	double infected_10s;
	// 20�� ������ ��
	double infected_20s;
	// 30�� ������ ��
	double infected_30s;
	// 40�� ������ ��
	double infected_40s;
	// 50�� ������ ��
	double infected_50s;
	// 60�� ������ ��
	double infected_60s;
	// 70�� ������ ��
	double infected_70s;
	// 80�� ������ ��
	double infected_80s;
	// 90�� ������ ��
	double infected_90s;
	//����Ű ��� ����
	HACCEL m_hAccel;
	// ��迡 ���Ǵ� ���� �ʱ�ȭ
	void statistics_init();
	// ���̺� ������ �� ����
	void Classification_by_age_group();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnAcceleratorresult();
	afx_msg void OnMenuSimulation();
	afx_msg void OnMenuSimulator();
	afx_msg void OnMenuResult();
};

#ifndef _DEBUG  // COVID19_SimulatorView.cpp�� ����� ����
inline COVID19_SimulatorDoc* COVID19_SimulatorView::GetDocument() const
   { return reinterpret_cast<COVID19_SimulatorDoc*>(m_pDocument); }
#endif

