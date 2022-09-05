#pragma once
#include <map>
#include <string>
#include <string>
#include <ctime>
using std::map;
using std::string;
namespace PM {
	using std::string;

	class Product
	{
	protected:
		Product() = default;
	public:
		Product(unsigned int id, string name, double price, unsigned int qty, tm date) :
			id{ id }, name{ name }, price{ price }, qty{ qty }, registered_date{ date }{}

		const unsigned int getId() const { return id; }

		unsigned int id;
		string name;
		double price;
		unsigned int qty;
		tm registered_date;

	};

	struct NoProduct : public Product { NoProduct() {} };
	const NoProduct no_product{};

	bool operator== (const Product& p, const NoProduct&);
	

	class ProductManager
	{
	private:

	public:

		bool addProduct(const string name, double price, unsigned int qty);
		bool eraseProduct(const unsigned int id);
		const Product& findProduct(const unsigned int id) const;

		const map< unsigned int, Product >& getProducts() const;

		//using iterator = ProductManager_iterator;


	private:
		static unsigned int product_id;
		map < unsigned int, Product > products;

	};


}
