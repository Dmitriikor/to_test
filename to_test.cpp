#include "Ray_template.h"
#include <fstream>
#include <format>
#include "Matrix.h"

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	Ray_template <char> adress = { 'c', 'o', 'r','n','e','r','_','p','a','t','h','_','o','u','t','.','t','x','t'};
	Ray_template <char> outfile_adress;
		outfile_adress = adress;

	print(outfile_adress);

	int t1 = clock();
		std::cout << "\n\t" << 4 % 2 << "   < 4 % 2  ||| 4 / 2 >   " << 4 / 2 << " ||| " << 5 % 2 << "   < 5 % 2 ||| 5 / 2 >   " << 5 / 2;

		Matrix<char> one(1,15);
		one.fill('o');
		std::cout << "\n\t" << one.get_N() << " || " << one.get_M() << "\n";
		one.print();

		one.resize(2, 25);
		for (int i = 0; i < 25; i++)
		one[1][i] = 'E';
		//one.fill('d');
		std::cout << "\n\t" << one.get_N() << " || " << one.get_M() << "\n";
		one.print();

		one.resize(1, 5);
		std::cout << "\n\t" << one.get_N() << " || " << one.get_M() << "\n";
		one.print();

		int t2 = clock();

		//double tr = double(t2 - t1) / CLOCKS_PER_SEC;
		std::cout << "timer = \t" << double(t2 - t1) / CLOCKS_PER_SEC << std::endl;

	return 0;
};
