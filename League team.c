#include <stdio.h>  // input/output functions
#include <stdlib.h> // standard library functions
#include <string.h> // string functions
#include <time.h>  // time functions

#define NUM_TEAMS 5 // Maximum number of teams that can be enrolled
#define SQUAD_SIZE 11 // Maximum number of players in a team

// Structure to store player information
struct Player {
    char name[50];      // Player's name
    int kit_number;     // Player's kit number
    char dob[50];       // Player's date of birth
    char position[50];  // Player's position
};

// Structure to store team information
struct Team {
    char team_name[20];    // Team name
    struct Player players[SQUAD_SIZE];  // Array of players in the team
    int activeSize;        // Number of active players in the team
};

// Array to store all teams
struct Team teams[NUM_TEAMS]; 
int current_num_teams = 0; // Track the number of enrolled teams

// Function prototypes
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void handle_error(); 

//Main loop
int main() {
    int choice;

    // Initialize the active player count for each team to 0
    for (int i = 0; i < NUM_TEAMS; i++) {
        teams[i].activeSize = 0;
    }

    // Main loop to display menu and execute functions based on user choice
    while (1) {
        display_menu();  // Display menu options
        printf("Enter your choice: ");
        scanf("%d", &choice);  // Get user's menu choice
        getchar(); // Consume the newline character left by scanf

        // Execute function based on user input
        switch (choice) {
            case 1:
                enroll_club();  // Enroll a new club
                break;
            case 2:
                add_player();  // Add a player to an existing team
                break;
            case 3:
                search_update();  // Search for and update player details
                break;
            case 4:
                display_club_statistics();
                break;  // Display statistics for all teams
            case 5:
                printf("Thank you for using the application\nExiting the Application....\n");
                return 0;  // Exit the program
            default:
                handle_error();  // Handle invalid input
                return 0;
        }
    }
}

// Function to display the main menu
void display_menu() {
    printf("\n*****Welcome to League Team Application*****\n");
    printf("\n1. Enroll a club\n");
    printf("2. Add a player\n");
    printf("3. Search and update\n");
    printf("4. Display Club Statistics\n");
    printf("5. Exit\n");
}

// Function to enroll a new club (team)
void enroll_club() {
    if (current_num_teams >= NUM_TEAMS) {
        printf("The maximum number of teams have already been enrolled.\n");
        return;
    }
    char club_name[20];
    printf("Enter the name of the club: ");
    fgets(club_name, sizeof(club_name), stdin);  // Get the team name from user
    club_name[strcspn(club_name, "\n")] = '\0';  // Remove the newline character from the input
    if (strlen(club_name) == 0) {
        printf("Club name cannot be empty.\n");
        return;
    }
    // Check if a team with the entered name already exists
    for (int i = 0; i < current_num_teams; i++) {
        if (strcasecmp(teams[i].team_name, club_name) == 0) {
            printf("A team with this name already exists.\n");
            return;
        }
    }
    // Add the new team to the list of enrolled teams
    strcpy(teams[current_num_teams].team_name, club_name);
    teams[current_num_teams].activeSize = 0;  // Initialize the active player count to 0
    current_num_teams++;  // Increment the team count
    printf("Team %s has been enrolled successfully.\n", club_name);

    if (current_num_teams == NUM_TEAMS) {
        printf("You have reached the maximum number of teams.\n");
    }
}

// Function to add a player to an existing team
void add_player() {
    // Variables to store player information
    int team_index, kit_number;
    char player_name[51], dob[11], position[31];

    // Check if any team has been enrolled
    if (current_num_teams == 0) {
        printf("No teams have been enrolled yet. Please enroll a team first.\n");
        return;
    }

    // Display list of enrolled teams
    printf("Following are the teams enrolled:\n");
    for (int i = 0; i < current_num_teams; i++) {
        printf("%d. %s\n", i + 1, teams[i].team_name);
    }
    // Get user input for team selection
    printf("Select a team to add a player: ");
    scanf("%d", &team_index);
    getchar();  // Consume the newline character

    // Validate team selection
    if (team_index < 1 || team_index > current_num_teams) {
        handle_error();
        return;
    }

    team_index--;  // Adjust for 0-indexed array   

    // Check if the team already has the maximum number of players
    if (teams[team_index].activeSize >= SQUAD_SIZE) {
        printf("This team already has 11 players.\n");
        return;
    }

    // Collect player information (name) and validate duplicates
    while (1) {
        printf("Enter player name (max 50 characters): ");
        fgets(player_name, sizeof(player_name), stdin);
        player_name[strcspn(player_name, "\n")] = '\0';  // Remove newline character

        // Check for name duplicates
        int found_duplicate = 0;
        for (int i = 0; i < teams[team_index].activeSize; i++) {
            if (strcasecmp(teams[team_index].players[i].name, player_name) == 0) { 
                found_duplicate = 1; // Set flag if duplicate name is found
                break;
            }
        }
        // Display error message if duplicate name is found
        if (found_duplicate) {
            // Display players with the same name
            printf("Player with name %s already exists in this team. \n", player_name);
            printf("Players with the same name:\n");
            for (int i = 0; i < teams[team_index].activeSize; i++) {
                    printf("Name : %s Kit Number: %d \n", 
                    teams[team_index].players[i].name, 
                    teams[team_index].players[i].kit_number);
                    found_duplicate = 1;
            printf("Please enter a different name.\n");
            }
        } else {
            break;  // Exit loop if name is unique
        }
    }

    // Collect player information (kit number) and validate duplicates across all teams
    while (1) {
        printf("Enter kit number (1-99): ");
        scanf("%d", &kit_number);
        getchar();  // Consume newline character

        // Validate kit number range
        if (kit_number < 1 || kit_number > 99) {
            printf("Invalid kit number. Please enter a number between 1 and 99.\n");
            continue;
        }

        // Check for duplicate kit number across all teams
        int found_duplicate = 0;
        for (int i = 0; i < current_num_teams; i++) {
            for (int j = 0; j < teams[i].activeSize; j++) {
                if (teams[i].players[j].kit_number == kit_number) {
                    found_duplicate = 1;
                    printf("Kit number %d is already taken in team %s by player %s.\n", 
                           kit_number, teams[i].team_name, teams[i].players[j].name);
                    break;
                }
            }
            if (found_duplicate) break;
        }

        if (found_duplicate) {
            printf("Please enter a different kit number.\n");
        } else {
            break;  // Exit loop if kit number is unique across all teams
        }
    }

    // Collect remaining player information (DOB, position)
    printf("Enter date of birth (DD MM YYYY): ");
    fgets(dob, sizeof(dob), stdin);
    dob[strcspn(dob, "\n")] = '\0';  // Remove newline character

    getchar();
    
    // Collect remaining player information (DOB, position)
    printf("Enter position: ");
    fgets(position, sizeof(position), stdin);
    position[strcspn(position, "\n")] = '\0';  // Remove newline character

    // Add player to team
    strcpy(teams[team_index].players[teams[team_index].activeSize].name, player_name);
    teams[team_index].players[teams[team_index].activeSize].kit_number = kit_number;
    strcpy(teams[team_index].players[teams[team_index].activeSize].dob, dob);
    strcpy(teams[team_index].players[teams[team_index].activeSize].position, position);

    teams[team_index].activeSize++;  // Increment active player count
    printf("Player %s added to team %s successfully.\n", player_name, teams[team_index].team_name);
}

// Function to search and update player details
void search_update() {
    // Variables to store search criteria and update choice
    char search_name[50];
    int ch, kn, update_choice, update_choice1;
    int found = 0;

    // Check if any team has been enrolled
    if (current_num_teams == 0) {
        printf("No teams have been enrolled yet.\n");
        return;
    }

    // Ask user whether they want to search by kit number or name
    printf("1. Kit Number\n");
    printf("2. Player's Name\n");
    printf("Do you want to search for a member by entering name or kit number?");
    scanf("%d", &ch);
    getchar();  // Consume the newline character

    // Search by kit number
    if (ch == 1) {
        printf("Enter kit number to search: ");
        scanf("%d", &kn);
        getchar();  // Consume the newline character

        // Validate kit number
        if (kn < 1 || kn > 99) {
            handle_error();  // Handle invalid kit number
            return;
        }

        // Search through teams and players for matching kit number
        for (int i = 0; i < current_num_teams; i++) {
            for (int j = 0; j < teams[i].activeSize; j++) {
                if (teams[i].players[j].kit_number == kn) {
                    printf("Player found in team %s.\n", teams[i].team_name);
                    printf("Name: %s\n", teams[i].players[j].name);
                    printf("DOB: %s\n", teams[i].players[j].dob);
                    printf("Position: %s\n", teams[i].players[j].position);

                    // Option to update player details
                    printf("Do you want to update player details? (1 for Yes, 0 for No): ");
                    scanf("%d", &update_choice);
                    getchar();  // Consume newline character

                    // Update selected player details
                    if (update_choice == 1) {
                        printf("1. Name\n");
                        printf("2. Kit Number\n");
                        printf("3. DOB\n");
                        printf("4. Position\n");
                        printf("What do you want to update?");
                        scanf("%d", &update_choice1);
                        getchar();  // Consume newline character

                        if (update_choice1 == 1) {
                            printf("Enter new name: ");
                            fgets(teams[i].players[j].name, sizeof(teams[i].players[j].name), stdin);
                            teams[i].players[j].name[strcspn(teams[i].players[j].name, "\n")] = '\0';
                        } else if (update_choice1 == 2) {
                            printf("Enter new kit number: ");
                            scanf("%d", &teams[i].players[j].kit_number);
                            getchar();  // Consume newline character
                        } else if (update_choice1 == 3) {
                            printf("Enter new DOB: ");
                            fgets(teams[i].players[j].dob, sizeof(teams[i].players[j].dob), stdin);
                            teams[i].players[j].dob[strcspn(teams[i].players[j].dob, "\n")] = '\0';
                        } else if (update_choice1 == 4) {
                            printf("Enter new position: ");
                            fgets(teams[i].players[j].position, sizeof(teams[i].players[j].position), stdin);
                            teams[i].players[j].position[strcspn(teams[i].players[j].position, "\n")] = '\0';
                        }
                    }

                    found = 1;
                    break;
                }
            }
            if (found) break;
        }

        // If player was not found
        if (!found) {
            printf("Player with kit number %d not found.\n", kn);
        }
    } else if (ch == 2) {
        // Search by player name
        printf("Enter player name: ");
        fgets(search_name, sizeof(search_name), stdin);
        search_name[strcspn(search_name, "\n")] = '\0';

        // Search for player by name
        for (int i = 0; i < current_num_teams; i++) {
            for (int j = 0; j < teams[i].activeSize; j++) {
                if (strcasecmp(teams[i].players[j].name, search_name) == 0) {
                    printf("Player found in team %s.\n", teams[i].team_name);
                    printf("Name: %s\n", teams[i].players[j].name);
                    printf("DOB: %s\n", teams[i].players[j].dob);
                    printf("Position: %s\n", teams[i].players[j].position);

                    // Option to update player details
                    printf("Do you want to update player details? (1 for Yes, 0 for No): ");
                    scanf("%d", &update_choice);
                    getchar();

                    // Update selected player details
                    if (update_choice == 1) {
                        printf("1. Name\n");
                        printf("2. Kit Number\n");
                        printf("3. DOB\n");
                        printf("4. Position\n");
                        printf("What do you want to update?\n");
                        scanf("%d", &update_choice1);
                        getchar();

                        if (update_choice1 == 1) {
                            printf("Enter new name: ");
                            fgets(teams[i].players[j].name, sizeof(teams[i].players[j].name), stdin);
                            teams[i].players[j].name[strcspn(teams[i].players[j].name, "\n")] = '\0';
                        } else if (update_choice1 == 2) {
                            printf("Enter new kit number: ");
                            scanf("%d", &teams[i].players[j].kit_number);
                            getchar();
                        } else if (update_choice1 == 3) {
                            printf("Enter new DOB: ");
                            fgets(teams[i].players[j].dob, sizeof(teams[i].players[j].dob), stdin);
                            teams[i].players[j].dob[strcspn(teams[i].players[j].dob, "\n")] = '\0';
                        } else if (update_choice1 == 4) {
                            printf("Enter new position: ");
                            fgets(teams[i].players[j].position, sizeof(teams[i].players[j].position), stdin);
                            teams[i].players[j].position[strcspn(teams[i].players[j].position, "\n")] = '\0';
                        }
                    }

                    found = 1;
                    break;
                }
            }
            if (found) break;
        }

        // If player not found
        if (!found) {
            printf("Player with name %s not found.\n", search_name);
        }
    } else {
        handle_error();
    }
}


// Function to calculate age from DOB
int calculate_age(const char* dob) {
    // Variables to store date components
    int day, month, year;
    int current_day, current_month, current_year;
    
    // Parse the DOB (format: DD MM YYYY)
    sscanf(dob, "%d %d %d", &day, &month, &year);
    
    // Get current date
    time_t t = time(NULL); // Get current time
    struct tm tm = *localtime(&t); //Get current time
    current_day = tm.tm_mday; // Day of the month
    current_month = tm.tm_mon + 1; // Months are 0-based
    current_year = tm.tm_year + 1900; // Years since 1900

    // Calculate age
    int age = current_year - year;
    if (current_month < month || (current_month == month && current_day < day)) {
        age--; // Adjust if birthday hasn't occurred yet this year
    }
    return age;
}

// Function to display club statistics
void display_club_statistics() {
    int avg_age;
    printf("\n***** Club Statistics *****\n");
    if(current_num_teams == 0) {
        printf("No teams have been enrolled yet.\n"); // Display message if no teams are enrolled
        return;
    } 
    for (int i = 0; i < current_num_teams; i++) {
        int total_age = 0;
        for (int j = 0; j < teams[i].activeSize; j++) {
            total_age += calculate_age(teams[i].players[j].dob);
        }
        avg_age = (teams[i].activeSize > 0) ? total_age / teams[i].activeSize : 0;
        
        printf("\nTeam: %s\n", teams[i].team_name); // Display team name
        printf("Number of players: %d\n", teams[i].activeSize); // Display number of players
        printf("Average age of players: %d years\n", avg_age); // Print average age after team details
        printf("Players:\n"); 
        
        for (int j = 0; j < teams[i].activeSize; j++) {
            int age = calculate_age(teams[i].players[j].dob); // Calculate player's age
            printf("%d. %s, Kit Number: %d, Position: %s, Age: %d years\n",
                   j + 1, 
                   teams[i].players[j].name, 
                   teams[i].players[j].kit_number,
                   teams[i].players[j].position, 
                   age);
        }
    }
}

// Function to handle errors
void handle_error() {
    printf("Invalid input. Please try again.\n");
}
 