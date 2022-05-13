#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <typeinfo>

void adjMatrix(int** adj, int size, bool type)
{
	std::string input;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (adj[i][j] == 0)
			{
				std::cout << "Vertex " << i + 1 << ".\nEdge weight for vertex N" << j + 1 << ".\n" <<
					"Type 0 for no edge.\nInput: ";
				getline(std::cin, input);
				adj[i][j] = std::stoi(input);
				if(type)
					adj[j][i] = std::stoi(input);
				system("cls");
			}
		}
		system("pause");
		system("cls");
	}
}

template <class T, class U>
void print(T adj, U size, U width)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < width; j++)
			std::cout << std::setw(2) << adj[i][j];
		std::cout << "\n";
	}
}


int mostConnected(int** adj, int size)
{
	int max[2] = { 0, 0 };
	int zeroes = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (adj[i][j] == 0)
				zeroes++;
		}
		if (i == 0)
			max[1] = zeroes;
		else if (max[1] > zeroes)
		{
			max[0] = i; max[1] = zeroes;
		}
		zeroes = 0;
	}
	
	return size - max[1];
}


void adjVectors(int** adj, int** adjVec, int size, int width)
{
	for (int i = 0; i < size; i++)
	{
		int h = 0;
		for (int j = 0; j < size; j++)
		{
			if (adj[i][j] != 0)
			{
				adjVec[i][h] = j+1;
				h++;
			}
		}
	}
}


void edgeListFill(std::vector<std::vector<int>>& edgeList, int** adjVec, int size, int width)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (adjVec[i][j] != 0)
			{
				edgeList[0].push_back(i + 1);
				edgeList[1].push_back(adjVec[i][j]);
			}
		}
	}
}


void adjListFill(std::vector<std::vector<int>>& adjList, int** adjVec, int size, int width)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (adjVec[i][j] != 0)
			{
				adjList[i].push_back(adjVec[i][j]);
			}
		}
	}
}


int incMatrix(std::vector<std::vector<int>>& inc, int** adjVec, int size, int width, bool type)
{
	int tail;
	if (type)
		tail = 1;
	else
		tail = -1;
	int edges = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < width; j++)
		{
			bool match = 0;
			if (adjVec[i][j] != 0)
			{
				if (type && edges != 0)
				{
					for (int f = 0; f < inc[i].size(); f++)
					{
						if (inc[i][f] == 1 && inc[adjVec[i][j] - 1][f] == 1)
						{
							match = true;
							break;
						}
					}
				}
				if (match)
					continue;
				inc[i].push_back(1);
				if(i != adjVec[i][j] - 1)
					inc[adjVec[i][j] - 1].push_back(tail);
				edges++;
				for (int n = 0; n < size; n++)
				{
					if (n != i && (n != adjVec[i][j] - 1))
						inc[n].push_back(0);
				}
			}
		}
	}

	return edges;
}


int main()
{
	int size = 1;
	bool type = true;
	std::string input;

	std::cout << "Specify the number of vertices: ";
	getline(std::cin, input);
	size = std::stoi(input);

	std::cout << "Directed or undirected?\n0. Directed;\t1.Undirected.\nInput: ";
	getline(std::cin, input);
	if (std::stoi(input) == 0)
		type = false;
	else
		type = true;
	system("cls");

	int** adj = new int*[size];
	for (int i = 0; i < size; i++) {
		adj[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			adj[i][j] = 0;
		}
	}

	adjMatrix(adj, size, type);
	std::cout << "Adjacency Matrix\n";
	print(adj, size, size);
	std::cout << "\n";

	int** adjVec = new int* [size];
	int width = mostConnected(adj, size);
	for (int i = 0; i < size; i++)
	{
		adjVec[i] = new int[width];
		for (int j = 0; j < width; j++)
		{
			adjVec[i][j] = 0;
		}
	}

	std::cout << "Adjacency Vectors\n";
	adjVectors(adj, adjVec, size, width);
	print(adjVec, size, width);
	std::cout << "\n";

	std::cout << "Edge List\n";
	std::vector<std::vector<int>> edgeList (2);
	edgeListFill(edgeList, adjVec, size, width);
	print(edgeList, edgeList.size(), edgeList[0].size());
	std::cout << "\n";

	std::cout << "Adjacency Lists\n";
	std::vector<std::vector<int>> adjList (size);
	adjListFill(adjList, adjVec, size, width);
	for (int i = 0; i < adjList.size(); i++)
	{
		std::cout << std::setw(2) << i+1 << "=>";
		for (int j = 0; j < adjList[i].size(); j++)
		{
			std::cout << std::setw(2) << adjList[i][j];
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	std::cout << "Incidence Matrix\n";
	std::vector<std::vector<int>> inc(size);
	int edges = incMatrix(inc, adjVec, size, width, type);
	print(inc, size, edges);

	return 0;
}