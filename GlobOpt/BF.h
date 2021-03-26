#pragma once
#include "classes.h"
#include <vector>
#include <iostream>
#include <cmath>
class BF : public IMethod
{
protected:
	double CalculateR(int p);
public:
	BF(TTask* Task, int count, double _eps);
	void FirstIteration();
	void DoIteration();
	void Solve();
	void CalculateIterationPoint();
};

BF::BF(TTask* Task, int count, double _eps)
{
	pTask = Task;
	IterationCount = count;
	eps = _eps;
	Trials.reserve(IterationCount);
}

double BF::CalculateR(int p) 
{
	return Trials[p].x-Trials[p-1].x;
}

void BF::FirstIteration()
{
	double xA = pTask->GetA();
	double xB = pTask->GetB();
	double yA = pTask->CalculateFunction(xA);
	double yB = pTask->CalculateFunction(xB);
	/*Trials[0].x = xA;
	Trials[1].x = xB;
	Trials[0].FuncValue = yA;
	Trials[1].FuncValue = yB;
	Trials[0].IterationNumber = 1;
	Trials[1].IterationNumber = 2;*/
	Trials[0] = { xA, yA, 1 };
	Trials[1] = { xB, yB, 2 };
	CurTrial = { xB, yB, 2 };
	BestTrial = { xB, yB, 2 };
	t = 1;
	IterationCount = 1;
}

void BF::DoIteration()
{
	double MaxR = -100000;
	InitIteration();
	CalculateIterationPoint();
	CalculateFunction();
	RenewSearchData();
	for (int i = 1; i < Trials.size(); i++)
	{
		double CurrR = CalculateR(i);
		if (CurrR > MaxR) {
			MaxR = CurrR;
			t = i;
		}
	}
	FinalizeIteration();
}

void BF::Solve()
{
	FirstIteration();
	while (CheckStopCondition() != true)
		DoIteration();
}

void BF :: CalculateIterationPoint()
{
	CurTrial.x = 0.5 * (Trials[t - 1].x - Trials[t].x);
}
