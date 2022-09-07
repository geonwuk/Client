#pragma once
#include "ProductManager.h"
#include <iosfwd>
#include "Table.h"

namespace PM {
	class QueryProduct{
	public:
		QueryProduct(ProductManager& pm) : pm{ pm } {}
		void QueryAddProduct();
		void QueryEraseProduct();
		void QueryShowProduct();
		void QuerySaveProduct();
		void QueryLoadProduct();
	private:
		ProductManager& pm;
		static TB::Table table;
	};
}


