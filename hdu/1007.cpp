#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

#define MAXNUM 100000

typedef struct POINT_ {
	double x;
	double y;
}POINT;

POINT points[MAXNUM];

void init(void) {
	memset(points, 0, MAXNUM);
	return ;
}

bool smaller(const POINT& a, const POINT& b) {
	if (a.x > b.x)
		return false;
	return true;
}

double dist(const double x, const double y) {
	return sqrt(x*x+y*y)/2;
}

double findRadius(int l, int h) {
	double r = 0.0;
	double r1 = 0.0;
	double r2 = 0.0;
	double r3 = 0.0;
	int idx;
	
	if (h-l == 1) {
		return dist(points[l].x-points[h].x, points[l].y-points[h].y);
	}
	if (h-l == 2) {
		double tempr1, tempr2, tempr3;
		tempr1 = dist(points[l].x-points[l+1].x, points[l].y-points[l+1].y);
		tempr2 = dist(points[l].x-points[l+2].x, points[l].y-points[l+2].y);
		tempr3 = dist(points[l+2].x-points[l+1].x, points[l+2].y-points[l+1].y);
		if (r1 < r2) r = r1;
		else r = r2;
		if (r < r3) return r;
		else return r3;
	}
	
	idx = (l+h)/2;
	r1 = findRadius(0, idx);
	r2 = findRadius(idx, h);
	if (r1 < r2) r = r1;
	else r = r2;
	
	// combine the left and right element
	
	return r;
}

int main(int argc, char** argv) {
	int num;
	int i;
	double r;
	
	while (cin >> num && num) {
		// initialize
		init();
		i = 0;
		
		// read input
		while (i < num) {
			cin >> points[i++].x >> points[i++].y;
		}
		
		sort(points, points+num, smaller);
		r = findRadius(0, num);
		
		cout << r << endl;
	}
	
	return 0;
}
