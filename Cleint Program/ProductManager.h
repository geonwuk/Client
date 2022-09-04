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
		Product(unsigned int id, string ID, string name, double price, double discounted_ratio, tm date) :
			id{ id }, ID{ ID }, name{ name }, price{ price }, discounted_ratio{ discounted_ratio }, registered_date{ date }{}

		const unsigned int getId() const { return id; }

		unsigned int id;
		string ID;
		string name;
		double price;
		double discounted_ratio;
		tm registered_date;



	};

	struct NoProduct : public Product { NoProduct() {} };
	static const NoProduct no_product;

	bool operator== (const Product& p, const NoProduct&);
	

	class ProductManager
	{
	public:
		friend bool operator!= (const Product& p, const NoProduct& np);
	private:
		map < string, Product* > products_by_string;

	public:

		void addProduct(string ID, string name, double price, double discounted_ratio);
		bool eraseProduct(string ID);
		const Product& findProduct(const string& ID) const;

		const map< unsigned int, Product >& getProducts() const;

		//using iterator = ProductManager_iterator;


	private:
		unsigned int product_id=0;
		map < unsigned int, Product > products;

	};


}
