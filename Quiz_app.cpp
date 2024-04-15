#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Structure to hold each question
struct Question {
    string questionText;
    string optionA;
    string optionB;
    string optionC;
    string optionD;
    char correctOption;
};

// Function to read questions from file
void readQuestionsFromFile(Question questions[], const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        int index = 0;
        while (getline(file, line)) {
            questions[index].questionText = line;
            getline(file, questions[index].optionA);
            getline(file, questions[index].optionB);
            getline(file, questions[index].optionC);
            getline(file, questions[index].optionD);
            file >> questions[index].correctOption;
            file.ignore(); // Ignore newline character
            index++;
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
        exit(EXIT_FAILURE);
    }
}

// Function to display a question and get user's answer
char askQuestion(Question q) {
    cout << q.questionText << endl;
    cout << "A. " << setw(15) << left << q.optionA << endl;
    cout << "B. " << setw(15) << left << q.optionB << endl;
    cout << "C. " << setw(15) << left << q.optionC << endl;
    cout << "D. " << setw(15) << left << q.optionD << endl;
    
    char userAnswer;
    cout << "Your answer (A, B, C, or D): ";
    cin >> userAnswer;
    
    // Validate user's input
    while (toupper(userAnswer) != 'A' && toupper(userAnswer) != 'B' && toupper(userAnswer) != 'C' && toupper(userAnswer) != 'D') {
        cout << "Invalid input. Please enter A, B, C, or D: ";
        cin >> userAnswer;
    }
    
    return toupper(userAnswer);
}

// Function to check if the answer is correct and update score
bool checkAnswer(Question q, char userAnswer, int& score) {
    if (userAnswer == toupper(q.correctOption)) {
        score++;
        return true;
    } else {
        return false;
    }
}

// Function to display the menu
void displayMenu() {
    cout << "===================================" << endl;
    cout << setw(15) << left << "Welcome to the Quiz Game!" << endl;
    cout << "===================================" << endl;
    cout << setw(10) << left << "1. Start Quiz" << endl;
    cout << setw(10) << left << "2. Instructions" << endl;
    cout << setw(10) << left << "3. Exit" << endl;
    cout << "===================================" << endl;
}

int main() {
    const string filename = "questions.txt";
    const int numQuestions = 7; // Change this according to the number of questions in the file
    Question questions[numQuestions];

    readQuestionsFromFile(questions, filename);

    int choice;
    int score;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                score = 0;
                // Ask each question, provide feedback, and update score
                for (int i = 0; i < numQuestions; i++) {
                    char userAnswer = askQuestion(questions[i]);
                    if (checkAnswer(questions[i], userAnswer, score)) {
                        cout << "Correct!" << endl;
                    } else {
                        cout << "Wrong!" << endl;
                    }
                }
                // Display final score
                cout << "===================================" << endl;
                cout << "Your final score is: " << score << "/" << numQuestions << endl;
                cout << "===================================" << endl;
                break;
            case 2:
                cout << "===================================" << endl;
                cout << "Instructions:" << endl;
                cout << "Answer each question by entering the corresponding letter (A, B, C, or D)." << endl;
                cout << "===================================" << endl;
                break;
            case 3:
                cout << "===================================" << endl;
                cout << "Exiting the program. Goodbye!" << endl;
                cout << "===================================" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
                break;
        }
    } while (choice != 3);

    return 0;
}

