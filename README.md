# Notepad Qt Application
Notepad application built with C++ and Qtcreator. This project demonstrates how to create a basic text editor with standard file operations and a modern UI.

## Features
- Create, open, save, and save files as new (New, Open, Save, Save As, Exit)
- Detect unsaved changes and prompt the user to save before closing or opening a file
- Dynamic window title updates to show current file name

  ## Screenshot
  [Notepad UI](Screenshot/NotePad Ui.png)
  [Notepad Menu Bar](Screenshot/Notepad menu bar.png)
  [Notepad QMessage](Screenshot/Notepad Change case.png)

## Properties Used
- QMainWindow – Main application window
- QTextEdit – Text editing area
- QFile – File input/output operations
- QTextStream – Reading/writing text
- QFileDialog – File selection dialogs
- QMessageBox – Dialogs for warnings/questions
- QAction – Menu actions (New, Open, Save, Save As, Exit)
- QFileInfo – Get file information (like file name from path)
