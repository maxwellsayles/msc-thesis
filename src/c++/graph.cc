#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// generate a path of length t, given a permutation on the number of states n
void make_path (long p, int n, int t, vector<int>& path)
{
	path.clear();
	path.reserve(t+1);
	
	while (t >= 0)
	{
		path.push_back (p % n);
		p /= n;
		t--;
	}
}


// convert a path to a string
string path_to_string (const vector<int>& path)
{
	ostringstream o(ostringstream::out);
	o << '[';
	for (int i = 0;  i < path.size(); )
	{
		o << path[i];
		i ++;
		if (i != path.size())
		{
			o << ", ";
		}
	}
	o << ']';
	return o.str();
}


// counts the number of hits to each node, excluding the final step
void hit_count (const vector<int>& path, int* hits, int n)
{
	for (int i = 0;  i < n;  i ++)
	{
		hits[i] = 0;
	}
	
	for (int i = 0;  i < path.size()-1;  i ++)
	{
		hits[path[i]] ++;
	}
}


// calculates the distance from the expected number of hits squared
void path_variance (const vector<int>& path, int n, double* expected, double* variance)
{
	int hits[n];
	hit_count (path, hits, n);
	
	for (int i = 0;  i < n;  i ++)
	{	
		double diff = hits[i] - expected[i];
		variance[i] = diff*diff;
	}
}


// calculate the probability of taking a given path
double path_prob (const vector<int>& path, const double* P, const double* w, int n)
{
	int start = path[0];
	double prob = w[start];
	
	int i = 1;
	while (i < path.size())
	{
		int next = path[i];
		
		prob *= P[start*n + next];
		
		start = next;
		i ++;
	}
	
	return prob;
}


void calc_variance (double* P, double* w, int n, int t)
{
	long pend = (long)pow((double)n, (double)t+1);
	double variance_sum[n];
	double expected[n];
	for (int i = 0;  i < n;  i ++)
	{
		variance_sum[i] = 0;
		expected[i] = t * w[i];
	}

	double prob_sum = 0;
	for (long p = 0;  p < pend;  p ++)
	{
		vector<int> path;
		make_path (p, n, t, path);
		double prob = path_prob (path, P, w, n);
		prob_sum += prob;

		if (prob > 0)
		{
			double variance[n];
			path_variance (path, n, expected, variance);
			for (int i = 0;  i < n;  i ++)
			{
				variance_sum[i] += variance[i] * prob;
			}
		}
	}
	
	cout << '[';
	for (int i = 0;  i < n-1;  i ++)
	{
		cout << variance_sum[i] << ", ";
	}
	cout << variance_sum[n-1] << ']' << endl;
}


int main(int argc, char** argv)
{
	double P[] = {
		0, 0.5, 0.5, 0,
		0.5, 0, 0.5, 0,
		1.0/3, 1.0/3, 0, 1.0/3,
		0, 0, 1, 0
		};
	
	double w[] = { 0.25, 0.25, 0.375, 0.125 };

	int n = 4;
	
	int t = 2;
	while (1)
	{
		cout << "t=" << t << ' ';
		calc_variance (P, w, n, t);
		t ++;
	}
	
	return 0;
}

