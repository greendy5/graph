#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
using namespace std;
char buff[10];
string strng;
int temp;
vector<vector<pair<int, int>>> list;
vector<vector<tuple<int, int, int>>> listm;
vector<pair<int, int>> vectPairs;
vector<tuple<int, int, int>> vectTuples;
vector<vector<int>> matrix;

class Graph
{
	int indx, vertexAmount, edgesAmount;
	bool orient, mass;
public:
	void readGraph(string fileName)
	{
		ifstream input(fileName);
		input >> buff;
		switch (buff[0])
		{
		case 'C':
		{
			indx = 1;
			getline(input, strng);
			vertexAmount = strng[1] - '0';
			for (int j = 2; j < strng.length(); j++)
				vertexAmount = vertexAmount * 10 + (strng[j] - '0');
			break;
		}
		case 'L':
		{
			indx = 2;
			getline(input, strng);
			vertexAmount = strng[1] - '0';
			for (int j = 2; j < strng.length(); j++)
				vertexAmount = vertexAmount * 10 + (strng[j] - '0');
			break;
		}
		case 'E':
		{
			indx = 3;
			getline(input, strng);
			vertexAmount = strng[1] - '0';
			int i = 2;
			while (strng[i] != ' ')
			{
				vertexAmount = vertexAmount * 10 + (strng[i] - '0');
				i++;
			}
			i++;
			edgesAmount = strng[i] - '0';
			i++;
			while (i < strng.length())
			{
				edgesAmount = edgesAmount * 10 + (strng[i] - '0');
				i++;
			}
			break;
		}
		}
		input >> buff;
		if (buff[0] == '0') orient = false; else orient = true;
		input >> buff;
		if (buff[0] == '0') mass = false; else mass = true;

		if (indx == 1)
		{
			getline(input, strng);
			int linenum = 0;
			while (getline(input, strng))
			{
				matrix.push_back(vector<int>());
				temp = strng[0] - '0';
				for (int i = 1; i < strng.length(); i++)
					if (strng[i] != ' ')
					{
						temp *= 10; temp += strng[i] - '0';
					}
					else
					{
						matrix[linenum].push_back(temp);
						temp = strng[i + 1] - '0';
						i++;
					}
				matrix[linenum].push_back(temp);
				linenum++;
			}
		}
		if (indx == 2)
		{
			if (!mass)
			{
				getline(input, strng);
				int linenum = 0;
				while (getline(input, strng))
				{
					list.push_back(vector<pair<int, int>>());
					temp = strng[0] - '0';
					for (int i = 1; i < strng.length(); i++)
						if (strng[i] != ' ')
						{
							temp *= 10; temp += strng[i] - '0';
						}
						else
						{
							list[linenum].push_back(make_pair(linenum + 1, temp));
							temp = strng[i + 1] - '0';
							i++;
						}
					list[linenum].push_back(make_pair(linenum + 1, temp));
					linenum++;
				}
			}
			else
			{
				int tempTwo;
				getline(input, strng);
				int linenum = 0;
				while (getline(input, strng))
				{
					listm.push_back(vector<tuple<int, int, int>>());
					temp = strng[0] - '0';
					for (int i = 1; i < strng.length(); i++)
						if (strng[i] != ' ')
						{
							if (strng[i] != ',')
							{
								temp *= 10;
								temp += strng[i] - '0';
							}
							else
							{
								tempTwo = temp;
								temp = strng[i + 1] - '0';
								i++;
								continue;
							}
						}
						else
						{
							listm[linenum].push_back(make_tuple(linenum + 1, tempTwo, temp));
							temp = strng[i + 1] - '0';
							i++;
						}
					listm[linenum].push_back(make_tuple(linenum + 1, tempTwo, temp));
					linenum++;
				}
			}
		}

		if (indx == 3)
		{
			if (!mass)
			{
				getline(input, strng);
				int linenum = 0;
				while (getline(input, strng))
				{
					vectPairs.push_back(pair<int, int>());
					vectPairs[linenum].first = strng[0] - '0';
					int i = 1;
					while (strng[i] != ' ')
					{
						vectPairs[linenum].first = vectPairs[linenum].first * 10 + strng[i] - '0';
						i++;
					}
					i++;
					vectPairs[linenum].second = strng[i] - '0';
					i++;
					while (i < strng.length())
					{
						vectPairs[linenum].second = vectPairs[linenum].second * 10 + strng[i] - '0';
						i++;
					}
					linenum++;
				}
			}
			else
			{
				getline(input, strng);
				int linenum = 0;
				while (getline(input, strng))
				{
					vectTuples.push_back(tuple<int, int, int>());
					get<0>(vectTuples[linenum]) = strng[0] - '0';
					int i = 1;
					while (strng[i] != ' ')
					{
						get<0>(vectTuples[linenum]) = get<0>(vectTuples[linenum]) * 10 + strng[i] - '0';
						i++;
					}
					i++;
					get<1>(vectTuples[linenum]) = strng[i] - '0';
					i++;
					while (strng[i] != ' ')
					{
						get<1>(vectTuples[linenum]) = get<1>(vectTuples[linenum]) * 10 + strng[i] - '0';
						i++;
					}
					i++;
					get<2>(vectTuples[linenum]) = strng[i] - '0';
					i++;
					while (i < strng.length())
					{
						get<2>(vectTuples[linenum]) = get<2>(vectTuples[linenum]) * 10 + strng[i] - '0';
						i++;
					}
					linenum++;
				}
			}
		}
	}
	void writeGraph(string fileName)
	{
		ofstream output(fileName);
		if (indx == 1)
		{
			output << "C" << ' ' << vertexAmount << endl;
			orient ? output << 1 : output << 0;
			output << ' ';
			mass ? output << 1 : output << 0;
			output << endl;
			for (int i = 0; i < matrix.size(); i++)
			{
				output << matrix[i][0];
				for (int j = 1; j < matrix[i].size(); j++)
					output << ' ' << matrix[i][j];
				output << endl;
			}
		}
		if (indx == 2)
		{
			output << "L" << ' ' << vertexAmount << endl;
			orient ? output << 1 : output << 0;
			output << ' ';
			mass ? output << 1 : output << 0;
			output << endl;
			if (!mass)
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
				for (int i = 0; i < listm.size(); i++)
				{
					if (listm[i].size() != 0) output << get<1>(listm[i][0]) << ',' << get<2>(listm[i][0]);
					for (int j = 1; j < listm[i].size(); j++)
						output << ' ' << get<1>(listm[i][j]) << ',' << get<2>(listm[i][j]);
					output << endl;
				}
			}
		}
		if (indx == 3)
		{
			output << "E" << ' ' << vertexAmount << ' ' << edgesAmount << endl;
			orient ? output << 1 : output << 0;
			output << ' ';
			mass ? output << 1 : output << 0;
			output << endl;
			if (!mass)
				for (int i = 0; i < vectPairs.size(); i++)
					output << vectPairs[i].first << ' ' << vectPairs[i].second << endl;
			else
				for (int i = 0; i < vectTuples.size(); i++)
					if (get<2>(vectTuples[i]) != -1)
						output << get<0>(vectTuples[i]) << ' ' << get<1>(vectTuples[i]) << ' ' << get<2>(vectTuples[i]) << endl;
		}
	}
	void removeEdge(int from, int to)
	{
		if (indx == 1)
			matrix[from - 1][to - 1] = 0;
		if (indx == 2)
		{
			if (!mass)
			{
				for (int i = 0; i < list[from - 1].size(); i++)
					if (list[from - 1][i].second == to) list[from - 1].erase(list[from - 1].begin() + i);
				if (!orient)
					for (int i = 0; i < list[to - 1].size(); i++)
						if (list[to - 1][i].second == from) list[to - 1].erase(list[to - 1].begin() + i);
			}
			else
			{
				for (int i = 0; i < listm[from - 1].size(); i++)
					if (get<1>(listm[from - 1][i]) == to) listm[from - 1].erase(listm[from - 1].begin() + i);
				if (!orient)
					for (int i = 0; i < listm[to - 1].size(); i++)
						if (get<1>(listm[to - 1][i]) == from) listm[to - 1].erase(listm[to - 1].begin() + i);
			}
		}
		if (indx == 3)
		{
			if (!mass)
			{
				for (int i = 0; i < vectPairs.size(); i++)
					if (vectPairs[i].first == from && vectPairs[i].second == to)
						vectPairs.erase(vectPairs.begin() + i);
			}
			else
			{
				for (int i = 0; i < vectTuples.size(); i++)
					if (get<0>(vectTuples[i]) == from && get<1>(vectTuples[i]) == to)
						vectTuples.erase(vectTuples.begin() + i);
			}
		}
	}
	void addEdge(int from, int to, int weight = 1)
	{
		if (indx == 1)
			matrix[from - 1][to - 1] = weight;
		if (indx == 2)
		{
			if (!mass)
			{
				list[from - 1].push_back(make_pair(from, to));
				if (!orient)
					list[to - 1].push_back(make_pair(to, from));
			}
			else
			{
				listm[from - 1].push_back(make_tuple(from, to, weight));
				if (!orient)
					listm[to - 1].push_back(make_tuple(to, from, weight));
			}
		}
		if (indx == 3)
		{
			if (!mass)
				vectPairs.push_back(make_pair(from, to));
			else
				vectTuples.push_back(tuple<int, int, int>(from, to, weight));
		}
	}
	int changeEdge(int from, int to, int newWeight)
	{
		int oldWeight;
		if (indx == 1)
		{
			oldWeight = matrix[from - 1][to - 1];
			matrix[from - 1][to - 1] = newWeight;
		}
		if (indx == 2)
		{
			for (int i = 0; i < listm[from - 1].size(); i++)
				if (get<1>(listm[from - 1][i]) == to)
				{
					oldWeight = get<2>(listm[from - 1][i]);
					get<2>(listm[from - 1][i]) = newWeight;
				}
			if (!orient)
			{
				for (int i = 0; i < listm[to - 1].size(); i++)
					if (get<1>(listm[to - 1][i]) == from)
					{
						oldWeight = get<2>(listm[to - 1][i]);
						get<2>(listm[to - 1][i]) = newWeight;
					}
			}
		}
		if (indx == 3)
			for (int i = 0; i < vectTuples.size(); i++)
				if (get<0>(vectTuples[i]) == from && get<1>(vectTuples[i]) == to)
				{
					oldWeight = get<2>(vectTuples[i]);
					get<2>(vectTuples[i]) = newWeight;
				}
		return oldWeight;
	}
	void transformToAdjList()
	{
		if (indx == 1)
		{
			if (!mass)
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
					listm.push_back(vector<tuple<int, int, int>>());
					for (int j = 0; j < matrix[i].size(); j++)
						if (matrix[i][j] != 0)
							listm[i].push_back(tuple<int, int, int>(i + 1, j + 1, matrix[i][j]));
				}
			matrix = vector<vector<int>>();
		}
		if (indx == 3)
		{
			if (!mass)
			{
				for (int i = 0; i < vertexAmount; i++)
					list.push_back(vector<pair<int, int>>()); // CHECK THIS
				for (int i = 0; i < vertexAmount; i++)
				{
					for (int j = 0; j < vectPairs.size(); j++)
						if (vectPairs[j].first == i + 1)
						{
							list[i].push_back(make_pair(i + 1, vectPairs[j].second));
							if (!orient)
								list[vectPairs[j].second - 1].push_back(make_pair(vectPairs[j].second, i + 1));
						}
				}
			}
			else
			{
				for (int i = 0; i < vertexAmount; i++)
					listm.push_back(vector<tuple<int, int, int>>());
				for (int i = 0; i < vertexAmount; i++)
				{
					for (int j = 0; j < vectTuples.size(); j++)
						if (get<0>(vectTuples[j]) == i + 1)
						{
							listm[i].push_back(tuple<int, int, int>(get<0>(vectTuples[j]), get<1>(vectTuples[j]), get<2>(vectTuples[j])));
							if (!orient)
								listm[get<1>(vectTuples[j]) - 1].push_back(tuple<int, int, int>(get<1>(vectTuples[j]), get<0>(vectTuples[j]), get<2>(vectTuples[j])));
						}
				}
			}
			vectPairs = vector<pair<int, int>>();
			vectTuples = vector<tuple<int, int, int>>();
		}
		indx = 2;
	}
	void transformToListOfEdges()
	{
		if (indx == 1)
		{
			if (!mass)
				for (int i = 0; i < matrix.size(); i++)
				{
					vectPairs.push_back(pair<int, int>());
					for (int j = 0; j < matrix[i].size(); j++)
						if (matrix[i][j] != 0)
							vectPairs.push_back(make_pair(i + 1, j + 1));
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
		if (indx == 2)
		{
			if (!mass)
			{
				for (int i = 0; i < list.size(); i++)
					for (int j = 0; j < list[i].size(); j++)
					{
						bool next = false;
						if (!orient && list[i][j].first < list[i][j].second)
							for (int k = 0; k < list[list[i][j].second - 1].size(); k++)
								if (list[list[i][j].second - 1][k].second == list[i][j].first) next = true;
						if (next) continue;
						else vectPairs.push_back(make_pair(list[i][j].first, list[i][j].second));
					}
			}
			else
			{
				for (int i = 0; i < listm.size(); i++)
					for (int j = 0; j < listm[i].size(); j++)
					{
						bool next = false;
						if (!orient && get<0>(listm[i][j]) < get<1>(listm[i][j]))
							for (int k = 0; k < listm[get<1>(listm[i][j]) - 1].size(); k++)
								if (get<1>(listm[get<1>(list[i][j])][k]) == get<0>(listm[i][j])) next = true;
						if (next) continue;
						else vectTuples.push_back(tuple<int, int, int>(get<0>(listm[i][j]), get<1>(listm[i][j]), get<2>(listm[i][j])));
					}
			}
			list = vector<vector<pair<int, int>>>();
			listm = vector<vector<tuple<int, int, int>>>();
		}
		indx = 3;
	}
	void transformToAdjMatrix()
	{
		if (indx == 2)
		{
			if (!mass)
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
				for (int i = 0; i < listm.size(); i++)
				{
					matrix.push_back(vector<int>());
					for (int j = 0; j < listm.size(); j++)
						matrix[i].push_back(0);
				}
				for (int i = 0; i < listm.size(); i++)
					for (int j = 0; j < listm[i].size(); j++)
						matrix[i][get<1>(listm[i][j]) - 1] = get<2>(listm[i][j]);
			}
			list = vector<vector<pair<int, int>>>();
			listm = vector<vector<tuple<int, int, int>>>();
		}
		if (indx == 3)
		{
			if (!mass)
			{
				for (int i = 0; i < vertexAmount; i++)
				{
					matrix.push_back(vector<int>());
					for (int j = 0; j < vertexAmount; j++)
						matrix[i].push_back(0);
				}
				for (int i = 0; i < vectPairs.size(); i++)
				{
					matrix[vectPairs[i].first - 1][vectPairs[i].second - 1] = 1;
					if (!orient)
						matrix[vectPairs[i].second - 1][vectPairs[i].first - 1] = 1;
				}
			}
			else
			{
				for (int i = 0; i < vectTuples.size(); i++)
				{
					matrix.push_back(vector<int>());
					for (int j = 0; j < vectTuples.size(); j++)
						matrix[i].push_back(0);
				}
				for (int i = 0; i < vectTuples.size(); i++)
				{
					matrix[get<0>(vectTuples[i]) - 1][get<1>(vectTuples[i]) - 1] = get<2>(vectTuples[i]);
					if (!orient)
						matrix[get<1>(vectTuples[i]) - 1][get<0>(vectTuples[i]) - 1] = get<2>(vectTuples[i]);
				}
			}
			vectPairs = vector<pair<int, int>>();
			vectTuples = vector<tuple<int, int, int>>();
		}
		indx = 1;
	}

	int checkBipart(vector<char> &marks)
	{
		if (indx != 2) transformToAdjList();
		vector<int> queue, visited;
		marks[0] = 'A';
		queue.push_back(1);
		visited.push_back(1);
		while (queue.size() != 0)
		{
			for (int i = 0; i < list[queue.back() - 1].size(); i++)
			{
				if (find(visited.begin(), visited.end(), list[queue.back() - 1][i].second) == visited.end() && find(queue.begin(), queue.end(), list[queue.back() - 1][i].second) == queue.end())
					queue.insert(queue.begin(), list[queue.back() - 1][i].second);
				if (marks[list[queue.back() - 1][i].second - 1] == ' ')
					if (marks[queue.back() - 1] == 'A')
						marks[list[queue.back() - 1][i].second - 1] = 'B';
					else
						marks[list[queue.back() - 1][i].second - 1] = 'A';
				else
					if (marks[list[queue.back() - 1][i].second - 1] == marks[queue.back() - 1])
						return 0;
			}
			visited.push_back(queue.back());
			queue.erase(queue.end() - 1, queue.end());
		}
		return 1;
	}

	bool FindChain(int vert, vector<pair<int, int>> &bipart, vector<int> &visited, vector<int> oldQueue, vector<char> &marks)
	{
		if (find(visited.begin(), visited.end(), vert) != visited.end()) { cout << "ALREADY IN VISITED: " << vert << endl; return false; }
		visited.push_back(vert);
		if (marks[vert - 1] == 'B')
		{
			for (int i = 0; i < bipart.size(); i++)
				if (bipart[i].second == vert)
				{
					oldQueue = vector<int>();
					oldQueue.push_back(bipart[i].first);
					return FindChain(bipart[i].first, bipart, visited, oldQueue, marks);
				}
		}
		vector<int> newQueue;
		for (int i = 0; i < oldQueue.size(); i++)
			for (int j = 0; j < list[oldQueue[i] - 1].size(); j++)
			{
				if (find(oldQueue.begin(), oldQueue.end(), list[oldQueue[i] - 1][j].second) == oldQueue.end())
					newQueue.push_back(list[oldQueue[i] - 1][j].second);
				if (find(visited.begin(), visited.end(), list[oldQueue[i] - 1][j].second) == visited.end())
				{
					int to = list[oldQueue[i] - 1][j].second;
					bool notVis = true;
					for (int k = 0; k < bipart.size(); k++)
						if ((bipart[k].second == to && marks[oldQueue[i] - 1] == 'A') || (bipart[k].first == to && marks[oldQueue[i] - 1] == 'B'))
							notVis = false;
					if (notVis)
					{
						if (marks[oldQueue[i] - 1] == 'B') return true;
						bool changed = false;
						for (int k = 0; k < bipart.size(); k++)
							if (bipart[k].first == vert)
							{
								changed = true;
								bipart[k].second = to;
								break;
							}
						if (!changed)
							for (int k = 0; k < bipart.size(); k++)
								if (bipart[k].first == -1)
								{
									bipart[k].first = vert;
									bipart[k].second = to;
									break;
								}
						return true;
					}
				}
			}
		for (int i = 0; i < oldQueue.size(); i++)
			for (int j = 0; j < list[oldQueue[i] - 1].size(); j++)
			{
				if (find(visited.begin(), visited.end(), list[oldQueue[i] - 1][j].second) == visited.end())
				{
					int to = list[oldQueue[i] - 1][j].second;
					bool notVis = true;
					for (int k = 0; k < bipart.size(); k++)
						if ((bipart[k].second == to && marks[oldQueue[i] - 1] == 'A') || (bipart[k].first == to && marks[oldQueue[i] - 1] == 'B'))
							notVis = false;
					if (find(visited.begin(), visited.end(), to) != visited.end()) continue;
					if (FindChain(to, bipart, visited, newQueue, marks))
					{
						if (marks[oldQueue[i] - 1] == 'B') return true;
						bool changed = false;
						for (int k = 0; k < bipart.size(); k++)
							if (bipart[k].first == vert)
							{
								changed = true;
								bipart[k].second = to;
								break;
							}
						if (!changed)
							for (int k = 0; k < bipart.size(); k++)
								if (bipart[k].first == -1)
								{
									bipart[k].first = vert;
									bipart[k].second = to;
									break;
								}
						return true;
					}
				}
			}
		return false;
	}

	vector<pair<int, int>>getMaximumMatchingBipart()
	{
		vector<pair<int, int>> bipart;
		vector<char> marks;
		vector<int> queue, visited;
		for (int i = 0; i < vertexAmount; i++)
			marks.push_back(' ');
		if (checkBipart(marks) == 0) { cout << "no no no"; return bipart; }
		for (int i = 0; i < marks.size(); i++)
			if (marks[i] == 'A')
				bipart.push_back(pair<int, int>(-1, -1));
		queue.push_back(0);
		for (int i = 0; i < vertexAmount; i++)
		{
			queue[0] = i + 1;
			if (marks[i] != 'A') continue;
			FindChain(i + 1, bipart, visited, queue, marks);
			visited = vector<int>();
		}
		for (int i = 0; i < bipart.size(); i++)
			if (bipart[i].first == -1)
				bipart.erase(bipart.begin() + i);
		for (int i = 0; i < bipart.size(); i++)
			if (bipart[i].first == -1)
				bipart.erase(bipart.begin() + i);
		for (int i = 0; i < bipart.size(); i++)
			if (bipart[i].first == -1)
				bipart.erase(bipart.begin() + i);
		for (int i = 0; i < bipart.size(); i++)
			if (bipart[i].first == -1)
				bipart.erase(bipart.begin() + i);
		for (int i = 0; i < bipart.size(); i++)
			if (bipart[i].first == -1)
				bipart.erase(bipart.begin() + i);
		return bipart;
	}
};
