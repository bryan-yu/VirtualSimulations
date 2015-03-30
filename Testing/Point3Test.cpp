#include "Testing.h"
#include "../clean/Point3.h"

namespace Point3Test
{
	bool test1()
	{ 
		AABSEngine::Core::Point3 test;
		bool success = test[0] == 0 && test[1] == 0 && test[2] == 0;
		std::cout << "Test 1: Default Constructor" << std::endl;
		std::cout << "\tX: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test2()
	{ 
		AABSEngine::Core::Point3 test(1,2,3);
		bool success = test[0] == 1 && test[1] == 2 && test[2] == 3;
		std::cout << "Test 2: Parameterised Constructor" << std::endl;
		std::cout << "\tX: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test3()
	{ 
		AABSEngine::Core::Point3 test(1,2,3);
		AABSEngine::Core::Point3 test2 = test;
		bool success = test[0] == test2[0] && test[1] == test2[1] && test[2] == test2[2];
		std::cout << "Test 3: Copy Constructor" << std::endl;
		std::cout << "\tp1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tp2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test4() 
	{ 
		bool success = true;		
		std::cout << "Test 4: Destructor" << std::endl;
		std::cout << "\tTODO if required" << std::endl;
		return success; 
	}

	bool test5() 
	{ 
		AABSEngine::Core::Point3 test;
		bool success = test.X() == 0;
		std::cout << "Test 5: X Accessor" << std::endl;
		std::cout << "\tX: " << test.Z() << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test6() 
	{ 
		AABSEngine::Core::Point3 test;
		bool success = test.Y() == 0;
		std::cout << "Test 6: Y Accessor" << std::endl;
		std::cout << "\tY: " << test.Y() << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test7() 
	{ 
		AABSEngine::Core::Point3 test;
		bool success = test.Z() == 0;
		std::cout << "Test 7: Z Accessor" << std::endl;
		std::cout << "\tZ: " << test.Z() << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test8() 
	{ 
		AABSEngine::Core::Point3 test(1,2,3);
		Ogre::Vector3 otest = test.get();
		bool success = (otest[0] == 1 && otest[1] == 2 && otest[2] == 3);
		std::cout << "Test 8: get() Accessor" << std::endl;
		std::cout << "\tOgre vector X: " << otest[0] << " Y: " << otest[1] << " Z: " << otest[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test9() 
	{
		AABSEngine::Core::Point3 test(1,2,3);
		bool success = (test[0] == 1) && (test[1] == 2) && (test[2] == 3); 
		std::cout << "Test 9: [] operator" << std::endl;
		std::cout << "\tX: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		print_individual_success(success);
		return success;
	} 

	bool test10()
	{ 
		AABSEngine::Core::Point3 test(1,2,3);
		AABSEngine::Core::Point3 test1 = test;
		bool success = (test[0] == test1[0]) && (test[1] == test1[1]) && (test[2] == test1[2]);
		std::cout << "Test 10: Assignment operator" << std::endl;
		std::cout << "\tX: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		print_individual_success(success);
		return success; 
	} 

	bool test11()
	{ 
		AABSEngine::Core::Point3 test(1,2,3);
		AABSEngine::Core::Point3 test2(1,2,3);
		bool success = test == test2;
		std::cout << "Test 11: Equality operator" << std::endl;
		print_individual_success(success);
		return success;
	} 

	bool test12() 
	{ 
		AABSEngine::Core::Point3 test(1,2,3);
		AABSEngine::Core::Point3 test2(1,2,4);
		bool success = test != test2;
		std::cout << "Test 11: Inequality operator" << std::endl;
		print_individual_success(success);
		return success;
	} 

	bool test13() 
	{ 
		AABSEngine::Core::Point3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(1,2,3);
		AABSEngine::Core::Point3 result = test + test2;
		bool success = (result[0] == (test[0] + test2[0])) && (result[1] == (test[1] + test2[1]))
			&& (result[2] == (test[2] + test2[2]));
		std::cout << "Test 12: Addition operator" << std::endl;
		std::cout << "\tp1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tp2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		std::cout << "\tp3 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		print_individual_success(success);
		return true; 
	} 

	bool test14() 
	{ 
		AABSEngine::Core::Point3 test(1,2,3);
		AABSEngine::Core::Point3 test2(5,1,3);
		AABSEngine::Core::Vector3 result = test - test2;
		bool success = (result[0] == (test[0] - test2[0])) && (result[1] == (test[1] - test2[1]))
			&& (result[2] == (test[2] - test2[2]));
		std::cout << "Test 12: Subtraction operator" << std::endl;
		std::cout << "\tp1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tp2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		std::cout << "\tp3 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		print_individual_success(success);
		return true; 
	} 

	bool dotest()
	{
		bool success = true;
		std::cout << "#################################################" << std::endl;
		std::cout << "##                 Point3 Tests                ##" << std::endl;
		std::cout << "#################################################" << std::endl;
		std::cout << std::endl;

		//////////////////////////////////////////////////////////////////////////////
		// constructor
		success = success && test1();
		//////////////////////////////////////////////////////////////////////////////
 		// parameterised constructor
		success = success && test2();
		//////////////////////////////////////////////////////////////////////////////
		// copy constructor
		success = success && test3();
		//////////////////////////////////////////////////////////////////////////////
		// desctructor
		success = success && test4();
		//////////////////////////////////////////////////////////////////////////////
		// X accessor
		success = success && test5();
		//////////////////////////////////////////////////////////////////////////////
		// Y accessor
		success = success && test6();
		//////////////////////////////////////////////////////////////////////////////
		// z ACCESSOR
		success = success && test7();
		//////////////////////////////////////////////////////////////////////////////
		// get accesspr
		success = success && test8();
		//////////////////////////////////////////////////////////////////////////////
		// [] accessor
		success = success && test9();
		//////////////////////////////////////////////////////////////////////////////
		// assignment operator
		success = success && test10();
		//////////////////////////////////////////////////////////////////////////////
		// equality operator
		success = success && test11();
		//////////////////////////////////////////////////////////////////////////////
		// inequality operator
		success = success && test12();
		//////////////////////////////////////////////////////////////////////////////
		// addition operator
		success = success && test13();
		//////////////////////////////////////////////////////////////////////////////
		// subtraction operator
		success = success && test14();

		return success;
	}
}