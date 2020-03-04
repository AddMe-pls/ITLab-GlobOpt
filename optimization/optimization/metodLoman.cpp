#include "C:\Users\HP-PC\Desktop\2 семестр лабы иипр\ITLab\ITLab-GlobOpt\GlobOpt\classes.h"
#include "metodLoman.h"
#include <math.h>
#include <vector>

using namespace std;

void TPiyavskogoMethod::FirstIteration()
{
	pTask = new TTask();

	Trials[0].x = pTask.A;
	Trials[1].x = pTask.B;
	Trials[0].FuncValue = func(a_);
	Trials[0].IterationNumber = 1;
	Trials[1].FuncValue = func(b_);
	Trials[1].IterationNumber = 2;



}

double TPiyavskogoMethod::CalculateR(int p) //, double M ее вручную где то чтоли объявить?
{
	double R;
	if (p == 1)
		R= 0.5*M*(Trials[pTask.B].x - Trials[pTask.A].x) - (Trials[pTask.B].z + Trials[pTask.A].z) / 2; //добавить что за PTASK
	else
	R = 0.5*M*(Trials[p].x - Trials[p - 1].x) - (Trials[p].FuncValue + Trials[p - 1].FuncValue) / 2;

	return R;

}

void TPiyavskogoMethod::CalculateIterationPoint()
{



}


bool TPiyavskogoMethod::CheckStopCondition()//я бы написал если бы структуру передать можно было в параметрах
{
	if (TTrial. )


}

bool TPiyavskogoMethod::UpdateOptimumEstimation(const TTrial& trial)
{
	TTrial CurTrial;
	int t = 1;//тк имеем один интервал                                                             вероятно это все не в этой функции должно происходить    
	int T = 1;//номер лучшего
	do
	{
		double best_Character = CalculateR(1);
		for (int i = 1; i < t; i++)
		{
	
			if (CalculateR(i) >= best_Character)
			{
				best_Character = CalculateR(i);
				T = i;
			}
		}
		t++;//колич интервалов		
		CurTrial.x = 0.5*(Trials[T].x + Trials[T - 1].x) - (Trials[T].FuncValue - Trials[T - 1].FuncValue) / (2 * M); //это наверное  в CalculateIterationPoint
		CurTrial.FuncValue = func(CurTrial.x);
		CurTrial.IterationNumber;
		Trials.insert(Trials.begin() + T, CurTrial);
	} while (CheckStopCondition()); //tmp.k < MaxTrial_ && fabs(Trials[T].x - searchInfo[T - 1].x) > eps

}






double func(double x)
{
	return sin(x) + sin(10*x/3);
}
Trial checkInfo(double a_, double b_, int MaxTrial_, double eps_, double m_)
{
	int T=1;//хранится номер лучшего интервала
	Trial tmp;
	tmp.k = 2;//количество испытаний 
	double eps = eps_;//точность

	vector<Trial> searchInfo(MaxTrial_);// ;
	vector<double> R(MaxTrial_);//запись характеристик 
	
	double m = m_;
	searchInfo[0].x = a_;
	searchInfo[1].x = b_;
	searchInfo[0].z = func(a_);
	searchInfo[0].k = 1;
	searchInfo[1].z = func(b_);
	searchInfo[1].k = 2;

	int t = 1;//тк имеем один интервал
	
    double best_Character;

	R[1] = 0.5*m*(searchInfo[1].x - searchInfo[0].x) - (searchInfo[1].z + searchInfo[0].z) / 2;
	do
	{
		best_Character = R[1];
		for (int i = 1; i < t; i++)
		{
			
			R[i] = 0.5*m*(searchInfo[i].x - searchInfo[i - 1].x) - (searchInfo[i].z + searchInfo[i - 1].z) / 2;
			if (R[i] >= best_Character)
			{
				best_Character = R[i];
				T = i;
			}
		}
				t++;//колич интервалов		
				tmp.x = 0.5*(searchInfo[T].x + searchInfo[T - 1].x) - (searchInfo[T].z - searchInfo[T - 1].z) / (2 * m);  				
				tmp.z = func(tmp.x);
				tmp.k++;				
				 searchInfo.insert(searchInfo.begin() + T, tmp);	                                     	
	} while (tmp.k < MaxTrial_ && fabs(searchInfo[T].x - searchInfo[T - 1].x) > eps );
	
	return tmp;
}


