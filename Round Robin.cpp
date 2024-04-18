/*--- Author 
	  Hasheem Ahmed ---*/

// Iostream for cout cin
#include <iostream>

//Iomanip for the setw and setfill
#include <iomanip>

//Conio.h for the _getch() function to stay on screen until key is pressed
#include <conio.h>
using namespace std;

// Round Robin Algorithm Class

class RoundRobin
{
public:

	// Variables
	int NumberOfProcess;
	int* Proc;
	int* AT;
	int* BT;
	int* CT;
	int* WT;
	int* TAT;
	int* Temp;
	int Quantum;

	//Default Constructor
	RoundRobin()
	{
		NumberOfProcess = Quantum = 0;
		AT = BT = CT = WT = TAT = Proc = Temp =  NULL;
	}

	//Parameterized Constructor
	RoundRobin(int Process,int Quantum)
	{
		this->Quantum = Quantum;
		this->NumberOfProcess = Process;
		Proc = new int[Process];
		AT = new int[Process];
		BT = new int[Process];
		CT = new int[Process];
		WT = new int[Process];
		TAT = new int[Process];
		Temp = new int[Process];
	}

	// Arrival Time Input Asker
	bool ArrivalTimeInput()
	{
		do
		{
			char ch ;
			cout << "Do You want to enter the arrival time?(y/n)";
			cin >> ch;

			if (ch == 'Y' || ch == 'y')
				return true;
			else if (ch == 'N' || ch == 'n')
				return false;
			else
				cout << "Invalid Input\n";

		}while (true);
	}
	// Input the arrival time and burst time values
	void ATinput()
	{
		bool valid = this->ArrivalTimeInput();
		cout << "Enter the Arrival and Burst time : ";
		for (int i = 0; i < NumberOfProcess; i++)
		{
			cout << "P" << i + 1 << " - \n";
			this->Proc[i] = i + 1;
			if (valid == true)
			{
				cout << "Arrival Time : ";
				cin >> this->AT[i];
			}
			else
				this->AT[i] = 0;
			cout << "Burst Time : ";
			cin >> this->BT[i];

			// Using the Temp Array To not Disturb the Original Burst Time
			this->Temp[i] = this->BT[i];
		}
	}

	// Is Empty Function Checks for all the Processes Burst Time
	bool isEmpty()
	{
		bool empty = true;
		for (int i = 0; i < this->NumberOfProcess; i++)
		{
			if (this->Temp[i] != 0)
				empty = false;
		}

		return empty;
	}

	// Is Full Function Checks for the All Processes Completion Time
	bool isFull()
	{
		bool empty = true;
		for (int i = 0; i < this->NumberOfProcess; i++)
		{
			if (this->CT[i] == 0)
				empty = false;
		}

		return empty;
	}


	// Initialize the Completion Time Array to zero
	void zeroCompletion()
	{
		for (int i = 0; i < this->NumberOfProcess; i++)
		{
			this->CT[i] = 0;
		}
	}

	// calculating the completion time
	void CalculatingCT()
	{
		int CompletionTime = 0;
		this->zeroCompletion();

		// Running the loop Until All Process has been run
		while (!this->isEmpty() || !this->isFull() )
		{
			for (int i = 0; i < this->NumberOfProcess; i++)
			{
				if(this->Temp[i] / this->Quantum != 0)
				{
					this->Temp[i] -= this->Quantum;
					CompletionTime += this->Quantum;

					if (this->CT[i] == 0 && this->Temp[i] == 0)
						this->CT[i] = CompletionTime;
				}
				else
				{
					CompletionTime += this->Temp[i];
					this->Temp[i] = 0;

					if(this->CT[i] == 0)
					this->CT[i] = CompletionTime;
				}
			}
		}
	}


	// Calculating the waiting time
	void CalculatingWT()
	{
		for (int i = 0; i < NumberOfProcess; i++)
		{
			this->WT[i] = this->CT[i] - (this->AT[i] + this->BT[i]);
		}
	}


	// calculating turn around time
	void CalculatingTAT()
	{
		for (int i = 0; i < NumberOfProcess; i++)
		{
			this->TAT[i] = this->WT[i] + this->BT[i];
		}
	}

	// Swap function for Sorting Values using pass by reference
	void swap(int& x, int& y)
	{
		int temp = x;
		x = y;
		y = temp;
	}

	//Sorting the Arrival time values by BUBBLE SORT
	void SortingATandBT()
	{
		bool sort = true;
		while (sort)
		{
			sort = false;
			for (int i = 0; i < this->NumberOfProcess - 1; i++)
			{
				if (this->AT[i] > this->AT[i + 1])
				{
					swap(this->AT[i], this->AT[i + 1]);
					swap(this->BT[i], this->BT[i + 1]);
					swap(this->Temp[i], this->Temp[i + 1]);
					swap(this->Proc[i], this->Proc[i + 1]);
					sort = true;
				}
			}
		}
	}

	// calculating the average waiting time
	float AvgWaitingTime()
	{
		float avgWaitingTime = 0;

		for (int i = 0; i < this->NumberOfProcess; i++)
		{
			avgWaitingTime += this->WT[i];
		}

		return avgWaitingTime / this->NumberOfProcess;
	}

};


// Main Function
int main()
{
	// User Input for Number of Process
	int Process,Quantum;
	cout << "Enter Number of Process : ";
	cin >> Process;

	// Input the Quantum Number From User
	cout << "Enter Quantum Number : ";
	cin >> Quantum;

	


	// making Object of the FCFS class and initializing the Number of process
	RoundRobin obj(Process,Quantum);


	// Taking Input of the Arrival time and Burst time
	obj.ATinput();

	// Sorting the Arrival Time 
	obj.SortingATandBT();

	// Calculating the Completion time, Waiting Time , Turn Around Time
	obj.CalculatingCT();
	obj.CalculatingWT();
	obj.CalculatingTAT();

	// Use to clear console
	system("cls");

	// MAking the Table for the output
	cout << setw(70) << setfill('-') << " \n";
	cout << setfill(' ') << "|                      Round Robin - RR                            |\n";
	cout << setw(70) << setfill('-') << " \n";
	cout << "|" << setfill(' ') << "Process    |    AT    |    BT    |    CT    |   TAT    |     WT   |\n";
	cout << setw(70) << setfill('-') << " \n";
	cout << setfill(' ');


	// Outputting the Values of AT, BT, Ct, WT, TAT
	for (int i = 0; i < obj.NumberOfProcess; i++)
	{
		cout << "|";
		cout << setw(10) << "P" << obj.Proc[i] << "|";
		cout << setw(10) << obj.AT[i] << "|";
		cout << setw(10) << obj.BT[i] << "|";
		cout << setw(10) << obj.CT[i] << "|";
		cout << setw(10) << obj.TAT[i] << "|";
		cout << setw(10) << obj.WT[i] << "|\n";
	}


	// Outputting Average Waiting Time
	cout << setw(70) << setfill('-') << " \n";
	cout << "|" << setw(56) << setfill(' ') << " Average Waiting Time |" << setw(10) << obj.AvgWaitingTime() << "|\n";
	cout << setw(70) << setfill('-') << " \n";

	// For stay on the screen
	_getch();
	return 0;
}