#pragma once
#include "OrderManager.h"
#include "Table.h"
namespace OM {
	class QueryOrder{
	public:
		QueryOrder(OM::OrderManager& om) : om{ om } {}
		void QueryAddOrder();	//�ֹ��߰�
		void QueryEraseOrder();	//�ֹ�����
		void QueryShowOrder();	//�ֹ���ȸ
		void QuerySaveOrder();	//�ֹ�����
		void QueryLoadOrder();	//�ֹ��ҷ�����
	private:
		OM::OrderManager& om;	//OrderManager�� ���� �۾��� �Ѵ�
		static TB::Table table;	//���̺� �������� ����ϱ� ���� ����� ���� �����ؾ� ��
	};
}


