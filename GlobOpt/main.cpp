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
protected:
	// Коэффициенты для подсчета значения функции
	double K[1000000], A[1000000], C[1000000];
	//Оптимальная точка
	double ox, oFuncVal;
public:
	TSHProblem()
	{
		for (long long int i = 0; i < 1000000; i++)
		{
			K[i] = rand() % (3 - 1 + 1) + 1;
			A[i] = rand();
			C[i] = rand() % (10 - 32767 + 1) + 32767;
		}
		IProblem* problem = this;
		TTask task(problem);
		IMethod* method = new BF(&task, 1000, 0.0001);
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
		long long int xi = x * 100000;
		for (int i = 0; i < 10; i++)
		{
			res += 1 / (K[xi] * pow((x - A[xi]), 2) + C[xi]);
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
	double A[100000], B[100000];
	//Оптимальная точка
	double ox, oFuncVal;
public:
	THLProblem()
	{
		for (long long int i = 0; i < 100000; i++)
		{
			A[i] = rand() % (1 + 1 + 1) + 1;
			B[i] = rand() % (1 + 1 + 1) + 1;
		}
		//ox = 0.0;
		//oFuncVal = 0.0;
		IProblem* problem = this;
		TTask task(problem);
		IMethod* method = new BF(&task, 1000, 0.0001);
		method->Solve();
		TTrial opt;
		opt = method->GetOptimEstimation();
		ox = opt.x;
		oFuncVal = opt.FuncValue;
		delete problem;
		delete method;
	}
	///Инициализация задачи
	virtual int Initialize()
	{
		/*IProblem* problem = new THLProblem();
		TTask task(problem);
		IMethod* method = new BF(&task, 300, 0.001);
		method->Solve();
		TTrial opt;
		opt = method->GetOptimEstimation();
		ox = opt.x;
		oFuncVal = opt.FuncValue;
		delete problem;
		delete method;*/
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
		long long int xi = x * 100000;
		for (int i = 0; i < 14; i++)
		{
			res += A[xi]* sin(2*M_PI*x*i) + B[xi]*cos(2*M_PI*x*i) ;
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
	IProblem* problem = new THLProblem();
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