//
//  quiz.cpp
//  QuizGenerator
//

// Functions definitions
#include "quiz.hpp"
#include "fstream"
#include <iostream>
using namespace std;

// question
question::question(string text, string answer) {
  _text = text;
  _answer = answer;
}

// true or false question
tf_question::tf_question(string text, string answer) {
  _text = text;
  if (answer == "T" || answer == "F" || answer == "t" || answer == "f") {
    _answer = answer;
  } else {
    _answer = "T";
    cout << "Invalid answer. Setting answer to True.\n";
  }
}

// add a question
void quiz::add_question(question *q) {
  if (_size < _capacity) {
    _questions[_size] = q;
    _size++;
  } else {
    cout << "Sorry, can't create any more questions.\n";
  }
}

// add a true or false question
void quiz::add_tf_question(tf_question *tfq) {
  if (_size < _capacity) {
    _questions[_size] = tfq;
    _size++;
  } else {
    cout << "Sorry, can't create any more questions.\n";
  }
}

// save file
void quiz::save(string savefilename) {
  ofstream fout;
  fout.open(savefilename);
  fout << _size << endl;
  for (int i = 0; i < _size; i++) {
    fout << _questions[i]->as_save_text();
  }
  if (fout) {
    cout << "File saved successfully!\n\n";
  } else {
    cout << "File did not save.\n\n";
  }
  fout.close();
}

// load file
void quiz::load(string loadfilename) {
  ifstream fin;
  string currentline, text, answer;
  int numquestions;

  for (int i = 0; i < _size; i++) {
    delete _questions[i];
    _questions[i] = nullptr;
  }
  delete[] _questions;
  _questions = nullptr;

  fin.open(loadfilename);
  fin >> numquestions;
  fin.ignore();

  _capacity = numquestions + 30;
  _questions = new question *[_capacity];

  for (int i = 0; i < numquestions; i++) {
    getline(fin, currentline);

    if (currentline == "[SQ]") {
      getline(fin, text);
      getline(fin, answer);
      question *sq_temp = new question(text, answer);
      add_question(sq_temp);

    } else if (currentline == "[TFQ]") {
      getline(fin, text);
      getline(fin, answer);
      tf_question *tfq_temp = new tf_question(text, answer);
      add_tf_question(tfq_temp);
    }
  }

  cout << "File loaded successfully!\n\n";
  fin.close();
}

// display quiz
void quiz::display() {
  cout << "Question and Answer list\n";
  for (int i = 0; i < _size; i++) {
    cout << i + 1 << ". " << _questions[i]->text() << endl;
    cout << "Answer: " << _questions[i]->answer() << endl;
  }
  cout << endl;
}

// true or false answer
void tf_question::set_answer(string answer) {
  if (answer == "T" || answer == "F" || answer == "t" || answer == "f") {
    _answer = answer;
  } else {
    _answer = "T";
    cout << "Invalid answer. Setting answer to True.\n";
  }
}

// create question
question *create_question() {
  string text, answer;
  cout << "Please enter your question: ";
  getline(cin, text);
  cout << "Please enter the answer: ";
  getline(cin, answer);
  question *q = new question(text, answer);
  cout << "Question added!" << endl << endl;
  return q;
}

// create true or false question
tf_question *create_tf_question() {
  string text, answer;
  cout << "Please enter your True/False question: ";
  getline(cin, text);
  cout << "Please enter the answer (T/F): ";
  getline(cin, answer);
  tf_question *tfq = new tf_question(text, answer);
  cout << "True/False question added!" << endl << endl;
  return tfq;
}
