#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <iomanip> 
#include <sstream>

using namespace std;

class Trial{
public:
	double x;
	double y;
	Trial() :x(0.0), y(0.0){}
	Trial(double a) {
		x = a;
		y = a * a;
	}
	Trial(double a, double b, int c) :x(a), y(b) {}
	Trial(const Trial &v) {
		x = v.x;
		y = v.y;
	}
	Trial& operator=(const Trial& v) {
		if (this == &v) {
			return *this;
		}
		x = v.x;
		y = v.y;
		return *this;
	}
	friend ostream& operator<<(ostream &out, const Trial &v);
};

ostream& operator<<(ostream &out, const Trial &v) {
		out << " x = " << v.x << "  y = " << v.y << endl;
		return out;
	}

double Function(double x) {
	return x * x;
}

// вычисл€ет характеристику M интервала двух точек типа 
double M(Trial a, Trial b) {
	double M = (b.y - a.y) / (b.x - a.x);
	if (M == 0.0) { M = 1.0; }
	if (M < 0) { M = -M; }
	return 2.7 * M;
}

// вычисл€ет характеристику R интервала, принимет две точки класса поинт и их характеристику ћ
double R(Trial a, Trial b, double m) {
	double r = m * (b.x - a.x) + (((b.y - a.y) * (b.y - a.y)) / (m * (b.x - a.x))) - 2 * (b.y - a.y);
	return r;
}
double NX(Trial a, Trial b, double m) {
	double NX = (((b.x + a.x) / 2) - ((b.y - a.y) / m));
	return NX;
}

Trial CL(double a) {
	return Trial(a);
}

bool Stop(double number) {
	std::stringstream ss;
	ss << std::setprecision(15) << number;
	std::string strNum = ss.str();
	size_t pos = strNum.find('.');
	if (pos != strNum.npos)
		std::cout << "Number of digits after comma: " << strNum.size() - 1 - pos << std::endl;
	int Flag = strNum.size() - 1 - pos;
	if (Flag > 15) { return false; }
	else { return true; }
}

int main() {

	vector<double> ArM(100);
	ArM.clear();
	vector<double> ArR(100);
	ArR.clear();
	vector<Trial> A(100);
	
	A.clear();
	double a, b;
	cout << "¬ведите отрезок на котором хотите найти минимум" << '\n';
	cin >> a >> b;//отрезок на котором хотим найти минимум функции
	A.push_back(Trial(a));
	A.push_back(Trial(b));

	
	ArM.push_back(M(A[0], A[1]));
	ArR.push_back(R(A[0], A[1], ArM[0]));	
	Trial c(NX(A[0], A[1], ArM[0]));
	A.insert((A.begin() + 1), c);
	int it = 0;
	double Epsilon = 2;
	while( it < 1000 && Epsilon > 0.002) {
		it++;
		int ArMsize = ArM.size();
		ArM.clear();


		// нахождение максимума из ћ
		for (int im = 0; im < ArMsize + 1; im++) {
			ArM.push_back(M(A[im], A[im + 1]));//вычисление ћ
		}
		double MaxM = ArM[0];
		int indexM = 0;
		for (int i = 1; i < ArM.size(); i++) {
			if (ArM[i] > MaxM) {
				MaxM = ArM[i];
				indexM = i;
			}
		}
		

		//Ќахождение R
		int ArRsize = ArR.size();
		ArR.clear();
		for (int ir = 0; ir < ArRsize + 1; ir++) {
			ArR.push_back(R(A[ir], A[ir + 1], MaxM));//вычисление R
		}
		double MaxR = ArR[0];
		int indexR = 0;
		for (int i = 1; i < ArR.size(); i++) {
			if (ArR[i] > MaxR) {
				MaxR = ArR[i];
				indexR = i;
			}
		}

		//Trial c(NX(A[indexR], A[indexR + 1], MaxM));
		A.insert((A.begin() + (indexR+1)), CL(NX(A[indexR], A[indexR + 1], MaxM)));
		
		Epsilon = A[1].x - A[0].x;
		for (int i = 2; i < A.size(); i++) {
			if ((A[i].x - A[i - 1].x) < Epsilon)
				Epsilon = A[i].x - A[i - 1].x;
		}
	}
	Trial Best = A[0];
	for (int i = 1; i < A.size(); i++) {
		if (A[i].y < Best.y) {
			Best = A[i];
		}
	}
	cout << " Best Point = " << Best << " it = " << it << endl;

	system("pause");

	return 0;
}