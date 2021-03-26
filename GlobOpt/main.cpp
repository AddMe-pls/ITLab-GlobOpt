#define _USE_MATH_DEFINES

//#include "classes.h"
#include "BF.h"

//Функция y = (x-1)(x-1) при x \in [-1,2]
class TX2Problem : public IProblem
{

	///Инициализация задачи
	virtual int Initialize()
	{
		return IProblem::OK;
	}

	/// Метод возвращает границы области поиска
	virtual void GetBounds(double& lower, double& upper)
	{
		lower = -1;
		upper = 2;
	}
	/** Метод возвращает значение функции в точке глобального минимума
	\param[out] value оптимальное значение
	\return Код ошибки (#OK или #UNDEFINED)
	*/
	virtual int GetOptimumValue(double& value) const
	{
		value = 0;
		return IProblem::OK;
	}
	/** Метод возвращает координаты точки глобального минимума целевой функции
	\param[out] x точка, в которой достигается оптимальное значение
	\return Код ошибки (#OK или #UNDEFINED)
	*/
	virtual int GetOptimumPoint(double& x) const
	{
		x = 1;
		return IProblem::OK;
	}

	/** Метод, вычисляющий функцию задачи

	\param[in] x Точка, в которой необходимо вычислить значение
	\return Значение функции
	*/
	virtual double CalculateFunction(const double x) const
	{
		return (x - 1)*(x - 1);
	}

	///Деструктор
	~TX2Problem()
	{
	}

};

class TSHProblem : public IProblem
{

	///Инициализация задачи
	virtual int Initialize()
	{
		return IProblem::OK;
	}

	/// Метод возвращает границы области поиска
	virtual void GetBounds(double& lower, double& upper)
	{
		lower = 0;
		upper = 10;
	}
	/** Метод возвращает значение функции в точке глобального минимума
	\param[out] value оптимальное значение
	\return Код ошибки (#OK или #UNDEFINED)
	*/
	virtual int GetOptimumValue(double& value) const
	{
		value = 0;
		return IProblem::OK;
	}
	/** Метод возвращает координаты точки глобального минимума целевой функции
	\param[out] x точка, в которой достигается оптимальное значение
	\return Код ошибки (#OK или #UNDEFINED)
	*/
	virtual int GetOptimumPoint(double& x) const
	{
		//x = 1;
		IProblem* problem = new TSHProblem();
		TTask task(problem);


		return IProblem::OK;
	}

	/** Метод, вычисляющий функцию задачи

	\param[in] x Точка, в которой необходимо вычислить значение
	\return Значение функции
	*/
	virtual double CalculateFunction(const double x) const
	{
		double res = 0, K = 0, A = 0, C = 0;
		for (int i = 0; i < 10; i++)
		{
			K = rand() % (3 - 1 + 1) + 1;
			A = rand();
			C = rand() % (10 - 32767 + 1) + 32767;
			res += 1 / (K * pow((x - A), 2) + C);
		}
		return -res;
	}

	///Деструктор
	~TSHProblem()
	{
	}

};

class THLProblem : public IProblem
{

	///Инициализация задачи
	virtual int Initialize()
	{
		return IProblem::OK;
	}

	/// Метод возвращает границы области поиска
	virtual void GetBounds(double& lower, double& upper)
	{
		lower = 0;
		upper = 1;
	}
	/** Метод возвращает значение функции в точке глобального минимума
	\param[out] value оптимальное значение
	\return Код ошибки (#OK или #UNDEFINED)
	*/
	virtual int GetOptimumValue(double& value) const
	{
		value = 0;
		return IProblem::OK;
	}
	/** Метод возвращает координаты точки глобального минимума целевой функции
	\param[out] x точка, в которой достигается оптимальное значение
	\return Код ошибки (#OK или #UNDEFINED)
	*/
	virtual int GetOptimumPoint(double& x) const
	{
		x = 1;
		return IProblem::OK;

	}

	/** Метод, вычисляющий функцию задачи

	\param[in] x Точка, в которой необходимо вычислить значение
	\return Значение функции
	*/
	virtual double CalculateFunction(const double x) const
	{
		double res = 0, A = 0, B = 0;
		for (int i = 0; i < 14; i++)
		{
			A = rand() % (1 + 1 + 1) + 1;
			B = rand() % (1 + 1 + 1) + 1;
			res += A* sin(2*M_PI*x*i) + B*cos(2*M_PI*x*i) ;
		}
		return res;
	}

	///Деструктор
	~THLProblem()
	{
	}

};

//Пример создания конкретной задачи
int main(int argc, char * argv[])
{
	//Объявляем указатель на базовый класс и присваиваем ему указатель на производный класс
	IProblem* problem = new TX2Problem();
	//Инициализируем задачу оптимизации
	TTask task(problem);
	//И используем ее в методе

	//Для примера - печать таблицы значений функции
	int size = 20;
	double x = task.GetA();
	double h = (task.GetB() - task.GetA()) / size;

	std::cout << " x        f(x)" << std::endl;
	std::cout.precision(2);
	std::cout << std::fixed;
	for (int i = 0; i < size; i++)
	{
		x = task.GetA() + i*h;
		std::cout << x << "     " << task.CalculateFunction(x) << std::endl;
	}
	std::cout << std::endl << std::endl;

	std::cout << "min{f(x)} = " << task.GetOptimumValue() << std::endl;
	std::cout << "arg min{f(x)} = " << task.GetOptimumPoint() << std::endl << std::endl;


	delete problem;

	return 0;
}