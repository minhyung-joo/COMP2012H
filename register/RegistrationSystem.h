#ifndef REGSYSTEM_H
#define REGSYSTEM_H

#include "ReportGenerator.h"
#include "FileManager.h"
using namespace std;

class RegistrationSystem {
public:
  RegistrationSystem();

  void exec();
  
  bool checkID(const string &id);
  bool checkName(const string &name);
  bool checkYear(const string &year);
  bool checkGender(const string &gender);
  void insertStudent();
  void modifyStudent();
  void deleteStudent();
  void queryStudent();
  void studentManagement();
  
  bool checkCode(const string& code);
  bool checkCourseName(const string& name);
  bool checkCredit(const string& credit);
  void insertCourse();
  void modifyCourse();
  void deleteCourse();
  void queryCourse();
  void courseManagement();
  
  void addCourse();
  void dropCourse();
  bool checkMark(const string &mark);
  void modifyExam();
  void queryRegistration();
  void courseRegistration();
  
  void listStudent();
  void listCourse();
  void listCourseOfStudent();
  void listStudentOfCourse();
  void reportManagement();
  
  void saveData();
  void loadData();
  void fileManagement();
  
private:
  StudentTable studentTable;
  CourseTable courseTable;
  SelectionTable selectionTable;
  ReportGenerator *reportGenerator;
  FileManager *fileManager;
};

#endif