#pragma once
#include <map>
#include <string>
#include <ctime>
#include <iosfwd>
#include <locale>
#include <utility>
#include <fstream>
#include <vector>
namespace PM {
	using std::map;
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
		const std::string getName() const { return name; }
		const double getPrice() const { return price; }
		const unsigned int getQty() const { return qty; }
		const std::tm getDate() const { return registered_date; }

		unsigned int id;
		string name;
		double price;
		unsigned int qty;
		tm registered_date;
	};
	std::ofstream& operator<<(std::ofstream& out, const Product& p);
	std::ostream& operator<< (std::ostream& os, const Product& p);

	struct NoProduct : public Product { NoProduct() {} };
	const NoProduct no_product{};

	bool operator== (const Product& p, const NoProduct&);
	

	class ProductManager
	{
	public:
		bool addProduct(const string name, double price, unsigned int qty, std::tm local_time);
		bool eraseProduct(const unsigned int id);
		const Product& findProduct(const unsigned int id) const;
		const map< unsigned int, Product >& getProducts() const;
		const Product& getProduct(const unsigned int) const;
		ofstream& saveProducts(ofstream&) const;
		std::pair<std::ifstream&, std::vector<Product>> loadProducts(ifstream&);
		const unsigned int getMaxIndex() const;
	private:
		static unsigned int product_id;
		map < unsigned int, Product > products;
	};


}
