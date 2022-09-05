#pragma once
#include "ProductManager.h"
#include <iosfwd>

using namespace PM;

std::ostream& operator<< (std::ostream& os, const tm& p);
class QueryProduct
{
public:
	QueryProduct(ProductManager& pm) : pm{ pm } {}

	void QueryAddProduct();
	void QueryEraseProduct();
	void QueryShowProduct();
	void QuerySaveProduct();
	void QueryLoadProduct();

private:
	ProductManager& pm;
};

