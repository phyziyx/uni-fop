#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_RENTAL_TYPES	(3)
#define MAX_RENTAL_SIZE		(17)
#define	MAX_RENTS			(50)

char rentalTypes[MAX_RENTAL_TYPES][MAX_RENTAL_SIZE] = {
	"Bungalow",
	"Small Apartment",
	"Condominium"
};

typedef struct RentalData {
	char location[32];
	int  price;
	int  type;
	int  available;
} rentalData;

char command[16] = "\0";
rentalData rentsData[MAX_RENTS];
int rentsTotal = 0;
FILE *file;

void SaveRents();
void SaveRents() {
	// Saves the rent in the file according to our pattern
	int i = 0;
	// Overwrite the data by seeking to the beginning of the file
	fseek(file, 0, 0);
	for (i = 0; i != rentsTotal; ++ i) {
		fprintf(file, "%s\t%d\t%d\t%d\n",
			rentsData[i].location, rentsData[i].price, rentsData[i].type, rentsData[i].available
		);
	}
}

void showRentalTypes();
void showRentalTypes() {
	// Show the rental types
	int i = 0;
	for (i = 0; i != MAX_RENTAL_TYPES; ++ i) {
		printf("%d: %s\n", i, rentalTypes[i]);
	}
}

void showRentals();
void showRentals() {
	// Show the rental places list
	printf("-----------------------------------------------------------------\n");
	printf("ID\tLocation\tRent\t\tType\t\tStatus\n");
	printf("-----------------------------------------------------------------\n");
	if (!rentsTotal) {
		printf("No rental places.\n");
	} else {
		int i = 0;
		for (i = 0; i != rentsTotal; ++ i) {
			printf("%d\t%s\tRs. %d\t%s\t%s\n",
				(i + 1), rentsData[i].location, rentsData[i].price, rentalTypes[rentsData[i].type], (rentsData[i].available ? "Vacant" : "Occupied")
			);
		}
	}
	printf("-----------------------------------------------------------------\n");
}

void showCommands();
void showCommands() {
	// Does what the function name says:  Shows the command list
	printf("-----------------------------------------------------------------\n");
	printf("\t\t\tApartment Rental System \n");
	printf("-----------------------------------------------------------------\n");
	printf("The available commands are:\n");
	printf("Type 'view' or 'list' to view the list of available rental places\n");
	printf("Type 'add' to add new rental place\n");
	printf("Type 'rent' to rent a place\n");
	printf("Type 'unrent' to unrent a place\n");
	printf("Type 'exit' to exit out\n");
	printf("-----------------------------------------------------------------\n");
}

void resetMenu();
void resetMenu() {
	// Reset the command string and show the commands menu
	command[0] = '\0';
	showCommands();
}

void showUnrentMenu();
void showUnrentMenu() {
	// Show the unrenting menu for customers
	int rid = 0;
	showRentals();
	printf("Insert the rental place ID: ");
	fflush(stdin);
	scanf("%d", &rid);
	while (rid <= 0 || rid > rentsTotal) {
		printf("Invalid rent place entered.\n");
		scanf("%d", &rid);
	}
	// This is necessary because we +1 the array index in the showRentals list
	-- rid;
	// Do the sanity checks and then notify the user upon the operations status (success or fail)
	if (rentsData[rid].available) {
		printf("That place is not rented.\n");
	} else {
		rentsData[rid].available = 1;
		printf("'%s' was unrented.\n", rentsData[rid].location);
	}
}

void showRentMenu();
void showRentMenu() {
	// Show the renting menu for customers
	int rid = 0, days;
	showRentals();
	printf("Insert the rental place ID: ");
	fflush(stdin);
	scanf("%d", &rid);
	while (rid <= 0 || rid > rentsTotal) {
		printf("Invalid rent place entered.\n");
		scanf("%d", &rid);
	}
	printf("Insert the number of days you want to rent: ");
	fflush(stdin);
	scanf("%d", &days);
	while (days <= 0) {
		printf("Invalid day count entered.\n");
		scanf("%d", &days);
	}
	// This is necessary because we +1 the array index in the showRentals list
	-- rid;
	// Do the sanity checks and then notify the user upon the operations status (success or fail)
	if (!rentsData[rid].available) {
		printf("That place is not available for rent.\n");
	} else {
		rentsData[rid].available = 0;
		printf("'%s' was rented for %d day(s) costing Rs. %d.\n", rentsData[rid].location, days, rentsData[rid].price*days);
	}
}

void showAddMenu();
void showAddMenu() {
	// Show the rental menu for adding new location
	char name[32];
	int type = -1, rent = 0;

	fflush(stdin);
	printf("Insert new rental name: ");
	gets(name);

	fflush(stdin);
	printf("Insert rent of '%s': ", name);
	scanf("%d", &rent);

	printf("Insert type of '%s': \n", name);
	showRentalTypes();
	while (type == -1) {
		fflush(stdin);
		scanf("%d", &type);
		if (type < 0 || type >= MAX_RENTAL_TYPES) {
			printf("You inserted an invalid rental type.");
			type = -1;
		}
	}

	// Add data to the rents array
	strcat(rentsData[rentsTotal].location, name);
	rentsData[rentsTotal].price = rent;
	rentsData[rentsTotal].type = type;
	rentsData[rentsTotal].available = 1;
	rentsTotal ++;

	printf("You added location '%s' type %s for Rs. %d\n", name, rentalTypes[type], rent);
}

int LoadRents();
int LoadRents() {
	// Open the file 'rents.txt' in reading and writing mode (r+)
	// If the programme is ran for the first time, an error will occur
	// as the file does not exist, and it will then proceed to create
	// an empty file with writing mode (w)
	file = fopen("rents.txt", "r+");
	if (file == NULL) {
		// Failed to open? Attempt to create now now
		file = fopen("rents.txt", "w");
		if (file == NULL) {
			// Failed to create as well? Exit the programme
			printf("Failed to create 'rents.txt'...");
			return 1;
		}
		// Successfully created!  Close the file
		fclose(file);

		// Open the file in reading and writing mode (r+)
		file = fopen("rents.txt", "r+");
		if (file == NULL) {
			printf("Failed to open 'rents.txt'...");
			// If the file for some reason still fails to open,
			// Terminate our programme
			return 1;
		}
	}

	// Read the file line by line, and then parse the data into our structure
	char temp[128];
	while (fgets(temp, sizeof(temp), file)) {
		// string scanf for data parse
		sscanf(temp, "%[^\t]\t%d\t%d\t%d\n",
			&rentsData[rentsTotal].location, &rentsData[rentsTotal].price, &rentsData[rentsTotal].type, &rentsData[rentsTotal].available);
		// Increase the loaded rent places by one
		rentsTotal ++;
	}
	// Return 0 if no error is encountered
	return 0;
}

int main() {

	// If an error is encountered, stop the programme from executing
	if (LoadRents()) return 1;

	// Show the commands, and ask the user for input of command
	showCommands();
	while (command[0] == '\0') {
		fflush(stdin);
		scanf("%16s", &command);
		system("cls");

		printf("You entered command: %s\n", command);

		// View, List, Add, Rent, Unrent and Exit
		if (strcmp(command, "view") == 0 || strcmp(command, "list") == 0) {
			// If the user enters command 'view' or 'list', show them the list of apartments
			showRentals();
			fflush(stdin);
			resetMenu(command);
		}
		else if (strcmp(command, "add") == 0) {
			// If the user enters command 'add', show them the add menu
			showAddMenu();
			resetMenu(command);
		}
		else if (strcmp(command, "rent") == 0) {
			// If the user enters command 'rent', show them the rent menu
			showRentMenu();
			resetMenu(command);
		}
		else if (strcmp(command, "unrent") == 0) {
			// If the user enters command 'unrent', show them the unrent menu
			showUnrentMenu();
			resetMenu(command);
		}
		else if (strcmp(command, "exit") == 0) {
			// If the user enters command to exit, exit the programme
			SaveRents();
			fclose(file);
			exit(0);
		}
		else {
			// If the user enters an invalid command, show the command list again
			// and empty the command string for the while loop to run
			printf("You entered an invalid command!\n");
			resetMenu(command);
		}
	}

	// This is just to make sure the window does not close itself upon exit
	getch();

	return 0;
}
