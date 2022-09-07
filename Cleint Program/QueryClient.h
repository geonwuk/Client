#pragma once
#include "ClientManager.h"
#include <array>
#include "Table.h"

namespace CM{
	class QueryClient
	{
	public:
		QueryClient(ClientManager& cm);
		void QueryAddClient();		//���߰�
		void QueryEraseClient();	//������
		void QueryShowClient();		//����ȸ
		void QuerySaveClient();		//������
		void QueryLoadClient();		//���ε�
	private:
		ClientManager& cm;
		static TB::Table table;		//���̺� �������� ����ϱ� ���� ����� ���� �����ؾ� ��
	};
}
