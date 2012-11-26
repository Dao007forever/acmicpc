#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 3333;
const int inf = 0x3f3f3f3f;
struct SAP
{
	int cap[MAXN][MAXN], flow[MAXN][MAXN];
	int n;
	int h[MAXN], vh[MAXN], source, sink;
	void init(int n)
	{
		this->n = n;
		memset(cap, 0, sizeof(cap));
	}
	void addCap(int i, int j, int val)
	{
		cap[i][j] += val;
	}
	int sap(const int idx, const int maxCap)
	{
		if (idx == sink)
			return maxCap;
		int l = maxCap, d, minH = n;
		for (int i = 0; i < n; i++)
		{
			if (cap[idx][i] - flow[idx][i] > 0)
			{
				if (h[idx] == h[i] + 1)
				{
					d = sap(i, min(l, cap[idx][i] - flow[idx][i]));
					flow[idx][i] += d;
					flow[i][idx] -= d;
					l -= d;
					if (h[source] == n || l == 0) return maxCap - l;
				}
				minH = min(minH, h[i] + 1);
			}
		}
		if (l == maxCap)
		{
			vh[h[idx]]--;
			vh[minH]++;
			if (vh[h[idx]] == 0)
				h[source] = n;
			h[idx] = minH;
		}
		return maxCap - l;
	}
	int solve(int source, int sink)
	{
		if (source == sink) return inf;
		this->sink = sink;
		this->source = source;
		memset(flow, 0, sizeof(flow));
		memset(h, 0, sizeof(h));
		memset(vh, 0, sizeof(vh));
		int ans = 0;
		while (h[source] != n)
			ans += sap(source, inf);
		return ans;
	}
}sap;
int main()
{
	freopen("a", "r", stdin);
	map<string, int> clubs, parties;
	vector<string> persons;
	vector<int> p;
	vector<string> clubnames;
	vector<int> members[MAXN];
	int nclubs, nparties, Test;
	scanf("%d\n\n", &Test);
	while (Test--)
	{
		nclubs = nparties = 0;
		clubs.clear(); 
		parties.clear(); 
		persons.clear();
		clubnames.clear(); 
		p.clear(); 
		members[0].clear();
		
		string s;
		while (getline(cin, s) && s.size() > 1)
		{
			string name, party, club;
			istringstream ss(s);
			ss >> name >> party;
			persons.push_back(name);

			if (parties.find(party) == parties.end())
			{
				parties[party] = nparties++;
			}
			p.push_back(parties[party]);
			
			while (ss >> club)
			{
				if (clubs.find(club) == clubs.end())
				{
					members[nclubs].clear();
					clubs[club] = nclubs++;
					clubnames.push_back(club);
				}
				members[clubs[club]].push_back(persons.size() - 1);
			}
		}
		int npersons = persons.size();
		int source = 0, sink = nclubs + npersons + nparties + 1;
		sap.init(sink + 1);
		for (int i = 0; i < nclubs; i++)
		{
			sap.addCap(source, i + 1, 1);
			//cout << "source " << i + 1 << " 1" << endl;
		}
		for (int i = 0; i < nclubs; i++)
			for (int j = 0; j < members[i].size(); j++)
			{
				sap.addCap(i + 1, nclubs + members[i][j] + 1, 1);
				//cout << i + 1 << " " << nclubs + members[i][j] + 1 << " 1" << endl;
			}
		for (int i = 0; i < npersons; i++)
		{
			sap.addCap(nclubs + i + 1, nclubs + npersons + p[i] + 1, 1);
			//cout << nclubs + i + 1 << " " << nclubs + npersons + p[i] + 1 << " 1" << endl;
		}
		for (int i = 0; i < nparties; i++)
		{
			sap.addCap(nclubs + npersons + i + 1, sink, (nclubs + 1) / 2 - 1);
			//cout << nclubs + npersons + i + 1 << " sink " << (nclubs + 1) / 2 - 1 << endl;
		}
		int res = sap.solve(source, sink);
		if (res != nclubs) cout << "Impossible." << endl;
		else
		{
			for (int i = 0; i < nclubs; i++)
				for (int j = 0; j < npersons; j++)
					if (sap.flow[i + 1][nclubs + j + 1] == 1)
						cout << persons[j] << " " << clubnames[i] << endl;
		}
		if (Test) cout << endl;
	}
	return 0;
}
