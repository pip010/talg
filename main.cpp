



#include <iostream>
#include <cassert>





using namespace std;


////////////////////////////////////////////////////////







int main()
{
	using namespace talg;
	
	//exercise : http://en.cppreference.com/w/cpp/language/aggregate_initialization
	


	
	vec4_UND = vec4;
	
	vec4 = vec4 + vec4;
	
	std::cout << vec4 << std::endl;
	
	vec4 *= 0.5;
	
	std::cout << vec4 << std::endl;

	
	
	



	TMatrix<4,4,double> mat1{};
	mat1.map[0][0] = 1.0;
	mat1.map[1][1] = 1.0;
	mat1.map[2][2] = 1.0;
	mat1(3,3) = 1.0;


	//UGLYYYYY
	//but there is hope, see c++17
	//http://en.cppreference.com/w/cpp/language/aggregate_initialization
	TMatrix<4, 4, double> mat2={{
		{ 1.1,2.2,3.3,4.4 },
		{ 1.1,2.2,3.3,4.4 },
		{ 1.1,2.2,3.3,4.4 },
		{ 1.1,2.2,3.3,4.4 }
	}};
	
	
	TMatrix<2, 3, double> mat222 = {
		{1.1,2.2,3.3,
		 1.1,2.2,3.3 }
	};
	
	

	//auto aaaaaa = mat222 * mat222; // NO COMPILE :)
	
	std::cout << mat2 << std::endl;
	std::cout << mat2[1][1] << std::endl;
	std::cout << mat2(0,0) << std::endl;
	std::cout << mat2.data[3] << std::endl;
	
	TMatrix<5,5,double> mat3{};

	//std::array<std::array<double, 4>, 4> m{ {
	//	{ 1.1,2.2,3.3,4.4 },
	//	{ 1.1,2.2,3.3,4.4 },
	//	{ 1.1,2.2,3.3,4.4 },
	//	{ 1.1,2.2,3.3,4.4 }
	//} };
	
	PrintTypeTraits< TMatrix<5,5,double> >();

	auto vec44 = mat1 * vec4;
	std::cout << vec44<< std::endl;
	
	auto mat44 = mat2 * mat1;
	std::cout << mat44<< std::endl;
	
	auto mat55 = mat3 * mat3;
	std::cout << mat55<< std::endl;
	

    return 0;
}


