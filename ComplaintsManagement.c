#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>


typedef struct stUser;
enum enPermissions;
enum enMainMenuOption;
enum enClaimStatus;
enum enComplaintPriority;
enum enFindComplaintOption;
enum enStaticsMenuOption;
enum enManageUsersOption;


typedef struct stComplaint;

int ReadNumber(const char[]);
int ReadPositiveNumber(const char[]);
int ReadNumberInRange(int, int, const char[]);
void ReadString(char S1[], size_t, const char[]);
int RandomNumber(int, int);
void DrawScreenHeader(const char[], const char[]);
void PrintAccessDeniedMessage(void);
bool CheckAccessRights(enum enPermission);
void GetSystemDate(char sDate[], size_t);
void LowerAllString(char*, size_t);



void ComplaintsManager(void);
void SignUp(void);
void SetUserName(char[]);
bool UserNameExists(char*);
void SetPassword(char[],size_t);
bool IsValidPassword(char[]);
bool CheckPasswordStrength(char*);
bool IsSpecialCharExist(char*, size_t);
bool IsDigitExist(char*, size_t);
bool IsUpperCaseExist(char*, size_t);
bool IsLowerCaseExist(char*, size_t);

void SignIn(void);
void SetDefaultAdminInfo(void);
bool CheckIdentity(char*, size_t, char*, size_t);
void ShowMainMenuScreen(void);
void ShowClientsMenuScreen(void);
void PerformClientMenuOption(enum enClientMenuOption);
enum enClientMenuOption ReadClientOption(void);
void GoBackToClientsMenuScreen(void);
void ShowAddComplaintScreen(void);
void SetComplaintPriority(void);
int GenerateUniqueID(void);
bool IsIDExist(int);
void ShowComplaintsListByClientScreen(void);
void ShowUpdateComplaintByClientScreen(void);
bool CanClientUpdateComplaint(int);
void ShowUsersMenuScreen(void);
void PerformUsersMenuOption(enum enMainMenuOption);
enum enMainMenuOption ReadMainMenuOption(void);
void GoBackToMainMenuScreen(void);
void ShowComplaintsListScreen(void);
void PrintComplaintRecord(stComplaint);

void ShowUpdateComplaintScreen(void);

void ShowDeleteComplaintScreen(void);

void ShowFindClaimScreen(void);
void PerformFindComplaintMenuOption(enum enFindComplaintOption);
enum enFindComplaintOption ReadFindComplaintOption(void);
void ShowFindComplaintByIDScreen(void);
bool FindComplaintByID(struct stComplaint*, int);
void PrintComplaintInfo(stComplaint);
void ShowFindComplaintByNameScreen(void);
void ShowFindComplaintByDateScreen(void);
void ShowFindComplaintByStatusScreen(void);

void ShowProcessComplaintScreen(void);

void ShowOrderedClaimsScreen(void);
void SortComplaintsByPriority(void);
void PrintSortedComplaintsByPriority(void);

void ShowStaticsMenuScreen();
void PerformStaticsMenuOption(enum enStaticsMenuOption);
enum enStaticsMenuOption ReadStaticsMenuOption(void);
void GoBackToStaticsMenuScreen(void);
void ShowComplaintTotalNumberScreen(void);
void ShowComplaintResolutionRateScreen(void);
float CalculateResolutionRate(void);
void ShowProcessTimeAverageScreen(void);
float CaluculateProcessTimeAverage(void);
float ArrayAverage(int[100], int);
int ArraySum(int[100], int);

void ShowManageUsersScreen(void);
void PerformManageUsersMenuOption(enum enManageUsersOption);
void GoBackToManageMenuUsersScreen(void);
void ShowFindUserScreen(void);
void PrintUserCard(stUser);
void PrintUserPermissions(int);
bool FindUserByUserName(char*, struct stUser*);
void ShowUsersListScreen(void);
void PrintUserRecordLine(stUser);
void ShowAddNewUserScreen(void);
void ShowDeleteUserScreen(void);
void  DeleteUserByUserName(char*);
void ShowUpdateUserScreen(void);
void UpdateUserByUserName(char[]);
int ReadUserPermissions(void);


/*

0 = Black       8 = Gray
1 = Blue        9 = Light Blue
2 = Green       A = Light Green
3 = Aqua        B = Light Aqua
4 = Red         C = Light Red
5 = Purple      D = Light Purple
6 = Yellow      E = Light Yellow
7 = White       F = Bright White
*/


int main()
{
	//seeds the random numbers generator in C,called only once;
	srand((unsigned)time(NULL));
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
enum enPermissions
{
	pNothing = 0, pFullAccess = -1, pComplaintsList = 1, pUpdateComplaint = 2, pDeleteComplaint = 4, pFindComplaint = 8, pProcessComplaint = 16,
	pOrderedComplaintsList = 32, pStatistics = 64, pManageUsers = 128
};
enum enMainMenuOption
{
	eShowComplaintsList = 1, eUpdateComplaint = 2, eDeleteComplaint = 3,
	eFindClaim = 4, eProcessComplaint = 5, eShowOrderedClaims = 6, eStatics = 7, eManageUsers = 8, eExist = 9
};
enum enClaimStatus
{
	eRejected = -1, eInProgress = 0, eResolved = 1
};
enum enComplaintPriority { eHigh = 1, eMedium = 2, eLow = 3 };
typedef struct
{
	int ID;
	char Reason[100];
	char Description[200];
	char Category[30];
	enum enClaimStatus Status;
	char Date[20];
	time_t SubmissionMoment;
	time_t ProcessingComplaintMoment;
	char MadeBy[40];
	char Notes[40];
	enum enComplaintPriority Priority;

}stComplaint;
enum enClientMenuOption
{
	eAddComplaint = 1, eShowClientComplaint = 2, eUpdateComplaintByClient = 3, Exit

};
enum enFindComplaintOption
{
	eComplaintID = 1, eClientName = 2, eSubmissionDate, eStatus
};
enum enManageUsersOption { eUsersList = 1, eAddNewUsers = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eQuitManageMenu = 6 };
enum enStaticsMenuOption
{
	eComplaintTotalNumber = 1, eComplaintResolutionRate = 2, eProcessTimeAverage = 3, eQuitStatics = 4
};




stUser aUsers[100];
short UsersCounter = 0;
stUser CurrentUser;
stComplaint AllComplaints[100];
int ComplaintsCounter = 0;



/*********************************-Util fuctions-*************************/
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
int ReadNumberInRange(int From, int To, const char Message[])
{
	int Number = 0;
	do
	{
		Number = ReadNumber(Message);
		if (Number<From || Number>To)
			printf("\nout of range try again..");
	} while (Number<From || Number>To);
	return Number;
}
void ReadString(char S1[], size_t Size, const char Message[])
{
	printf("\n%s", Message);

	do
	{
		fgets(S1,Size, stdin);
		size_t StringLength = strlen(S1);

		// removing the new line char due to use fgets():
		if (StringLength > 0 && S1[StringLength - 1] == '\n')
			S1[StringLength - 1] = '\0';
	
	} while (strlen(S1) == 0);//make sure that the string entered is not empty
}
int RandomNumber(int From, int To)
{
	return (rand() % (To - From + 1)) + From;
}
void DrawScreenHeader(const char Title[], const char Subtitle[])
{
	system("color 0e");//set color to Light Yellow

	printf("\nAlami Co,ltd all rights reserved 2024");
	printf("\n%15s%s", "", "========================================");
	printf("\n%20s%s\n%25s%s", "", Title, "", Subtitle);
	printf("\n%15s%s\n", "", "========================================");

	time_t Now = time(NULL);
	printf("\n%15s%s%s", "", "current time : ", ctime(&Now));
	if (UsersCounter >=1)
	{
		printf("\n%15s%s%s\n\n", "", "Current User : ", aUsers[UsersCounter - 1].UserName);

	}

}
void PrintAccessDeniedMessage()
{
	system("cls");
	DrawScreenHeader("ACCESS DENIED", "CONTACT YOUR ADMIN");
	system("color f4");
}
bool CheckAccessRights(enum enPermission Permission)
{
	return ((enum enPermission)CurrentUser.Permssions) == pNothing ? false :
		((enum enPermission)CurrentUser.Permssions == pFullAccess ? true
			: ((CurrentUser.Permssions & Permission) == Permission));
}
void GetSystemDate(char sDate[], size_t Size)
{
	time_t Now = time(NULL);//get current time
	//sDate = ctime_s(sDate,Size, & Now);
	struct tm* CurrentTime = localtime(&Now);
	sprintf_s(sDate, Size, "%02d/%02d/%d", CurrentTime->tm_mday, CurrentTime->tm_mon + 1, CurrentTime->tm_year + 1900);
}
void LowerAllString(char* S1, size_t Length)
{
	for (size_t i = 0; i < Length; i++)
	{
		S1[i] = tolower(S1[i]);
	}
}

/*********************************-Util fuctions-*************************/




void ComplaintsManager()
{
	DrawScreenHeader("COMPLAINTS SECTION", "WELCOME");
	system("color 0b");//set color to blue
	printf("\n\n by submitting your complaints you help us to improve our sevices :-)");

	printf("\n\n\n Please Sign in  if you already have an account .\n if you don't then thanks for singing up : ");
	printf("\n\n\t [1] SIGN UP ");
	printf("\n\n\t [2] SIGN IN \n");
	int Choice = ReadNumberInRange(1, 2, "\n please make a choice from the menu above ,you can either sign up or sign in : \n");

	Choice == 1 ? SignUp() : SignIn();


}

void SignUp()
{
	system("cls");
	DrawScreenHeader("COMPLAINTS SECTION", "SIGN UP");
	system("color 09");//set color to blue
	char  Name[40];
	ReadString(Name, sizeof(Name), "\nYour Name : ");

	SetUserName(aUsers[++UsersCounter - 1].UserName);
	SetPassword(aUsers[UsersCounter - 1].Password, sizeof(aUsers[UsersCounter - 1].Password));

	strcpy_s(aUsers[UsersCounter - 1].FullName, sizeof(aUsers[UsersCounter - 1].FullName), Name);
	aUsers[UsersCounter - 1].IsClient = true;
	aUsers[UsersCounter - 1].Permssions = 0;

	system("color 0a");//set color to green
	printf("\nSaved Successfully!");
	Sleep(2 * 1000);
	SignIn();
}

void SetUserName(char UserName[])
{
	ReadString(UserName, sizeof(UserName), "\nUserName : ");
	while (UserNameExists(UserName))
	{
		system("color 04");//set color to red
		printf("\n Username already exists try again.");
		ReadString(UserName, sizeof(UserName), "\nUserName : ");

	}

}
bool UserNameExists(char* UserName)
{
	for (short i = 0; i < UsersCounter - 1; i++)
	{
		if (strcmp(aUsers[i].UserName, UserName) == 0)
			return true;

	}
	//if you reached here then the User with this username doesn't exist
	return false;
}

void SetPassword(char Password[],size_t Size)
{
	ReadString(Password, Size, "\nPassword : ");
	while (!IsValidPassword(Password))
	{
		system("color 04");//set color to red
		printf("\n Invalid Passowrd!try again.. ");
		ReadString(Password, sizeof(Password), "\nPassword : ");

	}

}

bool IsValidPassword(char Password[])
{
	// valid password should be strong and not a username:
	return (CheckPasswordStrength(Password) && (!UserNameExists(Password)));
}

bool CheckPasswordStrength(char* Password)
{
	size_t len = strlen(Password);
	return (len >= 8 && IsDigitExist(Password, len) && IsUpperCaseExist(Password, len)
		&& IsSpecialCharExist(Password, len) && IsLowerCaseExist(Password, len));

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
bool IsDigitExist(char* S1, size_t Length)
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


void SignIn()
{
	char UserName[20], Password[20];
	short Counter = 3;
	bool IsFirstSignIn = true;

	do
	{
		system("cls");
		DrawScreenHeader("COMPLAINTS SECTION", "SIGN IN");
		if (IsFirstSignIn)
		{
			SetDefaultAdminInfo();
			IsFirstSignIn = false;
		}
		system("color 09");//set color to blue

		ReadString(UserName, sizeof(UserName), "\nUserName : ");
		ReadString(Password, sizeof(Password), "\nPassword : ");
		if (!CheckIdentity(UserName, sizeof(UserName), Password, sizeof(Password)))
		{
			system("color 04");//set color to red
			printf("\n wrong username/password!");
			printf("\n You have (%hd) trials to login in (2)s : ", --Counter);
			Sleep(2 * 1000);
		}
		else
		{
			ShowMainMenuScreen();
			Counter = 3;
		}

		if (Counter == 0)
		{
			//sleep function for 30sec
			printf("\n try again after 1 hour!\n\n\a");
			Sleep(3600 * 1000);

			Counter = 3;
		}


	} while (true);



}

bool CheckIdentity(char* UserName, size_t UserNameSize, char* Password, size_t PasswordSize)
{
	for (short i = 0; i < UsersCounter; i++)
	{
		if (strcmp(UserName, aUsers[i].UserName) == 0 && strcmp(Password, aUsers[i].Password) == 0)
		{
			CurrentUser = aUsers[i];
			return true;
		}
	}
	return false;
}
void SetDefaultAdminInfo()
{
	char* Name = "Mohamed", * UserName = "admin", * Password = "admin";
	strcpy_s(aUsers[0].FullName, sizeof(aUsers[0].FullName), Name);
	strcpy_s(aUsers[0].UserName, sizeof(aUsers[0].UserName), UserName);
	strcpy_s(aUsers[0].Password, sizeof(aUsers[0].Password), Password);
	aUsers[0].Permssions = -1;
	aUsers[0].IsClient = 0;
	++UsersCounter;
}

void ShowMainMenuScreen()
{
	CurrentUser.IsClient ? ShowClientsMenuScreen() : ShowUsersMenuScreen();
}

/***********************client menu*************/
void ShowClientsMenuScreen()
{
	system("cls");
	DrawScreenHeader("Complaints Management system", "Main Menu screen");
	system("color 0b");//set color to Light Aqua;

	printf("\n%10s%s", "", "[1] Add a complaint.");
	printf("\n%10s%s", "", "[2] show your own complaints.");
	printf("\n%10s%s", "", "[3] Update Complaint .");
	printf("\n%10s%s", "", "[4] Exit .");

	PerformClientMenuOption(ReadClientOption());


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

void ShowAddComplaintScreen()
{
	//printf("\n add a complaiment screen will be here.. ");
	DrawScreenHeader("Complaints manager", "Add a complaint");
	system("color 0a");//set color to green
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

	AllComplaints[ComplaintsCounter].SubmissionMoment = time(NULL);
	ComplaintsCounter++;

}
void SetComplaintPriority()
{
	LowerAllString(AllComplaints[ComplaintsCounter].Description, strlen(AllComplaints[ComplaintsCounter].Description));
	char HighPriorityKeyWords[2][20] = { "urgent","immediate" };
	char MediumPriorityKeyWords[2][20] = { "important","problem" };
	for (size_t i = 0; i < 2; i++)
	{
		if (strstr(AllComplaints[ComplaintsCounter].Description, HighPriorityKeyWords[i]) != NULL)
		{
			AllComplaints[ComplaintsCounter].Priority = eHigh;
			return;//to exist func immediatly
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		if (strstr(AllComplaints[ComplaintsCounter].Description, MediumPriorityKeyWords[i]) != NULL)
		{
			AllComplaints[ComplaintsCounter].Priority = eMedium;
			return;
		}

	}
	//if we reched here,this means that the complaint has a low priority
	AllComplaints[ComplaintsCounter].Priority = eLow;

}
int GenerateUniqueID()
{
	int ID = 0;
	do
	{
		ID = RandomNumber(1, 99);
	} while (IsIDExist(ID));
	return ID;
}
bool IsIDExist(int ID)
{
	for (short i = 0; i < ComplaintsCounter; i++)
		if (AllComplaints[i].ID == ID)
			return true;
	//if you reached here this means that the ID does not exist!
	return false;
}

void ShowComplaintsListByClientScreen()
{
	//printf("\n complaints made by the current client will be here.. ");
	DrawScreenHeader("Complaints manager", "Show Client Complaints");
	short Counter = 0;
	stComplaint Complaint;
	strcpy_s(Complaint.MadeBy, sizeof(Complaint.MadeBy), CurrentUser.FullName);
	for (short i = 0; i < ComplaintsCounter; i++)
	{
		if (strcmp(AllComplaints[i].MadeBy, Complaint.MadeBy) == 0)
		{
			FindComplaintByID(&Complaint, AllComplaints[i].ID);
			printf("\n\nComplaint %d : \n", ++Counter);
			PrintComplaintInfo(Complaint);

		}
	}
	(Counter == 0) ? printf("\n no complaints for this name : \"%s\"", Complaint.MadeBy) : printf("");


}
bool CanClientUpdateComplaint(int ID)
{

	for (size_t i = 0; i < ComplaintsCounter; i++)
	{
		if (AllComplaints[i].ID == ID)
		{
			return ((AllComplaints[i].Status == eInProgress)
				&&
				((difftime(time(NULL), AllComplaints[i].SubmissionMoment) <= 24 * 3600)));
		}
	}
	return false;
}

void ShowUpdateComplaintByClientScreen()
{
	//printf("\n update complaint by client will be here..");
	DrawScreenHeader("Complaints manager", "Edit Complaint");

	int ID = ReadPositiveNumber("\nPlease your complaint ID you wanna Update\n\t(note that you can only update your complaint if it is still under processing whithin period of 24 hours since submission date) : ");
	stComplaint Complaint;
	if (FindComplaintByID(&Complaint, ID))
	{
		PrintComplaintInfo(Complaint);
		if (CanClientUpdateComplaint(Complaint.ID))
		{
			char Answer = 'n';
			printf("\nare you sure do you wanna update the complaint above [Y/N]: ");
			scanf_s(" %c", &Answer); getchar();
			if (tolower(Answer) == 'y')
			{
				for (size_t i = 0; i < ComplaintsCounter; i++)
				{
					ReadString(AllComplaints[i].Reason, sizeof(AllComplaints[ComplaintsCounter].Reason), "\nComplaint Reason : ");
					ReadString(AllComplaints[i].Description, sizeof(AllComplaints[ComplaintsCounter].Description), "\nDescription : ");
					ReadString(AllComplaints[i].Category, sizeof(AllComplaints[ComplaintsCounter].Category), "\nCategory : ");
					SetComplaintPriority();

					printf("\n\a updated successfully!");
					break;
				}
			}
			else
				printf("\n operation canceled!");
		}
		else
			printf("\nyou cannot update this complaint.");
	}
	else
		printf("\n the complaint you are looking for is not found!");

}

/***********************client menu*************/


/*****************users menu******************************/
void ShowUsersMenuScreen()
{
	system("cls");
	DrawScreenHeader("Complaints Management system", "Main Menu screen");
	system("color 0b");//set color to Light Aqua;

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
enum enMainMenuOption ReadMainMenuOption()
{
	return (enum enMainMenuOption)ReadNumberInRange(1, 9, "\nChoose what do you wanna do [1~9] : ");
}
void GoBackToMainMenuScreen()
{
	printf("\npress any key to go back to main screen ..");
	system("pause>0");
	ShowUsersMenuScreen();
}

/*Complaints list*/
void PrintComplaintRecord(stComplaint Complaint)
{
	printf("|%-40s|%-4d|%-20s|%-60s|%-20s|", Complaint.MadeBy, Complaint.ID, Complaint.Date, Complaint.Description,
		Complaint.Status == eRejected ? "Rejected" : Complaint.Status == eResolved ? "Resolved" : "Pending");

}
void ShowComplaintsListScreen()
{
	//printf("\n Complaints list screen will be here..");
	if (!CheckAccessRights(pComplaintsList))
	{
		PrintAccessDeniedMessage();
		return;
	}
	DrawScreenHeader("Complaints Manager", "Complaints list ");
	printf("\n%s", "_____________________________________________________________________________________________________________________________________________________");
	printf("\n|%-40s|%-4s|%-20s|%-60s|%-20s|", "Name", "ID", "Date", "Description", "Status");
	printf("\n%s", "_____________________________________________________________________________________________________________________________________________________");
	if (ComplaintsCounter != 0)
	{
		for (short i = 0; i < ComplaintsCounter; i++)
		{
			printf("\n");
			PrintComplaintRecord(AllComplaints[i]);
		}


	}
	else
		printf("\n\t\tNo available Complaints To Show!");


	printf("\n%s", "_____________________________________________________________________________________________________________________________________________________");

}

/*update complaint*/
void ShowUpdateComplaintScreen()
{
	///printf("\n update complaint screen will be here.. ");
	if (!CheckAccessRights(pUpdateComplaint))
	{
		PrintAccessDeniedMessage();
		return;
	}

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

/*delete complaint*/
void ShowDeleteComplaintScreen()
{
	//printf("\n delete complaint screen will be here.. ");
	if (!CheckAccessRights(pDeleteComplaint))
	{
		PrintAccessDeniedMessage();
		return;
	}

	DrawScreenHeader("Complaints Manager", "Delete Complaint");
	system("color 04");//set color to red


	stComplaint Complaint;
	if (FindComplaintByID(&Complaint, ReadPositiveNumber("\n enter an ID to serch for : ")))
	{
		printf("\n found ! \n");
		PrintComplaintInfo(Complaint);
		printf("\n Are you sure do you want to delete the Complaint above ? [Y/N]..");
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

/*find complaint*/
void ShowFindClaimScreen()
{
	//printf("\n find claim screen will be here.. ");
	if (!CheckAccessRights(pFindComplaint))
	{
		PrintAccessDeniedMessage();
		return;
	}


	DrawScreenHeader("Complaints manager", "Find Complaint screen");

	system("color 0b");//set color to Light Aqua;

	printf("\n\n You can serch for a specific complaint by : ");
	printf("\n\n \t[1] Complaint ID .");
	printf("\n \t[2] Client Name .");
	printf("\n \t[3] Submission Date.");
	printf("\n \t[4] By Status.");

	PerformFindComplaintMenuOption(ReadFindComplaintOption());
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
enum enFindComplaintOption ReadFindComplaintOption()
{
	return (enum enFindComplaintOption)ReadNumberInRange(1, 4, "\nMake a choice to serch by : ");
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
	if (FindComplaintByID(&Complaint, ReadPositiveNumber("\n enter an ID to serch for : ")))
	{
		printf("\n found ! \n");
		PrintComplaintInfo(Complaint);
	}
	else
		printf("\n the complaint that you're looking for doesn't exist.");

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
		if (strcmp(AllComplaints[i].Date, Complaint.Date) == 0)
		{
			FindComplaintByID(&Complaint, AllComplaints[i].ID);
			printf("\n\nComplaint %d : \n", ++Counter);
			PrintComplaintInfo(Complaint);
			printf("\n");
		}
	}
	(Counter == 0) ? printf("\n there is no complaint for this Date : \"%s\"", Complaint.Date) : printf("");

}

void ShowFindComplaintByStatusScreen()
{
	//printf("\n ShowFindComplaintByStatusScreen will be here.. ");
	DrawScreenHeader("Find Complaint", "By Status");
	printf("\n\n wich status are you looking for : ");
	printf("\n%s\n%s\n%s\n", "[1] Rejected", "[2] Pending", "[3] Resolved");

	stComplaint Complaint;
	Complaint.Status = (enum enClaimStatus)ReadNumberInRange(1, 3, "\n Choose from the menu above : ") - 2;
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


/*process complain*/
void ShowProcessComplaintScreen()
{
	//printf("\n process complaintscreen will be here..");
	if (!CheckAccessRights(pProcessComplaint))
	{
		PrintAccessDeniedMessage();
		return;
	}

	DrawScreenHeader("Complaints Manager", "Process Complaint");

	stComplaint Complaint;
	if (FindComplaintByID(&Complaint, ReadPositiveNumber("\n enter an ID to serch for : ")))
	{
		printf("\n found ! \n");
		PrintComplaintInfo(Complaint);

		printf("\nto mark it as \"rejected\" choose -1 ");
		printf("\nto mark it as \"in progress\" choose 0 ");
		printf("\nto mark it as \"solved\" choose 1 ");

		enum enClaimStatus NewStatus = (enum enClaimStatus)ReadNumberInRange(-1, 1, "\n your Choice : ");
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
				AllComplaints[i].ProcessingComplaintMoment = time(NULL);
				break;
			}
		}
	}
	else
		printf("\n the complaint that you're looking for doesn't exist.");



}


/*complaints by priority*/
void ShowOrderedClaimsScreen()
{
	//printf("\n ordered claims list screen will be here..");

	if (!CheckAccessRights(pOrderedComplaintsList))
	{
		PrintAccessDeniedMessage();
		return;
	}

	DrawScreenHeader("Ordered Complaints", "By Priority");
	SortComplaintsByPriority();
	PrintSortedComplaintsByPriority();

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
			printf("\n|%-4d|%-60s|%-10s|", AllComplaints[i].ID, AllComplaints[i].Description,
				AllComplaints[i].Priority == eHigh ? "High" : AllComplaints[i].Priority == eMedium ? "Medium" : "Low");
		}
	}
	else
		printf("\n\t\t no available complaints in the system!");
	printf("\n____________________________________________________________________________\n");

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

}


/*statistics*/
void ShowStaticsMenuScreen()
{
	//printf("\n statics and reports menu screen will be here.. ");
	system("cls");
	if (!CheckAccessRights(pStatistics))
	{
		PrintAccessDeniedMessage();
		return;
	}
	DrawScreenHeader("Complaints Management", "STATISTICS & REPORTS");

	system("color 0b");//set color to Light Aqua;


	printf("\n%10s%s", "", "[1] Show total number of complaints.");
	printf("\n%10s%s", "", "[2] Show Complaint Resolution Rate.");
	printf("\n%10s%s", "", "[3] Show Taken Time To process a complaint.");
	printf("\n%10s%s", "", "[4] Exit.");

	PerformStaticsMenuOption(ReadStaticsMenuOption());


}
void PerformStaticsMenuOption(enum enStaticsMenuOption Option)
{
	switch (Option)
	{
	case eComplaintTotalNumber:
		system("cls");
		ShowComplaintTotalNumberScreen();
		GoBackToStaticsMenuScreen();
		break;
	case eComplaintResolutionRate:
		system("cls");
		ShowComplaintResolutionRateScreen();
		GoBackToStaticsMenuScreen();
		break;
	case eProcessTimeAverage:
		system("cls");
		ShowProcessTimeAverageScreen();
		GoBackToStaticsMenuScreen();
		break;
	case eQuitStatics:
		break;
	default:
		break;
	}
}
enum enStaticsMenuOption ReadStaticsMenuOption()
{
	return (enum enStaticsMenuOption)ReadNumberInRange(1, 4, "\nChoose What do you wanna do [1~4] : ");
}
void GoBackToStaticsMenuScreen()
{
	printf("\nPress any key to go back to Statics Menu Screen..");
	system("pause>0");
	ShowStaticsMenuScreen();
}


void ShowComplaintTotalNumberScreen()
{
	//printf("\n Total number of Complaints will be here.. ");

	DrawScreenHeader("Statistics & Reports", "ToTal number Of Comlaints");

	if (ComplaintsCounter == 0)
		printf("\n\n\n\t no available complaints!");
	else
		printf("\n\n\n\tTOTAL NUMBER OF COMPLAINTS : %d\n\n", ComplaintsCounter);
}


void ShowComplaintResolutionRateScreen()
{
	//printf("\nComplaint resolution Rate will be here.. ");
	DrawScreenHeader("Statistics & Reports", "Resolution Rate");

	if (ComplaintsCounter == 0)
		printf("\n\n\nno available complaints!");
	else
		printf("\n\n\n\tNUMBER OF SOLVED COMPLAINTS OUT OF TOTAL COMPLAINTS : %.02f %%\n\n", CalculateResolutionRate());

}
float CalculateResolutionRate()
{
	if (ComplaintsCounter == 0)
		return 0;
	int iResolvedComplaints = 0;
	for (size_t i = 0; i < ComplaintsCounter; i++)
	{
		if (AllComplaints[i].Status != eInProgress)
			++iResolvedComplaints;
	}
	return ((float)iResolvedComplaints / ComplaintsCounter) * 100;
}


void ShowProcessTimeAverageScreen()
{
	//printf("\n process average time will be here.. ");
	DrawScreenHeader("STATICS & REPORTS", "AVERAGE TIME");
	if (ComplaintsCounter == 0)
		printf("\n\n\n\t no available complaints!");
	else
		printf("\n\n\n\taverage of time taken to process one complaint is :%.02f s .\n\n", CaluculateProcessTimeAverage());
}
float CaluculateProcessTimeAverage()
{
	int arrProcessPeriode[100];
	int TotalTime = 0;
	for (size_t i = 0; i < ComplaintsCounter; i++)
	{
		arrProcessPeriode[i] = difftime(AllComplaints[i].ProcessingComplaintMoment, AllComplaints[i].SubmissionMoment);
	}
	return ArrayAverage(arrProcessPeriode, ComplaintsCounter);

}
float ArrayAverage(int arr[100], int arrLength)
{
	return (float)ArraySum(arr, arrLength) / arrLength;
}
int ArraySum(int arr[100], int arrLength)
{
	int Sum = 0;
	for (size_t i = 0; i < arrLength; i++)
	{
		Sum += arr[i];
	}
	return Sum;
}





/*manage users*/
void ShowManageUsersScreen()
{
	//printf("\n manage users screen will be here..");
	if (!CheckAccessRights(pManageUsers))
	{
		PrintAccessDeniedMessage();
		return;
	}

	system("cls");
	DrawScreenHeader("Complaints manager", "Manage Users");

	system("color 0b");//set color to Light Aqua;
	printf("\n\n \t[1] Show Users List.");
	printf("\n \t[2] Add New user .");
	printf("\n \t[3] Delete User .");
	printf("\n \t[4] Update User info .");
	printf("\n \t[5] Find User  .");
	printf("\n \t[6] exit  .");
	PerformManageUsersMenuOption(ReadManageUsersMenuOption());

}
void PerformManageUsersMenuOption(enum enManageUsersOption Option)
{
	switch (Option)
	{
	case eUsersList:
		system("cls");
		ShowUsersListScreen();
		GoBackToManageMenuUsersScreen();
		break;
	case eAddNewUsers:
		system("cls");
		ShowAddNewUserScreen();
		GoBackToManageMenuUsersScreen();
		break;
	case eDeleteUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageMenuUsersScreen();
		break;
	case eUpdateUser:
		system("cls");
		ShowUpdateUserScreen();
		GoBackToManageMenuUsersScreen();
		break;
	case eFindUser:
		system("cls");
		ShowFindUserScreen();
		GoBackToManageMenuUsersScreen();
		break;
	case eQuitManageMenu:
		break;
	default:
		break;
	}
}
enum enManageUsersOption ReadManageUsersMenuOption()
{
	return (enum enManageUsersOption)ReadNumberInRange(1, 6, "\nchoose What do you want to do[1~6] ..");
}
void GoBackToManageMenuUsersScreen()
{
	printf("\npress any key to go back to manage users menu screen..");
	system("pause>0");
	ShowManageUsersScreen();
}


void ShowUsersListScreen()
{
	//printf("\n users list screen will be here..");
	DrawScreenHeader("MANAGE USERS", "USERS LIST");

	printf("\n\t%s%s\n", "___________________________________________",
		"_________________________________________________________");

	printf("\t|%-45s|%-20s|%-20s|%-11s|", "FullName", "username", "password", "Permissions");
	printf("\n\t%s%s\n", "___________________________________________",
		"_________________________________________________________");


	if (UsersCounter == 0)
	{
		printf("\n no available users in the system!");
	}
	else
	{
		for (size_t i = 0; i < UsersCounter; i++)
		{
			PrintUserRecordLine(aUsers[i]);
		}

	}
	printf("\n\t%s%s\n", "___________________________________________",
		"_________________________________________________________");

}
void PrintUserRecordLine(stUser User)
{
	printf("\n\t|%-45s|%-20s|%-20s|%-11d|", User.FullName, User.UserName, User.Password, User.Permssions);
}


void ShowAddNewUserScreen()
{
	//printf("\nadd new users screen will be here...");
	DrawScreenHeader("Manage users", "Add new User");
	system("color 0a");//set color to green
	ReadString(aUsers[UsersCounter].FullName, sizeof(aUsers[UsersCounter].FullName), "\nFullName : ");
	SetUserName(aUsers[UsersCounter].UserName);
	SetPassword(aUsers[UsersCounter].Password,sizeof(aUsers[UsersCounter].Password));
	aUsers[UsersCounter].Permssions = ReadUserPermissions();

	UsersCounter++;
	printf("\nadded successfully!");
	PrintUserCard(aUsers[UsersCounter - 1]);
}
int ReadUserPermissions()
{
	int Permissions = 0;
	char Answer = 'n';
	printf("\n Do you want to give him full access [Y/N]..");
	scanf_s(" %c", &Answer); getchar();
	if (tolower(Answer) == 'y')
		return -1;
	printf("\ndo you want to give him access to : ");
	printf("\n\t-Complaints List [Y/N]");
	scanf_s(" %c", &Answer); getchar();
	if (tolower(Answer) == 'y')
	{
		Permissions += pComplaintsList;
	}

	printf("\n\t-Update Complaint [Y/N]");
	scanf_s(" %c", &Answer); getchar();
	if (tolower(Answer) == 'y')
	{
		Permissions += pUpdateComplaint;
	}


	printf("\n\t-Delete complaint [Y/N]");
	scanf_s(" %c", &Answer); getchar();
	if (tolower(Answer) == 'y')
	{
		Permissions += pDeleteComplaint;
	}

	printf("\n\t-Find Complaint [Y/N]");
	scanf_s(" %c", &Answer); getchar();
	if (tolower(Answer) == 'y')
	{
		Permissions += pFindComplaint;
	}

	printf("\n\t-Process Complaint [Y/N]");
	scanf_s(" %c", &Answer); getchar();
	if (tolower(Answer) == 'y')
	{
		Permissions += pProcessComplaint;
	}

	printf("\n\t-Complaints ordered by priority[Y/N]");
	scanf_s(" %c", &Answer); getchar();
	if (tolower(Answer) == 'y')
	{
		Permissions += pOrderedComplaintsList;
	}

	printf("\n\t-Statics and Reports [Y/N]");
	scanf_s(" %c", &Answer); getchar();
	if (tolower(Answer) == 'y')
	{
		Permissions += pStatistics;
	}

	printf("\n\t-MANAGE USERS [Y/N]");
	scanf_s(" %c", &Answer); getchar();
	if (tolower(Answer) == 'y')
	{
		Permissions += pManageUsers;
	}

	return Permissions;

}


void ShowDeleteUserScreen()
{			//printf("\nDelete Users screen will be here..");
	DrawScreenHeader("MANAGE USERS", "delete User");
	system("color 04");//set color to red

	stUser User;
	char UserName[20];
	ReadString(UserName, sizeof(UserName), "\nEnter a username : ");
	char Answer = 'n';
	if (FindUserByUserName(UserName, &User))
	{
		PrintUserCard(User);
		printf("\nAre you sure do you want to delete the user above [Y/N] : ");
		scanf_s(" %c", &Answer); getchar();
		if (tolower(Answer) == 'y')
		{
			DeleteUserByUserName(UserName);
			printf("\n the user deleted successfully !");
		}
		else
			printf("\n canceled!");
	}
	else
		printf("\n the user with \"%s\" is not found!", UserName);
}
void  DeleteUserByUserName(char* UserName)
{
	size_t i = 0;
	for (i = 0; i < UsersCounter; i++)
	{
		if (strcmp(aUsers[i].UserName, UserName) == 0)
		{
			break;
		}
	}
	//moving array elements by 1:
	for (size_t j = i; j < UsersCounter - 1; j++)
	{
		aUsers[j] = aUsers[j + 1];
	}
	//decrease arraysize by one;
	--UsersCounter;
}


void ShowUpdateUserScreen()
{
	//printf("\nupdate user screen will be here..");

	DrawScreenHeader("MANAGE USER", "UPDATE USER");

	stUser User;
	char UserName[20];
	ReadString(UserName, sizeof(UserName), "\nEnter a username : ");
	char Answer = 'n';
	if (FindUserByUserName(UserName, &User))
	{
		PrintUserCard(User);
		printf("\nAre you sure do you want to Update the user above [Y/N] : ");
		scanf_s(" %c", &Answer); getchar();
		if (tolower(Answer) == 'y')
		{
			UpdateUserByUserName(UserName);
			printf("\n the user Updated successfully !");
		}
		else
			printf("\n canceled!");
	}
	else
		printf("\n the user with \"%s\" is not found!", UserName);


}
void UpdateUserByUserName(char UserName[])
{
	for (size_t i = 0; i < UsersCounter; i++)
	{
		if (strcmp(aUsers[i].UserName, UserName) == 0)
		{
			ReadString(aUsers[i].FullName, sizeof(aUsers[i].FullName), "\n new Name : ");
			ReadString(aUsers[i].Password, sizeof(aUsers[i].Password), "\nNew Password : ");
			aUsers[i].Permssions = ReadUserPermissions();
			break;
		}
	}
}



void ShowFindUserScreen()
{
	//printf("\nFind users screen will be here..");
	DrawScreenHeader("Manage Users", "Find User");
	char UserName[20];
	stUser User;
	ReadString(UserName, sizeof(UserName), "\n Enter a username to serch for : ");
	if (FindUserByUserName(UserName, &User))
	{
		printf("\nfound!");
		PrintUserCard(User);
	}
	else
		printf("\n the user with username : \"%s\" is not found!", UserName);
}
bool FindUserByUserName(char* UserName, stUser* User)
{
	for (size_t i = 0; i < UsersCounter; i++)
	{
		if (strcmp(aUsers[i].UserName, UserName) == 0)
		{
			*User = aUsers[i];
			return true;
		}
	}
	return false;//if you reached here ,the the user is not found!

}
void PrintUserCard(stUser User)
{
	printf("\n the followinge are the user's info : ");
	printf("\n%s", "________________________________________");
	printf("\n Full Name : %s\nUserName : %s\nPassword : %s", User.FullName, User.UserName, User.Password);
	PrintUserPermissions(User.Permssions);
	printf("\n%s", "________________________________________");

}
void PrintUserPermissions(int Permissions)
{
	if (Permissions == pFullAccess)
		printf("\n\tFull Access");
	else if (Permissions == pNothing)
		printf("\n he connot access to any screen !");
	else if (Permissions != 0)
	{
		printf("\nthis user has access to : ");
		if ((Permissions & pComplaintsList) == pComplaintsList)
			printf("\n\t-Complaints list.");
		if ((Permissions & pUpdateComplaint) == pUpdateComplaint)
			printf("\n\t-Update complaint.");
		if ((Permissions & pDeleteComplaint) == pDeleteComplaint)
			printf("\n\t-Delete complaint.");
		if ((Permissions & pFindComplaint) == pFindComplaint)
			printf("\n\t-Find Complaint.");
		if ((Permissions & pProcessComplaint) == pProcessComplaint)
			printf("\n\t-Process Complaint.");
		if ((Permissions & pOrderedComplaintsList) == pOrderedComplaintsList)
			printf("\n\t-Ordered Complaints list by priority.");
		if ((Permissions & pStatistics) == pStatistics)
			printf("\n\t-Statistics.");
		if ((Permissions & pManageUsers) == pManageUsers)
			printf("\n\t-Manage Users.");
	}
}


//program ends!
//                    by :  DEV.MOHAMED IDRISSI ALAMI
 //														all rights reserved 2024.