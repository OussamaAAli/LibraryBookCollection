#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

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


void printPersonDetail(Person *person)
{
    printf(" ID : %d\n", person->idPerson);
    printf("Name : %s %s\n");
    printf(" Date of Birth : %d %s %d\n", person->dateOfBirth.day, person->dateOfBirth.month, person->dateOfBirth.year);
    printf("Address : %d, %s, %d\n", person->adress.numberOfHouse, person->adress.street, person->adress.postalCode);

}

void registerUser()
{
    User *newUser = (User *)malloc(sizeof(User));
    if(!newUser)
    {
        printf("Memory allocation failed ");
        return;
    }


    printf("Enter first name : ");
    scanf("%s", newUser->person.firstName);

    printf("Enter last name : ");
    scanf("%s",newUser->person.lastName);

    printf("Enter date of birth in the format: DD MM YYYY (with a space between each part).");
    scanf("%d %s %d", &newUser->person.dateOfBirth.day, newUser->person.dateOfBirth.month, &newUser->person.dateOfBirth.year);

    printf("Enter your house number :");
    scanf("%d", &newUser->person.adress.numberOfHouse);

    while (getchar() != '\n');

    printf("Enter a street : ");
    scanf(" %[^\n]%*c", &newUser->person.adress.street);

    printf("Enter your postal code :");
    scanf("%d", &newUser->person.adress.postalCode);

    printf("Full Address: %d, %s ,%d \n", newUser->person.adress.numberOfHouse, newUser->person.adress.street, newUser->person.adress.postalCode);


    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    newUser->person.idPerson = (tm.tm_year + 1900) * 1000 + (tm.tm_yday + 1) * 100 + userCounter++;

    printf("Id person : %d \n", newUser->person.idPerson);

    totalUsers++;
    user = realloc(user, totalUsers * sizeof(user));
    user[totalUsers - 1] = *newUser;

    printf("User registration successfully completed !\n");


    printPersonDetail(&newUser->person);


}

void registerTutor()
{

    Tutor *newTutor = (Tutor *)malloc(sizeof(Tutor));
    if(!newTutor)
    {
        printf("Memory allocation failed \n");
        return;
    }

    printf("\n--- Register a New Tutor ---\n");

    printf("Enter first name: ");
    scanf("%s", newTutor->person.firstName);

    printf("Enter last name: ");
    scanf("%s", newTutor->person.lastName);

    printf("Enter date of birth in the format: DD MM YYYY (with a space between each part) ");
    scanf("%d %s %d", &newTutor->person.dateOfBirth.day, &newTutor->person.dateOfBirth.month, &newTutor->person.dateOfBirth.year);

    printf("Enter your house number : ");
    scanf("%d", &newTutor->person.adress.numberOfHouse);

    while (getchar() != '\n');

    printf("Enter a street : ");
    scanf("%[^\n]%*c", &newTutor->person.adress.street);


    printf("Enter your postal code :");
    scanf("%d", &newTutor->person.adress.postalCode);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    newTutor->tutorID = (tm.tm_year+1900)*1000 + (tm.tm_yday+1)*100 + tutorCounter++;

    printf("Id user %d", newTutor->tutorID);

    newTutor->managedBooks = NULL;
    newTutor->totalBook = 0;

    printPersonDetail(&newTutor->person);


}



void borrowBook()
{
    printf("Borrow a book function\n");
}

void ModifyContactDetails()
{
    printf("Modify Contact function\n");
}

void modifyBookDetails()
{
    printf("Modify book function\n");
}


void mainMenu()
{
    int choice, validInput;

    do
    {

        printf("\n--- Main Menu ---\n");
        printf("1. Register as a User\n");
        printf("2. Register as a Tutor\n");
        printf("3. Borrow a book \n");
        printf("4. Modify contact details\n");
        printf("5. Modify Book Details (Tutors Only)\n");
        printf("6. Exit\n");
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
        registerUser();
        break;

    case 2:
        registerTutor();
        break;
    case 3:
        borrowBook();
        break;
    case 4:
        ModifyContactDetails();
        break;
    case 5:
        modifyBookDetails();
        break;
    case 6:
        printf("Goodbye!\n");
        exit(0);
    default:
        printf("Failed, please try again ! \n");
        mainMenu();
    }

}

int main()
{

    mainMenu();
    return 0;
}
