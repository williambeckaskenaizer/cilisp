# ciLisp
ciLisp is a custom implementation of a compiler for s-expressions using List. Dubbed "ciLisp", the project contains a total of 9 tasks, each implementing their own type of functionality.

### How to run
There are several components required for ciLisp to compile. 
Please ensure that you're either on a Mac/Linux, or using the Ubuntu terminal for Windows.

#### For macOS 
You will need to install [Brew](https://brew.sh/) or a similar package manager. 
First, enter ```brew install flex bison``` and wait for the install to finish.
Next, navigate to the folder containing cilisp, and type ```make clean```, followed by ```make```.
Finally, run the program with ```./cilisp```.

#### For Windows
You will need to have the [Ubuntu Terminal](https://www.microsoft.com/en-us/p/ubuntu/9nblggh4msv6#activetab=pivot:overviewtab) installed. 
Once you have the Ubuntu CLI open, type ```sudo apt-get install flex bison```
Next, navigate to the folder containing cilisp, and type ```make clean```, followed by ```make```.
Finally, run the program with ```./cilisp```.

#### For Linux
Open Linux CLI, and type ```sudo apt-get install flex bison``` (or use your preferred package manager.)
Once this is finished, navigate to the task directory you wish to run, and type ```make clean```, followed by ```make```.
Then, simply enter ```./cilisp```.

### Using the Program
ciLisp interprets commands in the form of numbers and operations as follows:
To add the integers 2 and 3, enter ```(add 2 3)```, and the result will be ```5.00000```.
Beyond addition, ciLisp can compare two numbers, return the square root of numbers, take logarithms, absolute values, and more. 
Expressions do not have to be singular. (add (add 1 3) (add 2 4)) is valid as well.