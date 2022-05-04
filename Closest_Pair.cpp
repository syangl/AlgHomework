#include <iostream>
#include<algorithm>
#include<vector>
#include<utility>
#include<iomanip>
using namespace std;


bool cmp_y(pair<int, int>a, pair<int, int>b)
{
	return a.second < b.second;
}

bool cmp_x(pair<int, int>a, pair<int, int>b)
{
	return a.first < b.first;
}

float square(pair<float, float> p1, pair<float, float> p2) {
    return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}

float Closest_Pair(vector<pair<float,float>> P) {//P is in order
    //init min
	float  min_res = 1e9;
	if (P.size() <= 3) 
	{
		min_res = square(P[0], P[1]);
		if (P.size() == 3) 
		{
			if (square(P[0], P[2]) < min_res) 
			{
				min_res = square(P[0], P[2]);
			}
			else if (square(P[1], P[2]) < min_res) 
			{
				min_res = square(P[1], P[2]);
			}
		}
		return min_res;
    }

	//create Q, R
	vector<pair<float, float>> Q, R;
	int mid = (P.size() % 2 == 0) ? (P.size() / 2) : (P.size() / 2 + 1);
	int i = 0;
	while (i < P.size()) 
	{
		if (i < mid) {
			Q.push_back(P[i]);
		}
		else {
			R.push_back(P[i]);
		}
		i++;
	}
	//Q,R is in order
	min_res = min(Closest_Pair(Q), Closest_Pair(R));

	//create S
	float mid_x = (Q[Q.size() - 1].first+R[0].first)/2;
	vector<pair<float, float>> S;
	int j = 0;
	while (j < P.size())
	{
		if ((P[j].first - mid_x) <= min_res && (mid_x - P[j].first) <= min_res) 
		{
			S.push_back(P[j]);
		}
		j++;
	}

	//find min
	sort(S.begin(), S.end(), cmp_y);
	int k = 0;
	while (k < S.size())
	{
		for (int i = 1; i <= 11; i++) {
			if (k + i < S.size())
			{
				min_res = min(min_res, square(S[k], S[k + i]));
			}
		}
		k++;
	}

	return min_res;
}

int main()
{
	int n;
	cin >> n;
	vector<pair<float, float>> P;
	pair<float, float> point;
	for (int i = 0; i < n; i++) {
		cin >> point.first >> point.second;
		P.push_back(point);
	}
    
	sort(P.begin(), P.end(), cmp_x);

	float min_res = Closest_Pair(P);

	cout << fixed << setprecision(2)  << min_res;
	
	return 0;
}