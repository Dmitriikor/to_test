#include "Ray_template.h"
#include <fstream>
#include <format>
#include <thread>
#include <Windows.h>
#include <mutex>
#include <future>
#include "windows.h" 
#include "Matrix.h"

int ctr = 0;
int ctr_ds = 0;


void threadFunction(Matrix<char> &a, bool &is_thread_complite_task)
{
	ctr++;
	int loc_ctr = ctr;
	std::cout << "\n\n\nentered thread "<< loc_ctr <<"  " << std::this_thread::get_id() << std::endl;
	for (size_t i = 0; i < a.get_N(); i++)
	{
		for (size_t j = 0; j < a.get_M(); j++)
			if (a[i][j] == 't') {
				std::cout << "\n\t t- found at:" << i << ", " << j << "\n";
				
			}
	}
	std::cout << "\nleaving thread " << loc_ctr << "  " << std::this_thread::get_id() << std::endl;
	a.resize(1, 1);
	is_thread_complite_task = true;
};


void do_something_1() {

	std::cout << "\n\t\t\t\t\t\t\t\t\t do_something_1" << "\n";
}



void do_something(bool &a) {
	while (a == false)
	{
		ctr_ds++;
		Sleep(1000);

		std::cout << "\n\t\t\t\t\t\t\t\t\t" << ctr_ds << "\n";
		
	}
}

int main()
{
	
		std::thread test;
		{
			std::cout << "before starting, joinable: " << test.joinable() << '\n';

			test = std::thread{ do_something_1 };
			std::cout << "after starting, joinable: " << test.joinable() << '\n';

			if (test.joinable())
			{
				test.join();
			}

			std::cout << "after joining, joinable: " << test.joinable() << '\n';
		
			bool a = false;
		
			auto test_async = std::async(std::launch::async, do_something, std::ref(a));


			std::cout << "after detaching, joinable: " << test.joinable() << '\n';

			Sleep(10000);
			a = true;

			test_async._Is_ready_at_thread_exit();
		}
		///return 33;

		std::cout << "\n" << std::thread::hardware_concurrency() << "\n";
		std::cout << "\nMain thread " << std::this_thread::get_id() << std::endl;


		///::ios_base::sync_with_stdio(false);
		///std::cin.tie(NULL);

		Ray_template <char> adress = { 'c', 'o', 'r','n','e','r','_','p','a','t','h','_','o','u','t','.','t','x','t' };
		Ray_template <char> outfile_adress;
		outfile_adress = adress;

		print(outfile_adress);

		double t1 = clock();
		std::cout << "\n\t" << 4 % 2 << "   < 4 % 2  ||| 4 / 2 >   " << 4 / 2 << " ||| " << 5 % 2 << "   < 5 % 2 ||| 5 / 2 >   " << 5 / 2 << "\n";

		Matrix<char> one(1, 1500000000);
		one.fill('o');
		one.set_at(0, 1499999997, 't');

		bool timer_1 = false;
		bool is_free = true;
		std::thread thr;
		do {
			if (is_free == true)
			{
				std::lock_guard<std::mutex> lock(std::mutex);
				thr = std::move(std::thread{ threadFunction, std::ref(one), std::ref(timer_1) }); 
				///thr.detach();
				std::cout << "\n T \n";
				break;
			}
		} while (is_free == false);

		///Sleep(1);
		///::cout << "\n\t" << one.get_N() << " || " << one.get_M() << "\n";


		Matrix<char> one_2(1, 1500000000);
		one_2.set_at(0, 1499999997, 't');

		is_free = true;
		bool timer_2 = false;
		std::thread thr_2;
		do {
			if (is_free == true)
			{
				std::lock_guard<std::mutex> lock(std::mutex);
				///std::thread thr_2(threadFunction, std::ref(one_2), std::ref(timer_2));
				thr_2 = std::move(std::thread{ threadFunction, std::ref(one_2), std::ref(timer_2) }); 
				///
				std::cout << "\n T \n";
				break;
			}
		} while (is_free == false);

		///std::cout << "\n\t" << one_2.get_N() << " || " << one_2.get_M() << "\n";
		///one.print();


		Matrix<char> one_3(1, 15);
		one_3.resize(1, 1500000000);
		one_3.set_at(0, 1499999997, 't');

		is_free = true;
		bool timer_3 = false;
		std::thread thr_3;
		std::cout << "\nis_free = " << is_free << "\n";
		do {
			if (is_free == true)
			{
				std::lock_guard<std::mutex> lock(std::mutex);
				thr_3 = std::thread(threadFunction, std::ref(one_3), std::ref(timer_3));
				thr_3.detach();
				std::cout << "\n T \n";
				break;
			}
		} while (is_free == false);

		///std::cout << "\n\t" << one_3.get_N() << " || " << one_3.get_M() << "\n";
		///one.print();
		///int t2 = clock();
		///double tr = double(t2 - t1) / CLOCKS_PER_SEC;
		///std::cout << "timer = \t" << double(t2 - t1) / CLOCKS_PER_SEC << std::endl;

		double timer;
		double t3 = 0;

		std::cout << std::endl;
		while (true) {

			if (timer_1 != false && timer_2 != false && timer_3 != false)
			{
				std::cout << std::endl;

				double t2 = clock();
				Sleep(10);
				std::cout << "\t\n" << timer_1 << " " << timer_2 << " " << timer_3 << "\n";
				std::cout << "timer = \t" << double(t2 - t1) / CLOCKS_PER_SEC << std::endl;
				timer = t2 - t1;
				break;
			}
			else {
				if (t3 == 0)
				{
					t3 = clock();

					std::cout << t3 / CLOCKS_PER_SEC << std::endl;
				}
				Sleep(10);
			}
		}
		double t4 = clock();
		std::cout << t4 / CLOCKS_PER_SEC << std::endl;
		std::cout << " waiting timer = \t" << double(t4 - t3) / CLOCKS_PER_SEC << std::endl;

		Sleep(10000);
		std::cout << "\033c" << "\t\n" << timer / CLOCKS_PER_SEC;
		std::cout << std::endl;

		thr_2.detach();
		thr.join();

	return 0;
};
