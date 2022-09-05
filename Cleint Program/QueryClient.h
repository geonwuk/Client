#pragma once
#include "ClientManager.h"
#include <array>
class QueryClient
{
public:
	QueryClient(ClientManager& cm);

	void QueryAddClient();
	void QueryEraseClient();
	void QueryShowClient();

private:
	ClientManager& cm;
	static std::array<unsigned int, 4> fields;
	using FIELD = decltype(fields);
	using CONTENT = std::array<std::string, 4>;
	void print(CONTENT content, char start, char pad);
};

