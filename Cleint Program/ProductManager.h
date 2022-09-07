#pragma once
#include <map>
#include <string>
#include <ctime>
#include <iosfwd>
#include <utility>
#include <fstream>
#include <vector>
namespace PM {
	using std::map;
	using std::string;
	using std::ofstream;
	using std::ifstream;

	class Product{
	public:
		Product(unsigned int id, string name, unsigned int price, unsigned int qty, std::tm date) :
			id{ id }, name{ name }, price{ price }, qty{ qty }, registered_date{ date }{}

		const unsigned int getId() const { return id; }
		const string getName() const { return name; }
		const unsigned int getPrice() const { return price; }
		const unsigned int getQty() const { return qty; }
		const std::tm getDate() const { return registered_date; }
	protected:
		Product() = default;
	private:
		unsigned int id;		//��ǰ id
		string name;			//��ǰ �̸�
		unsigned int price;		//��ǰ ����
		unsigned int qty;		//��ǰ ���
		tm registered_date;		//��ǰ ��� ��¥

	};
	ofstream& operator<<(ofstream& out, const Product& p);

	struct NoProduct : public Product { NoProduct() {} };		//findProduct(id)���� ���� id�� �ش��ϴ� ���� ���ٸ� ������ Ŭ����
	const NoProduct no_product{};								//NoProduct ��ü
	bool operator== (const Product& p, const NoProduct&);		//findProduct(id)���� ���� ��ü�� no_product�� ���Ͽ� ����� �� �ְ� ������ �����ε�
	

	class ProductManager
	{
	public:
		bool addProduct(const string name, const unsigned int price, const unsigned int qty, const std::tm local_time);
		bool eraseProduct(const unsigned int id);
		const Product& findProduct(const unsigned int id) const;
		const map< unsigned int, Product >& getProducts() const;
		const Product& getProduct(const unsigned int) const;
		ofstream& saveProducts(ofstream&) const;
		std::pair<ifstream&, std::vector<Product>> loadProducts(ifstream&);
		const unsigned int getMaxIndex() const;
	private:
		static unsigned int product_id;
		map < unsigned int, Product > products;
	};


}
