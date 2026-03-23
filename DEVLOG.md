# Expression Format Detector + Stack Evaluator
## CS 210 (Spring 26)

---

### Entry 1
#### Date: 2026-03-18

Today I created a DEVLOG to maintain a comprehensive log of changes that are made to this project,
changed whose full detail's cannot fit onto a single git commit message, as well as fully developed the
ArrayStack header file. I decided to implement thrown exceptions into the pop and top methods, as
they both have the possibility of trying to access data inside an empty stack, which should be guarded against.
While it is easy to simply early return on pop, as it has a void return type, throwing an exception is
essential in top, as the method demands something tangible to be returned. I tested these ArrayStack methods
by calling upon them in different situations. Since there is no max stack capacity, there is only one test to do
in order to test push. For size, I checked its output after pushes and pops. For the methods that could potentially
output something unexpected, such as trying to remove from an empty stack, I checked regular conditions and
then those special conditions, ensuring that the code functions as intended for all conditions that the code may
be executed under.

---

### Entry 2
#### Date: 2026-03-19

I implemented the tokenizer algorithm today, which basically takes a string and converts it to one character string tokens
and stores those tokens into a vector. I then tested out the tokenizer so that it would ignore the spaces that may appear 
in a string by creating a string with random characters and numbers, separated by spaces, and then feeding it into the 
tokenizer algorithm. After feeding it into the tokenizer algorithm, I printed the string value of all the Token structs 
in the tokens vector, ensuring that it is equivalent to the string I fed into it, but without the spaces.

---

### Entry 3
#### Date: 2026-03-22

Today I began implementing the precedence helper method and improved the tokenizer method. The issue with the tokenizer 
method previously was that it converted every char that is not a space in the string into a Token object. However, this 
time, I improved the tokenizer method so that only digits and the characters that relate to arithmetic operations get converted 
into tokens. This will help reduce the amount of code that I would have to develop for the detection and conversion methods.
Due to the lesser amount of code being written, this would also reduce the possibility of bugs that could show up after I
develop the initial method. I then tested the rewritten tokenizer method by implementing a string with all the characters
on my keyboard, and verifying that only numbers and arithmetic operator characters are left remaining. When I started
implementing the precedence method, I only started developing for expressions without parentheses. For the next iteration
of precedence, I will ensure that it works on expressions with parentheses, but for now, this will have to do.