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
    int borrowedById;
    int borrowCount;


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
    printf("ID : %d\n", person->idPerson);
    printf("Full Name : %s %s\n", person->firstName, person->lastName);
    printf("Date of Birth : %d %s %d\n", person->dateOfBirth.day, person->dateOfBirth.month, person->dateOfBirth.year);
    printf("Address : %d, %s, %d\n", person->adress.numberOfHouse, person->adress.street, person->adress.postalCode);
    printf("\n \n");

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

    printf("Enter date of birth in the format: DD MM YYYY (with a space between each part) : ");
    scanf("%d %s %d", &newUser->person.dateOfBirth.day, newUser->person.dateOfBirth.month, &newUser->person.dateOfBirth.year);

    printf("Enter your house number :");
    scanf("%d", &newUser->person.adress.numberOfHouse);

    while (getchar() != '\n');

    printf("Enter a street : ");
    fgets(newUser->person.adress.street, sizeof(newUser->person.adress.street),stdin );
    newUser->person.adress.street[strcspn(newUser->person.adress.street, "\n")] = '\0';

    printf("Enter your postal code :");
    scanf("%d", &newUser->person.adress.postalCode);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    newUser->person.idPerson = (tm.tm_year + 1900) * 1000 + (tm.tm_yday + 1) * 100 + userCounter++;

    printf("Id person : %d \n", newUser->person.idPerson);

    totalUsers++;
    user = realloc(user, totalUsers * sizeof(User));
    if (!user)
    {
        printf("Memory allocation failed\n");
        free(newUser);
        return;
    }

    user[totalUsers - 1] = *newUser;
    printf("\n \n \n");
    printf(" **** User registration successfully completed! **** \n");
    printf("\n \n \n");

    printPersonDetail(&newUser->person);

    free(newUser);
    mainMenu();

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

    printf("\n \n \n");
    printf(" **** Tutor registration successfully completed! **** \n");
    printf("\n \n \n");
    printPersonDetail(&newTutor->person);



    totalTutors++;
    tutor = realloc(tutor, totalTutors * sizeof(Tutor));
    if (!tutor)
    {
        printf("Memory allocation failed\n");
        free(newTutor);
        return;
    }

    tutor[totalTutors - 1] = *newTutor;
    free(newTutor);
    mainMenu();


}

void addBook(int tutorNumber)
{
    if (totalTutors == 0)
    {
        printf("\n \n *** No tutors exist. Please register a tutor first. ***\n");
        mainMenu();
        return;
    }

    printf("Select a tutor from the list (or enter 0 to return to the main menu):\n");
    printf("0: Add a new tutor\n");
    for (int i = 0; i < totalTutors; i++)
    {
        printf("%d: %s %s (ID: %d)\n", i + 1, tutor[i].person.firstName, tutor[i].person.lastName, tutor[i].tutorID);
    }

    int tutorInput;
    printf("Enter tutor number: ");
    if (scanf("%d", &tutorInput) != 1 || tutorInput < 0 || tutorInput > totalTutors)
    {
        printf("Invalid input. Returning to main menu.\n");
        while (getchar() != '\n');
        mainMenu();
        return;
    }

    if (tutorInput == 0)
    {
        mainMenu();
        return;
    }

    tutorNumber = tutor[tutorInput - 1].tutorID;

    Book newBook;
    newBook.bookID = bookCounter++;
    newBook.tutorId = tutorNumber;
    newBook.borrowedById = -1;
    newBook.borrowCount = 0;

    printf("Enter book name: ");
    while (getchar() != '\n');
    fgets(newBook.bookName, sizeof(newBook.bookName), stdin);
    newBook.bookName[strcspn(newBook.bookName, "\n")] = '\0';

    printf("Enter creation date in the format: DD MM YYYY (with a space between each part) ");
    scanf("%d %s %d", &newBook.creationDte.day, newBook.creationDte.month, &newBook.creationDte.year);

    printf("Enter quantity: ");
    scanf("%d", &newBook.quantity);

    for (int i = 0; i < totalTutors; i++)
    {
        if (tutor[i].tutorID == tutorNumber)
        {
            tutor[i].managedBooks = realloc(tutor[i].managedBooks, (tutor[i].totalBook + 1) * sizeof(Book));
            if (!tutor[i].managedBooks)
            {
                printf("Memory allocation failed while adding the book!\n");
                return;
            }
            tutor[i].managedBooks[tutor[i].totalBook] = newBook;
            tutor[i].totalBook++;
            printf("\nBook added successfully!\n\n");
            displayBookDetails(&newBook);
            break;
        }
    }

    mainMenu();
}

void displayBookDetails(Book *book)
{
    printf("Book Details:\n");
    printf("ID: %d\n", book->bookID);
    printf("Name: %s\n", book->bookName);
    printf("Creation Date: %d %s %d\n", book->creationDte.day, book->creationDte.month, book->creationDte.year);
    printf("Quantity: %d\n", book->quantity);
    printf("Tutor ID: %d\n", book->tutorId);
    printf("\n\n");
}

void borrowBook()
{
    if (totalUsers == 0)
    {
        printf("\n*** No users registered. Returning to the main menu. ***\n");
        mainMenu();
        return;
    }

    printf("\n--- Registered Users ---\n");
    printf("0: Return to main menu\n");
    for (int i = 0; i < totalUsers; i++)
    {
        printf("%d: %s %s (ID: %d)\n", i + 1, user[i].person.firstName, user[i].person.lastName, user[i].person.idPerson);
    }

    int userInput;
    printf("Enter the number corresponding to your user (or 0 to return to the main menu): ");
    if (scanf("%d", &userInput) != 1 || userInput < 0 || userInput > totalUsers)
    {
        printf("Invalid input. Returning to the main menu.\n");
        while (getchar() != '\n');
        mainMenu();
        return;
    }

    if (userInput == 0)
    {
        mainMenu();
        return;
    }

    User *selectedUser = &user[userInput - 1];

    printf("\n--- Available Books ---\n");
    int availableBooks = 0;
    for (int i = 0; i < totalTutors; i++)
    {
        for (int j = 0; j < tutor[i].totalBook; j++)
        {
            Book *currentBook = &tutor[i].managedBooks[j];
            if (currentBook->quantity > 0)
            {
                printf("ID: %d | Title: %s | Quantity: %d\n", currentBook->bookID, currentBook->bookName, currentBook->quantity);
                availableBooks++;
            }
        }
    }

    if (availableBooks == 0)
    {
        printf("\n*** No books are currently available. Returning to the main menu. ***\n");
        mainMenu();
        return;
    }

    int bookID;
    printf("\nEnter the ID of the book you want to borrow: ");
    if (scanf("%d", &bookID) != 1)
    {
        printf("Invalid input. Returning to the main menu.\n");
        while (getchar() != '\n');
        mainMenu();
        return;
    }

    for (int i = 0; i < totalTutors; i++)
    {
        for (int j = 0; j < tutor[i].totalBook; j++)
        {
            Book *currentBook = &tutor[i].managedBooks[j];
            if (currentBook->bookID == bookID && currentBook->quantity > 0)
            {
                currentBook->borrowedById = selectedUser->person.idPerson;
                currentBook->borrowCount++;
                currentBook->quantity--;

                printf("\nBook borrowed successfully: %s\n", currentBook->bookName);
                printf("User: %s %s (ID: %d)\n", selectedUser->person.firstName, selectedUser->person.lastName, selectedUser->person.idPerson);
                printf("Remaining quantity: %d\n", currentBook->quantity);
                printf("Total borrow count: %d\n", currentBook->borrowCount);

                mainMenu();
                return;
            }
        }
    }

    printf("\nInvalid book ID or the book is not available. Returning to the main menu.\n");
    mainMenu();
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
        printf("3. Add a Book\n");
        printf("4. Borrow a book \n");
        printf("5. Modify contact details\n");
        printf("6. Modify Book Details (Tutors Only)\n");
        printf("0. Exit\n");
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
        addBook(0);
        break;
    case 4:
        borrowBook();
        break;
    case 5:
        ModifyContactDetails();
        break;
    case 6:
        modifyBookDetails();
        break;
    case 0:
        printf("\n \n Goodbye! \n \n");
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
