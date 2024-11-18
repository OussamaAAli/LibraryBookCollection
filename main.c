#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int day;
    char month[15];
    int year;
} Date;

typedef struct
{
    int numberOfHouse;
    char street[30];
    int postalCode;

} Adress;


typedef struct
{

    int idPerson;
    char firstName[50];
    char lastName[50];
    Date dateOfBirth;
    Adress adress;
    char registrationDate[50];


} Person;

typedef struct
{
    Person person;
    int userRegistrationNumber;
    int borrowedBookCount;;

} User;


typedef struct
{
    int bookID;
    char bookName[50];
    Date creationDte;
    int quantity;
    int tutorId;


} Book;

typedef struct
{
    Person person;
    int tutorID;
    Book *managedBooks;
    int totalBook;



} Tutor;


User *user = NULL;
Tutor *tutor = NULL;
int totalUsers = 0;
int totalTutors = 0;
int userCounter = 1;
int bookCounter = 1;
int tutorCounter = 1;


void mainMenu();
void registerUser();
void registerTutor();
void addBook(int tutorNumber);
void displayUsrDetails(User u);
void displayTutorDetails(Tutor t);


void mainMenu()
{
    int choice, validInput;

    do
    {

        printf("\n--- Main Menu ---\n");
        printf("1. Register as a User\n");
        printf("2. Register as a Tutor\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        validInput = scanf("%d", &choice);

        if (!validInput)
        {
            printf("invalid input ! Please enter a number \n");

            while(getchar() != '\n');
        }

    }
    while (!validInput);



    switch(choice)
    {

    case 1 :
        registerTutor();
        break;

    case 2:
        registerTutor();
        break;
    case 3:
        printf("GoodBy\n");
        exit(0);
    default:
        printf("Failed, please try again ! \n");
        mainMenu();



    }

}

void registerUser()
{
    printf("User registration process\n");
}

void registerTutor()
{
    printf("Tutor registration process\n");
}

int main()
{
    mainMenu();
    return 0;
}
