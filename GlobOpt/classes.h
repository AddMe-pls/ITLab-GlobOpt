#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

/**
������� �����-���������, �� �������� ����������� ������, ����������� ������ �����������.

� ������ #TIProblem ������� ��������� �������, ������� ������ ���� ����������� � ����������� ������� � ��������.
*/
class IProblem
{
public:
	
	/// ��� ������, ������������, ���� �������� ��������� �������
	static const int OK = 0;
	/** ��� ������, ������������ �������� #GetOptimumValue � #GetOptimumPoint,
	���� ��������������� ��������� ������ �� ����������,
	*/
	static const int UNDEFINED = -1;
	/// ��� ������, ������������, ���� �������� �� ���������
	static const int ERROR = -2;

	///������������� ������
	virtual int Initialize() = 0;

	/// ����� ���������� ������� ������� ������
	virtual void GetBounds(double& lower, double& upper)=0;
	/** ����� ���������� �������� ������� � ����� ����������� ��������
	\param[out] value ����������� ��������
	\return ��� ������ (#OK ��� #UNDEFINED)
	*/
	virtual int GetOptimumValue(double& value) const
	{
		return IProblem::UNDEFINED;
	}
	/** ����� ���������� ���������� ����� ����������� �������� ������� �������
	\param[out] y �����, � ������� ����������� ����������� ��������
	\return ��� ������ (#OK ��� #UNDEFINED)
	*/
	virtual int GetOptimumPoint(double& y) const = 0;

	/** �����, ����������� ������� ������

	\param[in] y �����, � ������� ���������� ��������� ��������
	\return �������� �������
	*/
	virtual double CalculateFunction(const double y) const = 0;

	///����������
	virtual ~IProblem() {}
};

// ------------------------------------------------------------------------------------------------
struct TTrial
{
	/// ����� �� �������
	double  x;
	/// �������� ������� ������
	double FuncValue;
	/// ����� ��������
	int IterationNumber;
};

// ------------------------------------------------------------------------------------------------
class TTask
{
protected:
	/// ����� ������� ������� ������
	double     A;
	/// ������ ������� ������� ������
	double     B;
	/// ��������� �� ���� ������ �����������
	IProblem*  pProblem;
	/// ����������� �������� ������� ������� (����������, ���� �������� �� ������)
	double     OptimumValue;
	/// ���������� ����������� �������� ������� ������� (����������, ���� ��������)
	double     OptimumPoint;
	/// true, ���� � ������ �������� ����������� �������� ��������
	bool       IsOptimumValueDefined;
	/// true, ���� � ������ �������� ����� ����������� ��������
	bool       IsOptimumPointDefined;

public:
	TTask(IProblem* _problem)
	{
		pProblem = _problem;
		pProblem->GetBounds(A, B);
		if (pProblem->GetOptimumPoint(OptimumPoint) == IProblem::OK)
		{
			IsOptimumPointDefined = true;
		}
		if (pProblem->GetOptimumValue(OptimumValue) == IProblem::OK)
		{
			IsOptimumValueDefined = true;
		}

	}
	virtual ~TTask()
	{

	}

	/// ���������� ����� ������� ������� ������
	const double GetA() const { return A; }
	/// ���������� ������ ������� ������� ������
	const double GetB() const { return B; }
	/// ���������� ������� ��������� �������� ����������� ��������
	double GetOptimumValue() const { return OptimumValue; }
	/// ���������� ������� ��������� ���������� ����� ����������� ��������
	const double GetOptimumPoint()
	{ 
		pProblem->GetOptimumPoint(OptimumPoint);
		return OptimumPoint; 
	}
	/// ���������� �������� �� ��� ������ �������� ����������� ��������
	bool GetIsOptimumValueDefined() const { return IsOptimumValueDefined; }
	/// ���������� �������� �� ��� ������ ���������� ����������� ��������
	bool GetIsOptimumPointDefined() const { return IsOptimumPointDefined; }
	/// ���������� ������� ������
	IProblem* getProblem() { return pProblem; }
	/// ��������� �������� �������
	virtual double CalculateFunction(const double y)
	{
		return pProblem->CalculateFunction(y);
	}
};


/**
��������� ������������������� ��������� ���������� �����������.

� ������ #IMethod ��������� �������� �������, ������������ ������ ������������������� ���������.
*/
class IMethod
{
protected:
	///��������� �� �������� ������
	TTask *pTask;
	///
	std::vector<TTrial> Trials;

	TTrial CurTrial;

	TTrial BestTrial;

	int t;

	double eps;

	bool recalc;

	int IterationCount;

	/** ���������� �������������� ���������

	\param[in] p ��������� �� ��������, �������������� �������� ���� ���������
	\return �������������� ���������
	*/
	virtual double CalculateR(int p) = 0;

	/** ���������� ������� ������ ��������

	���� ���������� ����� ����� ������� ������ ��������, �� ��� ������ ����������� � ����������� ���� #recalc.
	\param[in] trial �����, ������� ���������� �������� � ������� ���������
	\return true, ���� ������� �������, ����� false
	*/
	virtual bool UpdateOptimumEstimation(const TTrial& trial);

	/// ��������� ������ �� ����� � ����������� ����������� ��������
	virtual bool CheckOptimumPoint(const TTrial& trial);

public:

	/** ������� ��������� ������ �������� ������
	*/
	virtual void FirstIteration() = 0;
	/** ������� ��������� ������� �������� ������
	*/
	virtual void DoIteration() = 0;

	/** ������� ��������� ������� ������� ������
	*/
	virtual void Solve() = 0;

	/** ������� ���������� � ������ ���������� ��������
	*/
	virtual void InitIteration();
	/** ���������� ����� ��������� ��������	

	��������� ������������ � CurTrial
	*/
	virtual void CalculateIterationPoint() = 0;
	/** �������� ���������� �������� ��������� ������

	����� ���������� ������ � ��������� �������:
	- ����� ��������� ��������� ����������� ���������� ��������
	- ���� �������� ���� ������ � �������� �������� \f$ x_t - x_{t-1} < \epsilon \f$
	- ���� �������� ����� ����� � �������� �������� \f$ \| y^k - y^\ast \| < \epsilon \f$

	\return ������, ���� �������� ��������� ��������; ���� - � ��������� ������.
	*/
	virtual bool CheckStopCondition();

	/** ���������� ������� ������

	���������� ��������� � ����� �� CurTrial, ���������	������������ ���� ��
	*/
	virtual void CalculateFunction();
	/** ���������� ��������� ����������
	*/
	virtual void RenewSearchData();
	/** ������� ������� �������� ��������

	\return ������, ���� ������� ���������; ���� - � ��������� ������
	*/
	virtual bool EstimateOptimum();
	/** ������� ���������� � ����� ���������� ��������
	*/
	virtual void FinalizeIteration();
	/** �������� ����� ���������

	\return ����� ���������
	*/
	virtual int GetIterationCount();
	/** �������� ������� ������ ��������

	\return ���������, ��������������� �������� ��������
	*/
	virtual TTrial GetOptimEstimation();
	/** �������� ������� ���������

	\return ������� ���������
	*/
	virtual TTrial GetCurTrial();
	/** ���������� ������� ������� ������
	*/
	virtual void SetBounds();
	/**���� ����������

	������� ���������� ����� ����� ���������, ����������� ��� ������� ������� ������
	\return ����� ����� ���������
	*/
	virtual int GetNumberOfTrials();
	///�������� ����� �������� � ��������� ��������
	virtual int GetBestTrialIteration();
	/**������� ���������� ����� ��������� � ����

	\param[in] fileName ��� �����, � ������� ����� �������� �����
	*/
	virtual void PrintPoints(const std::string& fileName);

	/// ���������� ����������� ��������
	virtual double GetAchievedAccuracy();
};

bool IMethod::UpdateOptimumEstimation(const TTrial& trial)
{
	if (trial.FuncValue < BestTrial.FuncValue)
	{
		BestTrial = trial;
		recalc = true;
		return true;
	}
	else return false;
}

bool IMethod:: CheckOptimumPoint(const TTrial& trial)
{
	if (trial.x + eps >= pTask->GetOptimumPoint() && pTask->GetOptimumPoint() >= trial.x - eps)
		return true;
	else
	    return false;
}

void IMethod:: InitIteration()
{
	IterationCount++;
	recalc = false;
}

bool IMethod::CheckStopCondition()
{
	if (fabs(Trials[t].x - Trials[t - 1].x) <= eps * (pTask->GetB() - pTask->GetA()))
		return true;
	else
		return false;
}

void IMethod::CalculateFunction()
{
	CurTrial.FuncValue = pTask->CalculateFunction(CurTrial.x);
}

void IMethod::RenewSearchData()
{
	//std::vector <int>::iterator iter;
	//iter = Trials.begin() + t;
	Trials.insert(Trials.begin()+t, CurTrial); 
}

bool IMethod::EstimateOptimum()
{
	return recalc;
}

void IMethod:: FinalizeIteration()
{
	UpdateOptimumEstimation(CurTrial);
}

int IMethod::GetIterationCount()
{
	return IterationCount;
}

TTrial IMethod::GetOptimEstimation()
{
	return BestTrial;
}

TTrial IMethod::GetCurTrial()
{
	return CurTrial;
}

void IMethod::SetBounds()
{

}

int IMethod::GetNumberOfTrials()
{
	return Trials.size();
}

int IMethod::GetBestTrialIteration()
{
	return BestTrial.IterationNumber;
}

double IMethod::GetAchievedAccuracy()
{
	return fabs(Trials[t].x - Trials[t - 1].x);
}

void IMethod:: PrintPoints(const std::string& fileName)
{

}