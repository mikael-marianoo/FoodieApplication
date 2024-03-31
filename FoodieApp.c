/*************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and 
applying the concepts learned. I have constructed the functions and their respective algorithms 
and corresponding code by myself. The program was run, tested, and debugged by my own efforts. I 
further certify that I have not copied in part or whole or otherwise plagiarized the work of other 
students and/or persons.
 
 <MARIANO, JEAN MIKAEL V.>, DLSU ID# <12193291>
 <TANHEHCO, SYDNEY TAYLOR C.>, DLSU ID# <12041475>
*************************************************************************************************/


#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_USERS 10
#define MAX_FOODS 50
#define MAX_SIZE 100
#define MAX_RECIPES 20


typedef char Str50 [51];
typedef char Str10 [11];
typedef char Str11 [12];
typedef char Str20 [21];
typedef char Str30 [31];
typedef char Str80 [81];
typedef char Str300 [301];
typedef char Char1;
typedef char Str160 [161];

// User struct
typedef struct {
    Str50 username;
    Str50 password;
    Str80 fullName;
    Str30 emailAddress;
    Str11 mobileNumber;
} User;


// This represents an entry for a food item
struct FoodEntry {
    Str50 name;
    Char1 type;
    int timesEaten;
    Str10 dateFirstTried;
    Str30 locationFirstTried;
    Str300 description;
};

//This represents an entry for a recipe
struct RecipeEntry{
    Str50 recipeName;
    Str160 Description;
    int timetoprepare;
    int timetocook;
    int numberofingredients;
    char list_of_ingredients[20][80];
    int number_of_instructions;
    char instructions[20][100];
};

//Mr Froggy *optional
void Image()
{
    printf("\t\t\t\t\t\t   _      _    \n");
    printf("\t\t\t\t\t\t  |_|    |_|   \n");
    printf("\t\t\t\t\t\t  | |____| |   \n");
    printf("\t\t\t\t\t\t |' 0    0 '|  \n");
    printf("\t\t\t\t\t\t '.O______O.'  \n");
    printf("\t\t\t\t\t\t   | |  | |    \n\n");
}

//Introduction *optional
void Introduction()
{
    printf("\t\t\t\t\t   =========================\n");
    printf("\t\t\t\t\t   ||      Welcome To     ||\n");
    printf("\t\t\t\t\t   || Foodie Application  ||\n");
    printf("\t\t\t\t\t   ||         Beta        ||\n");
    printf("\t\t\t\t\t   =========================\n\n");
}

//Interface *optional
void Interface()
{
    printf("\t\t\t\t   =========================\n");
    printf("\t\t\t\t   ||       Food Log      ||\n");
    printf("\t\t\t\t   ||         Menu        ||\n");
    printf("\t\t\t\t   =========================\n\n");
    printf("\t\t\t\t  ============================\n");
    printf("\t\t\t\t  ||                        ||\n");
    printf("\t\t\t\t  || [1] Add Food Entry     ||\n");
    printf("\t\t\t\t  || [2] Delete Food Log    ||\n");
    printf("\t\t\t\t  || [3] Edit Food Entry    ||\n");
    printf("\t\t\t\t  || [4] Display Food Entry ||\n");
    printf("\t\t\t\t  || [5] Add Recipe Entry   ||\n");
    printf("\t\t\t\t  || [6] Delete Recipe Log  ||\n");
    printf("\t\t\t\t  || [7] Edit Recipe Log    ||\n");
    printf("\t\t\t\t  || [8] Display Recipe Log ||\n");
    printf("\t\t\t\t  || [9] View User          ||\n");
    printf("\t\t\t\t  || [0] Log Out            ||\n");
    printf("\t\t\t\t  ||                        ||\n");
    printf("\t\t\t\t  ============================\n\n");

}

// This function checks if a given string is a valid Username
// It returns 1 if the email is valid, 0 otherwise
int isValidUsername(char* username)
{
    int i;
    int len = strlen(username);
    char c;
    if (len < 8 || len > 50)
    {
        return 0;
    }
    for (i = 0; i < len; i++)
    {
        c = username[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')))
        {
            return 0;
        }
    }
    return 1;
}

//This function checks if a given string is a valid password
// Returns 1 if the password is valid, and 0 otherwise.
int isValidPassword(char password[])
{
    int i, uppercaseCount = 0, lowercaseCount = 0, digitCount = 0, specialCharCount = 0;
    char specialChars[] = "!@#$%&*.()";

    // Check if the length of the password is within the required range.
    if (strlen(password) < 8 || strlen(password) > 20)
    {
        return 0;
    }

    // Iterate through each character of the password and count the number of uppercase letters, lowercase letters, digits, and special characters.
    for (i = 0; password[i] != '\0'; i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            uppercaseCount++;
        }
        else if (password[i] >= 'a' && password[i] <= 'z')
        {
            lowercaseCount++;
        }
        else if (password[i] >= '0' && password[i] <= '9')
        {
            digitCount++;
        }
        else if (strchr(specialChars, password[i]) != NULL)
        {
            specialCharCount++;
        }
    }

    // Check if the password contains at least one uppercase letter, one lowercase letter, one digit, and one special character.
    if (uppercaseCount == 0 || lowercaseCount == 0 || digitCount == 0 || specialCharCount == 0)
    {
        return 0;
    }

    return 1;
}

// This function checks if a given string is a valid email address
// It returns 1 if the email is valid, 0 otherwise
int isValidEmailAddress(char* emailAddress)
{
    int atPosition = -1; // Initialize the position of the '@' character to -1
    int dotPosition = -1; // Initialize the position of the '.' character to -1
    int i;
    int domainLen = 0; // Initialize the length of the domain to 0

    // Loop through the characters in the email address
    for (i = 0; emailAddress[i] != '\0'; i++)
    {
        // If the current character is '@', set its position to atPosition
        if (emailAddress[i] == '@')
        {
            atPosition = i;
        }
        // If the current character is '.', and there was an '@' earlier, set its position to dotPosition
        else if (emailAddress[i] == '.' && atPosition != -1)
        {
            dotPosition = i;
        }
        // If there was an '@' earlier, and there is no '.' yet, increment the domain length
        else if (atPosition != -1 && dotPosition == -1)
        {
            domainLen++;
        }
    }

    // If the '@' character was not found, or the '.' character was not found, or '.' appears before '@', or the domain length is 0, return 0 (invalid email)
    if (atPosition == -1 || dotPosition == -1 || dotPosition < atPosition || domainLen == 0)
    {
        return 0;
    }

    // Otherwise, the email is valid
    return 1;
}

// This function checks if a given string is a valid Mobile Number
// It returns 1 if the email is valid, 0 otherwise
int isValidMobileNumber(char* mobileNumber)
{
    int i;
    int length = strlen(mobileNumber);

    if (length != 11 || mobileNumber[0] != '0')
    {
        return 0;
    }

    for (i = 1; i < length; i++)
    {
        if (mobileNumber[i] < '0' || mobileNumber[i] > '9')
        {
            return 0;
        }
    }

    return 1;
}

//This function lets the user register and put it in the binary file named "user.dat"
//It also create the file
//It returns 1 if all the input is valid, 0 otherwise
int registerUser()
{
    User user;
    FILE *file = fopen("user.dat", "ab"); // Open the user.dat file in append binary mode

    if (!file) // Check if the file was successfully opened
    {
        printf("Unable to open file.\n");
        return 0;
    }

    // Get a valid username from the user
    while (1)
    {
        printf("Enter username: ");
        scanf("%s", user.username);
        if (isValidUsername(user.username))
        {
            break;
        }
        printf("Invalid username. Please try again.\n");
        getch();
    }

    // Get a valid password from the user
    while (1)
    {
        printf("Enter password: ");
        scanf("%s", user.password);
        if (isValidPassword(user.password))
        {
            break;
        }
        printf("Invalid password. Please make sure it has 8-20 characters, at least 1 uppercase, 1 lowercase, 1 number and 1 special character.\n");
        getch();
    }

    // Get the user's full name
    printf("Enter full name: ");
    scanf(" %[^\n]s", user.fullName);

    // Get a valid email address from the user
    while (1)
    {
        printf("Enter email address: ");
        scanf("%s", user.emailAddress);
        if (strlen(user.emailAddress) <= 30 && isValidEmailAddress(user.emailAddress))
        {
            break;
        }
        printf("Invalid email address. Please try again.\n");
    }

    // Get a valid mobile number from the user
    while (1)
    {
        printf("Enter mobile number: ");
        scanf("%s", user.mobileNumber);
        if (isValidMobileNumber(user.mobileNumber))
        {
            break;
        }
        printf("Invalid mobile number. Please try again.\n");
    }

    // Write the user data to the file
    fwrite(&user, sizeof(User), 1, file);
    fclose(file); // Close the file
    printf("User registered successfully.\n");
    getch();
    system("cls");
    return 1; // Return 1 to indicate successful registration
}

/*This function prompts the user to enter their login credentials
(username and password) and verifies if they exist in the user.dat file.
If there is no match, the user is given up to three attempts to enter the correct credentials.
It returns 1 if the input is valid, if it is invalid Exiting program using exit(0).
*/
int canLogin()
{
    //initialize variables
    int i = 0;
    int attempts = 3;
    char username[50], password[50];

    //prompt user to enter login credentials
    printf("Please enter your login credentials:\n");
    printf("Username: ");
    scanf("%s", username);

    //prompt user to enter password and replace characters with *
    printf("Password: ");
    while (1)
    {
        int c = getch();
        //if user presses enter, end loop
        if (c == '\r')
        {
            password[i] = '\0';
            break;
        }
        //if user presses backspace and there are characters entered, erase last character
        else if (c == '\b' && i > 0)
        {
            i--;
            printf("\b \b");
        } 
        //if there are less than 20 characters and the user didn't press backspace, store character in password and replace with *
        else if (i < 20 && c != '\b')
        {
            password[i++] = c;
            printf("*");
        }
    }

    //open user.dat file for reading
    FILE *fp = fopen("user.dat", "rb");

    //if the file is not null
    if (fp != NULL)
    {
        //read user data from the file
        User u;
        while (fread(&u, sizeof(User), 1, fp)) {
            //if the entered username and password match any user data, print welcome message and return 1
            if (strcmp(u.username, username) == 0 && strcmp(u.password, password) == 0)
            {
                printf("\nWelcome, %s!\n", u.fullName);
                fclose(fp);
                return 1;
            }
        }
        fclose(fp);
    }

    //if no match is found, prompt user to try again up to three times
    while (--attempts > 0)
    {
        printf("\nIncorrect username or password. %d attempts remaining.\n", attempts);
        printf("Please enter your login credentials:\n");
        printf("Username: ");
        scanf("%s", username);
        
        printf("Password: ");
        i = 0;
        while (1)
        {
            int c = getch();
            //This part of code replaces the text input password into *
            if (c == '\r')
            {
                password[i] = '\0';
                break;
            }
            else if (c == '\b' && i > 0)
            {
                i--;
                printf("\b \b");
            } else if (i < 20 && c != '\b')
            {
                password[i++] = c;
                printf("*");
            }
        }
        
        fp = fopen("user.dat", "rb");

        if (fp != NULL)
        {
            User u;
            while (fread(&u, sizeof(User), 1, fp)) {
                if (strcmp(u.username, username) == 0 && strcmp(u.password, password) == 0)
                {
                    printf("\n\nWelcome, %s!\n", u.fullName);
                    fclose(fp);
                    return 1;
                }
            }
            fclose(fp);
        }
    }

    printf("\nFailed to login after 3 attempts. Exiting program.\n");
    getch();
    //terminates the program immediately with a status code of 0, indicating successful termination.
    exit(0);
}

//View Users
void viewUsers()
{
    int i;
    FILE *fp = fopen("user.dat", "rb");

    if (fp != NULL)
    {
        User u;
        while (fread(&u, sizeof(User), 1, fp))
        {
            printf("Username: %s\n", u.username);
            printf("Password: ");
            for (i = 0; i < strlen(u.password); i++)
            {
                printf("*");
            }
            printf("\n");
            printf("Full Name: %s\n", u.fullName);
            printf("Email Address: %s\n", u.emailAddress);
            printf("Mobile Number: %s\n\n", u.mobileNumber);
        }
        fclose(fp);
    }
    else
    {
        printf("Error: unable to open user.dat file.\n");
    }
}

//Validation of Date
int validate_date(const char* date_str)
{
    int day, month, year;
    if (sscanf(date_str, "%d/%d/%d", &month, &day, &year) != 3)
    {
        return 0;
    }
    if (month < 1 || month > 12 || day < 1 || day > 31)
    {
        return 0;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        return 0;
    }
    if (month == 2)
    {
        int is_leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !is_leap_year))
        {
            return 0;
        }
    }
    if (year < 1500 || year > 2023)
	{
        return 0;
    }
    return 1;
}

//This function allows the user to add a food from the food log file.
void addFood()
{
    char food_name[50], food_type, description[100], date_first_tried[20], location_first_tried[50];
    int food_times_eaten;
    int valid_input = 0, food_name_exists = 0;
    static int num_records = 0; // counter for number of records added
    if (num_records >= 50)
    {
        printf("Maximum number of records reached. Cannot add new record.\n");
        return;
    }
    FILE *fp;
    fp = fopen("foodlogs.txt", "r");
    

    printf("Enter Food Name: ");
    scanf(" %s", food_name);

    // Check if food name already exists in the file
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        char *token = strtok(buffer, "\n");
        if (strcmp(token, food_name) == 0)
        {
            food_name_exists = 1;
            break;
        }
    }
    fclose(fp);

    if (food_name_exists)
    {
        printf("Food name already exists in the log. Please enter a different name.\n");
        return;
    }

    printf("Enter Food Type (a for appetizer, m for main course, d for dessert): ");
    scanf(" %c", &food_type);
    while (food_type != 'a' && food_type != 'm' && food_type != 'd')
    {
        printf("Invalid input. Please enter a, m, or d: ");
        scanf(" %c", &food_type);
    }

    while(!valid_input)
    {
        printf("Enter Food Times Eaten: ");
        if (scanf("%d", &food_times_eaten) != 1 || food_times_eaten < 0)
        {
            printf("Invalid input. Please enter a non-negative integer.\n");
            while (getchar() != '\n');
        }
        else
        {
            valid_input = 1;
        }
    }

    printf("Enter Date First Tried (MM/DD/YYYY): ");
    scanf("%s", date_first_tried);
    while (!validate_date(date_first_tried))
    {
        printf("Invalid date format. Please enter date in MM/DD/YYYY format: ");
        scanf("%s", date_first_tried);
    }

    printf("Enter Location First Tried: ");
    scanf(" %[^\n]", location_first_tried);

    printf("Enter Description: ");
    scanf(" %[^\n]", description);

    fp = fopen("foodlogs.txt", "a+");
    fprintf(fp, "%s\n%c\t%d\n%s\n%s\n%s\n", food_name, food_type, food_times_eaten, date_first_tried, location_first_tried, description);
    fclose(fp);

    num_records++; // increment the counter after a record is added
    printf("\nFood information has been logged successfully!\n");
}

//This function allows the user to delete a food from the food log file.
void deleteFood()
{
    Str50 input;
    int found = 0;
    char confirm;
    int i, j;
    struct FoodEntry foodLog;
    
    FILE *fp = fopen("foodlogs.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }
    
    FILE *temp = fopen("temp.txt", "w+");
    if (temp == NULL)
    {
        printf("Error: could not open file.\n");
        fclose(fp);
        return;
    }
    
    printf("Enter the name of the food item to delete: ");
    scanf("%s", input);
    
    // search for food name in file
    while (fscanf(fp, "%s %c %d %s %s %[^\n]",
                  foodLog.name,
                  &foodLog.type,
                  &foodLog.timesEaten,
                  foodLog.dateFirstTried,
                  foodLog.locationFirstTried,
                  foodLog.description) != EOF)
    {
        // if food name is found, display food log and confirm deletion
        if (strcmp(foodLog.name, input) == 0)
        {
            printf("Are you sure you want to delete this food log? (Y/N)\n");
            printf("%s\n%c\t%d\n%s\n%s\n%s\n",
                   foodLog.name,
                   foodLog.type,
                   foodLog.timesEaten,
                   foodLog.dateFirstTried,
                   foodLog.locationFirstTried,
                   foodLog.description);
            fflush(stdin);
            scanf("%c", &confirm);
            
            // input validation for confirmation
            while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n')
            {
                printf("Invalid input. Please enter Y or N: ");
                fflush(stdin);
                scanf("%c", &confirm);
            }
            
            // if deletion is confirmed, skip writing to temp file to effectively delete food log
            if (confirm == 'Y' || confirm == 'y')
            {
                found = 1;
                continue;
            }
        }
        
        // write food log to temp file if it is not being deleted
        fprintf(temp, "%s %c %d %s %s %s\n",
                foodLog.name,
                foodLog.type,
                foodLog.timesEaten,
                foodLog.dateFirstTried,
                foodLog.locationFirstTried,
                foodLog.description);
    }
    
    fclose(fp);
    fclose(temp);
    
    // delete original file and replace with temp file
    if (found)
    {
        remove("foodlogs.txt");
        rename("temp.txt", "foodlogs.txt");
        printf("\nThe food log has been deleted.\n");
    }
    else
    {
        remove("temp.txt");
        printf("No food were deleted.\n");;
    }
}

//This function allows the user to edie a food from the food log file.
void editFoodLogEntry()
{
    struct FoodEntry foodLog[MAX_FOODS];
    int numEntries = 0;
    int i, index = -1;
    Str50 entryName;
    char YesorNo;
    int valid_input = 0;
    char confirm_input;
	char confirm;

    FILE *fp = fopen("foodlogs.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    // read food log entries from file
    while (numEntries < MAX_FOODS && fscanf(fp, "%s %c %d %s %s %[^\n]",
               foodLog[numEntries].name,
               &foodLog[numEntries].type,
               &foodLog[numEntries].timesEaten,
               foodLog[numEntries].dateFirstTried,
               foodLog[numEntries].locationFirstTried,
               foodLog[numEntries].description) == 6)
    {
        numEntries++;
    }
    fclose(fp);

    if (numEntries == 0)
    {
        printf("Error: no food log entries found.\n");
        return;
    }

    // prompt user to enter the name of a food log entry to edit
    printf("Enter the name of a food log entry to edit: ");
    scanf("%s", entryName);
    
    // search for the selected entry by name
    for (i = 0; i < numEntries; i++)
    {
        if (strcmp(foodLog[i].name, entryName) == 0)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Error: could not find a food log entry with that name.\n");
        return;
    }

    // display the selected entry for editing
    printf("\nEntry found:\n");
    printf("%s\n%c\t%d\n%s\n%s\n%s\n",
           foodLog[index].name,
           foodLog[index].type,
           foodLog[index].timesEaten,
           foodLog[index].dateFirstTried,
           foodLog[index].locationFirstTried,
           foodLog[index].description);

    // prompt user to confirm editing
    while (!valid_input)
    {
        printf("\nDo you want to edit this entry? (y/n) ");
        scanf(" %c", &confirm_input);
        if (confirm_input == 'y' || confirm_input == 'n')
        {
            valid_input = 1;
            confirm = (confirm_input == 'y');
        }
        else
        {
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        }
    }

    if (!confirm)
    {
        printf("\nChanges discarded. The food log entry has not been edited.\n");
        return;
    }

    // write the edited food log entries to file
    fp = fopen("foodlogs.txt", "w");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    for (i = 0; i < numEntries; i++)
    {
        if (i == index)
        {
            printf("Enter the new name of the food item: ");
            scanf("%s", foodLog[i].name);
            printf("Enter the type of the food item (a for Appetizer, m for Main Dish,, d for Dessert): ");
            scanf(" %c", &foodLog[i].type);
            while (foodLog[i].type != 'a' && foodLog[i].type != 'm' && foodLog[i].type != 'd')
            {
                printf("Invalid input. Please enter a, m, or d: ");
                scanf(" %c", &foodLog[i].type);
            }
            while(!valid_input)
            {
                printf("Enter Food Times Eaten: ");
                if (scanf("%d", &foodLog[i].timesEaten) != 1 || foodLog[i].timesEaten < 0)
                {
                    printf("Invalid input. Please enter a non-negative integer.\n");
                    while (getchar() != '\n');
                }
                else
                {
                    valid_input = 1;
                }
            }
            printf("Enter Date First Tried (MM/DD/YYYY): ");
            scanf("%s", foodLog[i].dateFirstTried);
            while (!validate_date(foodLog[i].dateFirstTried))
            {
                printf("Invalid date format. Please enter date in MM/DD/YYYY format: ");
                scanf("%s", foodLog[i].dateFirstTried);
            }
            printf("Enter the location first tried: ");
            scanf("%s", foodLog[i].locationFirstTried);
            printf("Enter a description of the food item: ");
            scanf(" %[^\n]", foodLog[i].description);
            
            // prompt for confirmation before saving changes
            printf("%s\n%c\t%d\n%s\n%s\n%s\n",
                foodLog[i].name,
                foodLog[i].type,
                foodLog[i].timesEaten,
                foodLog[i].dateFirstTried,
                foodLog[i].locationFirstTried,
                foodLog[i].description);
            printf("\nAre you sure you want to save these changes? (y/n) ");
            while (1) {
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'n') {
                    break;
                }
                printf("Invalid input. Please enter 'y' or 'n': ");
            }
        
        // if confirmation is received, update file with edited entry
        if (confirm == 'y' || confirm == 'Y')
        {
            fprintf(fp, "%s %c %d %s %s %s\n",
                    foodLog[i].name,
                    foodLog[i].type,
                    foodLog[i].timesEaten,
                    foodLog[i].dateFirstTried,
                    foodLog[i].locationFirstTried,
                    foodLog[i].description);
            printf("\nThe food log has been updated.\n");
        }
        else
        {
            printf("\nThe food log has not been updated.\n");
        }
    }
    else
    {
        fprintf(fp, "%s %c %d %s %s %s\n",
                foodLog[i].name,
                foodLog[i].type,
                foodLog[i].timesEaten,
                foodLog[i].dateFirstTried,
                foodLog[i].locationFirstTried,
                foodLog[i].description);
    }
}

fclose(fp);
}

// Compare function for qsort to sort FoodEntry array alphabetically by name
int compareFoodEntry(const void* a, const void* b)
{
    const struct FoodEntry* fa = (const struct FoodEntry*)a;
    const struct FoodEntry* fb = (const struct FoodEntry*)b;
    return strcmp(fa->name, fb->name);
}

// This function displays the food log stored in the file
void displayFoodLog()
{
    struct FoodEntry foodLog[50];
    int numRecords = 0;
    int i;
    
    FILE* fp = fopen("foodlogs.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }
    
    // Read entries from file into array of FoodEntry structures
    while (fscanf(fp, "%s %c %d %s %s %[^\n]",
                  foodLog[numRecords].name,
                  &foodLog[numRecords].type,
                  &foodLog[numRecords].timesEaten,
                  foodLog[numRecords].dateFirstTried,
                  foodLog[numRecords].locationFirstTried,
                  foodLog[numRecords].description) != EOF)
    {
        numRecords++;
    }
    
    fclose(fp);
    
    // Sort array alphabetically by name
    qsort(foodLog, numRecords, sizeof(struct FoodEntry), compareFoodEntry);
    
    // Print sorted entries
    printf("Food Log:\n");
    for (i = 0; i < numRecords; i++) {
        printf("%s\n%c\t%d\n%s\n%s\n%s\n",
               foodLog[i].name,
               foodLog[i].type,
               foodLog[i].timesEaten,
               foodLog[i].dateFirstTried,
               foodLog[i].locationFirstTried,
               foodLog[i].description);
    }
}

//This function allows the user to add a recipe from the recipe log file.
void addRecipe()
{
    char recipe_name[50], recipe_description[160], list_of_ingredients[20][80], instructions[20][100];
    int time_to_prepare, time_to_cook, number_of_ingredients, number_of_instructions, i;
    int recipe_name_exists = 0;
    // counter for number of records added
    static int num_records = 0;
    // Check if recipe name already exists in the file
    char buffer[256];
    if (num_records >= 20)
    {
        printf("Maximum number of records reached. Cannot add new record.\n");
        return;
    }

    FILE *rp;
    rp = fopen("recipes.txt", "r");

    printf("Enter Recipe Name: ");
    scanf(" %[^\n]s", recipe_name);

    while (strlen(recipe_name) > 50 || strlen(recipe_name) < 3)
    {
        printf("Recipe name can only be 3-50 characters\n");
        printf("Enter Recipe Name: ");
        scanf(" %[^\n]s", recipe_name);
    }

    while (fgets(buffer, sizeof(buffer), rp))
    {
        char *token = strtok(buffer, "\n");
        if (strcmp(token, recipe_name) == 0)
        {
            recipe_name_exists = 1;
            break;
        }
    }
    fclose(rp);

    if (recipe_name_exists)
    {
        printf("Recipe name already exists in the log. Please enter a different name.\n");
        return;
    }

    printf("Enter Description of Recipe: ");
    scanf(" %[^\n]s", recipe_description);

    while (strlen(recipe_description) > 160 || strlen(recipe_description) < 3)
    {
        printf("Recipe description can only be 3-160 characters\n");
        printf("Enter Description of Recipe: ");
        scanf(" %[^\n]s", recipe_description);
    }

    printf("Enter The Time to Prepare The Food in Minutes: ");
    scanf("%d", &time_to_prepare);

    while (time_to_prepare < 1)
    {
        printf("You must enter a positive number\n");
        printf("Enter The Time to Prepare The Food in Minutes: ");
        scanf("%d", &time_to_prepare);
    }

    printf("Enter The Time Needed to Cook The Food(Minutes): ");
    scanf("%d", &time_to_cook);

    while (time_to_cook < 1)
    {
        printf("You must enter a positive number\n");
        printf("Enter The Time Needed to Cook The Food(Minutes): ");
        scanf("%d", &time_to_cook);
    }

    printf("Enter The Number of Ingredients: ");
    scanf("%d", &number_of_ingredients);

    while (number_of_ingredients < 1)
    {
        printf("You must enter a positive number\n");
        printf("Enter The Number of Ingredients: ");
        scanf("%d", &number_of_ingredients);
    }

    for (i = 0; i < number_of_ingredients; i++)
    {
        printf("Enter Ingredient #%d: ", i + 1);
        scanf(" %[^\n]s", list_of_ingredients[i]);
    }

    printf("Enter The Number of Instructions: ");
    scanf("%d", &number_of_instructions);

    while (number_of_instructions < 1)
    {
        printf("You must enter a positive number\n");
        printf("Enter The Number of Instructions: ");
        scanf("%d", &number_of_instructions);
    }

    for (i = 0; i < number_of_instructions; i++)
    {
        printf("Instruction #%d: ", i+1);
        scanf(" %[^\n]s", instructions[i]);
        while(strlen(instructions[i]) > 100 || strlen(instructions[i]) < 3)
        {
            printf("Instruction can only be 3-100 characters\n");
            printf("Instruction #%d: ", i+1);
            scanf(" %[^\n]s", instructions[i]);
        }
    }

    // Open the file in append mode to add the new recipe
    rp = fopen("recipes.txt", "a+");

    // Write the new recipe information to the file
    fprintf(rp, "%s\n%s\n%d\t%d\n%d\n", recipe_name, recipe_description, time_to_prepare, time_to_cook, number_of_ingredients);
    for (i = 0; i < number_of_ingredients; i++)
    {
        fprintf(rp, "%s\n", list_of_ingredients[i]);
    }
    fprintf(rp, "%d\n", number_of_instructions);
    for (i = 0; i < number_of_instructions; i++)
    {
        fprintf(rp, "%s\n", instructions[i]);
    }

    fclose(rp);

    // Increment the number of records added
    num_records++;

    // Print success message
    printf("\nRecipe information has been logged successfully!\n");
}

//This function allows the user to delete a recipe from the recipe log file.
void deleteRecipe()
{
    Str50 input;
    int found = 0;
    char confirm;
    int i, j,k;
    struct RecipeEntry RecipeLog;
    FILE *rp = fopen("recipes.txt", "r");
    if (rp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }
    FILE *temp2 = fopen("temp2.txt", "w+");
    if (temp2 == NULL)
    {
        printf("Error: could not open file.\n");
        fclose(rp);
        return;
    }
    printf("Enter the name of the recipe to delete: ");
    scanf(" %[^\n]", input);
    while (fscanf(rp, "%s %[^\n] %d %d %d",
              RecipeLog.recipeName,
              RecipeLog.Description,
              &RecipeLog.timetoprepare,
              &RecipeLog.timetocook,
              &RecipeLog.numberofingredients) == 5)
    {
        // read ingredients
        for (i = 0; i < RecipeLog.numberofingredients; i++)
        {
            fscanf(rp, " %[^\n]s", RecipeLog.list_of_ingredients[i]);
        }

        // read instructions
        while (fscanf(rp, "%d", &RecipeLog.number_of_instructions) == 1)
        fscanf(rp, " %[^\n]s", RecipeLog.instructions[0]);
        for (i = 1; i < RecipeLog.number_of_instructions; i++)
        {
            fscanf(rp, " %[^\n]s", RecipeLog.instructions[i]);
        }

        if (strcmp(RecipeLog.recipeName, input) == 0)
        {
                printf("\n%s\n%s\n%d\t%d\n%d\n",
                        RecipeLog.recipeName,
                        RecipeLog.Description,
                        RecipeLog.timetoprepare,
                        RecipeLog.timetocook,
                        RecipeLog.numberofingredients);
                for (j = 0; j < RecipeLog.numberofingredients; j++)
                {
                    printf("%s\n", RecipeLog.list_of_ingredients[j]);
                }
                printf("%d\n", RecipeLog.number_of_instructions);
                for (k = 0; k < RecipeLog.number_of_instructions; k++)
                {
                    printf("%s\n", RecipeLog.instructions[k]);
                } 
            printf("==============================================================\n");
            printf("Are you sure you want to delete this Recipe log? (Y/N) ");
            fflush(stdin);
            scanf("%c", &confirm);

            while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n')
            {
                printf("Invalid input. Please enter Y or N: ");
                fflush(stdin);
                scanf("%c", &confirm);
            }

            if (confirm == 'Y' || confirm == 'y')
            {
                found = 1;
                continue;
            }
        }

        fprintf(temp2, "%s %s %d %d %d ",
                RecipeLog.recipeName,
                RecipeLog.Description,
                RecipeLog.timetoprepare,
                RecipeLog.timetocook,
                RecipeLog.numberofingredients);

        for (i = 0; i < RecipeLog.numberofingredients; i++)
        {
            fprintf(temp2, "%s\n", RecipeLog.list_of_ingredients[i]);
        }

        fprintf(temp2, "%d %s\n", RecipeLog.number_of_instructions, RecipeLog.instructions[0]);

        for (i = 1; i < RecipeLog.number_of_instructions; i++)
        {
            fprintf(temp2, "%s\n", RecipeLog.instructions[i]);
        }
    }

    fclose(rp);
    fclose(temp2);

    if (found)
    {
    	
    	remove("recipes.txt");
    	rename("temp2.txt", "recipes.txt");
    	printf("\nThe Recipe log has been deleted.\n");
    }
    else
    {
        remove("temp2.txt");
        printf("\nChanges discarded. The selected recipe log entry has not been deleted.\n");
    }
}

//This function allows the user to edit a recipe from the recipe log file.
void editRecipeLogEntry()
{
	struct RecipeEntry RecipeLog[MAX_RECIPES];
    int numEntries = 0;
    int i, j,k, index = -1;
    Str50 entryName;
    char YesorNo;
    int valid_input = 0;
    char confirm_input;
	char confirm;
	
	FILE *rp = fopen("recipes.txt", "r");
    if (rp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }
    
    while (numEntries < MAX_RECIPES &&
           fscanf(rp, "%s %[^\n] %d %d %d ",
                  RecipeLog[numEntries].recipeName,
                  RecipeLog[numEntries].Description,
                  &RecipeLog[numEntries].timetoprepare,
                  &RecipeLog[numEntries].timetocook,
                  &RecipeLog[numEntries].numberofingredients) == 5)
    {
        for (i = 0; i < RecipeLog[numEntries].numberofingredients; i++)
        {
            fgets(RecipeLog[numEntries].list_of_ingredients[i], 80, rp);
            if (RecipeLog[numEntries].list_of_ingredients[i][strlen(RecipeLog[numEntries].list_of_ingredients[i])-1] == '\n')
            {
                RecipeLog[numEntries].list_of_ingredients[i][strlen(RecipeLog[numEntries].list_of_ingredients[i])-1] = '\0';
            }
        }

        while (numEntries < MAX_RECIPES &&
        fscanf(rp, "%d", &RecipeLog[numEntries].number_of_instructions) == 1);

        for (i = 0; i < RecipeLog[numEntries].number_of_instructions; i++)
        {
            fgets(RecipeLog[numEntries].instructions[i], 100, rp);
            if (RecipeLog[numEntries].instructions[i][strlen(RecipeLog[numEntries].instructions[i])-1] == '\n')
            {
                RecipeLog[numEntries].instructions[i][strlen(RecipeLog[numEntries].instructions[i])-1] = '\0';
            }
        }

        numEntries++;
    }
    fclose(rp);

    if (numEntries == 0)
    {
        printf("Error: no recipe log entries found.\n");
        return;
    }
    
    // prompt user to enter the name of a recipe log entry to edit
    printf("Enter the name of a recipe log entry to edit: ");
    scanf(" %[^\n]s", entryName);
    
    // search for the selected entry by name
    for (i = 0; i < numEntries; i++)
    {
        if (strcmp(RecipeLog[i].recipeName, entryName) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Error: could not find a recipe log entry with that name.\n");
        return;
    }

    
    // display the selected entry for editing
    printf("\nEntry found:\n");
    for (i = 0; i < numEntries; i++)
    {
        printf("%s\n%s\n%d\t%d\n%d\n",
                RecipeLog[i].recipeName,
                RecipeLog[i].Description,
                RecipeLog[i].timetoprepare,
                RecipeLog[i].timetocook,
                RecipeLog[i].numberofingredients);
        for (j = 0; j < RecipeLog[i].numberofingredients; j++)
        {
            printf("%s\n", RecipeLog[i].list_of_ingredients[j]);
        }
        printf("%d\n", RecipeLog[i].number_of_instructions);
        for (k = 0; k < RecipeLog[i].number_of_instructions; k++)
        {
            printf("%s\n", RecipeLog[i].instructions[k]);
        }
    }

    // prompt user to confirm editing
    while (!valid_input)
    {
        printf("==============================================================\n");
        printf("Are you sure you want to edit this Recipe log? (Y/N) ");
        scanf(" %c", &confirm_input);
        if (confirm_input == 'y' || confirm_input == 'n')
        {
            valid_input = 1;
            confirm = (confirm_input == 'y');
        }
        else
        {
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        }
    }

    if (!confirm)
    {
        printf("\nChanges discarded. The recipe log entry has not been edited.\n");
        return;
    }

    // edit the recipe log entry
    printf("\nEnter the new recipe name: ");
    scanf(" %[^\n]", RecipeLog[index].recipeName);

    printf("Enter the new description of the recipe: ");
    scanf(" %[^\n]", RecipeLog[index].Description);

    printf("Enter the new time to prepare the food in minutes: ");
    scanf("%d", &RecipeLog[index].timetoprepare);

    printf("Enter the new time needed to cook the food (minutes): ");
    scanf("%d", &RecipeLog[index].timetocook);

    printf("Enter the new number of ingredients: ");
    scanf("%d", &RecipeLog[index].numberofingredients);

    for (j = 0; j < RecipeLog[index].numberofingredients; j++)
    {
        printf("Enter ingredient %d: ", j+1);
        scanf(" %[^\n]", RecipeLog[index].list_of_ingredients[j]);
    }

    printf("Enter the new number of instructions: ");
    scanf("%d", &RecipeLog[index].number_of_instructions);

    for (j = 0; j < RecipeLog[index].number_of_instructions; j++)
    {
        printf("Enter instruction %d: ", j+1);
        scanf(" %[^\n]", RecipeLog[index].instructions[j]);
    }

    // write the edited recipe log entries to file
    rp = fopen("recipes.txt", "w");
    if (rp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    for (i = 0; i < numEntries; i++)
    {
        fprintf(rp, "%s\n%s\n%d\t%d\n%d\n", RecipeLog[index].recipeName, RecipeLog[index].Description, RecipeLog[index].timetoprepare, RecipeLog[index].timetocook, RecipeLog[index].numberofingredients);
        for (i = 0; i < RecipeLog[index].numberofingredients; i++)
        {
            fprintf(rp, "%s\n", RecipeLog[index].list_of_ingredients[i]);
        }
        fprintf(rp, "%d\n", RecipeLog[index].number_of_instructions);
        for (i = 0; i < RecipeLog[index].number_of_instructions; i++)
        {
            fprintf(rp, "%s\n", RecipeLog[index].instructions[i]);
        }
    }

    fclose(rp);
    printf("Recipe log updated successfully.\n");
    return;

}

// comparison function for qsort to sort RecipeEntry structs by recipe name
int compareRecipeNames(const void* a, const void* b)
{
    struct RecipeEntry* recipeA = (struct RecipeEntry*)a;
    struct RecipeEntry* recipeB = (struct RecipeEntry*)b;
    return strcmp(recipeA->recipeName, recipeB->recipeName);
}

//// Function to display all recipe entries in the log
void displayRecipeLog(const char* fileName)
{
    struct RecipeEntry RecipeLog[MAX_RECIPES];
    int numEntries = 0;
    int i, j, k;
    FILE *rp = fopen(fileName, "r");
    if (rp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    // read food log entries from file
    while (numEntries < MAX_RECIPES &&
           fscanf(rp, "%s %[^\n] %d %d %d ",
                  RecipeLog[numEntries].recipeName,
                  RecipeLog[numEntries].Description,
                  &RecipeLog[numEntries].timetoprepare,
                  &RecipeLog[numEntries].timetocook,
                  &RecipeLog[numEntries].numberofingredients) == 5)
    {
        // read the list of ingredients
        for (i = 0; i < RecipeLog[numEntries].numberofingredients; i++)
        {
            fgets(RecipeLog[numEntries].list_of_ingredients[i], 80, rp);
            // remove newline character if present
            if (RecipeLog[numEntries].list_of_ingredients[i][strlen(RecipeLog[numEntries].list_of_ingredients[i])-1] == '\n')
            {
                RecipeLog[numEntries].list_of_ingredients[i][strlen(RecipeLog[numEntries].list_of_ingredients[i])-1] = '\0';
            }
        }

        // read the number of instructions
        while (numEntries < MAX_RECIPES &&
        fscanf(rp, "%d", &RecipeLog[numEntries].number_of_instructions) == 1)
        {
            // read the list of instructions
            for (i = 0; i < RecipeLog[numEntries].number_of_instructions; i++)
            {
                fgets(RecipeLog[numEntries].instructions[i], 100, rp);
                // remove newline character if present
                if (RecipeLog[numEntries].instructions[i][strlen(RecipeLog[numEntries].instructions[i])-1] == '\n')
                {
                    RecipeLog[numEntries].instructions[i][strlen(RecipeLog[numEntries].instructions[i])-1] = '\0';
                }
            }

            numEntries++;
        }
    }
    fclose(rp);
    
    // sort recipe log entries alphabetically by name
    qsort(RecipeLog, numEntries, sizeof(struct RecipeEntry), compareRecipeNames);

    // display Recipe log entries
    printf("Recipe Log Entries:\n");
    for (i = 0; i < numEntries; i++)
    {
        printf("%s\n%s\n%d\t%d\n%d\n",
                RecipeLog[i].recipeName,
                RecipeLog[i].Description,
                RecipeLog[i].timetoprepare,
                RecipeLog[i].timetocook,
                RecipeLog[i].numberofingredients);
        for (j = 0; j < RecipeLog[i].numberofingredients; j++)
        {
            printf("%s\n", RecipeLog[i].list_of_ingredients[j]);
        }
        printf("%d\n", RecipeLog[i].number_of_instructions);
        for (k = 0; k < RecipeLog[i].number_of_instructions; k++)
        {
            printf("%s\n", RecipeLog[i].instructions[k]);
        }
    }
}


int main()
{
    const char* fileName = "foodlogs.txt";
    int i, j, c, k = 0;
    int choice;
    struct FoodEntry foodLog[MAX_FOODS];
    int numFoods = 0;

    do
    {
        Image();
        Introduction();
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        // Validate input as integer
        while (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a valid integer.\n");
            while (getchar() != '\n'); // clear input buffer
            printf("Enter your choice: ");
        }

        switch (choice)
        {
            case 1:
                registerUser();
                break;

            case 2:
                canLogin();
                getch();
                system("cls");
                while (1)
                {
                    // Print menu and get user choice
                    Interface();
                    printf("Enter your choice: ");

                    // Validate input as integer
                    while (scanf("%d", &choice) != 1)
                    {
                        printf("Invalid input. Please enter a valid integer.\n");
                        while (getchar() != '\n'); // clear input buffer
                        printf("Enter your choice: ");
                    }

                    // Call corresponding function based on user choice
                    switch (choice)
                    {
                        case 1:
                            addFood();
                            getch();
                            system("cls");
                            break;
                        case 2:
                            deleteFood();
                            getch();
                            system("cls");
                            break;
                        case 3:
                            editFoodLogEntry();
                            getch();
                            system("cls");
                            break;
                        case 4:
                            displayFoodLog("foodlogs.txt");
                            getch();
                            system("cls");
                            break;
                        case 5:
                            addRecipe();
                            getch();
                            system("cls");
                            break;
                        case 6:
                            deleteRecipe();
                            getch();
                            system("cls");
                            break;
                        case 7:
                            editRecipeLogEntry();
                            getch();
                            system("cls");
                            break;
                        case 8:
                            displayRecipeLog("recipes.txt");
                            getch();
                            system("cls");
                            break;
                        case 9:
                            viewUsers();
                            getch();
                            system("cls");
                            break;
                        case 0:
                            printf("Returning to Log in...\n");
                            getch();
                            system("cls");
                            break;
                        default:
                            printf("Invalid choice.\n");
                            getch();
                            system("cls");
                            break;
                    }
                    if (choice == 0)
                    {
                        break;
                    }
                }
                break;

            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
                getch();
                system("cls");
                break;
        }
    } while (choice != 3);

    return 0;
}