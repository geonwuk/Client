#pragma once
#include "ProductManager.h"
#include <iosfwd>
#include "Table.h"

namespace PM {
	class QueryProduct{
	public:
		QueryProduct(ProductManager& pm) : pm{ pm } {}
		void QueryAddProduct();		//��ǰ�߰�
		void QueryEraseProduct();	//��ǰ����
		void QueryShowProduct();	//��ǰ��ȸ
		void QuerySaveProduct();	//��ǰ����
		void QueryLoadProduct();	//��ǰ�ε�
	private:
		ProductManager& pm;
		static TB::Table table;		//���̺� �������� ����ϱ� ���� ����� ���� �����ؾ� ��
	};
}


