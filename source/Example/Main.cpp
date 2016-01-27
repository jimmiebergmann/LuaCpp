#include <iostream>

#include <LuaCpp/LuaCpp.hpp>

int main()
{

	Lua::State state;

	state.OpenStandardLibs();



	auto ret = state.ExecuteString("print(\"Test\");");

	if (std::get<0>(ret) == false)
	{
		std::cout << "Script error: " << std::get<1>(ret) << std::endl;
	}



	std::cin.get();
	return 0;
}