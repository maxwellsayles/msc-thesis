#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

typedef uint64_t u64;

// convert anything to string
template<class T>
inline std::string to_string (T x)
{
        std::stringstream ss;
        std::string str;
        ss << x;
        ss >> str;
        return str;
}

// returns an int between min and max inclusive
inline int randint (int min, int max)
{
	return (random() % (max-min+1)) + min;
//	return (rand() % (max-min+1)) + min;
}

// returns the number of set bits in an integer
inline int countSetBits (u64 m)
{
	u64 c = 0;
	while (m)
	{
		if (m & 1) c++;
		m >>= 1;
	}
	return c;
}

// returns true if the bit is set
inline bool isBitSet (u64 m, int b)
{
	return (m & (1<<b)) != 0;
}

// returns the binary string of an int
string toBinaryString (u64 number) {
	u64 remainder;

	if (number <= 1)
		return to_string(number);

	remainder = number&1;
	return toBinaryString (number >> 1) + to_string(remainder);
}



// returns a string of the set bits
string setBitsToString (u64 m)
{
	string res;

	u64 c = 0;
	while (m)
	{
		if (m & 1)
		{
			res += to_string(c);
			if (m != 1) res += ", ";
		}
		c ++;
		m >>= 1;
	}
	
	return res;
}

// graph class with helper functions
// only supports graphs with at most 64 vertices
class Graph;
ostream& operator<< (ostream& os, const Graph& g);
class Graph
{
public:
	Graph (int vertexCount)
		: n (vertexCount)
	{
		memset(matrix, 0, 64*sizeof(u64));
	}
		
	Graph (const Graph& g)
		: n (g.n)
	{
		memcpy(matrix, g.matrix, 64*sizeof(u64));
	}
		
	~Graph()
	{
	}
		
	Graph& operator= (const Graph& g)
	{
		if (n != g.n)
			n = g.n;

		memcpy(matrix, g.matrix, 64*sizeof(u64));
		
		return *this;
	}
	
	
	// makes an edge between vertices u and v
	void setEdge (int u, int v)
	{
		matrix[v] |= 1<<u;
		matrix[u] |= 1<<v;
	}
		
	// removes an edge between vertices u and v
	void clearEdge (int u, int v)
	{
		matrix[v] &= ~(1<<u);
		matrix[u] &= ~(1<<v);
	}
		
	// returns true if there is an edge between these two vertices
	bool hasEdge (int u, int v) const
	{
		return isBitSet(matrix[u],v);
	}
		
	// clears all the edges incident to a vertex v
	void clearIncidentEdges (int v)
	{
		for (int i = 0;  i < n;  i ++)
		{
			matrix[v] &= ~(1<<i);
			matrix[i] &= ~(1<<v);
		}
	}
	
	// returns true if there are any edges in this graph
	bool hasEdges() const
	{	// any bit in the matrix set?
		for (int i = 0;  i < n;  i ++)
		{
			if (matrix[i] != 0) 
				return true;
		}
		return false;
	}
		
	// clear all the edges associated with the vertices in the set
	// if there exist no remaining edges, we have a vertex cover
	bool isVertexCover (int verts) const
	{
		Graph tmp(*this);

		int i = 0;
		while (verts)
		{
			if (verts & 1)
			{
				tmp.clearIncidentEdges (i);
			}
			verts >>= 1;
			i ++;
		}
		
		return !tmp.hasEdges();
	}
		
	
	// returns the number of edges incident to this vertex
	int vertexDegree(int v) const
	{
		return countSetBits(matrix[v]);
	}
	
	
	// returns the smallest degree of all vertices within a bit mask
	int minDegree (int mask = -1) const
	{
		int d = n+1;
		for (int v = 0;  v < n;  v ++)
		{
			if (isBitSet(mask, v))
			{
				int dv = vertexDegree(v);
				if ((dv > 0) && (dv < d))
				{
					d = dv;
				}
			}
		}
		return d;
	}
		
		
		
	// returns the highest degree of all vertices within a bit mask
	int maxDegree (int mask = -1) const
	{
		int d = 0;
		for (int v = 0;  v < n;  v ++)
		{
			if (isBitSet(mask, v))
			{
				int dv = vertexDegree(v);
				if (dv > d) 
					d = dv;
			}
		}
		return d;
	}
		
		
		
		
	// returns a bit packed set of the vertices that have the highest degree
	// only vertices from within the bit mask are tested
	int verticesWithMaxDegree (int mask = -1) const
	{
		int res = 0;
		int d = maxDegree (mask);
		
		for (int v = 0;  v < n;  v ++)
		{
			if (isBitSet (mask, v))
				if (vertexDegree(v) == d)
					res |= (1<<v);
		}
		
		return res;
	}


	// returns a bit packed set of the vertices that have the highest degree
	// only vertices from within the bit mask are tested
	int verticesWithMinDegree (int mask = -1) const
	{
		int res = 0;
		int d = minDegree (mask);
		
		for (int v = 0;  v < n;  v ++)
		{
			if (isBitSet (mask, v))
				if (vertexDegree(v) == d)
					res |= (1<<v);
		}
		
		return res;
	}
		
	int getVertexCount() const { return n; }
		
private:
	int n; // number of vertices
	u64 matrix[64];
};


ostream& operator<< (ostream& os, const Graph& g)
{
	int n = g.getVertexCount();
	for (int v = 0;  v < n;  v ++)
	{
		for (int u = 0;  u < n;  u ++)
		{
			os << (g.hasEdge(u,v) ? '1' : '0');
		}
		os << endl;
	}
	return os;
}


// finds a minimal vertex cover using an exhaustive search
int bruteForceVertexCover (const Graph& g)
{
	int n = g.getVertexCount();
	int s = n+1;
	int sc = 0;
	for (int c = 1;  c < (1<<n);  c ++)
	{
		int k = countSetBits(c);
		if (k < s)
		{
			if (g.isVertexCover(c))
			{
				sc = c;
				s = k;
			}
		}
	}
	return sc;
}


// finds a minimal vertex cover using my greedy algorithm
int greedyVertexCover (const Graph& g)
{
	int n = g.getVertexCount();
	int res = 0;
	Graph t(g);
	
	// any vertex that has an edge to itself must be included in the solution set
	for (int i = 0;  i < n;  i ++)
	{
		if (g.hasEdge(i,i))
		{
			//cout << "Forced Adding " << i << endl;
			res |= 1<<i;
			t.clearIncidentEdges (i);
		}
	}
	
	// greedily choose from all remaining vertices
	while (t.hasEdges())
	{
		// get the set of vertices with the highest degree
		int vmask = t.verticesWithMaxDegree();
		//cout << "Start" << endl;
		//cout << "vmask: " << toBinaryString(vmask) << endl;
		//cout << t << endl;
		
		// for each vertex v in the mask, get the set of edges incident to v
		Graph t2(t);
		for (int v1 = 0;  v1 < n;  v1 ++)
		{
			for (int v2 = 0;  v2 < n;  v2 ++)
			{
				if (!isBitSet(vmask, v1) && !isBitSet(vmask, v2))
					t2.clearEdge (v1, v2);
			}
		}
		//cout << t2 << endl;
		
		// for each vertex v1 != v2 in the mask,
		//   if v1 and v2 share an edge, remove the edge from the set of edges in v1 and v2
		for (int v1 = 0;  v1 < n;  v1 ++)
		{
			for (int v2 = 0;  v2 < n;  v2 ++)
			{
				if (isBitSet(vmask, v1) && isBitSet(vmask, v2))
				{	// both v1 and v2 are vertices in the mask
					if (v1 != v2)
					{	// and they are both different vertices
						t2.clearEdge(v1,v2);
					}
				}
			}
		}
		//cout << t2 << endl;
		
		// pick the vertex with the most unshared edges (breaking ties arbitrarily)
		/*
		int vmask2 = vmask;
		if (t2.hasEdges())
		{
			
			int m = t2.verticesWithMaxDegree();
			cout << "mask: " << toBinaryString(m) << endl;
			vmask2 &= t2.verticesWithMaxDegree();
		}
		*/
		int vmask2 = t2.verticesWithMaxDegree (vmask);
		//cout << g << endl;
		//cout << t2 << endl;
		//cout << "vmask: " << toBinaryString(vmask) << endl;
		//cout << "vmask2: " << toBinaryString(vmask2) << endl;
		int v = 0;
		while (!isBitSet(vmask2,v))
			v ++;
		
		
		
		
		// remove v
		//cout << "Adding " << v << endl;
		t.clearIncidentEdges (v);
		res |= 1<<v;
		
		//string s;
		//cin >> s;
		//cout << endl;
	}
	
	return res;
}
	


// program entry
int main(int argc, char** argv)
{
	srandom((unsigned)time(0));
//	srand((unsigned)time(0));
	
	
	
	while (true)
	{
		int n = 19;
		Graph g(n);
	
		/*
		int e = randint(1, n*n/2);
		for (int i = 0;  i < e;  i ++)
		{
			int u = randint(0, n-1);
			int v = randint(0, n-1);
			g.setEdge(u,v);
		}
		*/
		
		
		/*
		// double-u
		g.setEdge (0, 4);
		g.setEdge (1, 4);
		g.setEdge (1, 3);
		g.setEdge (2, 3);
		*/
		
		/*
		// fish
		g.setEdge (0, 1);
		g.setEdge (0, 3);
		g.setEdge (1, 2);
		g.setEdge (1, 4);
		g.setEdge (2, 4);
		g.setEdge (4, 4);
		*/

		/*		
		// semi-octagon
		g.setEdge (0, 1);
		g.setEdge (0, 3);
		g.setEdge (0, 4);
		g.setEdge (1, 2);
		g.setEdge (2, 3);
		g.setEdge (2, 4);
		g.setEdge (3, 4);
		*/
		
		// small cactus
		g.setEdge (0, 1);
		g.setEdge (0, 2);
		g.setEdge (1, 3);
		g.setEdge (2, 3);
		g.setEdge (4, 5);
		g.setEdge (4, 6);
		g.setEdge (5, 7);
		g.setEdge (6, 7);
		g.setEdge (8, 9);
		g.setEdge (8, 10);
		g.setEdge (9, 11);
		g.setEdge (10, 11);
		g.setEdge (12, 13);
		g.setEdge (12, 14);
		g.setEdge (13, 15);
		g.setEdge (14, 15);
		g.setEdge (3, 16);
		g.setEdge (7, 16);
		g.setEdge (11, 17);
		g.setEdge (15, 17);
		g.setEdge (16, 18);
		g.setEdge (17, 18);


		int gvc = greedyVertexCover (g);
		cout << "GVC: " << setBitsToString(gvc) << endl;
		
		int bfvc = bruteForceVertexCover (g);
		cout << "BFVC: " << setBitsToString(bfvc) << endl;
		
		cout << endl;
		
		if (countSetBits(gvc) != countSetBits(bfvc))
		{
			cout << "FOUND A COUNTER EXAMPLE" << endl;
			cout << g << endl;
			return 1;
		}

	}
	
	return 0;
}


