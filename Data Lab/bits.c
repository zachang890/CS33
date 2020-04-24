/* 
 * CS:APP Data Lab 
 * 
 * <Zachary Chang 805289445>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
       /*The idea is to apply the xOR operator between every bit, this is accomplished by shifting all bits into the least significant bit and check if there are an even or odd number of zeros and ones (odd number of zeros causes xOR to return 1)*/
  int c;
  c = x ^ (x >> 1);
  c = c ^ (c >> 2);
  c = c ^ (c >> 4);
  c = c ^ (c >> 8);
  c = c ^ (c >> 16);
  return c&1;
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  /*Preserve the bits on the very right and make space in the front for them; prevent over/underflow and add the bits to the front with the OR operator */
  int bitsMoveRight, amountToMove, bitsToPreserve;
  bitsMoveRight = x >> n;
  amountToMove = ~n + 1 + 32;
  bitsToPreserve = x << amountToMove;
  return (bitsMoveRight & ~(1 << 31) >> (n + ~0)) | bitsToPreserve;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  /*Get the two bytes you want to swap to the very right; notice the property a ^ b == c then a ^ c == b; perform this property on each byte in the original x value */
  int positionN, positionM, xNRight, xMRight, fullRightByte, solution;
  positionN = n << 3;
  positionM = m << 3;
  xNRight = x >> positionN;
  xMRight = x >> positionM;
  fullRightByte = 255 & (xNRight ^ xMRight);
  solution = x ^ (fullRightByte << positionN);
  solution = solution ^ (fullRightByte << positionM);
  return solution;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  /*All bits from the 0th bit (least significant) to the 15th bit, inclusive, are free to be 0 or 1, but the rest must be either all 0 or all 1; Basic idea: check if you can right shift 15 bits and still extend the most significant bit and get all 0 or all 1 */
  return !((x >> 31) ^ (x >> 15));
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /* Uses DeMorgan's Law to produce and & from negation and the OR operator */
  return ~(~x | ~y);
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  /*Subtract the numbers as usual, extract the signs, only worry about when the signs are different (can cause overflow), check if the sign of x is the same as the resulting sign of subtraction */
  int subtracted, xSign, ySign, diffSign, subSign;
  subtracted = ~y + 1 + x;
  xSign = (x >> 31) & 1;
  ySign = (y >> 31) & 1;
  diffSign = xSign ^ ySign;
  subSign = (subtracted >> 31) & 1;
  return !(diffSign & (subSign ^ xSign));
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /*Find the signs of the difference and the two values; not greater if they are equal; only greater if y is negative and x is positive, or when their difference is positive and they have the same sign */
  int diffSign, xSign, ySign, xySame, signSame;
  diffSign = (x + (~y + 1)) >> 31;
  xSign = x >> 31;
  ySign = y >> 31;
  xySame = !(x ^ y);
  signSame = !(xSign ^ ySign);
  return (ySign & !signSame) | (signSame & !xySame & !diffSign);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /*Same idea as fitsShort, just that this time n is a variable; Everything from the 0th bit to the n-1th bit, inclusive, can be either or 0 or 1, all other bits must be either all 0 or all 1 */
  return !((x >> 31) ^ (x >> (n + ~0)));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* Basically converting two and from twos complement, negate and add 1 */
  return ~x + 1;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /*First check whether adding 1 leads to a 1 followed by all 0s, check also that x is not -1, which also satisfies first condition*/
  return !((x + 1) ^ ~x) & !!(x ^ (~0));
}
