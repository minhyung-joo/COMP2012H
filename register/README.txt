/**********************************************************************
 *  Course Registration System
 **********************************************************************/

Name: Minhyung, JOO
Login: mjoo

/**********************************************************************
 *  Class design
 **********************************************************************/

- RegistrationSystem has StudentTable, CourseTable, SelectionTable
- RegistrationSystem owns FileManager, ReportGenerator
- ReportGenerator owns StudentTable, CourseTable, SelectionTable, passed from RegistrationSystem
- Same for FileManager
- StudentTable and CourseTable each owns a HashTable data structure from hashtable.h
- SelectionTable owns two HashTables and one STL list

/**********************************************************************
 *  Program mechanism
 **********************************************************************/

- main.cpp has the main function.
- Create RegistrationSystem object and call exec().
- Inserting, modifying, querying, and deleting records are done directly
by RegistrationSystem
- ReportGenerator is used when outputting student, course, and registration
lists in HTML. It utilizes string stream and file stream.
- FileManager is used for saving and loading the records. It works similar
to ReportGenerator

/**********************************************************************
 *  Note
 **********************************************************************/

- When loading data, the existing data in the system is ERASED!