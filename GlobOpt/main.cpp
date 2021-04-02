#define _USE_MATH_DEFINES

//#include "classes.h"
#include "BF.h"

//������� y = (x-1)(x-1) ��� x \in [-1,2]
class TX2Problem : public IProblem
{

	///������������� ������
	virtual int Initialize()
	{
		return IProblem::OK;
	}

	/// ����� ���������� ������� ������� ������
	virtual void GetBounds(double& lower, double& upper)
	{
		lower = -1;
		upper = 2;
	}
	/** ����� ���������� �������� ������� � ����� ����������� ��������
	\param[out] value ����������� ��������
	\return ��� ������ (#OK ��� #UNDEFINED)
	*/
	virtual int GetOptimumValue(double& value) const
	{
		value = 0;
		return IProblem::OK;
	}
	/** ����� ���������� ���������� ����� ����������� �������� ������� �������
	\param[out] x �����, � ������� ����������� ����������� ��������
	\return ��� ������ (#OK ��� #UNDEFINED)
	*/
	virtual int GetOptimumPoint(double& x) const
	{
		x = 1;
		return IProblem::OK;
	}

	/** �����, ����������� ������� ������

	\param[in] x �����, � ������� ���������� ��������� ��������
	\return �������� �������
	*/
	virtual double CalculateFunction(const double x) const
	{
		return (x - 1)*(x - 1);
	}

	///����������
	~TX2Problem()
	{
	}

};

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>((double)rand() * fraction * (max - min + 1) + min);
}

class TSHProblem : public IProblem
{
protected:
	// ������������ ��� �������� �������� �������
	double K[1000000], A[1000000], C[1000000];
	//����������� �����
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
		IMethod* method = new BF(&task, 100, 0.0001);
		method->Solve();
		TTrial opt;
		opt = method->GetOptimEstimation();
		ox = opt.x;
		oFuncVal = opt.FuncValue;
	}
	///������������� ������
	virtual int Initialize()
	{
		return IProblem::OK;
	}

	/// ����� ���������� ������� ������� ������
	virtual void GetBounds(double& lower, double& upper)
	{
		lower = 0;
		upper = 10;
	}
	/** ����� ���������� �������� ������� � ����� ����������� ��������
	\param[out] value ����������� ��������
	\return ��� ������ (#OK ��� #UNDEFINED)
	*/
	virtual int GetOptimumValue(double& value) const
	{
		value = oFuncVal;
		return IProblem::OK;
	}
	/** ����� ���������� ���������� ����� ����������� �������� ������� �������
	\param[out] x �����, � ������� ����������� ����������� ��������
	\return ��� ������ (#OK ��� #UNDEFINED)
	*/
	virtual int GetOptimumPoint(double& x) const
	{
		x = ox;
		return IProblem::OK;
	}

	/** �����, ����������� ������� ������

	\param[in] x �����, � ������� ���������� ��������� ��������
	\return �������� �������
	*/
	virtual double CalculateFunction(const double x) const
	{
		double res = 0;
		long long int xi = x * 100000;
		for (int i = 1; i <= 10; i++)
		{
			res += 1 / (K[xi] * pow((x - A[xi]), 2) + C[xi]);
		}
		return -res;
	}

	///����������
	~TSHProblem()
	{
	}

};

class THLProblem : public IProblem
{
protected:
	// ������������ ��� �������� �������� �������
	double A[100001], B[100001];
	//����������� �����
	double ox, oFuncVal;
public:
	THLProblem()
	{
		for (std::size_t i = 0; i <= 100000; i++)
		{
			//(static_cast<double>rand()/static_cast<double>(RAND_MAX))*2-1
			A[i] = (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * 2 - 1;
			B[i] = (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) * 2 - 1;
			//A[i] = rand() % 3 - 1;
			//B[i] = rand() % 3 - 1;
			//A[i] = getRandomNumber(-1, 1);
			//B[i] = getRandomNumber(-1, 1);
		}
		ox = 0.0;
		oFuncVal = 0.0;
		IProblem* problem = this;
		TTask task(problem);
		IMethod* method = new BF(&task, 1000, 0.0001);
		method->Solve();
		TTrial opt;
		opt = method->GetOptimEstimation();
		ox = opt.x;
		oFuncVal = opt.FuncValue;
		//delete problem;
		//delete method;
	}
	///������������� ������
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

	/// ����� ���������� ������� ������� ������
	virtual void GetBounds(double& lower, double& upper)
	{
		lower = 0;
		upper = 1;
	}
	/** ����� ���������� �������� ������� � ����� ����������� ��������
	\param[out] value ����������� ��������
	\return ��� ������ (#OK ��� #UNDEFINED)
	*/
	virtual int GetOptimumValue(double& value) const
	{
		value = oFuncVal;
		return IProblem::OK;
	}
	/** ����� ���������� ���������� ����� ����������� �������� ������� �������
	\param[out] x �����, � ������� ����������� ����������� ��������
	\return ��� ������ (#OK ��� #UNDEFINED)
	*/
	virtual int GetOptimumPoint(double& x) const
	{
		x = ox;
		return IProblem::OK;
	}

	/** �����, ����������� ������� ������

	\param[in] x �����, � ������� ���������� ��������� ��������
	\return �������� �������
	*/
	virtual double CalculateFunction(const double x) const
	{
		double res = 0;
		long long int xi = x * 100000;
		for (int i = 1; i <= 14; i++)
		{
			res += A[xi]* sin(2*M_PI*x*i) + B[xi]*cos(2*M_PI*x*i) ;
		}
		return res;
	}

	///����������
	~THLProblem()
	{
	}

};

//������ �������� ���������� ������
int main(int argc, char * argv[])
{
	//��������� ��������� �� ������� ����� � ����������� ��� ��������� �� ����������� �����
	IProblem* problem = new THLProblem();
	//�������������� ������ �����������
	TTask task(problem);
	//� ���������� �� � ������
	//��� ������� - ������ ������� �������� �������
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