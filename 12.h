
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
#include <cstdlib>
using namespace std;

char buffer[100];
string str;
int tmp;

vector<tuple<int, int, int>> vectTuples;

bool TuplesCompare(const tuple<int, int, int> &lhs, const tuple<int, int, int> &rhs)
{
	return get<2>(lhs) < get<2>(rhs);
}

class DSU
{
private:
public:
	vector<int> p, rank;
	bool victory = true;
	DSU(int N)
	{
		for (int i = 0; i < N; i++)
		{
			p.push_back(i + 1);
			rank.push_back(0);
		}
	}
	int find(int x)
	{
		if (x == 0) return -1;
		return (x == p[x - 1] ? x : p[x - 1] = find(p[x - 1]));
	}

	void unite(int x, int y)
	{
		if ((x = find(x)) == (y = find(y)))
		{
			victory = false;
			return;
		}

		if (rank[x - 1] <  rank[y - 1])
			p[x - 1] = y;
		else
			p[y - 1] = x;

		if (rank[x - 1] == rank[y - 1])
			++rank[x - 1];
	}
};

class Graph
{
	int indicator, vertexAmount, edgeAmount;
	bool isOriented, w;
	vector<vector<pair<int, int>>> list;
	vector<vector<tuple<int, int, int>>> listTuples;
	vector<pair<int, int>> vectorPairs;
	vector<tuple<int, int, int>> vectTuples;
	vector<vector<int>> matrix;

public:
	Graph(int N = 1)
	{
		vertexAmount = N;
	}
	void readGraph(string fileName)
	{
		ifstream input(fileName);
		input >> fill;
		switch (fill[0])
		{
		case 'C':
		{
			indicator = 1;
			getline(input, str);
			vertexAmount = str[1] - '0';
			for (int j = 2; j < str.length(); j++)
				vertexAmount = vertexAmount * 10 + (str[j] - '0');
			break;
		}
		case 'L':
		{
			indicator = 2;
			getline(input, str);
			vertexAmount = str[1] - '0';
			for (int j = 2; j < str.length(); j++)
				vertexAmount = vertexAmount * 10 + (str[j] - '0');
			break;
		}
		case 'E':
		{
			indicator = 3;
			getline(input, str);
			vertexAmount = str[1] - '0';
			int i = 2;
			while (str[i] != ' ')
			{
				vertexAmount = vertexAmount * 10 + (str[i] - '0');
				i++;
			}
			i++;
			edgeAmount = str[i] - '0';
			i++;
			while (i < str.length())
			{
				edgeAmount = edgeAmount * 10 + (str[i] - '0');
				i++;
			}
			break;
		}
		}
		input >> fill;
		if (fill[0] == '0') isOriented = false; else isOriented = true;
		input >> fill;
		if (fill[0] == '0') w = false; else w = true;

		if (indicator == 1)
		{
			getline(input, str);
			int linenum = 0;
			while (getline(input, str))
			{
				matrix.push_back(vector<int>());
				tmp = str[0] - '0';
				for (int i = 1; i < str.length(); i++)
					if (str[i] != ' ')
					{
						tmp *= 10; tmp += str[i] - '0';
					}
					else
					{
						matrix[linenum].push_back(tmp);
						tmp = str[i + 1] - '0';
						i++;
					}
				matrix[linenum].push_back(tmp);
				linenum++;
			}
		}
		if (indicator == 2)
		{
			if (!w)
			{
				getline(input, str);
				int lineNum = 0;
				while (getline(input, str))
				{
					list.push_back(vector<pair<int, int>>());
					tmp = str[0] - '0';
					for (int i = 1; i < str.length(); i++)
						if (str[i] != ' ')
						{
							tmp *= 10; tmp += str[i] - '0';
						}
						else
						{
							list[lineNum].push_back(make_pair(lineNum + 1, tmp));
							tmp = str[i + 1] - '0';
							i++;
						}
					list[lineNum].push_back(make_pair(lineNum + 1, tmp));
					lineNum++;
				}
			}
			else
			{
				int tmp2;
				getline(input, str);
				int numLine = 0;
				while (getline(input, str))
				{
					listTuples.push_back(vector<tuple<int, int, int>>());
					tmp = str[0] - '0';
					for (int i = 1; i < str.length(); i++)
						if (str[i] != ' ')
						{
							if (str[i] != ',')
							{
								tmp *= 10;
								tmp += str[i] - '0';
							}
							else
							{
								tmp2 = tmp;
								tmp = str[i + 1] - '0';
								i++;
								continue;
							}
						}
						else
						{
							listTuples[numLine].push_back(make_tuple(numLine + 1, tmp2, tmp));
							tmp = str[i + 1] - '0';
							i++;
						}
					listTuples[numLine].push_back(make_tuple(numLine + 1, tmp2, tmp));
					numLine++;
				}
			}
		}

		if (indicator == 3)
		{
			if (!w)
			{
				getline(input, str);
				int linenum = 0;
				while (getline(input, str))
				{
					vectorPairs.push_back(pair<int, int>());
					vectorPairs[linenum].first = str[0] - '0';
					int i = 1;
					while (str[i] != ' ')
					{
						vectorPairs[linenum].first = vectorPairs[linenum].first * 10 + str[i] - '0';
						i++;
					}
					i++;
					vectorPairs[linenum].second = str[i] - '0';
					i++;
					while (i < str.length())
					{
						vectorPairs[linenum].second = vectorPairs[linenum].second * 10 + str[i] - '0';
						i++;
					}
					linenum++;
				}
			}
			else
			{
				getline(input, str);
				int linenum = 0;
				while (getline(input, str))
				{
					vectTuples.push_back(tuple<int, int, int>());
					get<0>(vectTuples[linenum]) = str[0] - '0';
					int i = 1;
					while (str[i] != ' ')
					{
						get<0>(vectTuples[linenum]) = get<0>(vectTuples[linenum]) * 10 + str[i] - '0';
						i++;
					}
					i++;
					get<1>(vectTuples[linenum]) = str[i] - '0';
					i++;
					while (str[i] != ' ')
					{
						get<1>(vectTuples[linenum]) = get<1>(vectTuples[linenum]) * 10 + str[i] - '0';
						i++;
					}
					i++;
					get<2>(vectTuples[linenum]) = str[i] - '0';
					i++;
					while (i < str.length())
					{
						get<2>(vectTuples[linenum]) = get<2>(vectTuples[linenum]) * 10 + str[i] - '0';
						i++;
					}
					linenum++;
				}
			}
		}
	}
	void addEdge(int from, int to, int weight = 1)
	{
		if (indicator == 1)
			matrix[from - 1][to - 1] = weight;
		if (indicator == 2)
		{
			if (!w)
			{
				list[from - 1].push_back(make_pair(from, to));
				if (!isOriented)
					list[to - 1].push_back(make_pair(to, from));
			}
			else
			{
				listTuples[from - 1].push_back(make_tuple(from, to, weight));
				if (!isOriented)
					listTuples[to - 1].push_back(make_tuple(to, from, weight));
			}
		}
		if (indicator == 3)
		{
			if (!w)
				vectorPairs.push_back(make_pair(from, to));
			else
				vectTuples.push_back(tuple<int, int, int>(from, to, weight));
		}
	}
	void writeGraph(string fileName)
	{
		ofstream output(fileName);
		if (indicator == 1)
		{
			output << "C" << ' ' << vertexAmount << endl;
			isOriented ? output << 1 : output << 0;
			output << ' ';
			w ? output << 1 : output << 0;
			output << endl;
			for (int i = 0; i < matrix.size(); i++)
			{
				output << matrix[i][0];
				for (int j = 1; j < matrix[i].size(); j++)
					output << ' ' << matrix[i][j];
				output << endl;
			}
		}
		if (indicator == 2)
		{
			output << "L" << ' ' << vertexAmount << endl;
			isOriented ? output << 1 : output << 0;
			output << ' ';
			w ? output << 1 : output << 0;
			output << endl;
			if (!w)
			{
				for (int i = 0; i < list.size(); i++)
				{
					if (list[i].size() != 0) output << list[i][0].second;
					for (int j = 1; j < list[i].size(); j++)
						output << ' ' << list[i][j].second;
					output << endl;
				}
			}
			else
			{
				for (int i = 0; i < listTuples.size(); i++)
				{
					if (listTuples[i].size() != 0) output << get<1>(listTuples[i][0]) << ',' << get<2>(listTuples[i][0]);
					for (int j = 1; j < listTuples[i].size(); j++)
						output << ' ' << get<1>(listTuples[i][j]) << ',' << get<2>(listTuples[i][j]);
					output << endl;
				}
			}
		}
		if (indicator == 3)
		{
			output << "E" << ' ' << vertexAmount << ' ' << edgeAmount << endl;
			isOriented ? output << 1 : output << 0;
			output << ' ';
			w ? output << 1 : output << 0;
			output << endl;
			if (!w)
				for (int i = 0; i < vectorPairs.size(); i++)
					output << vectorPairs[i].first << ' ' << vectorPairs[i].second << endl;
			else
				for (int i = 0; i < vectTuples.size(); i++)
					if (get<2>(vectTuples[i]) != -1)
						output << get<0>(vectTuples[i]) << ' ' << get<1>(vectTuples[i]) << ' ' << get<2>(vectTuples[i]) << endl;
		}
	}
	int changeEdge(int from, int to, int newWeight)
	{
		int oldWeight;
		if (indicator == 1)
		{
			oldWeight = matrix[from - 1][to - 1];
			matrix[from - 1][to - 1] = newWeight;
		}
		if (indicator == 2)
		{
			for (int i = 0; i < listTuples[from - 1].size(); i++)
				if (get<1>(listTuples[from - 1][i]) == to)
				{
					oldWeight = get<2>(listTuples[from - 1][i]);
					get<2>(listTuples[from - 1][i]) = newWeight;
				}
			if (!isOriented)
			{
				for (int i = 0; i < listTuples[to - 1].size(); i++)
					if (get<1>(listTuples[to - 1][i]) == from)
					{
						oldWeight = get<2>(listTuples[to - 1][i]);
						get<2>(listTuples[to - 1][i]) = newWeight;
					}
			}
		}
		if (indicator == 3)
			for (int i = 0; i < vectTuples.size(); i++)
				if (get<0>(vectTuples[i]) == from && get<1>(vectTuples[i]) == to)
				{
					oldWeight = get<2>(vectTuples[i]);
					get<2>(vectTuples[i]) = newWeight;
				}
		return oldWeight;
	}
	void removeEdge(int from, int to)
	{
		if (indicator == 1)
			matrix[from - 1][to - 1] = 0;
		if (indicator == 2)
		{
			if (!w)
			{
				for (int i = 0; i < list[from - 1].size(); i++)
					if (list[from - 1][i].second == to) list[from - 1].erase(list[from - 1].begin() + i);
				if (!isOriented)
					for (int i = 0; i < list[to - 1].size(); i++)
						if (list[to - 1][i].second == from) list[to - 1].erase(list[to - 1].begin() + i);
			}
			else
			{
				for (int i = 0; i < listTuples[from - 1].size(); i++)
					if (get<1>(listTuples[from - 1][i]) == to) listTuples[from - 1].erase(listTuples[from - 1].begin() + i);
				if (!isOriented)
					for (int i = 0; i < listTuples[to - 1].size(); i++)
						if (get<1>(listTuples[to - 1][i]) == from) listTuples[to - 1].erase(listTuples[to - 1].begin() + i);
			}
		}
		if (indicator == 3)
		{
			if (!w)
			{
				for (int i = 0; i < vectorPairs.size(); i++)
					if (vectorPairs[i].first == from && vectorPairs[i].second == to)
						vectorPairs.erase(vectorPairs.begin() + i);
			}
			else
			{
				for (int i = 0; i < vectTuples.size(); i++)
					if (get<0>(vectTuples[i]) == from && get<1>(vectTuples[i]) == to)
						vectTuples.erase(vectTuples.begin() + i);
			}
		}
	}
	void transformToAdjList()
	{
		if (indicator == 1)
		{
			if (!w)
				for (int i = 0; i < matrix.size(); i++)
				{
					list.push_back(vector<pair<int, int>>());
					for (int j = 0; j < matrix[i].size(); j++)
						if (matrix[i][j] != 0)
							list[i].push_back(make_pair(i + 1, j + 1));
				}
			else
				for (int i = 0; i < matrix.size(); i++)
				{
					listTuples.push_back(vector<tuple<int, int, int>>());
					for (int j = 0; j < matrix[i].size(); j++)
						if (matrix[i][j] != 0)
							listTuples[i].push_back(tuple<int, int, int>(i + 1, j + 1, matrix[i][j]));
				}
			matrix = vector<vector<int>>();
		}
		if (indicator == 3)
		{
			if (!w)
			{
				for (int i = 0; i < vertexAmount; i++)
					list.push_back(vector<pair<int, int>>()); // CHECK THIS
				for (int i = 0; i < vertexAmount; i++)
				{
					for (int j = 0; j < vectorPairs.size(); j++)
						if (vectorPairs[j].first == i + 1)
						{
							list[i].push_back(make_pair(i + 1, vectorPairs[j].second));
							if (!isOriented)
								list[vectorPairs[j].second - 1].push_back(make_pair(vectorPairs[j].second, i + 1));
						}
				}
			}
			else
			{
				for (int i = 0; i < vertexAmount; i++)
					listTuples.push_back(vector<tuple<int, int, int>>());
				for (int i = 0; i < vertexAmount; i++)
				{
					for (int j = 0; j < vectTuples.size(); j++)
						if (get<0>(vectTuples[j]) == i + 1)
						{
							listTuples[i].push_back(tuple<int, int, int>(get<0>(vectTuples[j]), get<1>(vectTuples[j]), get<2>(vectTuples[j])));
							if (!isOriented)
								listTuples[get<1>(vectTuples[j]) - 1].push_back(tuple<int, int, int>(get<1>(vectTuples[j]), get<0>(vectTuples[j]), get<2>(vectTuples[j])));
						}
				}
			}
			vectorPairs = vector<pair<int, int>>();
			vectTuples = vector<tuple<int, int, int>>();
		}
		indicator = 2;
	}
	void transformToListOfEdges()
	{
		if (indicator == 1)
		{
			if (!w)
				for (int i = 0; i < matrix.size(); i++)
				{
					vectorPairs.push_back(pair<int, int>());
					for (int j = 0; j < matrix[i].size(); j++)
						if (matrix[i][j] != 0)
							vectorPairs.push_back(make_pair(i + 1, j + 1));
				}
			else
				for (int i = 0; i < matrix.size(); i++)
				{
					for (int j = 0; j < matrix[i].size(); j++)
						if (matrix[i][j] != 0)
							vectTuples.push_back(tuple<int, int, int>(i + 1, j + 1, matrix[i][j]));
				}
			matrix = vector<vector<int>>();
		}
		if (indicator == 2)
		{
			if (!w)
			{
				for (int i = 0; i < list.size(); i++)
					for (int j = 0; j < list[i].size(); j++)
					{
						bool next = false;
						if (!isOriented && list[i][j].first < list[i][j].second)
							for (int k = 0; k < list[list[i][j].second - 1].size(); k++)
								if (list[list[i][j].second - 1][k].second == list[i][j].first) next = true;
						if (next) continue;
						else vectorPairs.push_back(make_pair(list[i][j].first, list[i][j].second));
					}
			}
			else
			{
				for (int i = 0; i < listTuples.size(); i++)
					for (int j = 0; j < listTuples[i].size(); j++)
					{
						bool next = false;
						if (!isOriented && get<0>(listTuples[i][j]) < get<1>(listTuples[i][j]))
							for (int k = 0; k < listTuples[get<1>(listTuples[i][j]) - 1].size(); k++)
								if (get<1>(listTuples[get<1>(list[i][j])][k]) == get<0>(listTuples[i][j])) next = true;
						if (next) continue;
						else vectTuples.push_back(tuple<int, int, int>(get<0>(listTuples[i][j]), get<1>(listTuples[i][j]), get<2>(listTuples[i][j])));
					}
			}
			list = vector<vector<pair<int, int>>>();
			listTuples = vector<vector<tuple<int, int, int>>>();
		}
		indicator = 3;
	}
	void transformToAdjMatrix()
	{
		if (indicator == 2)
		{
			if (!w)
			{
				for (int i = 0; i < vertexAmount; i++)
				{
					matrix.push_back(vector<int>());
					for (int j = 0; j < list.size(); j++)
						matrix[i].push_back(0);
				}
				for (int i = 0; i < list.size(); i++)
					for (int j = 0; j < list[i].size(); j++)
						matrix[i][list[i][j].second - 1] = 1;
			}
			else
			{
				for (int i = 0; i < listTuples.size(); i++)
				{
					matrix.push_back(vector<int>());
					for (int j = 0; j < listTuples.size(); j++)
						matrix[i].push_back(0);
				}
				for (int i = 0; i < listTuples.size(); i++)
					for (int j = 0; j < listTuples[i].size(); j++)
						matrix[i][get<1>(listTuples[i][j]) - 1] = get<2>(listTuples[i][j]);
			}
			list = vector<vector<pair<int, int>>>();
			listTuples = vector<vector<tuple<int, int, int>>>();
		}
		if (indicator == 3)
		{
			if (!w)
			{
				for (int i = 0; i < vertexAmount; i++)
				{
					matrix.push_back(vector<int>());
					for (int j = 0; j < vertexAmount; j++)
						matrix[i].push_back(0);
				}
				for (int i = 0; i < vectorPairs.size(); i++)
				{
					matrix[vectorPairs[i].first - 1][vectorPairs[i].second - 1] = 1;
					if (!isOriented)
						matrix[vectorPairs[i].second - 1][vectorPairs[i].first - 1] = 1;
				}
			}
			else
			{
				for (int i = 0; i < vertexAmount; i++)
				{
					matrix.push_back(vector<int>());
					for (int j = 0; j < vertexAmount; j++)
						matrix[i].push_back(0);
				}
				for (int i = 0; i < vectTuples.size(); i++)
				{
					matrix[get<0>(vectTuples[i]) - 1]
						[get<1>(vectTuples[i]) - 1] =
						get<2>(vectTuples[i]);
					if (!isOriented)
						matrix[get<1>(vectTuples[i]) - 1][get<0>(vectTuples[i]) - 1] = get<2>(vectTuples[i]);
				}
			}
			vectorPairs = vector<pair<int, int>>();
			vectTuples = vector<tuple<int, int, int>>();
		}
		indicator = 1;
	}
	Graph getSpaingTreePrima()
	{
		Graph result(vertexAmount);
		vector<vector<int>> resMatrix;
		vector<vector<tuple<int, int, int>>> resList;
		vector<int> line;
		unsigned int min = -1, minInLine;
		int minIndx, idx = -1, from = 0;
		return getSpaingTreeKruscal();
		result.w = true;
		result.isOriented = false;
		result.indicator = 1;
		line.push_back(1);
		while (line.size() < result.vertexAmount)
		{
			idx = -1;
			min = -1;
			for (int item = 0; item<line.size(); item++)
			{
				minInLine = -1;
				minIndx = 0;
				for (int i = 0; i < listTuples[line[item] - 1].size(); i++)
				{
					if (get<2>(listTuples[line[item] - 1][i]) < minInLine && get<2>(listTuples[line[item] - 1][i]) != 0 && find(line.begin(), line.end(), get<1>(listTuples[line[item] - 1][i])) == line.end())
					{
						minInLine = get<2>(listTuples[line[item] - 1][i]);
						minIndx = get<1>(listTuples[line[item] - 1][i]) - 1;
					}
				}
				if (minInLine < min && find(line.begin(), line.end(), minIndx + 1) == line.end())
				{
					min = minInLine;
					idx = minIndx;
					cout << idx << endl;
					from = line[item] - 1;
				}
			}
			if (idx != -1)
			{
				cout << from << endl;
				for (int z = 0; z<listTuples[from].size(); z++)
					if (get<1>(listTuples[from][z]) == idx)
						resList[from].push_back(make_tuple(from + 1, idx + 1, get<2>(listTuples[from][z])));
				line.push_back(idx + 1);
			}
			system("pause");
		}
		result.listTuples = resList;
		result.edgeAmount = vertexAmount - 1;

		return result;
	}
	Graph getSpaingTreeKruscal()
	{
		if (indicator != 3) transformToListOfEdges();
		Graph result(vertexAmount);
		result.w = true;
		result.isOriented = false;
		result.indicator = 3;
		DSU dsu(vertexAmount);
		sort(vectTuples.begin(), vectTuples.end(), TuplesCompare);
		for (int i = 0; i < vectTuples.size(); i++)
		{
			if (dsu.find(get<0>(vectTuples[i])) != dsu.find(get<1>(vectTuples[i])))
			{
				dsu.unite(get<0>(vectTuples[i]), get<1>(vectTuples[i]));
				result.vectTuples.push_back(make_tuple(get<0>(vectTuples[i]), get<1>(vectTuples[i]), get<2>(vectTuples[i])));
			}
		}
		result.edgeAmount = vertexAmount - 1;
		return result;
	}
	Graph getSpaingTreeBoruvka()
	{
		if (indicator != 3) transformToAdjList();
		vector<tuple<int, int, int>> edges;
		Graph result(vertexAmount);
		result.w = true;
		result.isOriented = false;
		result.indicator = 3;
		DSU dsu(vertexAmount);
		int numTrees = vertexAmount;
		for (int i = 0; i < vertexAmount; i++)
			edges.push_back(make_tuple(0, 0, 0));
		while (numTrees > 1)
		{
			for (int i = 0; i < edgeAmount; i++)
			{
				int from = dsu.find(get<0>(vectTuples[i])), two = dsu.find(get<1>(vectTuples[i]));
				if (from == two)
					continue;
				else
				{
					if (get<2>(edges[from - 1]) == 0 || get<2>(edges[from - 1]) > get<2>(vectTuples[i]))
						edges[from - 1] = vectTuples[i];
					if (get<2>(edges[two - 1]) == 0 || get<2>(edges[two - 1]) > get<2>(vectTuples[i]))
						edges[two - 1] = vectTuples[i];
				}
			}
			for (int i = 0; i < edges.size(); i++)
			{
				if (dsu.find(get<0>(edges[i])) != dsu.find(get<1>(edges[i])))
				{
					dsu.unite(get<0>(edges[i]), get<1>(edges[i]));
					result.vectTuples.push_back(make_tuple(get<0>(edges[i]), get<1>(edges[i]), get<2>(edges[i])));
					numTrees--;
				}
			}
			for (int z = 0; z < edges.size(); z++)
				edges[z] = make_tuple(0, 0, 0);
		}
		result.edgeAmount = vertexAmount - 1;
		return result;
	}

};
