#include "Testing.h"
#include "../clean/Vector3.h"

namespace Vector3Test
{
	bool test1()
	{
		AABSEngine::Core::Vector3 test;
		bool success = (test.X() == 0 && test.Y() == 0 && test.Z() == 0);
		std::cout << "Test 1: Default Constructor" << std::endl;
		std::cout << "\tX: " << test.X() << " Y: " << test.Y() << " Z: " << test.Z() << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test2()
	{
		AABSEngine::Core::Vector3 test(5, 6, 7);
		bool success = (test.X() == 5 && test.Y() == 6 && test.Z() == 7);
		std::cout << "Test 2: Parameterised Constructor" << std::endl;
		std::cout << "\tX: " << test.X() << " Y: " << test.Y() << " Z: " << test.Z() << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test3()
	{
		bool success = true;
		std::cout << "Test 3: Destructor" << std::endl;
		std::cout << "\tTODO if required" << std::endl;
		// ~~~ TODO destructor test if requied		
		return success;
	}

	bool test4()
	{
		AABSEngine::Core::Vector3 test(-1, 0, 0);
		bool success = (test.X() == -1);
		std::cout << "Test 4: X() Accessor" << std::endl;
		std::cout << "\tX: " << test.X() << std::endl;
		print_individual_success(success);
		return success;
	}
	bool test5()
	{
		AABSEngine::Core::Vector3 test(0, -1, 0);
		bool success = (test.Y() == -1);
		std::cout << "Test 5: Y() Accessor" << std::endl;
		std::cout << "\tY: " << test.Y() << std::endl;
		print_individual_success(success);
		return success;
	}
	bool test6()
	{
		AABSEngine::Core::Vector3 test(0, 0, -1);
		bool success = (test.Z() == -1);
		std::cout << "Test 6: Z() Accessor" << std::endl;
		std::cout << "\tZ: " << test.Z() << std::endl;
		print_individual_success(success);
		return success;
	}
	bool test7() 
	{ 
		AABSEngine::Core::Vector3 test(1,2,3);
		Ogre::Vector3 otest = test.get();
		bool success = (otest[0] == 1 && otest[1] == 2 && otest[2] == 3);
		std::cout << "Test 7 get() Accessor" << std::endl;
		std::cout << "\tOgre vector X: " << otest[0] << " Y: " << otest[1] << " Z: " << otest[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test8() 
	{ 
		// [] including bounds
		AABSEngine::Core::Vector3 test(0,1,2);
		bool success = (test[0] == 0 && test[1] == 1 && test[2] == 2);
		std::cout << "Test 8: [] operator" << std::endl;
		std::cout << "\t[0]: " << test[0] << " [1]: " << test[1] << " [2]: " << test[2] << std::endl;		
		// ~~~ TODO test out of bounds - consider pros and cons of exceptions ???
		print_individual_success(success);
		return success;
	}

	bool test9() 
	{ 
		// const [] including bounds
		AABSEngine::Core::Vector3 test(0,1,2);
		bool success = (test[0] == 0 && test[1] == 1 && test[2] == 2);
		std::cout << "Test 9: [] operator" << std::endl;
		std::cout << "\t[0]: " << test[0] << " [1]: " << test[1] << " [2]: " << test[2] << std::endl;
		// ~~~ TODO test out of bounds - consider pros and cons of exceptions ???
		print_individual_success(success);
		return success;
	}

	bool test10() 
	{ 
		AABSEngine::Core::Vector3 test(0,1,2);
		AABSEngine::Core::Vector3 test2;
		test2 = test;
		bool success = (test[0] == test2[0] && test[1] == test2[1] && test[2] == test2[2]);
		std::cout << "Test 10: Assignment operator" << std::endl;
		std::cout << "\tv1[0]: " << test[0] << " t2[0]: " << test2[0] << std::endl;
		std::cout << "\tv1[1]: " << test[1] << " t2[1]: " << test2[1] << std::endl;
		std::cout << "\tv1[2]: " << test[2] << " t2[2]: " << test2[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test11() 
	{ 
		AABSEngine::Core::Vector3 test(0,1,2);
		AABSEngine::Core::Vector3 test2(0,1,2);
		bool success = test == test2;
		std::cout << "Test 11: Equality operator" << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test12() 
	{ 
		AABSEngine::Core::Vector3 test(0,1,2);
		AABSEngine::Core::Vector3 test2(0,1,3);
		bool success = test != test2;
		std::cout << "Test 12: Inequality operator" << std::endl;
		print_individual_success(success);
		return success;
	}
	
	bool test13() 
	{ 
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(1,2,3);
		AABSEngine::Core::Vector3 testresult;
		testresult = test + test2;
		bool success = ((testresult[0] == test[0] + test2[0]) && (testresult[1] == test[1] + test2[1]) &&
			(testresult[2] == test[2] + test2[2]));
		std::cout << "Test 13: Addition operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		std::cout << "\tv3 X: " << testresult[0] << " Y: " << testresult[1] << " Z: " << testresult[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test14() 
	{ 
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(1,2,3);
		AABSEngine::Core::Vector3 testresult;
		testresult = test - test2;
		bool success = ((testresult[0] == test[0] - test2[0]) && (testresult[1] == test[1] - test2[1]) &&
			(testresult[2] == test[2] - test2[2]));
		std::cout << "Test 14: Subtraction operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		std::cout << "\tv3 X: " << testresult[0] << " Y: " << testresult[1] << " Z: " << testresult[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test15() 
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		Decimal testscalar = 2;
		AABSEngine::Core::Vector3 result = test * testscalar;
		bool success = ((result[0] == test[0] * testscalar) && (result[1] == test[1] * testscalar) &&
			(result[2] == test[2] * testscalar));
		std::cout << "Test 15: Scalar multiplication operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tscalar: " << testscalar << std::endl;
		std::cout << "\tv2 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test16() 
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(2,2,2);
		AABSEngine::Core::Vector3 testresult;
		testresult = test * test2;
		bool success = ((testresult[0] == test[0] * test2[0]) && (testresult[1] == test[1] * test2[1]) &&
			(testresult[2] == test[2] * test2[2]));
		std::cout << "Test 16: Vector element multiplication operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		std::cout << "\tv3 X: " << testresult[0] << " Y: " << testresult[1] << " Z: " << testresult[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test17() 
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		Decimal testscalar = 2;
		AABSEngine::Core::Vector3 result = test / testscalar;
		bool success = ((result[0] == test[0] / testscalar) && (result[1] == test[1] / testscalar) &&
			(result[2] == test[2] / testscalar));
		std::cout << "Test 17: Scalar division operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tscalar: " << testscalar << std::endl;
		std::cout << "\tv2 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test18()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(2,2,2);
		AABSEngine::Core::Vector3 testresult;
		testresult = test / test2;
		bool success = ((testresult[0] == test[0] / test2[0]) && (testresult[1] == test[1] / test2[1]) &&
			(testresult[2] == test[2] / test2[2]));
		std::cout << "Test 18: Vector element division operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		std::cout << "\tv3 X: " << testresult[0] << " Y: " << testresult[1] << " Z: " << testresult[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test19() 
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(2,3,4);
		AABSEngine::Core::Vector3 result = test2;
		//result = test2;
		std::cout << "Test 19: Vector element addition equals operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		result += test;
		std::cout << "\tv3 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		bool success = ((result[0] == test[0] + test2[0]) && (result[1] == test[1] + test2[1]) 
			&& (result[2] == test[2] + test2[2]));
		print_individual_success(success);
		return success; 
	}

	bool test20()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		Decimal scalar = 2;
		AABSEngine::Core::Vector3 result = test;
		std::cout << "Test 20: Scalar addition equals operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tscalar: " << scalar << std::endl;
		result += scalar;
		std::cout << "\tv2 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		bool success = ((result[0] == test[0] + scalar) && (result[1] == test[1] + scalar) 
			&& (result[2] == test[2] + scalar));
		print_individual_success(success);
		return success; 
	}

	bool test21() 
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(2,3,4);
		AABSEngine::Core::Vector3 result = test2;
		std::cout << "Test 21: Vector element minus equals operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		result -= test;
		std::cout << "\tv3 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		bool success = ((result[0] == test2[0] - test[0]) && (result[1] == test2[1] - test[1]) 
			&& (result[2] == test2[2] - test[2]));
		print_individual_success(success);
		return success; 
	}

	bool test22()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		Decimal scalar = 2;
		AABSEngine::Core::Vector3 result = test;
		std::cout << "Test 22: Scalar minus equals operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tscalar: " << scalar << std::endl;
		result -= scalar;
		std::cout << "\tv2 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		bool success = ((result[0] == test[0] - scalar) && (result[1] == test[1] - scalar) 
			&& (result[2] == test[2] - scalar));
		print_individual_success(success);
		return success; 
	}

	bool test23()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		Decimal scalar = 2;
		AABSEngine::Core::Vector3 result = test;
		std::cout << "Test 23: Scalar times equals operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tscalar: " << scalar << std::endl;
		result *= scalar;
		std::cout << "\tv3 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		bool success = ((result[0] == test[0] * scalar) && (result[1] == test[1] * scalar) 
			&& (result[2] == test[2] * scalar));
		print_individual_success(success);
		return success; 
	}

	bool test24() 
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(2,3,4);
		AABSEngine::Core::Vector3 result = test2;
		std::cout << "Test 24: Vector element times equals operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		result *= test;
		std::cout << "\tv3 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		bool success = ((result[0] == test[0] * test2[0]) && (result[1] == test[1] * test2[1]) 
			&& (result[2] == test[2] * test2[2]));
		print_individual_success(success);
		return success; 
	}

	bool test25()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		Decimal scalar = 2;
		AABSEngine::Core::Vector3 result = test;
		std::cout << "Test 25: Scalar divide equals operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tscalar: " << scalar << std::endl;
		result /= scalar;
		std::cout << "\tv3 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		bool success = ((result[0] == test[0] / scalar) && (result[1] == test[1] / scalar) 
			&& (result[2] == test[2] / scalar));
		print_individual_success(success);
		return success; 
	}

	bool test26()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(2,4,6);
		AABSEngine::Core::Vector3 result = test2;
		std::cout << "Test 26: Vector element divide equals operator" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		result /= test;
		std::cout << "\tv3 X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		bool success = ((result[0] == test2[0] / test[0]) && (result[1] == test2[1] / test[1]) 
			&& (result[2] == test2[2] / test[2]));
		print_individual_success(success);
		return success; 
	}

	bool test27() 
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		Decimal mag = test.magnitude();
		Decimal calcmag = sqrt((test[0] * test[0]) + (test[1] * test[1]) + (test[2] * test[2]));
		bool success = mag == calcmag;
		std::cout << "Teset 27: Vector magnitude" << std::endl;
		std::cout << "\tX: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tMagnitude: " << mag << std::endl;
		print_individual_success(success);
		return success; 
	} 

	bool test28()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		Decimal mag = test.squaredMagnitude();
		Decimal calcmag = (test[0] * test[0]) + (test[1] * test[1]) + (test[2] * test[2]);
		bool success = mag == calcmag;
		std::cout << "Test 28: Vector squared magnitude" << std::endl;
		std::cout << "\tX: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tMagnitude: " << mag << std::endl;
		print_individual_success(success);
		return success; 
	} 

	bool test29()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(5,5,5);
		Decimal dist = test.distance(test2);
		Decimal distcalc = sqrt(pow(test[0] - test2[0], 2) + pow(test[1] - test2[1], 2) + pow(test[2] - test2[2], 2));
		bool success = dist == distcalc;
		std::cout << "Test 29: Vector distance" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Z: " << test2[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tDistance: " << dist << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test30()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(5,5,5);
		Decimal dist = test.squaredDistance(test2);
		Decimal distcalc = pow(test[0] - test2[0], 2) + pow(test[1] - test2[1], 2) + pow(test[2] - test2[2], 2);
		bool success = dist == distcalc;
		std::cout << "Test 30: Squared vector distance" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Z: " << test2[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tDistance: " << dist << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test31()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(5,5,5);
		Decimal dist = test.dotProduct(test2);
		Decimal distcalc = (test[0] * test2[0]) + (test[1] * test2[1]) + (test[2] * test2[2]);
		bool success = dist == distcalc;
		std::cout << "Test 31: Dot Product" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Z: " << test2[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tDistance: " << dist << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test32()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(5,5,5);
		Decimal dist = test.absDotProduct(test2);
		Decimal distcalc = (test[0] * test2[0]) + (test[1] * test2[1]) + (test[2] * test2[2]);
		bool success = dist == distcalc;
		std::cout << "Test 32: Absolute Dot Product" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Z: " << test2[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tDistance: " << dist << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test33()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2 = test;
		AABSEngine::Core::Vector3 testcalc = test;
		test2.normalise();
		Decimal length = test.magnitude();
		testcalc[0] = test[0] / length;
		testcalc[1] = test[1] / length;
		testcalc[2] = test[2] / length;
		bool success = ((test2[0] == testcalc[0]) && (test2[1] == testcalc[1]) && (test2[2] == testcalc[2]));
		std::cout << "Test 32: Absolute Dot Product" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tNormal: X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool test34()
	{
		AABSEngine::Core::Vector3 test(1,2,3);
		AABSEngine::Core::Vector3 test2(5,5,5);
		AABSEngine::Core::Vector3 result = test.crossProduct(test2);
		AABSEngine::Core::Vector3 testcalc;	
		testcalc[0] = (test[1] * test2[2]) - (test2[1] * test[2]);
		testcalc[1] = (test[2] * test2[0]) - (test[0] * test2[2]);
		testcalc[2] = (test[0] * test2[1]) - (test2[0] * test[1]);
		bool success = ((result[0] == testcalc[0]) && (result[1] == testcalc[1]) && (result[2] == testcalc[2]));
		std::cout << "Test 34: Cross Product" << std::endl;
		std::cout << "\tv1 X: " << test[0] << " Y: " << test[1] << " Z: " << test[2] << std::endl;
		std::cout << "\tv2 X: " << test2[0] << " Y: " << test2[1] << " Z: " << test2[2] << std::endl;
		std::cout << "\tv3: X: " << result[0] << " Y: " << result[1] << " Z: " << result[2] << std::endl;
		print_individual_success(success);
		return success;
	}

	bool dotest()
	{		
		bool success = true;
		std::cout << "#################################################" << std::endl;
		std::cout << "##                Vector3 Tests                ##" << std::endl;
		std::cout << "#################################################" << std::endl;
		std::cout << std::endl;
		
		//////////////////////////////////////////////////////////////////////////////
		// default constructor test
		success = success && test1();
		//////////////////////////////////////////////////////////////////////////////
		// Parameterised constructor
		success = success && test2();
		//////////////////////////////////////////////////////////////////////////////
		// Destructor // ???
		success = success && test3();
		//////////////////////////////////////////////////////////////////////////////
		// X Y Z accessors 
		success = success && test4();
		success = success && test5();
		success = success && test6();		
		//////////////////////////////////////////////////////////////////////////////
		// get accessor 
		success = success && test7();
		//////////////////////////////////////////////////////////////////////////////
		// [] operator including bounds 
		success = success && test8();
		//////////////////////////////////////////////////////////////////////////////
		// const [] operator including bounds 
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
		// addition 
		success = success && test13();
		//////////////////////////////////////////////////////////////////////////////
		// subtraction 
		success = success && test14();
		//////////////////////////////////////////////////////////////////////////////
		// scalar multiplication 
		success = success && test15();
		//////////////////////////////////////////////////////////////////////////////
		// vector element multiplication 
		success = success && test16();
		//////////////////////////////////////////////////////////////////////////////
		// scalar division 
		success = success && test17();
		//////////////////////////////////////////////////////////////////////////////
		// vector element division 
		success = success && test18();
		//////////////////////////////////////////////////////////////////////////////
		// vector plusequals 
		success = success && test19();
		//////////////////////////////////////////////////////////////////////////////
		// scalar plusequals 
		success = success && test20();
		//////////////////////////////////////////////////////////////////////////////
		// vector minusequals 
		success = success && test21();
		//////////////////////////////////////////////////////////////////////////////
		// scalar minusequals 
		success = success && test22();
		//////////////////////////////////////////////////////////////////////////////
		// scalar timesequals 
		success = success && test23();
		//////////////////////////////////////////////////////////////////////////////
		// vector element multiplication equals 
		success = success && test24();
		//////////////////////////////////////////////////////////////////////////////
		// scalar division equals 
		success = success && test25();
		//////////////////////////////////////////////////////////////////////////////
		// vector element division equals 
		success = success && test26();
		//////////////////////////////////////////////////////////////////////////////
		// magnitude 
		success = success && test27();
		//////////////////////////////////////////////////////////////////////////////
		// squared magnitude 
		success = success && test28();
		//////////////////////////////////////////////////////////////////////////////
		// distance 
		success = success && test29();
		//////////////////////////////////////////////////////////////////////////////
		// squared distance 
		success = success && test30();
		//////////////////////////////////////////////////////////////////////////////
		// dotproduct 
		success = success && test31();
		//////////////////////////////////////////////////////////////////////////////
		// absolute dot product 
		success = success && test32();
		//////////////////////////////////////////////////////////////////////////////
		// normalise
		success = success && test33();
		//////////////////////////////////////////////////////////////////////////////
		// cross product 
		success = success && test34();
		
		return success;
	}
}
