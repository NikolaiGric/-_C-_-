#include <iostream>
#include <consoleapi2.h>

using namespace std;
class BankAccount
{
	private:
		int accountNumber;
		double balance;
		double interestRate;
	public:
		BankAccount(int accNum, double initialBalance) {
			this->accountNumber = accNum;
			if (initialBalance < 0) {
				throw invalid_argument("Начальный баланс не может быть отрицательным");
			}
			this->balance = initialBalance;
			this->interestRate = 0;
		}
	
		void deposit(double amount) {
			if (amount <= 0) {
				throw invalid_argument("Некорректная сумма перевода");
			}
			balance -= amount;
			cout << "Средства успешно внесены. Остаток на счёте:" << balance << endl;
			}
		void withdraw(double amount) {
			if (amount <= 0) {
				throw invalid_argument("Некорректная сумма снятия.");
			}
			if (amount > balance) {
				throw invalid_argument("Недостаточно средств для снятия.");
			}
			balance -= amount;
			cout << "Средства успешно сняты. Остаток на счёте:" << balance << endl;

		}

		double getBalance(){
			return balance * interestRate / 100.0 * (1.0 / 12.0);
		}

		double getInterest() {
			return balance;
		}

		double getInterestRate() {
			return interestRate;
		}

		void setInterestRate(double rate) {
			this->interestRate = rate;
		}

		int getAccountNumber() {
			return accountNumber;
		}
		friend bool transfer(BankAccount& from, BankAccount& to, double amount);

		bool transfer(BankAccount& from, BankAccount& to, double amount) 
		{
			try
			{
				from.withdraw(amount);
				to.deposit(amount);
				return true;
			}
			catch (const invalid_argument& e)
			{
				cerr << "Ошибка при переводе: " << e.what() << endl;
				return false;
			}
		}
};
int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	try
	{
		BankAccount Tinkoff(1, 0);
		BankAccount Russia(2, 0);

		int choice;
		double amount;
		bool success;

		while (true)
		{
			cout << "Выбор действия:\n"
				"1. Пополнить счет\n"
				"2. Снять деньги\n"
				"3. Изменить процентную ставку\n"
				"4. Перевод\n"
				"5. Узнать текущую процентную ставку\n"
				"6. Выйти из программы\n";

			cout << "Вы выбрали: ";
			cin >> choice;

			if (!(cin >> choice)) {
				cout << "Ваш выбор пал не на число, нужно выбрать ещё раз." << endl;
				continue;
			}

			switch (choice)
			{
			default: 
				cout << "Ошибка действие должно быть из списка, а не по наитию" << endl;
			case 1:
				cout << "Введите сумму для пополнения: ";
				cin >> amount;
				Tinkoff.deposit(amount);
				break;
			case 2:
				cout << "Введите сумму для снятия: ";
				cin >> amount;
				Tinkoff.withdraw(amount);
				break;
			case 3:
				cout << "Введите новую процентную ставку: ";
				cin >> amount;
				Tinkoff.setInterestRate(amount);
				break;
			case 4:
				cout << "Введите сумму для перевода: ";
				cin >> amount;
				success = transfer(Tinkoff, Russia, amount);
				if (success) {
					cout << "Баланс счета 1: " << Tinkoff.getBalance() << endl;
					cout << "Баланс счета 2: " << Russia.getBalance() << endl;
				}
				break;
			case 5:
				cout << "Текущая процентная ставка: " << Tinkoff.getBalance() << "$" << endl;
				break;
			case 6:
				cout << "Выход из программы." << endl;
			}
		}
	}
	catch (const invalid_argument& e)
	{
		cerr << "Ошибка: " << e.what() << endl;
	}

	return 0;
}
