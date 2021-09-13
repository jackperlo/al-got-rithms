#  What is al(l)-got-rithms?
This repo contains an university project made by me, Alessio Mana and Fabrizio Sanino for our Algorithm and Data Structure Exam done in Turin in June 2021.</br>
Both *Merge-BinaryInsertion Sort* and the second exercises are written in C *(standard 89)* and developed for Unix-like systems, while the third and fourth are written in Java.



## Merge-BinaryInsertion Sort
What you need to execute this program is:
 - ***GCC*** compiler <br/>
    ``` sudo apt install gcc ```  <br> or <br> ``` sudo apt install build-essential``` 
 - ***Make*** util <br/>
    ``` sudo apt install make ```
 - ***Unity*** util (for unit testing) <br/>
 
    ### The idea Behind!
    In this program we tried to combine two really important algorithms: **Merge Sort** and **Binary Insertion Sort**. 
    We were given of a file (.csv) containing 20mln records, with 3 different fields inside each record:
      - id    : (int) unique identifier;
      - field1: (string) containing words extracted from Divina Commedia (we assumed the values don't contain commmas or blanks);
      - field2: (int);
      - field3: (floating point);<br/>
     Our goal was to **_sort each field (increasingly or not) faster than we could COMBINING Merge Sort and Binary Insertion Sort_**.
     
      #### How to do that?
      We used a parameter (we called it **_K_**) which manages our program to switch between Merge Sort, with complexity ```O(n log n)```, and Binary Insertion Sort (basically an Insertion Sort were the split is done by a common binary split) with complexity ```O(n^2)```. The goal was to find the best _K value_ which permits the faster sorting time. It turned out to be **_67_**. So the algorithm works like this: while the length of the array to sort is greather than 67 uses merge sort, binary insertion sort otherwise. 
      <br/>**THE GRAPHIC WHICH FOLLOW IS AN EMPIRICAL RESULT**, it could depends on the machine, or other stuffs; we combined the time results of sorting (each one alone) integers with binary sort and merge sort, and floats with binary sort and merge sort.
      ![Example Image](https://drive.google.com/uc?export=view&id=10gVZdCfUbVYHKl08gdilEIbAChcBU0Ua)
      
   
      #### How do I run this program?
      There is a ***Makefile*** which automatically compiles and runs the project:
        - You just have to know two simple commands to use it. Once you have opened a shell in the ```src``` folder, write: <br/>
        - ``` make all``` to compile the application.<br/>
        - ``` make run``` to run che application.<br/>
        - ``` CTRL-c``` if you want to force the termination of the program.

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
