#  What is al(l)-got-rithms?
This repo contains different university projects made by me, Alessio Mana and Fabrizio Sanino for our Algorithm and Data Structure Exam done in Turin in June 2021.</br>
<ul>
 <li><i>Merge-BinaryInsertion Sort</i>, written in C is about <i>Algorithms Complexity</i>, <i>Sorting Algorithms</i> and <i>Generic Programming</i></li>
 <li><i>Edit Distance Algorithm</i>, written in C is about <i>Algorithms Complexity</i>, <i>Recursion</i> and <i>Data Structure (Hash Table)</i></li>
</ul>

## Merge-BinaryInsertion Sort
   ### The idea Behind!
   In this program we tried to combine two really important algorithms: **Merge Sort** and **Binary Insertion Sort**.<br/>
   We were given of a file (.csv) containing 20mln records, with 3 different fields inside each record:<br/>
     - id    : (int) unique identifier;<br/>
     - field1: (string) containing words extracted from Divina Commedia (we assumed the values don't contain commas or blanks);<br/>
     - field2: (int);<br/>
     - field3: (floating point);<br/>
    Our goal was to **_sort by each field (increasingly or not) faster than we could, COMBINING Merge Sort and Binary Insertion Sort_**.<br/>
    We developed **_Generic Code_** so that our library(contained in ```merge_binary_insertion_sort.c```) manages the sorting of all types (such as field1, filed2 and field3).

   #### How to do that?
   We used a constant (we called it **_K_**) which manages our program to switch between Merge Sort, with complexity ```O(n log n)```, and Binary Insertion Sort (basically an Insertion Sort were the array split is done by a binary split) with complexity ```O(n^2)```.
   <br/>The goal was to find the best _K value_ which permits the faster sorting time. <br/>
   The idea behind is that, potentially, Insertion Sort could be faster than Merge Sort while working with really small size arrays.
   It turned out to be **_67_**. <br/>
   So, the algorithm works like this: while the length of the array to sort is bigger than 67 uses Merge Sort, Binary Insertion Sort otherwise. 
     <br/>**THE GRAPHIC WHICH FOLLOW IS AN EMPIRICAL RESULT** (obtained by bench marking arrays long 500 elements), it could depends on the machine, or other stuffs; we combined the sorting time results (done one by one): integers with Binary Insertion Sort and Merge Sort, and floats with Binary Insertion Sort and Merge Sort.
     ![Example Image](https://drive.google.com/uc?export=view&id=10gVZdCfUbVYHKl08gdilEIbAChcBU0Ua)
      
   ### What you need to execute this program is:
   - ***GCC*** compiler <br/>
    ``` sudo apt install gcc ```
   - ***Make*** util <br/>
    ``` sudo apt install make ```
   - ***Unity*** framework for unit testing **(:warning: Copyright (c) 2007-14 Mike Karlesky, Mark VanderVoord, Greg Williams)**, see: https://github.com/ThrowTheSwitch/Unity.git<br/>
   
   ### How do I run this program?
   There is a ***Makefile*** which automatically compiles and runs the project and tests:<br/>
     You just have to know two simple commands to use it. Once you have opened a shell in the ```root``` folder, write: <br/>
     - ``` make all``` to compile the application.<br/>
     - ``` make tests``` to run the 49 unit tests using *Unity Framework*<br/>
     - ``` make clean``` to clean the root folder by the obj files and the executables in the subdirectories<br/>
     - ``` make src=file.csv reverse=0 run ``` to run che application. ```src``` is the file to be sorted name, stored in the *src* folder; ```reverse=0``` sort by ascending order, 1 otherwise.<br/>
     - ``` CTRL-c``` if you want to force the termination of the program.

   :warning: We can't publish the file with 20mln records to be sorted due to copyright reasons. Btw you can try this program with a simple .csv file saved in the **```src```** folder were each record is organized like follow:<br/>
   ```1,hello,2735414,68601.754091```<br/>
   
   Once exectued, the sorted files are printed and saved in the **```src```** folder.

## Edit Distance Algorithm
   ### The idea Behind!
   What if we write something wrong on our smartph0n3? The automatic corrector does the work for us.<br/>
   Keeping this in mind we developed this algorithm.<br/>
   Once got the file containing the text to correct and a Dictionary, we check (word by word) whether it's contained in the dictionary (which means that's correct) or not. If not, we use the Edit Distance Algorithm to correct the word.<br/>
   The goal for this project was to compare a recursive version and a Dynamic Programming version of the same application. <br/>
   
   ### How does it work?
   We calculate the distance between the wrong word and every dictionary's word; the word with the shortest edit-distance will be the replacement of the wrong one (it may not make sense, doesn't matter).<br/>
   The operations allowed are Insertion and Deletion of a char to/from the wrong word. An example will follow:<br/>
   _"Home" e "Hoome" have edit-distance equals to 1 (1 deletion)_<br/>
   We wrote two versions of the algorithm, the first is a **Recursive One**, the second works on _**Dynamic Programming**_.
   
   #### Memoization Version (Dynamic Programming)
   We worked with an _Open Indexing - Two Layers Hashing Function, Hash Table_ which mainteined couple ```<key, value>```. <br/>
   - _Key_ is the concatenation between the two strings taken in exam. <br/>
   - _Value_ rapresents the edit-distance between the two strings calculated by the recursive version. ```example: <HomeHoome, 1>``` <br/> 
   
   This method permits us to obtain a more efficient application version. In fact, once calculated an edit-distance between two strings, the result is stored in the Hash Table. Its access is done in ```O(1)``` which is far more efficient than calculate again the edit-distance.<br/>
   At last we added another Hash Table containing the whole dictionary so that if a word is correct, the result is detected in an unique access to this Hash Table. ```example: <HomeHome, 0>```.<br/>
   
   ### What you need to execute this program is:
   - ***GCC*** compiler <br/>
    ``` sudo apt install gcc ```
   - ***Make*** util <br/>
    ``` sudo apt install make ```
   - ***Unity*** framework for unit testing **(:warning: Copyright (c) 2007-14 Mike Karlesky, Mark VanderVoord, Greg Williams)**, see: https://github.com/ThrowTheSwitch/Unity.git<br/>
   
   ### How do I run this program?
   There is a ***Makefile*** which automatically compiles and runs the project and tests:<br/>
     You just have to know two simple commands to use it. Once you have opened a shell in the ```root``` folder, write: <br/>
     - ``` make all``` to compile the application.<br/>
     - ``` make tests``` to run the unit tests using *Unity Framework*<br/>
     - ``` make clean``` to clean the root folder by the obj files and the executables in the subdirectories<br/>
     - ``` make cor=correctme.txt dic=dictionary.txt run ``` to run che application. ```cor``` is the file which you want to be corrected, ```dic``` is the file which rapresents your dictionary, both stored in the *bin* folder. <br/>
     - ``` CTRL-c``` if you want to force the termination of the program.

   :warning: We can't publish the dictionary file due to copyright reasons. Btw you can try this program with your own dictionary: a simple .txt file saved in the **```bin```** folder (one word per row). <br/>
   
 Once exectued, the corrected text is printed and saved in the _Corrected_file.txt_ file contained in the **```bin```** folder.
   
 
## Union-Find-Set Data Structure
   ### The idea Behind!
   We developed a Generic-Type Java Library containing the Union-Find-Set structure.<br/>
   Union-Find-Set, aka Disjoint-set, is a data structures which plays a key role in Kruskal's algorithm for finding the minimum spanning tree of a graph.<br/> 
   To maintain an efficient implementation the tree height is controlled using _Union By Rank_ and _Path Compression_ heuristics.<br/>
   We developed Unit Tests too, thanks to:<br/>
   - Hamcrest 1.3, **(:warning: Copyright (c) 2000-2015 www.hamcrest.org**, see:  ```https://github.com/hamcrest/JavaHamcrest.git```) <br/>
   - J-Unit 4.12, **(:warning: Copyright (c)**, see:  ```https://github.com/junit-team/junit4.git```) <br/>
   

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
