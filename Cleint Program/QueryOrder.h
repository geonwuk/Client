#pragma once
#include "OrderManager.h"
#include "Table.h"
namespace OM {
	class QueryOrder{
	public:
		QueryOrder(OM::OrderManager& om) : om{ om } {}
		void QueryAddOrder();	//주문추가
		void QueryEraseOrder();	//주문삭제
		void QueryShowOrder();	//주문조회
		void QuerySaveOrder();	//주문저장
		void QueryLoadOrder();	//주문불러오기
	private:
		OM::OrderManager& om;	//OrderManager가 실제 작업을 한다
		static TB::Table table;	//테이블 형식으로 출력하기 위해 멤버로 먼저 선언해야 함
	};
}


