#pragma once
#include "ProductManager.h"
#include <iosfwd>
#include "Table.h"

namespace PM {
	class QueryProduct{
	public:
		QueryProduct(ProductManager& pm) : pm{ pm } {}
		void QueryAddProduct();		//상품추가
		void QueryEraseProduct();	//상품삭제
		void QueryShowProduct();	//상품조회
		void QuerySaveProduct();	//상품저장
		void QueryLoadProduct();	//상품로드
	private:
		ProductManager& pm;
		static TB::Table table;		//테이블 형식으로 출력하기 위해 멤버로 먼저 선언해야 함
	};
}


