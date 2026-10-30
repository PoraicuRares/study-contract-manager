# Study Contract Manager

A desktop application written in **modern C++ with Qt 6** for managing a catalog of university courses and building a student's study contract.

I built it during the 2nd semester of my first year at university (2026) for the Object-Oriented Programming course. The UI text is in Romanian.

<!-- Screenshots: add images to a docs/ folder and uncomment the lines below
![Main window](docs/main-window.png)
![Study contract](docs/contract-window.png)
-->

## Features

**Course catalog**
- Add, edit and delete courses (name, hours per week, type, teacher)
- Input validation with descriptive error messages
- **Undo** for add / delete / edit operations
- Search by name
- Filter by hours per week or by teacher
- Sort by name, by hours, or by teacher and then type
- Statistics: percentage of courses of a given type
- Remove courses with duplicate types

**Study contract**
- Add courses to the contract, or generate a random contract with *N* courses
- Export the contract to a CSV file
- Several windows show the contract at the same time (a list, an editable table and a drawing view) and all of them update automatically when it changes

## Architecture and design

The code is organized in layers:

| Layer | Files | Responsibility |
|---|---|---|
| Domain | `disciplina`, `contract.h`, `validatori.h`, `exceptii.h` | Entities, validation, custom exceptions |
| Repository | `repository` | In-memory storage of courses |
| Service | `service` | Business logic, filtering and sorting, undo, the contract |
| GUI | `gui`, `contractwindow`, `searchwindow`, `CosCRUDGui`, `cosreadonlygui`, `tablemodel` | Qt Widgets user interface |

Design patterns and techniques used:
- **Command pattern** for undo (`undo.h`): each operation stores an `ActiveUndo` object that knows how to revert it. The objects are owned through `std::unique_ptr`.
- **Observer pattern** (`observer.h`): the service notifies every open contract window when the contract changes.
- **Qt Model/View**: a custom `QAbstractTableModel` (`tablemodel`) backs the table window.
- **STL algorithms and lambdas** (`std::copy_if`, `std::find_if`, `std::sort`, `std::unique`, `std::function`) for filtering and sorting.
- A hand-written generic singly linked list with an iterator (`lista.h`), kept from an earlier iteration of the lab.

## Code quality

- Compiled with **warning level 4, warnings treated as errors**, and MSVC static code analysis (`/analyze`) enabled
- Unit tests (`teste.cpp`) run automatically at startup and cover the domain, repository, service, contract and undo logic

## Building and running

Requirements:
- Windows with **Visual Studio 2022 or newer** and the *Desktop development with C++* workload
- **Qt 6** (developed with Qt 6.11) with the `core`, `gui` and `widgets` modules
- The **Qt VS Tools** extension for Visual Studio

Steps:
1. Clone the repository and open `lab 6-7.sln` in Visual Studio.
2. In *Extensions → Qt VS Tools → Qt Versions*, register your Qt installation. If the version name differs from `6.11.0`, select yours in the project's Qt settings.
3. Select the **Debug | x64** configuration and press **F5**.

## Project structure

```
lab 6-7.sln
lab 6-7/
├── lab 6-7.cpp            # entry point
├── disciplina.*           # Course entity
├── contract.h             # Study contract
├── validatori.h           # Validation
├── exceptii.h             # Custom exceptions
├── repository.*           # Storage
├── service.*              # Business logic
├── undo.h                 # Undo actions (Command pattern)
├── observer.h             # Observer / Observable
├── gui.*                  # Main window
├── contractwindow.*       # Contract window
├── searchwindow.*         # Search dialog
├── CosCRUDGui.*           # Contract as an editable table
├── cosreadonlygui.*       # Contract as a drawing
├── tablemodel.*           # Qt table model
├── teste.*                # Unit tests
├── console.*              # Earlier console UI (not part of the current build)
└── contract2025           # Sample exported contract
```
