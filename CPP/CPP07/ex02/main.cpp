#include "Array.hpp"
#include "colors.h"

int main()
{
    std::cout << "EMPTY STR TEST"<< std::endl;
	std::cout << "***************"<< std::endl;
	Array<char> str3;

	std::cout << "EMPTY INT TEST"<< std::endl;
	std::cout << "***************"<< std::endl;
	Array<int> tab3;


	std::cout << "CHAR STR TEST"<< std::endl;
	std::cout << "***************"<< std::endl;
	Array<char> str(17);
	str[0] = 'B';
	str[1] = 'o';
	str[2] = 'n';
	str[3] = 'j';
	str[4] = 'o';
	str[5] = 'u';
	str[6] = 'r';
	Array<char> str2(str);
	std::cout << "Str = " << str << std::endl;
	std::cout <<"Str2 = " << str2 << std::endl;
	str[0] = 'S';
	str[1] = 'a';
	str[2] = 'l';
	str[3] = 'u';
	str[4] = 't';
	str[5] = 0;
	str[6] = 0;
	std::cout << "Changement de STR par = : " << str << std::endl;
	std::cout << "Str = " << str << std::endl;
	std::cout <<"Str2 = " << str2 << std::endl;

	str2 = str;
	std::cout << "Assignation de STR2 par STR"<< std::endl;
	std::cout << "Str = " << str << std::endl;
	std::cout <<"Str2 = " << str2 << std::endl;


	try
	{
		std::cout << "Tentative d'acceder a un element avec index invalide"<< std::endl;
		std::cout << str[18] << std::endl;
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "INT ARRAY TEST"<< std::endl;
	std::cout << "***************"<< std::endl;
	Array<int> numbers(6);
	int* mirror = new int[6];
	srand(time(NULL));
	std::cout << "Numbers value"<< std::endl;
	std::cout << "***************"<< std::endl;
    for (int i = 0; i < 6; i++)
    {
        const int value = rand();
        numbers[i] = value;
		mirror[i] = numbers[i];
		std::cout << numbers[i] << std::endl;
	}
	std::cout << "Mirror value"<< std::endl;
	std::cout << "***************"<< std::endl;
	for (int i = 0; i < 6; i++)
    {
		std::cout << mirror[i] << std::endl;
	}
	try
    {
        numbers[-42] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
	delete [] mirror;
	return 0;
}

// #define MAX_VAL 750
// int main(int, char**)
// {
//     Array<int> numbers(MAX_VAL);
//     int* mirror = new int[MAX_VAL];
//     srand(time(NULL));
//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         const int value = rand();
//         numbers[i] = value;
//         mirror[i] = value;
//     }
//     //SCOPE
//     {
//         Array<int> tmp = numbers;
//         Array<int> test(tmp);
//     }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         if (mirror[i] != numbers[i])
//         {
//             std::cerr << "didn't save the same value!!" << std::endl;
//             return 1;
//         }
//     }
//     try
//     {
//         numbers[-2] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
//     try
//     {
//         numbers[MAX_VAL] = 0;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     for (int i = 0; i < MAX_VAL; i++)
//     {
//         numbers[i] = rand();
//     }
//     delete [] mirror;//
//     return 0;
// }
