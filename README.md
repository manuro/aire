aire
====
 
Software project to preserve some code fragments for the future.  

## Project guide

This project is a feel free to contribute project. Everyone is welcome to 
implement functionality that is useful or needed. Please do not hesitate to 
send a short mail with the things you want to add to start a discussion. 

**Project mission:** 
* Do not use any third-party library. 
* Use only system libraries and standard libraries like (STL or libc).
* Add only GPLv3 or compatible licenced code to the repository.

### Contributors
[manuro]

### Development process

#### New development

Please ask one of the developers before starting a new development task. It 
could be that the neccessary functionality is already implemented. Also maybe 
the developer can help you to start designing your module.  
Important note: **New module names have to be approved by all developers.**

1. Clone the git repository.
2. Develop the test case for your code.
3. Run all test cases in the project.
4. Update README about the contributed software.
5. Request push with detailed change log, README and test output.
6. Merge changes with main tree.
7. Feel happy because you are the main developer for the new code.

#### Bug fixing

1. Clone the git repository.
2. Assign the bug ticket to your name.
3. Write the test case to reproduce the bug.
4. Talk to main developer and fix the bug.
5. Run all test cases in the project.
6. Request push with detailed change log and test output.
7. Merge changes with main tree.

### General design conventions

* Every class has a `virtual initialize()` method that is executed by the 
  constructor of the class.
* Every class has a `virtual destroy()` method that is executed by the 
  destructor of the class.
* No class member initialization in the constructor.
* No class member deinitialization in the destructor.
* Make copy constructor private if it is not allowed to copy the class.
* Make assignment operator private if it is not allowed to copy the class.

### Module design

It is not clear at this time how we proceed with module design. Requirements 
on the module design:

* Modules can be depending on other modules.
* Independent compilation for a subset of modules.
* No circular dependencies are allowed. 

### General code conventions

* Restrict lines to maximal 80 characters.
* Restrict a file to maximal 1000 lines.
* Place a space between comma and parameter in function call or signature. 
  For example: read(buffer, size) This rule can be violated if the code line 
  exceeds the maximal characters and will fit into a line without spaces in 
  the parameter list.
* Abbreviations are explicit allowed and should be used if the length of the 
  name exceeds the restrictions. For example: `ThreadParams` instead of 
  `ThreadParameters`.
* Use descriptive abbreviations. For example: `getNumProcs` instead of 
  `getNumberOfProcessors`.
* Restrict a function or method call to maximal 3 lines.
* Indent your code with 3 spaces per layer and do not use tabulators.
* Do not indent ifdefs or the code within an ifdef.
* Do not mix languages. This is a C/C++ project and nothing else.
* Develop platform independent. Code must be able to run on Linux, Windows and 
  Mac Os.
* Do not use NULL! use instead nullptr (C++0x in gcc 4.6 / C++11 in 4.7)
* Write all code in the header file. Do not create seperate code files.

#### Class design

The design of a class uses the following template:

    class ClassName
    {
    public: 
      // Public methods
    protected: 
      // Optional for protected members and methods
    private: 
      // Private methods and members
    }

* If a class has no protected stuff than the protected keyword can be dropped.
* Ordering: First variables and constants then methods.
* No initialization in the constructor. Create `virtual void initialize()` 
  instead.
* No destruction in the destructor. Create `virtual void destroy()` instead.
* Create virtual destructor.
* Only create initialize and destroy if needed but create always default 
  constructor and destructor.
* Make always copy-constructor and assignment operator private if not needed.

#### Class names

* Class names should be in UpperCamelCase. For example: `StringTokenizer`, 
  `MailServer` or `DataArray`. 
* If it is possible choose a one word class name for abstract classes. For 
  example: `Tokenizer`, `Server` or `Array`. 
* Restrict class names to maximal 16 characters.

#### Class methods

* Method names should be in lowerCamelCase. For example: `readFile`, 
  `printDebug` or `clearSystem`. 
* Restrict method names to 16 characters.

#### Class members

* Member names should be in lowerCamelCase and always begin with an underscore. 
  For example: `_className`, `_currentStep` or `_numProcs`.
* Restrict member names to maximal 16 characters.
* Array type members should be named in plural e.g. `_messages`.

#### Constants

* Constants names must be in upper case. For example: RADIUS or PI.
* Restrict constant names to 16 characters.
* Use underscore as word separation. For example: `BLOCK_SIZE` or `NUM_PROCS`.

#### Global or static functions

* Global or static function names should be in UowerCamelCase.
* Restrict global or static function names to 16 characters.
* For inline functions use short names without lowerCamelCase. For 
  example: `isnan(...)`, `idx3d(...)` or `print()`. 
  
#### General code comment

* Don not use `/**/` as comment use `//` instead.
* Begin every comment line with `//` followed by a space. For example:
  `// This is a comment`.

#### Doxygen comments

Use doxygen style comments as follows:
 
    //! \brief <Short description>  
    //!  
    //! <Write a long description for this if it is neccessary>  
    //! \param <Param description>  
    //! \return <Return description>

### Copyright 

Use this copyright in any source file that is provided within this project:

    // Copyright (C) 2012 The contributors of aire
    //
    // This program is free software: you can redistribute it and/or modify  
    // it under the terms of the GNU General Public License as published by  
    // the Free Software Foundation, either version 3 of the License.  
    //
    // This program is distributed in the hope that it will be useful,  
    // but WITHOUT ANY WARRANTY; without even the implied warranty of  
    // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
    // GNU General Public License for more details.  
    //
    // You should have received a copy of the GNU General Public License  
    // along with this program. If not, see <http://www.gnu.org/licenses/>.
    //
    //! \file <filename>
    //! \brief <File description>


