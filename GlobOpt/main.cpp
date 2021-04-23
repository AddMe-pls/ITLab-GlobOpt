#define _USE_MATH_DEFINES

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
protected:
	// Коэффициенты для подсчета значения функции
	double K[10], A[10], C[10];
	//Оптимальная точка
	double ox, oFuncVal;
	//Seed для выбора определенной задачи
	int seed;
public:
	TSHProblem(int _seed = 1)
	{
		seed = _seed;
		srand(_seed);
		for (int i = 0; i < 10; i++)
		{
			K[i] = (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * 20 + 5;
			A[i] = (static_cast<double>(rand())/ static_cast<double>(RAND_MAX)) * 10;
			C[i] = (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * 0.2 + 1; 
		}
		IProblem* problem = this;
		TTask task(problem);
		IMethod* method = new BF(&task, 100, 0.001);
		method->Solve();
		TTrial opt;
		opt = method->GetOptimEstimation();
		ox = opt.x;
		oFuncVal = opt.FuncValue;
	}
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
		value = oFuncVal; //HUGE_VAL;
		return IProblem::OK;
	}
	/** Метод возвращает координаты точки глобального минимума целевой функции
	\param[out] x точка, в которой достигается оптимальное значение
	\return Код ошибки (#OK или #UNDEFINED)
	*/
	virtual int GetOptimumPoint(double& x) const
	{
		x = ox;
		return IProblem::OK;
	}

	/** Метод, вычисляющий функцию задачи

	\param[in] x Точка, в которой необходимо вычислить значение
	\return Значение функции
	*/
	virtual double CalculateFunction(const double x) const
	{
		double res = 0;
		for (int i = 0; i < 10; i++)
		{
			res += 1 / (K[i] * (x - A[i]) * (x - A[i]) + C[i]);
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
protected:
	// Коэффициенты для подсчета значения функции
	double A[14], B[14];
	//Оптимальная точка
	double ox, oFuncVal;
	//Seed для выбора определенной задачи
	int seed;
public:
	THLProblem(int _seed = 1)
	{
		seed = _seed;
		srand(_seed);
		for (std::size_t i = 0; i < 14; i++)
		{
			A[i] = (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * 2 - 1;
			B[i] = (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * 2 - 1;
		}
		ox = 0.0;
		oFuncVal = 0.0;
		IProblem* problem = this;
		TTask task(problem);
		IMethod* method = new BF(&task, 1000, 0.001);
		method->Solve();
		TTrial opt;
		opt = method->GetOptimEstimation();
		ox = opt.x;
		oFuncVal = opt.FuncValue;
	}
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
		value = oFuncVal;
		return IProblem::OK;
	}
	/** Метод возвращает координаты точки глобального минимума целевой функции
	\param[out] x точка, в которой достигается оптимальное значение
	\return Код ошибки (#OK или #UNDEFINED)
	*/
	virtual int GetOptimumPoint(double& x) const
	{
		x = ox;
		return IProblem::OK;
	}

	/** Метод, вычисляющий функцию задачи

	\param[in] x Точка, в которой необходимо вычислить значение
	\return Значение функции
	*/
	virtual double CalculateFunction(const double x) const
	{
		double res = 0;
		for (int i = 0; i < 14; i++)
		{
			res += A[i]* sin(2*M_PI*x*i) + B[i]*cos(2*M_PI*x*i) ;
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
	IProblem* problem = new TSHProblem();
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