#include <stdio.h>

// Define the struct for car details
struct Car {
    char plateNumber[20];
    char model[50];
    int modelYear;
};

int main() {
    // Create an instance of the Car struct
    struct Car myCar;

    // Get user input for car details
    printf("Enter car plate number: ");
    scanf("%s", myCar.plateNumber);

    printf("Enter car model: ");
    scanf("%s", myCar.model);

    printf("Enter car model year: ");
    scanf("%d", &myCar.modelYear);

    // Display the car details
    printf("\nCar Details:\n");
    printf("Plate Number: %s\n", myCar.plateNumber);
    printf("Model: %s\n", myCar.model);
    printf("Model Year: %d\n", myCar.modelYear);

    return 0;
}