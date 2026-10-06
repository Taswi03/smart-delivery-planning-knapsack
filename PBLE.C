#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent a package
typedef struct {
    int id;
    float value;
    float weight;
    float ratio;
    float fraction; // Stores the fraction of the package taken (0.0 to 1.0)
} Package;

// Function Prototypes
void enterPackageDetails(Package pkgs[], int *n, float *capacity);
void displayPackageDetails(Package pkgs[], int n);
void calculateRatios(Package pkgs[], int n);
void sortPackages(Package pkgs[], int n);
float findMaxValue(Package pkgs[], int n, float capacity, float *totalWeightUsed);
void displaySelectedPackages(Package pkgs[], int n);

int main() {
    Package pkgs[MAX];
    int n = 0;
    float capacity = 0;
    float totalWeightUsed = 0;
    float maxValue = 0;
    
    int choice;
    int dataEntered = 0, ratioCalculated = 0, sorted = 0, evaluated = 0;

    do {
        printf("\n=========================================\n");
        printf("    SMART DELIVERY PLANNING (KNAPSACK)   \n");
        printf("=========================================\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enterPackageDetails(pkgs, &n, &capacity);
                dataEntered = 1;
                ratioCalculated = 0;
                sorted = 0;
                evaluated = 0;
                break;

            case 2:
                if (!dataEntered) {
                    printf("\n[Error] Please enter package details first (Option 1).\n");
                } else {
                    displayPackageDetails(pkgs, n);
                }
                break;

            case 3:
                if (!dataEntered) {
                    printf("\n[Error] Please enter package details first (Option 1).\n");
                } else {
                    calculateRatios(pkgs, n);
                    ratioCalculated = 1;
                    printf("\n[Success] Value/Weight ratios calculated successfully!\n");
                    displayPackageDetails(pkgs, n);
                }
                break;

            case 4:
                if (!ratioCalculated) {
                    printf("\n[Error] Please calculate ratios first (Option 3).\n");
                } else {
                    sortPackages(pkgs, n);
                    sorted = 1;
                    printf("\n[Success] Packages sorted in decreasing order of ratio!\n");
                    displayPackageDetails(pkgs, n);
                }
                break;

            case 5:
                if (!sorted) {
                    printf("\n[Error] Please sort packages first (Option 4).\n");
                } else {
                    maxValue = findMaxValue(pkgs, n, capacity, &totalWeightUsed);
                    evaluated = 1;
                    printf("\n[Success] Maximum value computed successfully!\n");
                    printf("Maximum Achievable Value: %.2f\n", maxValue);
                    printf("Total Weight Used: %.2f / %.2f\n", totalWeightUsed, capacity);
                }
                break;

            case 6:
                if (!evaluated) {
                    printf("\n[Error] Please find the maximum value first (Option 5).\n");
                } else {
                    displaySelectedPackages(pkgs, n);
                }
                break;

            case 7:
                printf("\nExiting program. Thank you!\n");
                break;

            default:
                printf("\n[Invalid Choice] Please enter a choice between 1 and 7.\n");
        }
    } while (choice != 7);

    return 0;
}

// 1. Enter Package Details
void enterPackageDetails(Package pkgs[], int *n, float *capacity) {
    printf("\nEnter the number of packages: ");
    scanf("%d", n);

    if (*n <= 0 || *n > MAX) {
        printf("Invalid number of packages. Setting to default max limits.\n");
        *n = (*n > MAX) ? MAX : 0;
        return;
    }

    for (int i = 0; i < *n; i++) {
        pkgs[i].id = i + 1;
        pkgs[i].fraction = 0.0;
        printf("\nPackage %d:\n", pkgs[i].id);
        printf("  Enter Value/Profit: ");
        scanf("%f", &pkgs[i].value);
        printf("  Enter Weight: ");
        scanf("%f", &pkgs[i].weight);
    }

    printf("Enter Maximum Carrying Capacity of the Vehicle: ");
    scanf("%f", capacity);
    printf("\n[Success] Package details recorded successfully!\n");
}

// 2. Display Package Details
void displayPackageDetails(Package pkgs[], int n) {
    printf("\n----------------------------------------------------\n");
    printf("ID \t Value \t Weight \t Ratio (V/W)\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t %.2f \t %.2f \t\t %.2f\n", 
               pkgs[i].id, pkgs[i].value, pkgs[i].weight, pkgs[i].ratio);
    }
    printf("----------------------------------------------------\n");
}

// 3. Calculate Value/Weight Ratio
void calculateRatios(Package pkgs[], int n) {
    for (int i = 0; i < n; i++) {
        if (pkgs[i].weight > 0) {
            pkgs[i].ratio = pkgs[i].value / pkgs[i].weight;
        } else {
            pkgs[i].ratio = 0;
        }
    }
}

// 4. Sort Packages by Ratio (Descending Order using Bubble Sort)
void sortPackages(Package pkgs[], int n) {
    Package temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (pkgs[j].ratio < pkgs[j + 1].ratio) {
                temp = pkgs[j];
                pkgs[j] = pkgs[j + 1];
                pkgs[j + 1] = temp;
            }
        }
    }
}

// 5. Find Maximum Value (Greedy Approach)
float findMaxValue(Package pkgs[], int n, float capacity, float *totalWeightUsed) {
    float currentWeight = 0;
    float finalValue = 0.0;

    // Reset fractions
    for (int i = 0; i < n; i++) {
        pkgs[i].fraction = 0.0;
    }

    for (int i = 0; i < n; i++) {
        if (currentWeight + pkgs[i].weight <= capacity) {
            // Take the whole package
            currentWeight += pkgs[i].weight;
            finalValue += pkgs[i].value;
            pkgs[i].fraction = 1.0;
        } else {
            // Take fractional part of the package
            float remainingCapacity = capacity - currentWeight;
            pkgs[i].fraction = remainingCapacity / pkgs[i].weight;
            finalValue += pkgs[i].value * pkgs[i].fraction;
            currentWeight += remainingCapacity;
            break; // Vehicle is full
        }
    }
    *totalWeightUsed = currentWeight;
    return finalValue;
}

// 6. Display Selected Packages & Fractions
void displaySelectedPackages(Package pkgs[], int n) {
    printf("\n====================================================\n");
    printf("              SELECTED PACKAGES DETAILS             \n");
    printf("====================================================\n");
    printf("ID \t Value \t\t Weight \t Fraction Taken\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (pkgs[i].fraction > 0.0) {
            printf("%d \t %.2f \t\t %.2f \t\t %.2f (%.0f%%)\n", 
                   pkgs[i].id, 
                   pkgs[i].value, 
                   pkgs[i].weight, 
                   pkgs[i].fraction, 
                   pkgs[i].fraction * 100);
        }
    }
    printf("====================================================\n");
}