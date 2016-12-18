#ifndef RECORD_H
#define RECORD_H
#include "hashtable.h"
#include "datatype.h"

class StudentTable {
public:
	StudentTable();
  bool empty();
	void insert(Student s);
	Student query(string& key);
	Student remove(string& key);
	list<Student> getList();
	void clear();
private:
	HashTable<Student> *table;
};

class CourseTable {
public:
	CourseTable();
  bool empty();
	void insert(Course c);
	Course query(string& key);
	Course remove(string& key);
	list<Course> getList();
	void clear();
private:
	HashTable<Course> *table;
};

class SelectionTable {
public:
  SelectionTable();
  static bool comparePointers(CourseSelection*, CourseSelection*);
  void addCourse(string &id, string &code, string &mark);
  CourseSelection dropCourse(string& id, string& code);
  CourseSelection querySelection(string &id, string &code);
  list<CourseSelection*> querySelectionByID(string &id);
  list<CourseSelection*> querySelectionByCode(string &code);
  list<CourseSelection*> getList();
  void clear();
private:
  list<CourseSelection*> table;
  HashTable<CourseSelection*> *studentIndex;
  HashTable<CourseSelection*> *courseIndex;
};

#endif
