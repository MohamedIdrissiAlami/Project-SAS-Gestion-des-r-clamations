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
	time_t now= time(NULL);//number of secs since 1/1/1970
	sDate = ctime_s(sDate,Size, & now);
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

void ShowFindClaimScreen()
{
	printf("\n find claim screen will be here.. ");
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