#include "Records.h"

StudentTable::StudentTable() {
		table = new HashTable<Student>(29, 10);
	}

bool StudentTable::empty() {
  return table->empty();
}

	void StudentTable::insert(Student s) {
		table->insert(s);
	}

	Student StudentTable::query(string& key) {
		return table->query(key);
	}

	Student StudentTable::remove(string& key) {
		return table->remove(key);
	}

	list<Student> StudentTable::getList() {
		return table->getList();
	}
 
void StudentTable::clear() {
	table->clear();
}

CourseTable::CourseTable() {
		table = new HashTable<Course>(17, 36);
	}

bool CourseTable::empty() {
  return table->empty();
}

	void CourseTable::insert(Course c) {
		table->insert(c);
	}

	Course CourseTable::query(string& key) {
		return table->query(key);
	}

	Course CourseTable::remove(string& key) {
		return table->remove(key);
	}

	list<Course> CourseTable::getList() {
		return table->getList();
	}

void CourseTable::clear() {
	table->clear();
}

SelectionTable::SelectionTable() {
  studentIndex = new HashTable<CourseSelection*>(29, 10);
  courseIndex = new HashTable<CourseSelection*>(17, 36);
}

bool SelectionTable::comparePointers(CourseSelection *cs1, CourseSelection *cs2) {
	return *cs1 < *cs2;
}
void SelectionTable::addCourse(string &id, string &code, string &mark) {
  CourseSelection *cs = new CourseSelection(id, code, mark);
  table.push_front(cs);
  table.sort();
  
  studentIndex->insert(cs, id);
  courseIndex->insert(cs, code);
}

CourseSelection SelectionTable::dropCourse(string &id, string &code) {
  CourseSelection cs(id, code);
  CourseSelection *csp = &cs;
  CourseSelection foundItem;
  bool found = false;

  list<CourseSelection*>::iterator csit = table.begin();

  for ( ; csit != table.end(); ) {
    if (*csp == *(*csit)) {
      foundItem = *(*csit);
      csit = table.erase(csit);
      found = true;
    }
    else {
      ++csit;
    }
  }

  if (found) {
    studentIndex->remove(csp, id);
    courseIndex->remove(csp, code);
  }

  return foundItem;
}

CourseSelection SelectionTable::querySelection(string &id, string &code) {
  CourseSelection cs(id, code);
  CourseSelection *csp = &cs;  

  list<CourseSelection*>::iterator csit = table.begin();

  for ( ; csit != table.end(); ++csit) {
    if (*csp == *(*csit)) {
      CourseSelection found = *(*csit);
      return found;
    }
  }

  CourseSelection dummy;
  return dummy;
}

list<CourseSelection*> SelectionTable::querySelectionByID(string &id) {
  list<CourseSelection*> idQuery = studentIndex->queryAll(id);
  idQuery.sort(SelectionTable::comparePointers);
  return idQuery;
}

list<CourseSelection*> SelectionTable::querySelectionByCode(string &code) {
  list<CourseSelection*> codeQuery = courseIndex->queryAll(code);
  codeQuery.sort(SelectionTable::comparePointers);
  return codeQuery;
}

list<CourseSelection*> SelectionTable::getList() {
  return table;
}

void SelectionTable::clear() {
  for (int i = 0; i < table.size(); i++) {
	CourseSelection *cs = table.back();
	delete cs;
	table.pop_back();
  }
  table.clear();

  studentIndex->clear();
  courseIndex->clear();
}
