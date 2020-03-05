#include "classes.h"
#include <iostream>

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

//������ �������� ���������� ������
int main(int argc, char * argv[])
{
	//��������� ��������� �� ������� ����� � ����������� ��� ��������� �� ����������� �����
	IProblem* problem = new TX2Problem();
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