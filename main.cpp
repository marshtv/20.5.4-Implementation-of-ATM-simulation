#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>

int banknote_random() {
	switch (std::rand() % 6) {
		case 0:
			return 100;
		case 1:
			return 200;
		case 2:
			return 500;
		case 3:
			return 1000;
		case 4:
			return 2000;
		case 5:
			return 5000;
	}
}

int banknote_nominal_count(int atm_array[], int nominal) {
	int nominal_count = 0;
	for (int i = 0; i < 1000; ++i) {
		if (atm_array[i] == nominal)
			nominal_count++;
	}
	return nominal_count;
}

long long atm_sum(int atm_array[]) {
	long long sum = 0;
	for (int i = 0; i < 1000; ++i) {
		sum += (long long)atm_array[i];
	}
	return sum;
}

void atm_taking_banknote(int atm_array[], int nominal, int banknote_num) {
	for (int i = 0; i < 1000; ++i) {
		if (banknote_num == 0)
			break;
		else if (atm_array[i] == nominal) {
			atm_array[i] = 0;
			banknote_num -= 1;
		}
	}
}

int main() {
	std::srand(std::time(nullptr));
	int atm[1000];
	char operation;

	std::cout << "If You want to load banknote   to ATM, type '+'" << std::endl;
	std::cout << "If You want to receive money from ATM, type '-'" << std::endl;
	std::cin >> operation;
	int input_operation_count = 2;
	while (operation != '+' && operation != '-') {
		if (input_operation_count < 1) {
			std::cout << "The number of attempts has ended!" << std::endl << "Good by!" << std::endl;
			return 0;
		}
		std::cout << "ERROR input char!!! Try again!!!" << std::endl;
		std::cout << "If You want to load banknote   to ATM, type '+'" << std::endl;
		std::cout << "If You want to receive money from ATM, type '-'" << std::endl;
		std::cin >> operation;
		input_operation_count--;
	}
	if (operation == '+') {
		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "Please, load banknotes to ATM." << std::endl;
		for (int i = 0; i < 1000; ++i) {
			atm[i] = banknote_random();
		}

		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "Loading operation complete! ATM sum = " << atm_sum(atm) << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "Good by!" << std::endl;
	} else {
		std::ifstream atm_status_file(
			"F:\\__C++\\Skillbox\\20\\20.5.4 Implementation of ATM simulation\\Files\\atm_status.bin");
		for (int i = 0; i < 1000; ++i) {
			atm_status_file >> atm[i];
		}
		atm_status_file.close();

		std::cout << "-------------------------------------------------------------" << std::endl;
		std::cout << "Please, input sum You want to receive (min 100, max " << atm_sum(atm) << "):" << std::endl;
		long long receive_sum;
		std::cin >> receive_sum;
		if (receive_sum > atm_sum(atm) || receive_sum < 100) {
			std::cout << "SORRY, not enough money in ATM of too small sum." << std::endl;
			std::cout << "-------------------------------------------------------------" << std::endl;
			std::cout << "Good by!" << std::endl;
			return 0;
		}

		int nominal_5000_in_atm = banknote_nominal_count(atm, 5000);
		int nominal_2000_in_atm = banknote_nominal_count(atm, 2000);
		int nominal_1000_in_atm = banknote_nominal_count(atm, 1000);
		int nominal_500_in_atm = banknote_nominal_count(atm, 500);
		int nominal_200_in_atm = banknote_nominal_count(atm, 200);
		int nominal_100_in_atm = banknote_nominal_count(atm, 100);
		long long taking_banknote_5000 = 0;
		long long taking_banknote_2000 = 0;
		long long taking_banknote_1000 = 0;
		long long taking_banknote_500 = 0;
		long long taking_banknote_200 = 0;
		long long taking_banknote_100 = 0;

		if (receive_sum >= 5000) {
			if (receive_sum / 5000 > nominal_5000_in_atm) {
				taking_banknote_5000 = nominal_5000_in_atm;
				receive_sum -= nominal_5000_in_atm * 5000;
			} else {
				taking_banknote_5000 = receive_sum / 5000;
				receive_sum %= 5000;
			}
		}
		if (receive_sum >= 2000) {
			if (receive_sum / 2000 > nominal_2000_in_atm) {
				taking_banknote_2000 = nominal_2000_in_atm;
				receive_sum -= nominal_2000_in_atm * 2000;
			} else {
				taking_banknote_2000 = receive_sum / 2000;
				receive_sum %= 2000;
			}
		}
		if (receive_sum >= 1000) {
			if (receive_sum / 1000 > nominal_1000_in_atm) {
				taking_banknote_1000 = nominal_1000_in_atm;
				receive_sum -= nominal_1000_in_atm * 1000;
			} else {
				taking_banknote_1000 = receive_sum / 1000;
				receive_sum %= 1000;
			}
		}
		if (receive_sum >= 500) {
			if (receive_sum / 500 > nominal_500_in_atm) {
				taking_banknote_500 = nominal_500_in_atm;
				receive_sum -= nominal_500_in_atm * 500;
			} else {
				taking_banknote_500 = receive_sum / 500;
				receive_sum %= 500;
			}
		}
		if (receive_sum >= 200) {
			if (receive_sum / 200 > nominal_200_in_atm) {
				taking_banknote_200 = nominal_200_in_atm;
				receive_sum -= nominal_200_in_atm * 200;
			} else {
				taking_banknote_200 = receive_sum / 200;
				receive_sum %= 200;
			}
		}
		if (receive_sum >= 100) {
			if (receive_sum / 100 > nominal_100_in_atm) {
				std::cout << "SORRY, but not enough required banknotes for your sum!" << std::endl;
				std::cout << "Please try less sum!" << std::endl;
				std::cout << "-------------------------------------------------------------" << std::endl;
				std::cout << "Good by!" << std::endl;
				return 0;
			} else {
				taking_banknote_100 = receive_sum / 100;
				receive_sum %= 100;
			}
		}
		if (taking_banknote_5000 > 0) {
			atm_taking_banknote(atm, 5000, (int) taking_banknote_5000);
			std::cout << "5000 * " << taking_banknote_5000 << std::endl;
		}
		if (taking_banknote_2000 > 0) {
			atm_taking_banknote(atm, 2000, (int) taking_banknote_2000);
			std::cout << "2000 * " << taking_banknote_2000 << std::endl;
		}
		if (taking_banknote_1000 > 0) {
			atm_taking_banknote(atm, 1000, (int) taking_banknote_1000);
			std::cout << "1000 * " << taking_banknote_1000 << std::endl;
		}
		if (taking_banknote_500 > 0) {
			atm_taking_banknote(atm, 500, (int) taking_banknote_500);
			std::cout << "500 * " << taking_banknote_500 << std::endl;
		}
		if (taking_banknote_200 > 0) {
			atm_taking_banknote(atm, 200, (int) taking_banknote_200);
			std::cout << "200 * " << taking_banknote_200 << std::endl;
		}
		if (taking_banknote_100 > 0) {
			atm_taking_banknote(atm, 100, (int) taking_banknote_100);
			std::cout << "100 * " << taking_banknote_100 << std::endl;
		}

		std::cout << "Operation complete!" << std::endl;
		std::cout << "-------------------------------------------------------------" << std::endl;
		std::cout << "Good by!" << std::endl;
	}

	std::ofstream atm_status_file(
		"F:\\__C++\\Skillbox\\20\\20.5.4 Implementation of ATM simulation\\Files\\atm_status.bin",
		std::ios::binary);
	for (int i = 0; i < 1000; ++i) {
		atm_status_file << atm[i] << std::endl;
	}
	atm_status_file.close();
}
