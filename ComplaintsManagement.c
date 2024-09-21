#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>


void ComplaintsManager(void);
		typedef struct stUser;
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
	printf("\n%10s%s", "", "[8] MANAGE USERS.");
	printf("\n%10s%s", "", "[7] LOGOUT.");



	PerformMainMenuOption(ReadMainMenuOption());


}

typedef struct stUser
{
	char FullName[45];
	char UserName[20];
	char Password[20];
	int Permssions;

}stUser;

stUser aUsers[100];
short UsersCounter = 1;
stUser CurrentUser;

void SetDefaultAdminInfo()
{
	char* Name = "Mohamed", * UserName = "admin", * Password = "admin";
	strcpy_s(aUsers[0].FullName, sizeof(aUsers[0].FullName), Name);
	strcpy_s(aUsers[0].UserName, sizeof(aUsers[0].UserName), UserName);
	strcpy_s(aUsers[0].Password, sizeof(aUsers[0].Password), Password);
	aUsers[0].Permssions = -1;
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
	system("cls");
	DrawScreenHeader("COMPLAINTS SECTION", "SIGN IN");

	char UserName[20], Password[20];
	short Counter = 3;
	while (true)
	{
		ReadString(UserName, sizeof(UserName), "\nUserName : ");
		ReadString(Password, sizeof(Password), "\nPassword : ");
		if (!CheckIdentity(UserName, sizeof(UserName), Password, sizeof(Password)))
		{
			printf("\n\a wrong username/password!");
			printf("\n You have (%hd) trials to login : ", --Counter);
		}
		else
		{
			ShowMainMenuScreen();


		}

		if (Counter == 0)
		{
			//sleep function for 30sec
			printf("\n try again after 10seconds!\n\n\a\a\a");
			Sleep(10 * 1000);

			Counter = 0;
		}

	}

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


	printf("\nDone Successfully! \nusername : %s , Password : %s\npress any key to continue..", UserName, Password);
	
	system("pause>0");
	SignIn();
}


void ShowEndProgramScreen()
{
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
	
	//failed to sign in 
	ShowEndProgramScreen();
}