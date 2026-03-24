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

---

### Entry 4
#### Date: 2026-03-23

I improved the tokenizer algorithm to deal with a potential infix expression edge case and developed the isValidPostfix
method. I also intended to improve on the precedence method, but after looking at the assignment and researching the
Shunting-Yard algorithm, I realized that the precedence method is perfect for converting from infix to postfix. I originally
envisioned the precedence method to be used on postfix equations to help the computer solve postfix expressions, but I realize
that converting infix to postfix is the intended method to solve expressions instead of my vision. I then shifted my focus
to the potential edge case within an infix expression where a number comes right before a parentheses to imply multiplication.
In order to improve the tokenizer algorithm, I made sure that when the algorithm came across an open parentheses, it checks if
a number comes before the open parentheses, and if it does, it adds the multiplication operator as a token inbetween the number
and the parentheses. This check only occurs if the parentheses is not the very first token being added to the tokens vector.

---

### Entry 5
#### Date: 2026-03-24

I developed the evalPostfix method today. I used the isValidPostfix method within the method to first check to see whether
a passed through expression is truly in postfix notation before even attempting to evaluate it. While developing the
evalPostfix method, I realized that isValidPostfix has a bug where it accepts parentheses as a valid token type,
and adds it to numCount internally. So, I added an if statement that immediately returns false if it notices any parentheses
within an expression. I also tweaked the precedence method again and did not assign a precedence value to a closing parentheses,
as through the Shunting-Yard algorithm, a closing parentheses will never get pushed to the operator stack. It will instead
pop the stack until it reaches a matching closing parentheses. Therefore, I removed the condition for precedence to return 3
when it encounters a closing parentheses. In order to test evalPostfix, I just tested it on the valid postfix expression
and invalid postfix expressions that I have already created for the isValidPostfix method. When used on the valid postfix
expression, I calculated the number myself and checked to see if the method would return the same value that I had calculated,
which it did, thus verifying its capabilities for now.