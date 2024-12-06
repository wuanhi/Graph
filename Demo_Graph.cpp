#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <cstring>
using namespace std;
#define MAX 102
int Parent[MAX];
int SIZE[MAX]; 
// Stack 
struct Stack
{
	int top;
	int stack[MAX];
};
void Init_Stack(Stack& s)
{
	s.top = -1;
}
bool Is_Stack_Empty(Stack s)
{
	return s.top == -1;
}
bool Is_Stack_Full(Stack s)
{
	return s.top == MAX - 1;
}
void Push_Stack(Stack& s, int x)
{
	if (!Is_Stack_Full(s))
	{
		s.stack[++s.top] = x;
	}
	else cout << "Stack is Full ! " << endl;
}
int Pop_Stack(Stack& s)
{
	if (Is_Stack_Empty(s))
	{
		cout << "Stack is Empty ! " << endl;
	}
	else
	{
		return s.stack[s.top--];
	}
}
// Queue 
struct Node
{
	int info;
	Node* Next;
};
Node* Create_Node(const int x)
{
	Node* p = new Node;
	p->info = x;
	p->Next = NULL;
	return p;
}
struct Queue
{
	Node* root;
};
void Init_Queue(Queue& q)
{
	q.root = NULL;
}
bool Is_Queue_Empty(Queue q)
{
	if (q.root == NULL) return true;
	else return false; 
}
void EnQueue(Queue& q, const int x)
{
	if (q.root == NULL)
	{
		q.root = Create_Node(x);
	}
	else
	{
		Node* tmp = q.root;
		while (tmp->Next != NULL)
		{
			tmp = tmp->Next;
		}
		tmp->Next = Create_Node(x);
	}
}
int DeQueue(Queue& q)
{
	if (q.root == NULL)
	{
		cout << "Queue is Empty " << endl;
	}
	else
	{
		Node* tmp = q.root;
		q.root = tmp->Next;
		int x = tmp->info;
		delete tmp;
		return x;
	}
}
// Graph 
struct Edge
{
	int Current_Edge, Next_Edge, Weight; 
};
struct Graph
{
	int Amount_Vertice;
	int Matrix[MAX][MAX];
	char Name_Vertice[MAX];
	Edge edges[MAX]; 
	int Amount_Edges;
};
void Init_Graph(Graph& g)
{
	g.Amount_Vertice = 0;
	g.Amount_Edges = 0; 
}
void Init_Matrix(Graph& g)
{
	for (int i = 0; i < g.Amount_Vertice; i++)
	{
		for (int j = 0; j < g.Amount_Vertice; j++)
		{
			g.Matrix[i][j] = 0;
		}
	}
}
// Function of Graph in Menu 
void Display_Menu()
{
	cout << "====================== MENU ====================== " << endl
		<< "1. Khoi tao do thi " << endl
		<< "2. Nhap MA TRAN KE tu ban phim " << endl
		<< "3. Nhap MA TRAN KE tu File " << endl
		<< "4. Xuat MA TRAN KE " << endl
		<< "5. Duyet do thi theo chieu sau (DFS) " << endl
		<< "6. Duyet do thi theo chieu rong (BFS) " << endl
		<< "7. Tim Cay Khung Toi Tieu bang giai thuat Prim " << endl
		<< "8. Tim Cay Khung Toi Tieu bang giai thuat Kruskal " << endl
		<< "9. Thoat Menu !!! " << endl
		<< "==============> Su lua chon cua ban: ";
}
// Input KeyBoard
void Input_From_KeyBoard(Graph& g)
{
	cout << "Nhap so luong dinh do thi: ";
	cin >> g.Amount_Vertice;
	while (g.Amount_Vertice <= 0 || g.Amount_Vertice > MAX)
	{
		cout << "So luong dinh do thi khong hop le ! Vui long nhap lai ! " << endl;
		cout << "Nhap so luong dinh do thi: ";
		cin >> g.Amount_Vertice;
	}
	cout << "Nhap ten cho " << g.Amount_Vertice << " dinh do thi: ";
	for (int i = 0; i < g.Amount_Vertice; i++)
	{
		cin >> g.Name_Vertice[i];
	}
	cout << "Nhap ma tran cua do thi: " << endl << "=========== MATRIX ===========" << endl;
	for (int i = 0; i < g.Amount_Vertice; i++)
	{
		cout << "Dong thu " << i + 1 << " : ";
		for (int j = 0; j < g.Amount_Vertice; j++)
		{
			cin >> g.Matrix[i][j];
		}
	}
	cout << endl << "===========> DA NHAP MA TRAN THANH CONG ! " << endl;
}
// Input Matrix
void Input_Matrix_From_File(Graph& g, string FileName)
{
	ifstream MyFile;
	MyFile.open(FileName);
	if (MyFile.is_open())
	{
		MyFile >> g.Amount_Vertice;
		MyFile.ignore();
		for (int i = 0; i < g.Amount_Vertice; i++)
		{
			MyFile >> g.Name_Vertice[i];
		}
		MyFile.ignore();
		for (int i = 0; i < g.Amount_Vertice; i++)
		{
			for (int j = 0; j < g.Amount_Vertice; j++)
			{
				MyFile >> g.Matrix[i][j];
				if (g.Matrix[i][j] != 0)
				{
					bool Flag = false; 
					for (int m = 0; m < g.Amount_Vertice; m++)
					{
						if ((g.edges[m].Current_Edge == i && g.edges[m].Next_Edge == j) || (g.edges[m].Current_Edge == j && g.edges[m].Next_Edge == i))
						{
							Flag = true; 
							break; 
						}
					}
					if (Flag == false)
					{
						g.edges[g.Amount_Edges].Current_Edge = i; 
						g.edges[g.Amount_Edges].Next_Edge = j;
						g.edges[g.Amount_Edges].Weight = g.Matrix[i][j]; 
						g.Amount_Edges++; 
					}
				}
			}
		}
		MyFile.close();
		cout << "============= Da doc File thanh cong !!! =============" << endl;
	}
	else
	{
		cout << "Khong mo duoc File !" << endl;
		return;
	}
}
// Input List Edge
void Input_List_Edge_From_File(Graph& g, string FileName)
{
	ifstream MyFile; 
	MyFile.open(FileName); 
	if (MyFile.is_open())
	{
		MyFile >> g.Amount_Vertice >> g.Amount_Edges; 
		MyFile.ignore(); 
		int Vertice_Count = 0;
		// Init Matrix
		Init_Matrix(g); 
		for (int i = 0; i < g.Amount_Edges; i++)
		{
			char u, v; 
			int w; 
			MyFile >> u >> v >> w; 
			MyFile.ignore(); 
			// Add to Vertice Name if no Exist
			int Exist_U = -1, Exist_V = -1; 
			for (int j = 0; j < g.Amount_Vertice; j++)
			{
				if (g.Name_Vertice[j] == u) Exist_U = j; 
				if (g.Name_Vertice[j] == v) Exist_V = j; 
			}
			if (Exist_U == -1)
			{
				Exist_U = Vertice_Count; 
				g.Name_Vertice[Vertice_Count++] = u; 
			}
			if (Exist_V == -1)
			{
				Exist_V = Vertice_Count; 
				g.Name_Vertice[Vertice_Count++] = v; 
			}
			// Add to List_Edge 
			g.edges[i].Current_Edge = Exist_U; 
			g.edges[i].Next_Edge = Exist_V; 
			g.edges[i].Weight = w; 
			// Add to Matrix 
			g.Matrix[Exist_U][Exist_V] = w; 
			g.Matrix[Exist_V][Exist_U] = w;
		}
		cout << "=========== DA DOC FILE THANH CONG =========== " << endl; 
		MyFile.close(); 
	}
	else
	{
		cout << "Khong mo duoc File ! " << endl; 
		return; 
	}
}
// Input Adjacency List
int Get_Vertice_Index(Graph g, char x)
{
	for (int i = 0; i < g.Amount_Vertice; i++)
	{
		if (g.Name_Vertice[i] == x) return i; 
	}
	return -1; 
}
void Input_List_Adj_From_File(Graph& g, string FileName) {
	ifstream MyFile;
	MyFile.open(FileName);
	if (MyFile.is_open()) {
		MyFile >> g.Amount_Vertice; 
		MyFile.ignore();
		
		// Init Matrix 
		Init_Matrix(g); 
		for (int i = 0; i < g.Amount_Vertice; i++)
		{
			string line; 
			getline(MyFile, line);
			g.Name_Vertice[i] = line[0]; 
			for (int j = 0; j < line.length(); j++)
			{
				if (line[j] == ' ') continue;
				else 
				{
					int Current_Index = Get_Vertice_Index(g, line[0]); 
					int Next_Index = Get_Vertice_Index(g, line[j]);
					if (Current_Index != -1 && Next_Index != -1 && g.Matrix[Current_Index][Next_Index] == 0 && Current_Index != Next_Index)
					{
						int W = 0; 
						string tmp = ""; 
						int k = j + 2;
						while (k < line.length() && isdigit(line[k]))
						{
							tmp += line[k++]; 
						}
						if (!tmp.empty())
						{
							W = stoi(tmp); 
						}
						// Add weight to Matrix 
						g.Matrix[Current_Index][Next_Index] = W; 
						g.Matrix[Next_Index][Current_Index] = W; 
						// Add to List Edge 
						g.edges[g.Amount_Edges].Current_Edge = Current_Index; 
						g.edges[g.Amount_Edges].Next_Edge = Next_Index; 
						g.edges[g.Amount_Edges].Weight = W; 
						++g.Amount_Edges;
					}
				}
			}
		}
		MyFile.close();
		cout << "============= Da doc File thanh cong !!! =============" << endl;
	}
	else {
		cout << "Khong mo duoc File !" << endl;
		return;
	}
}
void Output(const Graph g)
{
	cout << "======================= MA TRAN KE ======================= " << endl;
	cout << "  | ";
	for (int i = 0; i < g.Amount_Vertice; i++)
	{
		cout << g.Name_Vertice[i] << "  ";
	}
	cout << endl << "-----------------------------" << endl;
	for (int i = 0; i < g.Amount_Vertice; i++)
	{
		cout << g.Name_Vertice[i] << " | ";
		for (int j = 0; j < g.Amount_Vertice; j++)
		{
			cout << g.Matrix[i][j];
			if (g.Matrix[i][j] < 10) cout << "  ";
			else cout << " ";
		}
		cout << endl;
	}
		cout << "Danh sach canh: " << endl;
		for (int i = 0; i < g.Amount_Edges; i++)
		{
			cout << g.edges[i].Current_Edge << " " << g.edges[i].Next_Edge << " " << g.edges[i].Weight << endl;
		}
}
// DFS & BFS 
bool Check_Exist_StartVertice(Graph g, char StartVertice, int& StartIndex)
{
	cout << "Nhap dinh bat dau: "; 
	cin >> StartVertice; 
	for (int i = 0; i < g.Amount_Vertice; i++)
	{
		if (StartVertice == g.Name_Vertice[i])
		{
			StartIndex = i; 
			return true; 
		}
	}
	cout << "Dinh " << StartVertice << " khong ton tai trong do thi ! " << endl; 
	return false; 
}
static void Browse_DFS(const Graph g)
{
	char StartVertice = ' '; 
	int StartIndex; 
	if (Check_Exist_StartVertice(g, StartVertice, StartIndex))
	{
		Stack s; 
		Init_Stack(s); 
		bool Is_Visited[MAX] = { false }; 
		int Result[MAX], tmp = 0;
		Push_Stack(s, StartIndex); 
		Is_Visited[StartIndex] = true; 
		Result[tmp++] = StartIndex; 
		while (!Is_Stack_Empty(s))
		{
			int Current_Vertice = Pop_Stack(s); 
			for (int i = 0; i < g.Amount_Vertice; i++)
			{
				if (g.Matrix[Current_Vertice][i] != 0 && !Is_Visited[i])
				{
					Push_Stack(s, Current_Vertice); 
					Push_Stack(s, i); 
					Is_Visited[i] = true; 
					Result[tmp++] = i; 
					break; 
				}
			}
		}
		cout << "Browse DFS: "; 
		for (int i = 0; i < tmp; i++)
		{
			cout << g.Name_Vertice[Result[i]] << " "; 
		}
		cout << endl; 
	}
	else return; 
}
static void Browse_BFS(const Graph g)
{
	char Start_Vertice = ' ';
	int Start_Index; 
	if (Check_Exist_StartVertice(g, Start_Vertice, Start_Index))
	{
		Queue q; 
		Init_Queue(q); 
		bool Is_Visited[MAX] = { false };
		int Result[MAX], tmp = 0; 
		Is_Visited[Start_Index] = true; 
		Result[tmp++] = Start_Index; 
		EnQueue(q, Start_Index); 
		while (!Is_Queue_Empty(q))
		{
			int Current_Vertice = DeQueue(q); 
			for (int i = 0; i < g.Amount_Vertice; i++)
			{
				if (g.Matrix[Current_Vertice][i] != 0 && !Is_Visited[i])
				{
					EnQueue(q, Current_Vertice); 
					EnQueue(q, i); 
					Is_Visited[i] = true; 
					Result[tmp++] = i; 
					break; 
				}
			}
		}
		cout << "Browse BFS: ";
		for (int i = 0; i < tmp; i++)
		{
			cout << g.Name_Vertice[Result[i]] << " ";
		}
		cout << endl;
	}
	else return; 
}
// Prim 
void Prim(const Graph g)
{
	char Start_Vertice = ' ';
	int Start_Index; 
	if (Check_Exist_StartVertice(g, Start_Vertice, Start_Index))
	{
		bool Is_Selected[MAX] = { false }; 
		int Count_Edge = 0, SUM = 0; 
		Is_Selected[Start_Index] = true; 
		while (Count_Edge < g.Amount_Vertice - 1)
		{
			int Min_Weight = INT_MAX;
			int Current_Vertice = -1, Next_Vertice = -1; 
			for (int i = 0; i < g.Amount_Vertice; i++)
			{
				if (Is_Selected[i])
				{
					for (int j = 0; j < g.Amount_Vertice; j++)
					{
						if (g.Matrix[i][j] != 0 && g.Matrix[i][j] < Min_Weight && !Is_Selected[j])
						{
							Min_Weight = g.Matrix[i][j]; 
							Current_Vertice = i; 
							Next_Vertice = j; 
						}
					}
				}
			}
			SUM += Min_Weight; 
			Is_Selected[Next_Vertice] = true; 
			cout << "Dinh: " << g.Name_Vertice[Current_Vertice] << " - Dinh: " << g.Name_Vertice[Next_Vertice] << " - Weight: " << Min_Weight << endl; 
			++Count_Edge; 
		}
		cout << "W(T) = " << SUM << endl; 
	}
	else return; 
}
// Kruskal 
void Swap_Edge(Edge& a, Edge& b)
{
	Edge tmp = a; 
	a = b;
	b = tmp; 
}
void Sort_Edge_Follow_Weight(Edge arr[], int nE)
{
	for (int i = 0; i < nE - 1; i++)
	{
		for (int j = i + 1; j < nE; j++)
		{
			if (arr[i].Weight > arr[j].Weight)
			{
				Swap_Edge(arr[i], arr[j]);
			}
		}
	}
}
void Set_Parent(const Graph g)
{
	for (int i = 0; i < g.Amount_Vertice; i++)
	{
		Parent[i] = i; 
		SIZE[i] = i; 
	}
}
int Find_Parent(int x)
{
	if (Parent[x] == x) return x; 
	else
	{
		return Parent[x] = Find_Parent(Parent[x]); 
	}
}
bool Union_Set(int a, int b)
{
	a = Find_Parent(a); 
	b = Find_Parent(b); 
	if (a == b) return false; 
	if (SIZE[a] > SIZE[b])
	{
		Parent[b] = a; 
		SIZE[a] += SIZE[b]; 
	} 
	else
	{
		Parent[a] = b; 
		SIZE[b] += SIZE[a]; 
	}
	return true; 
}
void Kruskal(Graph g)
{
	Edge result[MAX]; 
	Set_Parent(g);
	Sort_Edge_Follow_Weight(g.edges, g.Amount_Edges); 
	int Count_Edge = 0, SUM = 0; 
	for (int i = 0; i < g.Amount_Edges; i++)
	{
		int x = Find_Parent(g.edges[i].Current_Edge); 
		int y = Find_Parent(g.edges[i].Next_Edge); 
		if (Union_Set(x, y))
		{
			result[Count_Edge++] = g.edges[i];
			SUM += g.edges[i].Weight; 
			if (Count_Edge == g.Amount_Vertice - 1) break; 
		}
	}
	cout << "Cay khung toi tieu: " << endl; 
	for (int i = 0; i < Count_Edge; i++)
	{
		cout << "Dinh: " << g.Name_Vertice[result[i].Current_Edge] << " - Dinh: " << g.Name_Vertice[result[i].Next_Edge] << " - Trong so: " << result[i].Weight << endl; 
	}
	cout << "Tong trong so W(T) = " << SUM << endl; 
}

int main()
{
	Graph g;
	while (1)
	{
		system("cls"); 
		Display_Menu();
		int choice;
		bool Is_Initilized = false;
		cin >> choice; 
		switch (choice)
		{
		case 1:
		{
			cout << "--------- CHUC NANG KHOI TAO DO THI --------- " << endl;
			Init_Graph(g); 
			Is_Initilized = true; 
			cout << "--------- DA KHOI TAO DO THI THANH CONG ---------" << endl; 
		}
		break;
		case 2:
		{
			if (!Is_Initilized)
			{
				cout << "--------- CHUC NANG NHAP MA TRAN KE tu ban phim --------- " << endl;
				Input_From_KeyBoard(g);
			}
			else cout << "Vui long khoi tao do thi ! " << endl; 
		}
		break;
		case 3:
		{	
			if (!Is_Initilized)
			{
				cout << "--------- CHUC NANG NHAP MA TRAN KE tu File --------- " << endl;
				// Input_Matrix_From_File(g, "Matrix_Has_Weight.txt"); 
				Input_List_Adj_From_File(g, "Adj_List.txt");
			}
			else cout << "Vui long khoi tao do thi ! " << endl;
		}
		break;
		case 4:
		{
			if (!Is_Initilized)
			{
				cout << "--------- CHUC NANG XUAT MA TRAN KE --------- " << endl;
				Output(g); 
			}
			else cout << "Vui long khoi tao do thi ! " << endl;
		}
		break;
		case 5:
		{
			if (!Is_Initilized)
			{
				cout << "--------- CHUC NANG DUYET DFS ( CHIEU SAU ) --------- " << endl;
				Browse_DFS(g);
			}
			else cout << "Vui long khoi tao do thi ! " << endl;
		}
		break;
		case 6:
		{
			if (!Is_Initilized)
			{
				cout << "--------- CHUC NANG DUYET BFS ( CHIEU RONG ) --------- " << endl;
				Browse_BFS(g);
			}
			else cout << "Vui long khoi tao do thi ! " << endl;
		}
		break;
		case 7:
		{
			if (!Is_Initilized)
			{
				cout << "--------- CHUC NANG TIM CAY KHUNG TOI TIEU ( PRIM ) --------- " << endl;
				Prim(g);
			}
			else cout << "Vui long khoi tao do thi ! " << endl;
		}
		break;
		case 8:
		{
			if (!Is_Initilized)
			{
				cout << "--------- CHUC NANG TIM CAY KHUNG TOI TIEU ( Kruskal ) --------- " << endl;
				
				Kruskal(g);
			}
			else cout << "Vui long khoi tao do thi ! " << endl;
		}
		break;
		case 9: 
		{
			cout << "Cam on da su dung chuong trinh <333" << endl; 
			return 0; 
		}
		break; 
		default:
			cout << "Lua chon khong hop le ! " << endl; 
			break;
		}
		system("pause"); 
	}
	return 0;
}