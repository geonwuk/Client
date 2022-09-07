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
		unsigned int id;		//제품 id
		string name;			//제품 이름
		unsigned int price;		//제품 가격
		unsigned int qty;		//제품 재고량
		tm registered_date;		//제품 등록 날짜

	};
	ofstream& operator<<(ofstream& out, const Product& p);

	struct NoProduct : public Product { NoProduct() {} };		//findProduct(id)에서 만약 id에 해당하는 고객이 없다면 리턴할 클래스
	const NoProduct no_product{};								//NoProduct 객체
	bool operator== (const Product& p, const NoProduct&);		//findProduct(id)에서 받은 객체를 no_product와 비교하여 사용할 수 있게 연산자 오버로딩
	

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
