//
//  quiz.hpp
//  QuizGenerator
//

// Function prototypes
#pragma once
#ifndef QUIZ_HPP
#define QUIZ_HPP

#include "iostream"
using namespace std;

// question class
class question {
protected:
  string _text, _answer;

public:
  question(string text, string answer);
  question() : question("", "") {}

  string text() { return _text; }
  void set_text(string text) { _text = text; }

  string answer() { return _answer; }
  virtual void set_answer(string answer) { _answer = answer; }

  bool check(string answer) {
    if (answer == _answer) {
      return true;
    }
    else {
      return false;
    }
  }

  virtual string as_save_text() {
    return "[SQ]\n" + _text + "\n" + _answer + "\n";
  }
};

// true or false question class
class tf_question : public question {
public:
  tf_question(string text, string answer);
  tf_question() : tf_question("", "T") {}
  virtual void set_answer(string answer);
  virtual string as_save_text() {
    return "[TFQ]\n" + _text + "\n" + _answer + "\n";
  }
};

// quiz class
class quiz {
private:
  question **_questions;
  int _size;
  int _capacity;

public:
  quiz(int capacity) {
    _size = 0;
    _capacity = capacity;
    _questions = new question *[_capacity];
  }
  quiz() : quiz(100) {}
  ~quiz() {
    for (int i = 0; i < _size; i++) {
      delete _questions[i];
      _questions[i] = nullptr;
    }
    delete[] _questions;
    _questions = nullptr;
  }

  int capacity() { return _capacity; }
  int size() { return _size; }

  question *get_question(int index) { return _questions[index]; }

  void add_question(question *q);

  void add_tf_question(tf_question *tfq);

  void save(string savefilename);

  void load(string loadfilename);

  void display();
};

question *create_question();
tf_question *create_tf_question();

#endif
