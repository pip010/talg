#include "helpers.h"

void test_func_print_c(const double* array, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << array[i] << " ";
	}

	std::cout << std::endl;
}

void test_func_modify_c(double* array, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		array[i] = (double)i;
	}
}