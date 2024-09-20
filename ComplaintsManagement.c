#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void DrawScreenHeader(const char[], const char[]);
int ReadNumber(const char[]);
int ReadPositiveNumber(const char[]);
int ReadNumberInRange(int, int, const char[]);
enum enMainMenuOption;
enum enMainMenuOption ReadMainMenuOption(void);
void PerformMainMenuOption(enum enMainMenuOption);
void ReadString(char* , size_t , const char []);
void ShowMainMenuScreen(void);
void GoBackToMainMenuScreen(void);

void ShowAddComplaintScreen(void);
		enum enComplaintCategory;
		enum enClaimStatus;
		enum enComplaintCategory GetComplaintCategory(void);
		bool IsIDExist(int );
		int GenerateUniqueID();
		void GetSystemDate(char* , size_t );
void ShowComplaintsListScreen(void);
void ShowDeleteComplaintScreen(void);
void ShowUpdateComplaintScreen(void);
void ShowFindClaimScreen(void);
		enum enFindComplaintOption;
		enum enFindComplaintOption ReadFindComplaintOption(void);
		bool FindComplaintByID(stComplaint* , int );
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
	ShowMainMenuScreen();
	return 0;
}

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
	eAddComplaint=1,eShowComplaintsList=2,eUpdateComplaint=3,eDeleteComplaint=4,eFindClaim=5,eShowOrderedClaims=6,eStatics=7
};

enum enMainMenuOption ReadMainMenuOption()
{
	return (enum enMainMenuOption)ReadNumberInRange(1, 7, "\nChoose what do you wanna do [1~7] : ");
}

enum enComplaintCategory
{
	eUndefined = 1
};
enum enClaimStatus
{
	eRejected = -1,eInProgress=0,eResolved=1
};

typedef struct
{
	int ID;
	char Reason[100];
	char Description[200];
	enum enClaimCategory Category;
	enum enStatus Status;
	char Date[20];

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
enum enComplaintCategory GetComplaintCategory()
{
	return eUndefined;
	//we will handle this issue later
}
void GetSystemDate(char* sDate,size_t Size)
{
	 time_t Now= time(NULL);//get current time
	//sDate = ctime_s(sDate,Size, & Now);
	struct tm *CurrentTime=localtime(&Now);
	sprintf_s(sDate, Size, "%02d/%02d/%d", CurrentTime->tm_mday, CurrentTime->tm_mon + 1, CurrentTime->tm_year + 1900);
}
void ShowAddComplaintScreen()
{
	//printf("\n add a complaiment screen will be here.. ");
	DrawScreenHeader("Complaints manager", "Add a complaint");
	AllComplaints[ComplaintsCounter];
	AllComplaints[ComplaintsCounter].ID = GenerateUniqueID();
	ReadString(AllComplaints[ComplaintsCounter].Reason, sizeof(AllComplaints[ComplaintsCounter].Reason), "\nComplaint Reason : ");
	ReadString(AllComplaints[ComplaintsCounter].Description, sizeof(AllComplaints[ComplaintsCounter].Description), "\nDescription : ");
	AllComplaints[ComplaintsCounter].Status = eInProgress;
	AllComplaints[ComplaintsCounter].Category = GetComplaintCategory(AllComplaints[ComplaintsCounter].Description);
	GetSystemDate(AllComplaints[ComplaintsCounter].Date,sizeof(AllComplaints[ComplaintsCounter]));

	printf("\n\a added successfully!");
	printf("\n\n the following are the complaint's info : ");
	printf("\n Reason : %s", AllComplaints[ComplaintsCounter].Reason);
	printf("\n Description : %s", AllComplaints[ComplaintsCounter].Description);
	printf("\n\n date : %s", AllComplaints[ComplaintsCounter].Date);
	ComplaintsCounter++;
}



void ShowComplaintsListScreen()
{
	printf("\n Complaints list screen will be here..");
}

void ShowDeleteComplaintScreen()
{
	printf("\n delete complaint screen will be here.. ");
}

void ShowUpdateComplaintScreen()
{
	printf("\n update complaint screen will be here.. ");
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
	printf("\n ShowFindComplaintByNameScreen will be here.. ");
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


void ShowOrderedClaimsScreen()
{
	printf("\n ordered claims list screen will be here..");
}

void ShowStaticsMenuScreen()
{
	printf("\n statics and reports menu screen will be here.. ");
}

void PerformMainMenuOption(enum enMainMenuOption Option)
{
	switch (Option)
	{
	case eAddComplaint:
		system("cls");
		ShowAddComplaintScreen();
		GoBackToMainMenuScreen();
	case eShowComplaintsList:
		system("cls");
		ShowComplaintsListScreen();
		GoBackToMainMenuScreen();
	case eDeleteComplaint:
		system("cls");
		ShowDeleteComplaintScreen();
		GoBackToMainMenuScreen();
	case eUpdateComplaint:
		system("cls");
		ShowUpdateComplaintScreen();
		GoBackToMainMenuScreen();
	case eFindClaim:
		system("cls");
		ShowFindClaimScreen();
		GoBackToMainMenuScreen();
	case eShowOrderedClaims:
		system("cls");
		ShowOrderedClaimsScreen();
		GoBackToMainMenuScreen();
	case eStatics:
		system("cls");
		ShowStaticsMenuScreen();
		GoBackToMainMenuScreen();

	default:
		break;
	}
}

void GoBackToMainMenuScreen()
{
	printf("\npress any key to go back to main screen ..");
	system("pause>0");
	ShowMainMenuScreen();
}

void ShowMainMenuScreen()
{
	system("cls");
	DrawScreenHeader("Complaints Management system", "Main Menu screen");
	printf("\n%10s%s", "", "[1] Add a complaint.");
	printf("\n%10s%s", "", "[2] Show Complaints list.");
	printf("\n%10s%s", "", "[3] Update Complaint.");
	printf("\n%10s%s", "", "[4] Delete complaint.");
	printf("\n%10s%s", "", "[5] Find Claim.");
	printf("\n%10s%s", "", "[6] Claims ordered by priority.");
	printf("\n%10s%s", "", "[7] Statics and Reports.");

	PerformMainMenuOption(ReadMainMenuOption());


}