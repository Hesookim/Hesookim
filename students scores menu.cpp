#include <iostream>
using namespace std;

// Function to input scores
void inputScores(float scores[], int numStudents) {
    cout << "Enter the scores for " << numStudents << " students:\n";
    for (int i = 0; i < numStudents; i++) {
        cout << "Student " << i + 1 << ": ";
        cin >> scores[i]; // Taking score input for each student
    }
}

// Function to display scores
void displayScores(float scores[], int numStudents) {
    cout << "\nScores of the students:\n";
    for (int i = 0; i < numStudents; i++) {
        cout << "Student " << i + 1 << ": " << scores[i] << "\n"; // Showing each student's score
    }
}

// Function to sort scores from highest to lowest(Descending)
void sortScoresDescending(float scores[], int numStudents) {
    // using Bubble Sort to arrange scores in descending order for the class
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {
                // Swap scores if they are in the wrong order
                float temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }
    // Display sorted scores
    cout << "\nSorted scores (highest to lowest):\n";
    displayScores(scores, numStudents); // Reusing display function to show the sorted scores
}

// Function to search for a specific score given by the user
void searchScore(float scores[], int numStudents) {
    float targetScore;
    cout << "Enter the score you want to search for: ";
    cin >> targetScore;

    bool found = false;
    cout << "\nSearching for score " << targetScore << "...\n";
    for (int i = 0; i < numStudents; i++) {
        if (scores[i] == targetScore) {
            cout << "Student " << i + 1 << " has the score " << targetScore << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No student has the score " << targetScore << ".\n";
    }
}

// Recursive function to find the highest score of the students
float findHighest(float scores[], int numStudents, int index = 0) {
    if (index == numStudents - 1) return scores[index]; // Base case: last element
    return max(scores[index], findHighest(scores, numStudents, index + 1)); // Recursive call
}

// Recursive function to find the lowest score of the students
float findLowest(float scores[], int numStudents, int index = 0) {
    if (index == numStudents - 1) return scores[index]; // Base case: last element
    return min(scores[index], findLowest(scores, numStudents, index + 1)); // Recursive call
}

// Recursive function to calculate the average of scores of the students
float calculateAverage(float scores[], int numStudents, int index = 0, float sumScores = 0) {
    if (index == numStudents) return sumScores / numStudents; // Base case: return average
    return calculateAverage(scores, numStudents, index + 1, sumScores + scores[index]); // Recursive call
}

// Function to test pass/fail status of the students
void testPassFail(float scores[], int numStudents) {
    cout << "\nPass/Fail status:\n";
    for (int i = 0; i < numStudents; i++) {
        if (scores[i] >= 50) {
            cout << "Student " << i + 1 << ": Passed\n";
        } else {
            cout << "Student " << i + 1 << ": Failed\n";
        }
    }
}

int main() {
    int numStudents;

    // Ask the user for the number of students in the class
    cout << "Hello! Welcome to this program.\nPlease Enter the number of students: ";
    cin >> numStudents;

    // Check if the number of students is valid(classes have at least one person)
    if (numStudents <= 0) {
        cout << "Invalid number of students. Exiting program.\n";
        return 0;
    }

    float scores[numStudents];
    bool scoresEntered = false;

    while (true) {
        // Display menu options
        cout << "\nOptions of the Menu is as follows\n";
        cout << "The menu:\n";
        cout << "1. Enter student scores\n";
        cout << "2. Display scores\n";
        cout << "3. Find the highest score\n";
        cout << "4. Find the lowest score\n";
        cout << "5. Calculate the average score\n";
        cout << "6. Test pass/fail status\n";
        cout << "7. Search for a specific score\n";
        cout << "8. Exit the program\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        // Process user choice using switch statement
        switch (choice) {
            case 1:
                inputScores(scores, numStudents); // Input student scores
                scoresEntered = true;
                break;
            case 2:
                if (scoresEntered) {
                    displayScores(scores, numStudents); // Display scores
                } else {
                    //if user has not entered scores
                    cout << "No scores entered yet. Please enter scores first.\n";
                }
                break;
            case 3:
                if (scoresEntered) {
                    cout << "Highest score: " << findHighest(scores, numStudents) << "\n"; // Display highest score
                } else {
                    //if user has not entered scores
                    cout << "No scores entered yet. Please enter scores first.\n";
                }
                break;
            case 4:
                if (scoresEntered) {
                    cout << "Lowest score: " << findLowest(scores, numStudents) << "\n"; // Display lowest score
                } else {
                    //if user has not entered scores
                    cout << "No scores entered yet. Please enter scores first.\n";
                }
                break;
            case 5:
                if (scoresEntered) {
                    cout << "Average score: " << calculateAverage(scores, numStudents) << "\n"; // Display average score
                } else {
                    //if user has not entered scores
                    cout << "No scores entered yet. Please enter scores first.\n";
                }
                break;
            case 6:
                if (scoresEntered) {
                    testPassFail(scores, numStudents); // Check pass/fail status
                } else {
                    //if user has not entered scores
                    cout << "No scores entered yet. Please enter scores first.\n";
                }
                break;
            case 7:
                if (scoresEntered) {
                    searchScore(scores, numStudents); // Search for a specific score
                } else {
                    //if user has not entered scores
                    cout << "No scores entered yet. Please enter scores first.\n";
                }
                break;
            case 8:
                cout << "Exiting the program. Goodbye!\n";
                return 0; // Exit the program
            default:
                //if the entered number is not a defined choice
                cout << "Invalid choice. Please try again.\n"; // Handle invalid choice
                break;
        }
    }
    return 0;
}
