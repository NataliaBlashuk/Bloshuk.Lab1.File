#include <iostream>
#include <fstream>

int* EnterArray(int);
void DisplayArray(int*, int);
int FindMaxNeg(int*, int);
int FindMinPos(int*, int);
int EvenCount(int);
int* RandArray(int);
void WorkProcessWithArray(int*, int);
int ContentsFile(char*);
void CreateFile(char*, int, int*);
void AddFile(char*, int*, int, char*);
bool Continue(char);
void WithFile(int*, char*);
void WithoutFile(int*, int);

const int N = 210;
const int M = 18;

using namespace std;

int main()
{
	while (true)
	{
		char fileName[N] = "";
		int* a = RandArray(M);
		//int* b = EnterArray(n);

		char file;
		cout << "If you would like to work with file, please, press f or F\n If you don`t like to use file, press the other key ";
		cin >> file;
		if (file == 'f' || file == 'F')
			WithFile(a, fileName);
		else
		{
			int n;
			while (true)
			{
				cout << "Enter the number of elements in the array" << endl;
				cin >> n;
				if (n > 0) break;
				cout << "Error! Please, enter the other value" << endl;
			}
			WithoutFile(a, n);
		}
		break;
	}
	return 0;
}

int* EnterArray(int n)
{
	int* a = new int[n];
	cout << "Enter elements of array" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "a[" << (i + 1) << "] = ";
		cin >> *(a + i);
	}
	return a;
}

void DisplayArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
		cout << *(a + i) << " ";
}

int EvenCount(int number)
{
	if (number < 0)
		number = abs(number);
	int evenCounter = 0;
	while (number > 0)
	{
		if (number % 10 % 2 == 0)
			evenCounter++;
		number /= 10;
	}
	return evenCounter;
}

int* RandArray(int n)
{
	int* a = new int[n];
	for (int* p = a; p < a + n; p++)
		*p = rand() % 532 - 119;
	return a;
}

int FindMaxNeg(int* a, int n)
{
	for (int i = 1; i < n; i += 2)
	{
		if (*(a + i) < 0)
		{
			int maxNeg = *(a + i), maxNegIndex = i;
			for (int k = 1; k < n; k += 2)
			{
				if ((*(a + k) < 0) && (*(a + k) > maxNeg))
				{
					maxNeg = *(a + k);
					maxNegIndex = k;
				}
			}
			cout << endl << "Max negative element is " << maxNeg << endl;
			cout << "Max negative at the position " << maxNegIndex + 1 << endl;
			return maxNegIndex;
		}
	}
}

int FindMinPos(int* a, int n)
{
	for (int i = 1; i < n; i += 2)
	{
		if (*(a + i) > 0)
		{
			int minPos = *(a + i), minPosIndex = i;
			for (int k = 1; k < n; k += 2)
			{
				if ((*(a + k) > 0) && (*(a + k) < minPos))
				{
					minPos = *(a + k);
					minPosIndex = k;
				}
			}
			cout << endl << "Min positive element is " << minPos << endl;
			cout << "Min positive at the position " << minPosIndex + 1 << endl;
			return minPosIndex;
		}
	}
}

void WorkProcessWithArray(int* a, int n)
{
	int maxNegIndex = FindMaxNeg(a, n), minPosIndex = FindMinPos(a, n);
	int startIndex, endIndex;
	bool flag = 0;
	if (maxNegIndex > minPosIndex)
	{
		startIndex = minPosIndex;
		endIndex = maxNegIndex;
	}
	if (minPosIndex > maxNegIndex)
	{
		startIndex = maxNegIndex;
		endIndex = minPosIndex;
	}
	if (endIndex - startIndex <= 2 || endIndex - startIndex == endIndex)
	{
		cout << endl << "Only one element is between min positive and max negative. It`s " << *(a + startIndex + 1) << endl;
		flag = 1;
	}
	if (flag)
		return;

	for (int iterationCount = endIndex - startIndex - 1; iterationCount != 0; iterationCount--)
		for (int i = startIndex + 1; i < endIndex; i++)
		{
			if (i + 1 != endIndex)
				if (EvenCount(*(a + i)) > EvenCount(*(a + i + 1)))
					swap(*(a + i + 1), *(a + i));
		}

	int i, p = n - endIndex + startIndex - 1;
	int* b = new int[p];
	for (i = 0; i < startIndex; i++)
		*(b + i) = *(a + i);
	for (i = endIndex + 1; i < n; i++)
		*(b + (startIndex + i - endIndex - 1)) = *(a + i);
	for (i = 0; i < n - startIndex; i++)
		*(a + i) = *(a + (i + startIndex + 1));

	int m = endIndex - startIndex - 1;
	cout << "Array after sort" << endl;
	DisplayArray(a, m);
	//return m;
}

int ContentsFile(char* fileName)
{
	ifstream streamIn(fileName);
	if (!streamIn.is_open())
	{
		cout << "Cannot open file to read!" << endl;
		system("pause");
		exit(1);
	}
	int count = 0, term;
	while (!streamIn.eof())
	{
		streamIn >> term;
		count++;
	}
	streamIn.close();
	return count;
}

void CreateFile(char* fileName, int n, int* a)
{
	ofstream streamOut(fileName);
	if (!streamOut.is_open())
	{
		cout << "Cannot open file to write!" << endl;
		system("pause");
		exit(1);
	}
	cout << "Enter the elements of array" << endl;
	system("cls");
	int temp;
	for (int i = 0; i < n; i++)
	{
		temp = a[i];
		cin >> temp;
		streamOut.width(5);
		streamOut << temp;
	}
}

void AddFile(char* fileName, int* arr, int n, char*)
{
	ofstream streamOut(fileName, ios::app);
	if (!streamOut.is_open())
	{
		cout << "\nCannot open file to addition!\n";
		system("pause");
		exit(1);
	}
	streamOut << "\n\n";
	for (int i = 0; i < n; i++)
	{
		streamOut.width(5);
		streamOut << arr[i];
	}
	streamOut.close();
}

bool Continue(char)
{
	char yes;
	cout << endl << "If you would like to continue, please, press y or Y " << endl;
	cin >> yes;
	if (yes == 'y' || yes == 'Y')
		return true;
	return false;
}

void WithFile(int* a, char* fileName)
{
	cout << "Enter the name of source file, please: ";
	cin.ignore();
	cin.getline(fileName, N, '\n');
	while (true)
	{
		while (true)
		{
			int n;
			char yes = 'k';
			while (true)
			{
				cout << "Enter the number of elements in the array" << endl;
				cin >> n;
				if (n > 0) break;
				cout << "Error! Please, enter the other value" << endl;
			}
			int* a = RandArray(n);
			CreateFile(fileName, n, a);
			char* string = "Source array: ";
			AddFile(fileName, a, n, string);
			WorkProcessWithArray(a, n);
			string = "Array after sort: ";
			AddFile(fileName, a, n, string);
			cout << "Array was saved at file " << fileName << endl;

			if (Continue(yes))
				continue;
			break;
			system("pause");
		}
	}
}

void WithoutFile(int* a, int n)
{
	while (true)
	{
		char yes = 'k';
		int* a = RandArray(n);
		//int* a = EnterArray(n);
		system("cls");
		cout << "Source array " << endl;
		DisplayArray(a, n);
		cout << endl;
		WorkProcessWithArray(a, n);
		system("pause");
		system("cls");

		if (Continue(yes))
			continue;
		break;
	}
}
