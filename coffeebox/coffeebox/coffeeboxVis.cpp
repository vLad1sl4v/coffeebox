#include <iostream>
#include <cmath>
#include <Windows.h>
#include <cstdlib>

using namespace std;

const int PIN = 8815;
const int MAX_ATTEMPTS = 3;
const int MAX_CHOICE = 5;
const int MAX_CHOICE_DEPOSIT = 6;
const int MAX_CHOICE_COFFEE = 4;
const int MAX_CHOICE_SERVICE = 3;
const int INITIAL_CUPS = 7;
const int MAX_CUPS = 700;
const int CHOICE_TWO = 2;
const int CHOICE_THREE = 3;
const int CHOICE_FOUR = 4;
const int CHOICE_FIVE = 5;
const double PRICE_ESPRESSO = 1.9;
const double PRICE_CAPPUCCINO = 2.0;
const double PRICE_LATTE = 2.5;
const double TWO_RUBLES = 2.0;
const double ONE_RUBLE = 1.0;
const double FIFTY_PENNIES = 0.5;
const double TWENTY_PENNIES = 0.2;
const double TEN_PENNIES = 0.1;
const string CURRENC = "BYN";

double balance = 0.0;
double profit = 0.0;
int attempts = 0;
int cups = INITIAL_CUPS;

void clear();
void deposit();
void openServiceMenu();
void printYourChoice();
void printBalance();
void printCallService();
void printWarning();
void printYourCoffee();
void showMainMenu();
void showDepositMenu();
void showCoffeeMenu();
void showLoginService();
void showServiceMenu();
void goBack();
void makeCoffee(int);
double depositMoney(int);
double calculateNotEnough(int);

int main()
{
	int choice = 0;
	int pin = 0;
	int addCup = 0;
	bool madeCoffee = false;
	bool validPin = false;
	bool cupsMax = false;
	int block = 0;

	while (true)
	{
		clear();
		showMainMenu();
		printYourChoice();
		cin >> choice;

		if (choice < 1 or choice > CHOICE_FIVE)
		{
			printError(CHOICE_FIVE);
			goBack();
		}

		clear();

		if (choice == 1)
		{
			deposit();
		}
		else if (choice <= MAX_CHOICE_COFFEE)
		{
			if (cups != 0)
			{
				makeCoffee(choice); 
			}
			else
			{
				printCallService();
			}
			goBack();
		}
		else
		{
			do
			{
				showLoginService();
				cin >> pin;

				if (pin == 0)
					break;
				else if (pin != PIN)
				{
					attempts++;
					if (attempts == MAX_ATTEMPTS)
					{
						cout << "Too many attempts!" << endl;
						cout << "Coffeebox locking" << endl;
						return 0;
					}
				}
				clear();
			} while (pin != PIN);

			if (pin == 0)
				continue;

			openServiceMenu();

		}

	}
	return 0;
}

void clear()
{
	system("cls");
}

void deposit()
{
	int choice = 0;

	showDepositMenu();

	do
	{
		printYourChoice();
		cin >> choice;
		if (choice <= 0 or choice > MAX_CHOICE_DEPOSIT)
		{
			printError(MAX_CHOICE_DEPOSIT);
		}
		else if (choice != MAX_CHOICE_DEPOSIT)
		{
			balance += depositMoney(choice);
			profit += depositMoney(choice);
			printBalance();
		}
	} while (choice != MAX_CHOICE_DEPOSIT);
}

void openServiceMenu()
{
	int choice = 0;
	int addCup = 0;

	while (true)
	{
		clear();
		showServiceMenu();
		printYourChoice();
		cin >> choice;

		if (choice <= 0 or choice > MAX_CHOICE_SERVICE)
		{
			printError(MAX_CHOICE_SERVICE);
			continue;
		}

		else if (choice == MAX_CHOICE_SERVICE)
		{
			break;
		}

		else if (choice == 1)
		{
			clear();
			cout << "Accumulated cash:\t" << profit << " " << CURRENC << endl;
			profit = 0.0;
			cout << "Accumulated cash was taken" << endl;

			goBack();
			continue;
		}
		else if (choice == CHOICE_TWO)
		{
			clear();
			cout << "Input number of cups added: ";
			cin >> addCup;

			if (addCup <= 0)
			{
				cout << "You can not add 0 or less cups" << endl;
				goBack();
				continue;
			}
			else if (addCup + cups > MAX_CUPS)
			{
				cout << "Amount of cups is more than " << MAX_CUPS << endl;
				cout << "You should add " << MAX_CUPS - cups << " cups or less" << endl;

				goBack();
				continue;
			}

			cups += addCup;
		}
	}
}

	void showMainMenu()
	{
		cout << "Welcome to CoffeBox!" << endl;
		printBalance();
		cout << "Choose the option: " << endl;
		cout << "1. Deposit money" << endl;
		cout << "2. Espresso\t" << PRICE_ESPRESSO << " " << CURRENC << endl;
		cout << "3. Cappuccino\t" << PRICE_CAPPUCCINO << " " << CURRENC << endl;
		cout << "4. Latte\t" << PRICE_LATTE << " " << CURRENC << endl;
		cout << "5. Service menu" << endl;
		printWarning();
	}

	void showDepositMenu()
	{
		cout << "Deposit menu" << endl;
		cout << "Input coins:" << endl;
		cout << "1. 2 rubles" << endl;
		cout << "2. 1 ruble" << endl;
		cout << "3. 50 pennies" << endl;
		cout << "4. 20 pennies" << endl;
		cout << "5. 10 pennies" << endl;
		cout << "6. Back" << endl;
	}

	void showCoffeeMenu()
	{
		cout << "Coffee menu" << endl;
		printBalance();
		cout << "Choose your coffee: " << endl;
		cout << "1. Espresso\t" << PRICE_ESPRESSO << " " << CURRENC << endl;
		cout << "2. Cappuccino\t" << PRICE_CAPPUCCINO << " " << CURRENC << endl;
		cout << "3. Latte\t" << PRICE_LATTE << " " << CURRENC << endl;
		cout << "4. Back" << endl;
	}

	void showLoginService()
	{
		cout << "Login menu" << endl;
		cout << "Enter PIN (0 to go back)" << endl;
		cout << "Attempts left:\t" << MAX_ATTEMPTS - attempts << endl;
	}

	void showServiceMenu()
	{
		cout << "Service menu" << endl;
		cout << "Choose your option:" << endl;
		cout << "Accumulated cash:\t" << profit << " " << CURRENC << endl;
		cout << "Cups remaining:\t\t" << cups << endl;
		cout << "1. Take money" << endl;
		cout << "2. Add cups" << endl;
		cout << "3. Back" << endl;
	}

	void printYourChoice()
	{
		cout << "Your choice: ";
	}

	void printBalance()
	{
		cout << "Current balance: " << balance << " " << CURRENC << endl;
	}

	void printCallService()
	{
		cout << "Sorry, we are out of cups. Please, call the customer service" << endl;
	}

	void printError(int maxChoice)
	{
		cout << "Error! Input [1.." << maxChoice << "]" << endl;
	}

	void printWarning()
	{
		if (cups <= 5)
		{
			cout << "Warning, only " << cups << " cups left. Please, call the customer service" << endl;
		}
	}

	void goBack()
	{
		int back = 0;

		cout << "Input any number to go back" << endl;
		cin >> back;
	}

	void makeCoffee(int choiceCoffee)
	{
		balance = round(balance * 100) / 100;

		if (choiceCoffee == CHOICE_TWO and balance >= PRICE_ESPRESSO)
		{
			balance -= PRICE_ESPRESSO;
		}
		else if (choiceCoffee == CHOICE_THREE and balance >= PRICE_CAPPUCCINO)
		{
			balance -= PRICE_CAPPUCCINO;
		}
		else if (choiceCoffee == CHOICE_FOUR and balance >= PRICE_LATTE)
		{
			balance -= PRICE_LATTE;
		}
		else
		{
			cout << "Insufficient funds. Go back to menu and replenish the deposit" << endl;
			cout << "You need " << calculateNotEnough(choiceCoffee) << " " << CURRENC << " more" << endl;
			return;
		}
		cups--;
		printYourCoffee(); //+
	}

	void printYourCoffee()
	{
		cout << "Your drink is being prepared, please wait" << endl;
		Sleep(3000);
		cout << "Take your coffee, please" << endl;
		cout << "Have a nice day!" << endl;
	}

	double depositMoney(int choiceDeposit)
	{
		double deposit = 0.0;

		if (choiceDeposit == 1)
			deposit = TWO_RUBLES;
		else if (choiceDeposit == CHOICE_TWO)
			deposit = ONE_RUBLE;
		else if (choiceDeposit == CHOICE_THREE)
			deposit = FIFTY_PENNIES;
		else if (choiceDeposit == CHOICE_FOUR)
			deposit = TWENTY_PENNIES;
		else
			deposit = TEN_PENNIES;

		return deposit;
	}

	double calculateNotEnough(int choiceCoffee)
	{
		double difference = 0.0;

		if (choiceCoffee == CHOICE_TWO)
		{
			difference = PRICE_ESPRESSO - balance;
		}
		else if (choiceCoffee == CHOICE_THREE)
		{
			difference = PRICE_CAPPUCCINO - balance;
		}
		else
		{
			difference = PRICE_LATTE - balance;
		}

		return difference;
	}