#  What is al(l)-got-rithms?
This repo contains different university projects made by me, Alessio Mana and Fabrizio Sanino for our Algorithm and Data Structure Exam done in Turin in June 2021.</br>
<ul>
 <li><i>Merge-BinaryInsertion Sort</i>, written in C is about the Algorithms Complexity</li>
</ul>

## Merge-BinaryInsertion Sort
   ### The idea Behind!
   In this program we tried to combine two really important algorithms: **Merge Sort** and **Binary Insertion Sort**.<br/>
   We were given of a file (.csv) containing 20mln records, with 3 different fields inside each record:<br/>
     - id    : (int) unique identifier;<br/>
     - field1: (string) containing words extracted from Divina Commedia (we assumed the values don't contain commas or blanks);<br/>
     - field2: (int);<br/>
     - field3: (floating point);<br/>
    Our goal was to **_sort by each field (increasingly or not) faster than we could, COMBINING Merge Sort and Binary Insertion Sort_**.

   #### How to do that?
   We used a constant (we called it **_K_**) which manages our program to switch between Merge Sort, with complexity ```O(n log n)```, and Binary Insertion Sort (basically an Insertion Sort were the split is done by a common binary split) with complexity ```O(n^2)```.
   <br/>The goal was to find the best _K value_ which permits the faster sorting time. It turned out to be **_67_**. <br/>
   So, the algorithm works like this: while the length of the array to sort is greather than 67 uses merge sort, binary insertion sort otherwise. 
     <br/>**THE GRAPHIC WHICH FOLLOW IS AN EMPIRICAL RESULT**, it could depends on the machine, or other stuffs; we combined the time results of sorting (each one alone) integers with binary sort and merge sort, and floats with binary sort and merge sort.
     ![Example Image](https://drive.google.com/uc?export=view&id=10gVZdCfUbVYHKl08gdilEIbAChcBU0Ua)
      
   ### What you need to execute this program is:
   - ***GCC*** compiler <br/>
    ``` sudo apt install gcc ```  <br> or <br> ``` sudo apt install build-essential``` 
   - ***Make*** util <br/>
    ``` sudo apt install make ```
   - ***Unity*** framework for unit testing **(:warning: Copyright (c) 2007-14 Mike Karlesky, Mark VanderVoord, Greg Williams)**, see: https://github.com/ThrowTheSwitch/Unity.git<br/>
   
   ### How do I run this program?
   There is a ***Makefile*** which automatically compiles and runs the project and tests:<br/>
     You just have to know two simple commands to use it. Once you have opened a shell in the ```root``` folder, write: <br/>
     - ``` make all``` to compile the application.<br/>
     - ``` make tests``` to run the 49 unit tests using *Unity Framework*<br/>
     - ``` make clean``` to clean the root folder by the obj files and the executable in the subdirectories<br/>
     - ``` make src=$file.csv$ reverse=0 run ``` to run che application. ```src``` is the file name stored in the *src folder* in which all the records to be sorted are contained; ```reverse=0``` sort by ascending order, 1 otherwise.<br/>
     - ``` CTRL-c``` if you want to force the termination of the program.

   :warning: We can't publish the file with 20mln records to be sorted due to copyright reasons. Btw you can try this program with a simple .csv file saved in the **```src```** folder were each record is organized like follow:<br/>
   ```1,hello,2735414,68601.754091```<br/>
   
   Once exectued, the sorted files are printed and saved in the **```src```** folder.

## Must know
The game use some parameteres:
- *Execution Parameters*: these are specified in the ***Settings*** file and will affect the result of the game. <br/>
  **If you modify them you don't have to recompile the application.** (Just write "make run" in the shell).
- *Compilation Parameters*: these are specified in the ***Common.h*** file (row: 26, 27) and affect the size of the map (height and width). <br/>
  **If you modify them you have to recompile the application.** (first you write "make all" and then, one compiled, "make run").


## For the most curious
This project was our first experience in C concurrent programming. It allowed us to learn the mechanisms behind this kind of programming and share some good time togheter. We take advantage of all those system calls which are essential in this kind of application. We also made experience on all the IPC such as Semaphores, Shared Memory and Message Queues. We enjoyed it a lot!
For sure something could be done in a better way (such as the algorithm which calculates the path a taxi have to follow to reach the destination/source) but we focused more over the "concurrent side" of the project.<br/>
For more examples, please refer to the [Documentation](https://dr
ive.google.com/file/d/1nuqLbpuRCTUlv6wC8aB1Gj7PbQfNN3VL/view?usp=sharing).<br/>
Hope you enjoy this,<br/> 
Jack & Ale

## Contact
Giacomo Perlo: [Linkedin](https://www.linkedin.com/in/giacomo-perlo/), <perlogiacomo@gmail.com><br/>
Alessio Mana: [Linkedin](https://www.linkedin.com/in/alessio-mana-051112175/), <alessioma20@gmail.com><br/> 
If you need help or want to know something more about all of this, we are ready and excited to help you!
