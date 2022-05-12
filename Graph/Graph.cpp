#include <string>
#include <iostream>
#include <iomanip>

void adjMatrix(int** adj, int size, bool type)
{
	std::string input;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (adj[i][j] == 0 && i != j)
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

void print(int** adj, int size, int width)
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

	adjVectors(adj, adjVec, size, width);
	print(adjVec, size, width);

	return 0;
}
