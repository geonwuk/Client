#pragma once
#include "ProductManager.h"
#include <iosfwd>

using namespace PM;

std::ostream& operator<< (std::ostream& os, const tm& p);
std::ostream& operator<< (std::ostream& os, const Product& p);
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

