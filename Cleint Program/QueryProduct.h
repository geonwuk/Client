#pragma once
#include "ProductManager.h"
class QueryProduct
{
public:
	QueryProduct(ProductManager& pm) : pm{ pm } {}

	void QueryAddProduct();
	void QueryEraseProduct();
	void QueryShowProduct();

private:
	ProductManager& pm;
};

