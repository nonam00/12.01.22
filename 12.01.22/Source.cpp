#include <iostream>
#include <string>
#include <vector>
#include <map>;
#include <random>
#include <Windows.h>

//рандом
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution <> gen32(1, 100);

//заполнение массива
void fill(int* array[], int colums, int rows);

//вывод массива
void print_array(int* array[], int colums, int rows);		

//сумма чисел по диагонали
void diagonal_summ(int* array[], int colums, int rows);

//сумма чисел вокруг €чейки
void coord_summ(int* array[], int colums, int rows);

//класс хран€щий в себе все значени€ массива и их индексы
class Values1
{

public:

	Values1(int* array[], int colums, int rows)
	{
		std::string str;
		for (int i = 0; i < colums; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				
				str = std::to_string(i) + ":" + std::to_string(j);
				data.insert(std::pair<int, std::string>(array[i][j], str));
			}
		}
	}

	void print()
	{
		for (auto item : data)
		{
			std::cout << item.first << " - " << item.second << std::endl;
		}
	}

protected:
	
	std::map<int, std::string> data;
};


int main()
{
	//русский €зык
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int colums;		//число столбцов
	int rows;		//число строк

	std::cout << "¬ведите ширину" << std::endl;
	std::cin >> colums; std::cout << std::endl;
	
	std::cout << "¬ведите длину" << std::endl;
	std::cin >> rows; std::cout << std::endl;
	
	int** array = new int* [colums];
	for (int i = 0; i < colums; i++)
		array[i] = new int[rows];

	fill(array, colums, rows);
	print_array(array, colums, rows);

	Values1 value(array, colums, rows);
	value.print();

	diagonal_summ(array, colums, rows);

	coord_summ(array, colums, rows);

	//высвобождение пам€ти
	for (int i = 0; i < colums; i++)
		delete array[i];
	delete[]array;

	return 0;
}

void fill(int* array[], int colums, int rows)
{
	for (int i = 0; i < colums; i++)
		for (int j = 0; j < rows; j++)
			array[i][j] = gen32(rng);
}

void print_array(int* array[], int colums, int rows)
{
	for (int i = 0; i < colums; i++)
	{
		for (int j = 0; j < rows; j++)
			std::cout << array[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void diagonal_summ(int* array[], int colums, int rows)
{
	int summ = 0;

	char choice;
	std::cout << "¬ведите по какой диагонали считать сумму: " << std::endl << std::endl;
	std::cout << "  /       \\" << std::endl << " /   или   \\" << std::endl << "/           \\ " << std::endl << std::endl;
	std::cin >> choice; std::cout << std::endl;

	switch (choice)
	{
	case '/':
		for (int i = 0, j = rows - 1; i < colums; i++, j--)
			summ += array[i][j];
		break;
	case '\\':
		for (int i = 0, j = 0; i < colums; i++, j++)
			summ += array[i][j];
		break;
	default:
		std::cout << "“акого варианта не существует" << std::endl;
		break;
	}
	std::cout << summ << std::endl;
}

void coord_summ(int* array[], int colums, int rows)
{
	int x, y;
	std::cout << "¬ведите координаты: " << std::endl;
	std::cin >> x >> y; std::cout << std::endl;

	int summ = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{

			int current_colum = x + i;
			int current_row = y + j;
			bool isInline = current_colum >= 0 && current_colum < colums
				&& current_row >= 0 && current_row < rows;
			bool isSelf = current_row != x || current_colum != y;
			if (isSelf && isInline)
			{
				summ += array[current_colum][current_row];
			}
		}
	}
	std::cout << summ << std::endl;
}