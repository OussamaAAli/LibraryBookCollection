#include <stdio.h>
#include <stdlib.h>

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
    Person person;
    int tutorID;
    Book *managedBooks;
    int totalBook;



} Tutor;


typedef struct
{
    int bookID;
    char bookName[50];
    Date creationDte;
    int quantity;
    int tutorId;


} Book;



User *user = NULL;
Tutor *tutor = NULL;
int totalUsers = 0;
int totalTutors = 0;
int userCounter = 1;
int bookCounter = 1;
int tutorCounter = 1;

int main()
{
    printf("Hello world!\n");
    return 0;
}
