#include "../clean/BasicTutorial6.h"
#include "Testing.h"

int main(int argc, char* argv[])
{
	bool success = true;

	std::cout << "#################################################" << std::endl;
	std::cout << "##               AABSEngine Tests              ##" << std::endl;
	std::cout << "#################################################" << std::endl;
	std::cout << std::endl;

	/* automatically verifiable tests */
	success = success && Vector3Test::dotest();
	success = success && Point3Test::dotest();
	success = success && GameObjectTest::doTest();
	
	/* not automatically verifiable tests ??? */
	//success = success && InputTest::dotest();

	/* output overall pass/fail message */
	int colour = success ? FGGREEN_BGBLACK : FGRED_BGBLACK;
	print_coloured("#################################################", colour);
	std::cout << std::endl;
	print_coloured("##            AABSEngine Tests ", colour);
	print_coloured(success ? "Passed" : "Failed", colour);
	print_coloured("          ##", colour);
	std::cout << std::endl;
	print_coloured("#################################################", colour);
	std::cout << std::endl;

	char ch;
	std::cin >> ch;
}