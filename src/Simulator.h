#pragma once


// Simulator ��ȭ �����Դϴ�.

class Simulator : public CDialog
{
	DECLARE_DYNAMIC(Simulator)

public:
	Simulator(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Simulator();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Simulator };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int start_flag;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
