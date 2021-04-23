#define _USE_MATH_DEFINES

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


class TSHProblem : public IProblem
{
protected:
	// ������������ ��� �������� �������� �������
	double K[10], A[10], C[10];
	//����������� �����
	double ox, oFuncVal;
	//Seed ��� ������ ������������ ������
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
		value = oFuncVal; //HUGE_VAL;
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
		for (int i = 0; i < 10; i++)
		{
			res += 1 / (K[i] * (x - A[i]) * (x - A[i]) + C[i]);
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
	double A[14], B[14];
	//����������� �����
	double ox, oFuncVal;
	//Seed ��� ������ ������������ ������
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
	///������������� ������
	virtual int Initialize()
	{
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
		for (int i = 0; i < 14; i++)
		{
			res += A[i]* sin(2*M_PI*x*i) + B[i]*cos(2*M_PI*x*i) ;
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
	IProblem* problem = new TSHProblem();
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