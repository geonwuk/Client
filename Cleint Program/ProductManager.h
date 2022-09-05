#pragma once
#include <map>
#include <string>
#include <string>
#include <ctime>
#include <iosfwd>

using std::map;
using std::string;
namespace PM {
	using std::string;
	using std::ofstream;
	using std::ostream;
	using std::ifstream;
	class Product
	{
		friend class ProductManager;
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
	std::ofstream& operator<<(std::ofstream& out, const Product& p);
	std::ostream& operator<< (std::ostream& os, const Product& p);

	//ofstream& operator<< (ofstream&, const Product&);

	struct NoProduct : public Product { NoProduct() {} };
	const NoProduct no_product{};

	bool operator== (const Product& p, const NoProduct&);
	

	class ProductManager
	{
	public:
		bool addProduct(const string name, double price, unsigned int qty);
		bool eraseProduct(const unsigned int id);
		const Product& findProduct(const unsigned int id) const;
		const map< unsigned int, Product >& getProducts() const;
		ofstream& saveProducts(ofstream&) const;
		ifstream& loadProducts(ifstream&);
	private:
		static unsigned int product_id;
		map < unsigned int, Product > products;
	};


}
