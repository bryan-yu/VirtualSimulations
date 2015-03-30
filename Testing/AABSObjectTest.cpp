#include "Testing.h"

#include "../clean/Object.h"

namespace GameObjectTest
{
	bool doTest()
	{
		bool success = true;

		std::cout << "#################################################" << std::endl;
		std::cout << "##                 Object Test                 ##" << std::endl;
		std::cout << "#################################################" << std::endl;
		std::cout << std::endl;

		std::cout << "Creating an object" << std::endl;
		AABSEngine::Core::GameObject go1;
		success = (go1.GetName() == "1");
		std::cout << "object id: " << go1.GetName() << std::endl;
		print_individual_success(success);

		return success;
	}
}