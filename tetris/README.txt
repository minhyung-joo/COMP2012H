COMP 2012H Project 2 Tetris

Design
------
class MainWindow
- Sets up the window of the application.
- Uses QGridLayout to manage the child components.
- Owns GameBoard and PreviewBoard objects.
- QStrings and QLabels are used for the level and score displays.

class PreviewBoard
- Owns a Block object for passing to the GameBoard object.
- Starts with the signal from GameBoard object.

class GameBoard
- Owns a Block object, and a coordinate system which is a 20x10 integer array.
- Owns a PreviewBoard object for communication and receiving new blocks.
- This is the only object receiving focus for keyboard inputs.
- Some algorithms are heavily borrowed from the Qt Tetrix example, especially the rotation mechanism. (link included in the bottom)

class Block
- Abstract tetris block definition.
- Does not extend any Qt class.
- Initialized with a random shape.
- The shape matrix concept borrowed from the Qt Tetrix example.

Reference
---------
Qt Tetrix example
http://doc.qt.io/qt-4.8/qt-widgets-tetrix-example.html
