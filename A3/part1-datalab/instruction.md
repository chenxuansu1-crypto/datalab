# Datalab — 70 Points

---

The purpose of this assignment is to become more familiar with bit-level representations of integers and floating point numbers. You’ll do this by solving a series of programming “puzzles.” Many of these puzzles are quite artificial, but you’ll find yourself thinking much more about bits in working your way through them.

**For Mac user (with Apple Silicon):**
	
In datalab part, the executable file named "dlc" won't work on your machine without running it on some emulator. It was written for Intel machine. The workaround is to install docker and do your lab on the docker. Here is the instruction:
	
1. Prerequisites: Docker installed and running: [https://www.docker.com/](https://www.docker.com/)
	
2. Setup: To get started, follow these steps.
    - Run Docker and look for terminal access at the bottom-right of the screen
	- Download Docker image by entering the following command: `docker pull xieguochao/csapp`
	- Run Docker container: `docker run -p 7777:7777 -v "$PWD/labs:/home/csapp" xieguochao/csapp`
	- Open your web browser and access `http://localhost:7777` (password: csapp). At this point, you will be presented with VScode inside the docker
	- Clone the A3 by accessing terminal on VSCode (inside running container): `git clone YOUR_GITHUB_CLASSROOM_REPO`



## 1. Handout Instructions

---

You will need a starter package which can be found on your GitHub repository. The only file you will be modifying and turning in is **bits.c** inside datalab directory.

<aside>
💡

TLDR: modify bits.c and push the code on your repository on GtiHub Classroom

</aside>

The bits.c file contains a skeleton for each of the 10 programming puzzles. Your assignment is to complete each function skeleton using only straightline code for the integer puzzles (i.e., no loops or conditionals) and a limited number of C arithmetic and logical operators. Specifically, you are only allowed to use the following eight operators:

`! ~ & ^ | + << >>`

A few of the functions further restrict this list. Also, you are not allowed to use any constants longer than 8 bits. See the comments in bits.c for detailed rules and a discussion of the desired coding style.

## 2. The Puzzles

---

This section describes the puzzles that you will be solving in bits.c.

### **2.1** Bit Manipulations

Table 1 describes a set of functions that manipulate and test sets of bits. The “Rating” field gives the difficulty rating (the number of points) for the puzzle, and the “Max ops” field gives the maximum number of operators you are allowed to use to implement each function. See the comments in bits.c for more details on the desired behavior of the functions. You may also refer to the test functions in tests.c. These are used as reference functions to express the correct behavior of your functions, although they don’t satisfy the coding rules for your functions.

Table 1: Bit-Level Manipulation Functions.

| Name | Description | Rating | Max Ops |
| --- | --- | --- | --- |
| minusOne(void) | Return the value -1 | 1 | 2 |
| sign(x) | Return 1 if positive, 0 if zero, -1 if negative | 2 | 10 |
| negate(x) | Compute -x | 2 | 5 |
| anyEvenBit(x) | Return 1 if any even bit in x is set to 1 | 2 | 12 |
| getByte(x,n) | Extract byte n from word x | 2 | 6 |
| byteSwap(x,n,m) | Swap the m and n byte of x | 2 | 25 |
| bitMask(x,y) | Generate a mask consisting of all 1’s from lowbit to highbit | 3 | 16 |
| absVal(x) | Compute the absolute value of x | 4 | 10 |
| bitCount(x) | Count the number of 1’s in x. | 4 | 40 |
| bang(x) | Compute !n without using ! operator. | 4 | 12 |
| greatestBitPos(x) | Compute a mask marking the most significant 1 bit. | 4 | 70 |

### **2.2** Two’s Complement Arithmetic

Table 2 describes a set of functions that make use of the two’s complement representation of integers. Again, refer to the comments in bits.c and the reference versions in tests.c for more information.

Table 2: Arithmetic Functions

| Name | Description | Rating | Max Ops |
| --- | --- | --- | --- |
| tmin() | Most negative two’s complement integer | 1 | 4 |
| divpwr2(x,n) | Compute x/(2^n) | 2 | 15 |
| isLessOrEqual(x,y) | x <= y? | 3 | 24 |
| isPositive(x) | x > 0? | 3 | 8 |

## 3. Evaluation

---

Your score will be computed by multiplying the rating points with 2 out of a maximum of 70 points. Any points extra (up to 78 is your extra credit). Only answer that are correct and performs well (defined below) count.

**Correctness points:** 

- We will evaluate your functions using the btest program, which is described in the next section. You will get full credit for a puzzle if it passes all of the tests performed by btest, and no credit otherwise.

**Performance points:**

- Our main concern at this point in the course is that you can get the right answer. However, we want to instill in you a sense of keeping things as short and simple as you can. Furthermore, some of the puzzles can be solved by brute force, but we want you to be more clever. Thus, for each function we’ve established a maximum number of operators that you are allowed to use for each function. This limit is very generous and is designed only to catch egregiously inefficient solutions. You will receive two points for each correct function that satisfies the operator limit.

## 4. Autograding your work

---

We have included some autograding tools in the handout directory — btest and dlc — to help you check the correctness of your work.

- **btest:** This program checks the functional correctness of the functions in bits.c. To build and use it, type the following two commands:
    
    ```bash
    unix> make
    
    unix> ./btest
    ```
    

Notice that you must rebuild btest each time you modify your bits.c file.

You’ll find it helpful to work through the functions one at a time, testing each one as you go. You can use the -f flag to instruct btest to test only a single function:

```bash
unix> ./btest -f bitAnd
```

You can feed it specific function arguments using the option flags -1, -2, and -3:

```bash
unix> ./btest -f bitAnd -1 7 -2 0xf
```

Check the file README for documentation on running the btest program.

- **dlc:** This is a modified version of an ANSI C compiler from the MIT CILK group that you can use to check for compliance with the coding rules for each puzzle. The typical usage is:
    
    ```bash
    unix> ./dlc bits.c
    ```
    
    The program runs silently unless it detects a problem, such as an illegal operator, too many operators, or non-straightline code in the integer puzzles. Running with the -e switch:
    
    ```bash
    unix> ./dlc -e bits.c
    ```
    
    causes dlc to print counts of the number of operators used by each function. Type ./dlc -help
    
    for a list of command line options.
    
    <aside>
    💡
    
    Note !!! inside `/dlcdir` , there is a Makefile that you can use to create a working `dlc` binary for your machine.
    
    </aside>
    

## 5. Advice

---

- Don’t include the <stdio.h> header file in your bits.c file, as it confuses dlc and results in some non-intuitive error messages. You will still be able to use printf in your bits.c file for debugging without including the <stdio.h> header, although gcc will print a warning that you can ignore.
- The dlc program enforces a stricter form of C declarations than is the case for C++ or that is enforced by gcc. In particular, any declaration must appear in a block (what you enclose in curly braces) before any statement that is not a declaration. For example, it will complain about the following code:
    
    
    ```c
    int foo(int x) {
    	int a = x;
    	a *= 3;              /* Statement that is not a declaration */ 
    	int b = a; /* ERROR: Declaration not allowed here */
    }
    ```
