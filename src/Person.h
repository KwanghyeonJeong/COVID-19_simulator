#pragma once
class Person
{
public:
	Person();
	~Person();
	// ���� ������� 
	int m_age;
	// ���� 0=�񰨿��� -1=������ 1=ȸ����
	int m_status;

	// x��ǥ
	int x;
	// y��ǥ
	int y;
	// �ẹ�� 0:�񰨿� or ȸ�� 2~14:13�ܰ��� �ẹ��..
	int m_hiden;
	// ȸ���� 7~21...15�ܰ� ������ų �� ����..
	int m_Rcov_Period;
};

