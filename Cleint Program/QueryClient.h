#pragma once
#include "ClientManager.h"
#include <array>
#include "Table.h"

namespace CM{
	class QueryClient
	{
	public:
		QueryClient(ClientManager& cm);
		void QueryAddClient();		//고객추가
		void QueryEraseClient();	//고객삭제
		void QueryShowClient();		//고객조회
		void QuerySaveClient();		//고객저장
		void QueryLoadClient();		//고객로드
	private:
		ClientManager& cm;
		static TB::Table table;		//테이블 형식으로 출력하기 위해 멤버로 먼저 선언해야 함
	};
}
