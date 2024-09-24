#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>


void ComplaintsManager(void);
		typedef struct stUser;
		//struct stUser CurrentUser;
		void SetDefaultAdminInfo(void);
		bool CheckIdentity(char*, size_t, char*, size_t);
		void SignIn(void);
		bool UserNameExist(char*, size_t);
		bool IsLowerCaseExist(char*, size_t);
		bool IsUpperCaseExist(char*, size_t);
		bool IsDigitExist(char*, size_t);
		bool IsSpecialCharExist(char*, size_t);
		bool CheckPasswordStrength(char* );
		void SignUp(void);
		void ShowEndProgramScreen(void);

void ShowClientsMenuScreen(void);
void ShowUsersMenuScreen(void);

void DrawScreenHeader(const char[], const char[]);
int ReadNumber(const char[]);
int ReadPositiveNumber(const char[]);
int ReadNumberInRange(int, int, const char[]);
enum enMainMenuOption;
enum enMainMenuOption ReadMainMenuOption(void);
void PerformUsersMenuOption(enum enMainMenuOption);
void ReadString(char* , size_t , const char []);
void ShowMainMenuScreen(void);
void GoBackToMainMenuScreen(void);

void ShowAddComplaintScreen(void);
		enum enComplaintCategory;
		enum enClaimStatus;
		bool IsIDExist(int );
		int GenerateUniqueID();
		void GetSystemDate(char* , size_t );
void ShowComplaintsListScreen(void);
void ShowDeleteComplaintScreen(void);
void ShowUpdateComplaintScreen(void);
void ShowFindClaimScreen(void);
		enum enFindComplaintOption;
		enum enFindComplaintOption ReadFindComplaintOption(void);
		bool FindComplaintByID(struct stComplaint* , int );
		void PrintComplaintInfo(stComplaint );
		void ShowFindComplaintByIDScreen(void);
		void ShowFindComplaintByNameScreen(void);
		void ShowFindComplaintByDateScreen(void);
		void ShowFindComplaintByStatusScreen(void);
		void PerformFindComplaintMenuOption(enum enFindComplaintOption );
void ShowOrderedClaimsScreen(void);
void ShowStaticsMenuScreen(void);

int main()
{
	//seeds the random numbers generator in C,called only once;
	srand(time(NULL));
	//ShowMainMenuScreen();
	ComplaintsManager();
	return 0;
}

typedef struct stUser
{
	char FullName[45];
	char UserName[20];
	char Password[20];
	int Permssions;
	bool IsClient;

}stUser;

stUser aUsers[100];
short UsersCounter = 1;
stUser CurrentUser;


int ReadNumber(const char Message[])
{
	int Number = 0;
	printf("%s", Message);
	scanf_s("%d", &Number);
	getchar();
	return Number;
}
int ReadPositiveNumber(const char Message[])
{
	int Number = 0;
	do
	{
		Number = ReadNumber(Message);
		if (Number < 0)
			printf("\n try again with a positive number : ");

	} while (Number < 0);
	return Number;
}

int ReadNumberInRange(int From,int To,const char Message[])
{
	int Number = 0;
	do
	{
		Number = ReadNumber(Message);
		if (Number<From || Number>To)
			printf("\nout of range try again..");
	} while (Number<From||Number>To);
	return Number;
}

void ReadString(char* S1, size_t Size, const char Message[])
{
	printf("\n%s", Message);
	fgets(S1, Size, stdin);
	size_t StringLength = strlen(S1);

	// removing the new line char due to use fgets():
	if (StringLength > 0 && S1[StringLength - 1] == '\n')
		S1[StringLength - 1] = '\0';
}

int RandomNumber(int From, int To)
{
	return (rand() % (To - From + 1)) + From;
}

void DrawScreenHeader(const char Title[], const char Subtitle[])
{
	printf("\nAlami Co,ltd all rights reserved 2024");
	printf("\n%15s%s","", "========================================");
	printf("\n%20s%s\n%25s%s","", Title,"", Subtitle);
	printf("\n%15s%s\n", "", "========================================");

}

enum enMainMenuOption
{
	 eShowComplaintsList = 1, eUpdateComplaint = 2, eDeleteComplaint = 3,
	eFindClaim = 4,eProcessComplaint=5, eShowOrderedClaims = 6, eStatics = 7, eManageUsers = 8, eExist = 9
};

enum enMainMenuOption ReadMainMenuOption()
{
	return (enum enMainMenuOption)ReadNumberInRange(1, 9, "\nChoose what do you wanna do [1~9] : ");
}

enum enClaimStatus
{
	eRejected = -1,eInProgress=0,eResolved=1
};

enum enComplaintPriority{eHigh=1,eMedium=2,eLow=3};

typedef struct
{
	int ID;
	char Reason[100];
	char Description[200];
	char Category[30];
	enum enClaimStatus Status;
	char Date[20];
	char MadeBy[40];
	char Notes[40];
	enum enComplaintPriority Priority;

}stComplaint;

stComplaint AllComplaints[100];

int ComplaintsCounter = 0;



bool IsIDExist(int ID)
{
	for (short i = 0; i < ComplaintsCounter; i++)
		if (AllComplaints[i].ID == ID)
			return true;
	//if you reached here this means that the ID does not exist!
	return false;
}
int GenerateUniqueID()
{
	int ID=0;
	do
	{
		ID = RandomNumber(1, 99);
	} while (IsIDExist(ID));
	return ID;
}
void GetSystemDate(char* sDate,size_t Size)
{
	 time_t Now= time(NULL);//get current time
	//sDate = ctime_s(sDate,Size, & Now);
	struct tm *CurrentTime=localtime(&Now);
	sprintf_s(sDate, Size, "%02d/%02d/%d", CurrentTime->tm_mday, CurrentTime->tm_mon + 1, CurrentTime->tm_year + 1900);
}
			void PrintComplaintRecord(stComplaint Complaint)
			{
				printf("|%-40s|%-4d|%-20s|%-60s|%-20s|", Complaint.MadeBy,Complaint.ID, Complaint.Date, Complaint.Description,
					Complaint.Status==eRejected? "Rejected": Complaint.Status==eResolved? "Resolved":"Pending");
				
			}
		void ShowComplaintsListScreen()
		{
			//printf("\n Complaints list screen will be here..");
			DrawScreenHeader("Complaints Manager", "Complaints list ");
			printf("\n%s","_____________________________________________________________________________________________________________________________________________________");
			printf("\n|%-40s|%-4s|%-20s|%-60s|%-20s|", "Name","ID", "Date", "Description", "Status");
			printf("\n%s", "_____________________________________________________________________________________________________________________________________________________");
			if (ComplaintsCounter != 0)
			{
				for (short i = 0; i < ComplaintsCounter; i++)
				{
					printf("\n");
					PrintComplaintRecord(AllComplaints[i ]);
				}
				
				
			}
			else
				printf("\n\t\tNo available Complaints To Show!");


			printf("\n%s", "_____________________________________________________________________________________________________________________________________________________");

		}
		void ShowDeleteComplaintScreen()
		{
			//printf("\n delete complaint screen will be here.. ");
			DrawScreenHeader("Complaints Manager", "Delete Complaint");


			stComplaint Complaint;
			if (FindComplaintByID(&Complaint, ReadPositiveNumber("\n enter an ID to serch for : ")))
			{
				printf("\n found ! \n");
				PrintComplaintInfo(Complaint);
				printf("\n Are you sure do you want to delete the Complaint above ? [Y/N]..");
				char Answer = 'n';
				scanf_s(" %c",&Answer);//!
				getchar();
				if (tolower(Answer) == 'y')
				{
					short i = 0;
					for (i = 0; i < ComplaintsCounter; i++)
					{
						if (AllComplaints[i].ID == Complaint.ID)
						{
							break;
						}
					}
					for (short j = i; j < ComplaintsCounter - 1; j++)
					{
						AllComplaints[j] = AllComplaints[j + 1];
					}
					--ComplaintsCounter;
					printf("\n the complaint deleted successfully!");
				}
				else
					printf("\nOperation Canceled!");
			}
			else
				printf("\n the complaint that you're looking for doesn't exist.");


		}
		void ShowUpdateComplaintScreen()
		{
			///printf("\n update complaint screen will be here.. ");
			DrawScreenHeader("Complaint Manager", "Update complaint");

			stComplaint Complaint;
			if (FindComplaintByID(&Complaint, ReadPositiveNumber("\n enter an ID to serch for : ")))
			{
				printf("\n found ! \n");
				PrintComplaintInfo(Complaint);
				printf("\n Are you sure do you want to update the Complaint above ? [Y/N]..");
				char Answer = 'n';
				scanf_s(" %c", &Answer);//!
				getchar();
				if (tolower(Answer) == 'y')
				{
					short i = 0;
					for (i = 0; i < ComplaintsCounter; i++)
					{
						if (AllComplaints[i].ID == Complaint.ID)
						{
							ReadString(AllComplaints[i].MadeBy, sizeof(AllComplaints[i].MadeBy), "\nCustmor name : ");
							ReadString(AllComplaints[i].Category, sizeof(AllComplaints[i].Category), "\n Category : ");
							ReadString(AllComplaints[i].Reason, sizeof(AllComplaints[i].Reason), "\n Reason : ");
							ReadString(AllComplaints[i].Description, sizeof(AllComplaints[i].Description), "\nDescription : ");
							AllComplaints[i].Status = (enum enClaimStatus)ReadNumberInRange(-1, 1, "\n please set Complaint status :\nChoose \'-1\'for rejected,\'0\'for Inprogress,\'1\'for resolved : ");
							printf("\n the complaint updated successfully!");
							PrintComplaintInfo(AllComplaints[i]);

							
							break;
						}
					}
				}
				else
					printf("\nOperation Canceled!");
			}
			else
				printf("\n the complaint that you're looking for doesn't exist.");

		}
			enum enFindComplaintOption
{
	eComplaintID = 1, eClientName = 2, eSubmissionDate, eStatus
};
			enum enFindComplaintOption ReadFindComplaintOption()
{
	return (enum enFindComplaintOption)ReadNumberInRange(1, 4, "\nMake a choice to serch by : ");
}
			bool FindComplaintByID(stComplaint* Complaint, int ID)
			{
				for (short i = 0; i < ComplaintsCounter; i++)
				{
					if (AllComplaints[i].ID == ID)
					{
						*Complaint = AllComplaints[i];
						return true;
					}
				}
				//if you reached here this means that the complaint is not found!
				return false;
			}
			void PrintComplaintInfo(stComplaint Complaint)
{
	printf("\n\n\t the following are the complaint's info : ");
	printf("\n %s%02d%s", "__________________ID = ", Complaint.ID, "_____________________");
	printf("\n\t ID  : %d", Complaint.ID);
	printf("\n\t Reason : %s", Complaint.Reason);
	printf("\n\t Description : %s", Complaint.Description);
	printf("\n\t Status : %s", (Complaint.Status == eRejected ? "Rejected" : Complaint.Status == eInProgress ? "Pending" : "Resolved"));
	printf("\n %s%s", "_______________________", "_______________________");

}
			void ShowFindComplaintByIDScreen()
{
	//printf("\n Find complaint by ID screen will  be here..");
	DrawScreenHeader("Find Complaint", "By ID");

	stComplaint Complaint;
	if (FindComplaintByID(&Complaint,ReadPositiveNumber("\n enter an ID to serch for : ")))
	{
		printf("\n found ! \n");
		PrintComplaintInfo(Complaint);
	}
	else
		printf("\n the complaint that you're looking for doesn't exist.");

}
			void ShowFindComplaintByNameScreen()
			{
				//printf("\n ShowFindComplaintByNameScreen will be here.. ");
				DrawScreenHeader("Find Complaint", "By Name");
				short Counter = 0;
				stComplaint Complaint;
				ReadString(Complaint.MadeBy, sizeof(Complaint.MadeBy), "\nEnter a Customer name : ");
				for (short i = 0; i < ComplaintsCounter; i++)
				{
					if (strcmp(AllComplaints[i].MadeBy, Complaint.MadeBy) == 0)
					{
						FindComplaintByID(&Complaint, AllComplaints[i].ID);
						printf("\n\nComplaint %d : \n", ++Counter);
						PrintComplaintInfo(Complaint);
						break;
					}
				}
				(Counter == 0) ? printf("\n no complaints for this name : \"%s\"", Complaint.MadeBy) : printf("");


			}
			void ShowFindComplaintByDateScreen()
{
	//printf("\n ShowFindComplaintByDateScreen will be here..");
	DrawScreenHeader("Find Complaint", "By Submission Date");
	short Counter = 0;
	stComplaint Complaint;
	ReadString(Complaint.Date, sizeof(Complaint.Date), "\nEnter a Date \"dd/mm/yyyy\" : ");
	for (short i = 0; i < ComplaintsCounter; i++)
	{
		if (strcmp(AllComplaints[i].Date, Complaint.Date)==0)
		{
			FindComplaintByID(&Complaint, AllComplaints[i].ID);
			printf("\n\nComplaint %d : \n",++Counter);
			PrintComplaintInfo(Complaint);
			break;
		}
	}
	(Counter == 0)? printf("\n there is no complaint for this Date : \"%s\"", Complaint.Date) : printf("");

}
			void ShowFindComplaintByStatusScreen()
{
	//printf("\n ShowFindComplaintByStatusScreen will be here.. ");
	DrawScreenHeader("Find Complaint", "By Status");
	printf("\n\n wich status are you looking for : ");
	printf("\n%s\n%s\n%s\n", "[1] Rejected", "[2] Pending" ,"[3] Resolved");

	stComplaint Complaint;
	Complaint.Status= (enum enClaimStatus)ReadNumberInRange(1, 3, "\n Choose from the menu above : ")-2;
	short Counter = 0;
	for (short i = 0; i < ComplaintsCounter; i++)
	{
		if (AllComplaints[i].Status == Complaint.Status)
		{
			FindComplaintByID(&Complaint, AllComplaints[i].ID);
			printf("\n\nComplaint %d : \n", ++Counter);
			PrintComplaintInfo(Complaint);

		}
	}
	(Counter == 0) ? printf("\n No complaint matches the status you're looking for") : printf("");

}
			void PerformFindComplaintMenuOption(enum enFindComplaintOption Option)
{
	switch (Option)
	{
	case eComplaintID:
		system("cls");
		ShowFindComplaintByIDScreen();
		break;
	case eClientName:
		system("cls");
		ShowFindComplaintByNameScreen();
		break;
	case eSubmissionDate:
		system("cls");
		ShowFindComplaintByDateScreen();
		break;
	case eStatus:
		system("cls");
		ShowFindComplaintByStatusScreen();
		break;
	default:
		break;
	}
}
		void ShowFindClaimScreen()
{
	//printf("\n find claim screen will be here.. ");

	DrawScreenHeader("Complaints manager", "Find Complaint screen");
	printf("\n\n You can serch for a specific complaint by : ");
	printf("\n\n \t[1] Complaint ID .");
	printf("\n \t[2] Client Name .");
	printf("\n \t[3] Submission Date.");
	printf("\n \t[4] By Status.");
	 
	PerformFindComplaintMenuOption(ReadFindComplaintOption());
}

		void SortComplaintsByPriority()
		{
			for (short i = 0; i < ComplaintsCounter - 1; i++)
			{
				for (short j = 0; j < ComplaintsCounter - i - 1; j++)
				{
					if (AllComplaints[j].Priority > AllComplaints[j + 1].Priority)
					{
						stComplaint tempComplaint = AllComplaints[j];
						AllComplaints[j] = AllComplaints[j + 1];
						AllComplaints[j + 1] = tempComplaint;
					}
				}
			}


				/*
				
						for (size_t i = 0; i < ArrLength-1; i++)
						{
							for (size_t j = 0; j < ArrLength-i-1; j++)
							{
								if (Arr[j] > Arr[j+1 ])
								{
									Swap(Arr[j], Arr[j + 1]);
								}

							}
						}

				*/
		}
		void PrintSortedComplaintsByPriority()
		{
			
			printf("\n____________________________________________________________________________");
			printf("\n|%-4s|%-60s|%-10s|", "ID", "Description ", "Priority");
			printf("\n____________________________________________________________________________");

			if (ComplaintsCounter > 0)
			{
				for (short i = 0; i < ComplaintsCounter; i++)
				{
					printf("\n|%-4d|%-60s|%-10s|",AllComplaints[i].ID ,AllComplaints[i].Description,
						AllComplaints[i].Priority == eHigh ? "High" : AllComplaints[i].Priority == eMedium ? "Medium" : "Low");
				}
			}
			else
				printf("\n\t\t no available complaints in the system!");
			printf("\n____________________________________________________________________________\n");

		}
		void ShowOrderedClaimsScreen()
		{
			//printf("\n ordered claims list screen will be here..");
			DrawScreenHeader("Ordered Complaints", "By Priority");
			SortComplaintsByPriority();
			PrintSortedComplaintsByPriority();

		}
		void ShowStaticsMenuScreen()
{
	printf("\n statics and reports menu screen will be here.. ");
}
		void ShowManageUsersScreen()
{
	printf("\n manage users screen will be here..");
}
		void ShowProcessComplaintScreen()
		{
			//printf("\n process complaintscreen will be here..");
			DrawScreenHeader("Complaints Manager", "Process Complaint");
		
			stComplaint Complaint;
			if (FindComplaintByID(&Complaint, ReadPositiveNumber("\n enter an ID to serch for : ")))
			{
				printf("\n found ! \n");
				PrintComplaintInfo(Complaint);

				printf("\nto mark it as \"rejected\" choose -1 ");
				printf("\nto mark it as \"in progress\" choose 0 ");
				printf("\nto mark it as \"solved\" choose 1 ");

				enum enClaimStatus NewStatus =(enum enClaimStatus) ReadNumberInRange(-1,1,"\n your Choice : ");
				for (short i = 0; i < ComplaintsCounter; i++)
				{
					if (AllComplaints[i].ID == Complaint.ID)
					{
						AllComplaints[i].Status = NewStatus;
						printf("\ndo you want to add notes : [Y/N]");
						char Answer = 'n';
						scanf_s(" %c", &Answer);
						getchar();
						if (tolower(Answer) == 'y')
						{						

							ReadString(AllComplaints[i].Notes, sizeof(AllComplaints[i].Notes), "\n your notes : ");
						}

						break;
					}
				}
			}
			else
				printf("\n the complaint that you're looking for doesn't exist.");



		}
		void PerformUsersMenuOption(enum enMainMenuOption Option)
{
	switch (Option)
	{
	case eShowComplaintsList:
		system("cls");
		ShowComplaintsListScreen();
		GoBackToMainMenuScreen();
		break;
	case eUpdateComplaint:
		system("cls");
		ShowUpdateComplaintScreen();
		GoBackToMainMenuScreen();
		break;
	case eDeleteComplaint:
		system("cls");
		ShowDeleteComplaintScreen();
		GoBackToMainMenuScreen();
		break;
	case eFindClaim:
		system("cls");
		ShowFindClaimScreen();
		GoBackToMainMenuScreen();
		break;
	case eProcessComplaint:
		system("cls");
		ShowProcessComplaintScreen();
		GoBackToMainMenuScreen();
		break;
	case eShowOrderedClaims:
		system("cls");
		ShowOrderedClaimsScreen();
		GoBackToMainMenuScreen();
		break;
	case eStatics:
		system("cls");
		ShowStaticsMenuScreen();
		GoBackToMainMenuScreen();
		break;
	case eManageUsers:
		system("cls");
		ShowManageUsersScreen();
		GoBackToMainMenuScreen();
		break;
	case eExist:  
		break;
	default:
		break;
	}
}
		void GoBackToMainMenuScreen()
{
	printf("\npress any key to go back to main screen ..");
	system("pause>0");
	ShowUsersMenuScreen();
}
	void ShowUsersMenuScreen()
{
	system("cls");
	DrawScreenHeader("Complaints Management system", "Main Menu screen");
	printf("\n%10s%s", "", "[1] Show Complaints list.");
	printf("\n%10s%s", "", "[2] Update Complaint.");
	printf("\n%10s%s", "", "[3] Delete complaint.");
	printf("\n%10s%s", "", "[4] Find Complaint.");
	printf("\n%10s%s", "", "[5] Process Complaint.");
	printf("\n%10s%s", "", "[6] Claims ordered by priority.");
	printf("\n%10s%s", "", "[7] Statics and Reports.");
	printf("\n%10s%s", "", "[8] MANAGE USERS.");
	printf("\n%10s%s", "", "[9] EXIT.");


	PerformUsersMenuOption(ReadMainMenuOption());
	system("cls");

}





		enum enClientMenuOption
{
	eAddComplaint = 1, eShowClientComplaint = 2, eUpdateComplaintByClient = 3,Exit

};
		enum enClientMenuOption ReadClientOption()
{
	return (enum enClientMenuOption)ReadNumberInRange(1, 4, "\nChoose what do you wanna do [1,4]..");
}
		void GoBackToClientsMenuScreen()
{
	printf("\nPress any key to go back to main menu ..");
	system("pause>0");
	ShowClientsMenuScreen();
}


		void LowerAllString(char *S1,size_t Length)
		{
			for (size_t i = 0; i < Length; i++)
			{
				S1[i] = tolower(S1[i]);
			}
		}

		void SetComplaintPriority()
		{
			LowerAllString(AllComplaints[ComplaintsCounter].Description, strlen(AllComplaints[ComplaintsCounter].Description));
			char HighPriorityKeyWords[2][20] = { "urgent","immediate" };
			char MediumPriorityKeyWords[2][20] = { "important","problem" };
			for (size_t i = 0; i < 2; i++)
			{
				if (strstr(AllComplaints[ComplaintsCounter].Description,HighPriorityKeyWords[i]) != NULL)
				{
					AllComplaints[ComplaintsCounter].Priority = eHigh;
					return;//to exist func immediatly
				}
			}

			for (size_t i = 0; i < 2; i++)
			{
				if (strstr(AllComplaints[ComplaintsCounter].Description, MediumPriorityKeyWords[i])!= NULL)
				{
					AllComplaints[ComplaintsCounter].Priority = eMedium;
					return;
				}
				
			}
			//if we reched here,this means that the complaint has a low priority
			AllComplaints[ComplaintsCounter].Priority = eLow;

		}
		void ShowAddComplaintScreen()
		{
			//printf("\n add a complaiment screen will be here.. ");
			DrawScreenHeader("Complaints manager", "Add a complaint");
			AllComplaints[ComplaintsCounter].ID = GenerateUniqueID();
			ReadString(AllComplaints[ComplaintsCounter].Reason, sizeof(AllComplaints[ComplaintsCounter].Reason), "\nComplaint Reason : ");
			ReadString(AllComplaints[ComplaintsCounter].Description, sizeof(AllComplaints[ComplaintsCounter].Description), "\nDescription : ");
			AllComplaints[ComplaintsCounter].Status = eInProgress;
			
			ReadString(AllComplaints[ComplaintsCounter].Category, sizeof(AllComplaints[ComplaintsCounter].Category), "\nCategory : ");
			GetSystemDate(AllComplaints[ComplaintsCounter].Date, sizeof(AllComplaints[ComplaintsCounter]));
			strcpy_s(AllComplaints[ComplaintsCounter].MadeBy, sizeof(AllComplaints[ComplaintsCounter].MadeBy), CurrentUser.FullName);
		    SetComplaintPriority();
			
			printf("\n\a added successfully!");
			printf("\n\n the following are the complaint's info : ");
			printf("\n Reason : %s", AllComplaints[ComplaintsCounter].Reason);
			printf("\n Description : %s", AllComplaints[ComplaintsCounter].Description);
			printf("\n\n date : %s", AllComplaints[ComplaintsCounter].Date);

			ComplaintsCounter++;
		}
		void ShowComplaintsListByClientScreen()
{
	printf("\n complaints made by the current client will be here.. ");
}
		void ShowUpdateComplaintByClientScreen()
		{
			printf("\n update complaint by client will be here..");
		}
		void PerformClientMenuOption(enum enClientMenuOption Option)
		{
			switch (Option)
	{
	case eAddComplaint:
		system("cls");
		ShowAddComplaintScreen();
		GoBackToClientsMenuScreen();
		break;
	case eShowClientComplaint:
		system("cls");
		ShowComplaintsListByClientScreen();
		GoBackToClientsMenuScreen();

		break;
	case eUpdateComplaintByClient:
		system("cls");
		ShowUpdateComplaintByClientScreen();
		GoBackToClientsMenuScreen();
	case Exit:
		break;
	default:
		break;
	}
		}
	void ShowClientsMenuScreen()
{
	system("cls");
	DrawScreenHeader("Complaints Management system", "Main Menu screen");
	printf("\n%10s%s", "", "[1] Add a complaint.");
	printf("\n%10s%s", "", "[2] show your own complaints.");
	printf("\n%10s%s", "", "[3] Update Complaint .");
	printf("\n%10s%s", "", "[4] Exit .");

	PerformClientMenuOption(ReadClientOption());


}

void ShowMainMenuScreen()
{
	CurrentUser.IsClient ? ShowClientsMenuScreen() : ShowUsersMenuScreen();
}





void SetDefaultAdminInfo()
{
	char* Name = "Mohamed", * UserName = "admin", * Password = "admin";
	strcpy_s(aUsers[0].FullName, sizeof(aUsers[0].FullName), Name);
	strcpy_s(aUsers[0].UserName, sizeof(aUsers[0].UserName), UserName);
	strcpy_s(aUsers[0].Password, sizeof(aUsers[0].Password), Password);
	aUsers[0].Permssions = -1;
	aUsers[0].IsClient = 0;
}
bool CheckIdentity(char* UserName, size_t UserNameSize, char* Password, size_t PasswordSize)
{
	for (short i = 0; i < UsersCounter; i++)
	{
		if (strcmp(UserName, aUsers[i].UserName) == 0 && strcmp(Password, aUsers[i].Password)==0)
		{
			CurrentUser = aUsers[i];
			return true;
		}
	}
	return false;
}

void SignIn()
{
	do
	{
			system("cls");
			DrawScreenHeader("COMPLAINTS SECTION", "SIGN IN");

			char UserName[20], Password[20];
			short Counter = 3;

			ReadString(UserName, sizeof(UserName), "\nUserName : ");
			ReadString(Password, sizeof(Password), "\nPassword : ");
			if (!CheckIdentity(UserName, sizeof(UserName), Password, sizeof(Password)))
			{
				printf("\n\a wrong username/password!");
				printf("\n You have (%hd) trials to login : ", --Counter);
				ReadString(UserName, sizeof(UserName), "\nUserName : ");
				ReadString(Password, sizeof(Password), "\nPassword : ");

			}
			else
			{
				ShowMainMenuScreen();
			}

			if (Counter == 1)
			{
				//sleep function for 30sec
				printf("\n try again after 10seconds!\n\n\a");
				Sleep(10 * 1000);

				Counter = 0;
			}


	} while (true);



}

bool UserNameExist(char* UserName, size_t Size)
{
	for (short i = 0; i < UsersCounter; i++)
	{
		if (strcmp(aUsers[i].UserName, UserName)==0)
			return true;

	}
	//if you reached here then the User with this username doesn't exist
	return false;
}

bool IsLowerCaseExist(char* S1, size_t Length)
{
	for (short i = 0; i < Length; i++)
	{
		if ((int)S1[i] >= 97 && (int)S1[i] <= 122)
			return true;
	}
	return false;
}

bool IsUpperCaseExist(char* S1, size_t Length)
{
	for (short i = 0; i < Length; i++)
	{
		if ((int)S1[i] >= 65 && (int)S1[i] <= 90)
			return true;
	}
	return false;

}
bool IsDigitExist(char *S1,size_t Length)
{
	for (short i = 0; i < Length; i++)
	{
		if ((int)S1[i] >= 48 && (int)S1[i] <= 57)
			return true;
	}
	return false;

}
bool IsSpecialCharExist(char* S1, size_t Length)
{
	for (short i = 0; i < Length; i++)
	{
		if ((int)S1[i] >= 32 && (int)S1[i] <= 64)
			return true;
	}
	return false;

}

bool CheckPasswordStrength(char *Password)
{
	size_t len = strlen(Password);
	return (len >= 8 && IsDigitExist(Password, len) && IsUpperCaseExist(Password, len)
		&& IsSpecialCharExist(Password, len) && IsLowerCaseExist(Password, len));

}

void SignUp()
{
	system("cls");
	DrawScreenHeader("COMPLAINTS SECTION", "SIGN UP");
	char UserName[20], Password[20], Name[40];
	ReadString(Name, sizeof(Name), "\nYour Name : ");


	ReadString(UserName, sizeof(UserName), "\nUserName : ");
	while (UserNameExist(UserName, sizeof(UserName)))
	{
		printf("\n Username already exists try again..");
		ReadString(UserName, sizeof(UserName), "\nUserName : ");

	}

	ReadString(Password, sizeof(Password), "\nPassword : ");
	while (!CheckPasswordStrength(Password))
	{
		printf("\n a strong password should contains at last : CAPITAL letter, small letter,number and special char. ");
		ReadString(Password, sizeof(Password), "\nPassword : ");

	}
	strcpy_s(aUsers[++UsersCounter - 1].FullName, sizeof(aUsers[UsersCounter - 1].FullName), Name);
	strcpy_s(aUsers[UsersCounter - 1].UserName, sizeof(aUsers[UsersCounter - 1].UserName), UserName);
	strcpy_s(aUsers[UsersCounter - 1].Password, sizeof(aUsers[UsersCounter - 1].Password), Password);
	aUsers[UsersCounter - 1].IsClient = true;
	aUsers[UsersCounter - 1].Permssions = 0;

	printf("\nDone Successfully! \nusername : %s , Password : %s\npress any key to continue..", UserName, Password);
	
	system("pause>0");
	SignIn();
}

void ShowEndProgramScreen()
{
	system("cls");
	printf("\n program ends ");
	system("pause>0");
}


void ComplaintsManager()
{
	DrawScreenHeader("COMPLAINTS SECTION", "WELCOME");

	printf("\n\n by submitting your complaints you help us to improve our sevices :-)");

	printf("\n\n\n Please Sign in  if you already have an account .\n if you don't then thanks for singing up : ");
	printf("\n\n\t [1] SIGN UP ");
	printf("\n\n\t [2] SIGN IN \n");
	SetDefaultAdminInfo();
	int Choice=ReadNumberInRange(1, 2, "\n please make a choice from the menu above ,you can either sign up or sign in : \n");

	Choice == 1 ? SignUp() : SignIn();
	
	 
	ShowEndProgramScreen();
}
