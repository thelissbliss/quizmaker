//
//  main.cpp
//  QuizGenerator
//

// Main function
#include "quiz.hpp"
#include <iostream>

using namespace std;

int main() {
  quiz quizmaker(50);
  string choice, loadfilename, savefilename;

  cout << "Welcome to QuizMaker" << endl << endl;
  // Menu
  do {
    cout << "What would you like to do?" << endl;
    cout << "a. Create a question" << endl;
    cout << "b. Create a True/False question" << endl;
    cout << "c. Display questions" << endl;
    cout << "d. Save questions" << endl;
    cout << "e. Load questions" << endl;
    cout << "f. Quit" << endl;
    cout << "Choice: ";
    getline(cin, choice);
    cout << endl;

    if (choice == "a" || choice == "A") {
      quizmaker.add_question(create_question());
    } else if (choice == "b" || choice == "B") {
      quizmaker.add_tf_question(create_tf_question());
    } else if (choice == "c" || choice == "C") {
      quizmaker.display();
    } else if (choice == "d" || choice == "D") {
      cout << "What filename would you like to use? ";
      getline(cin, savefilename);
      quizmaker.save(savefilename);
    } else if (choice == "e" || choice == "E") {
      cout << "What file would you like to load? ";
      getline(cin, loadfilename);
      quizmaker.load(loadfilename);
    } else if (choice != "f" && choice != "F") {
      cout << "Invalid option" << endl << endl;
    }
  } while (choice != "f" && choice != "F");
  cout << "Thank you for using QuizMaker!" << endl;
  return 0;
}
