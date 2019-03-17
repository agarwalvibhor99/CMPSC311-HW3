#include "hw3.h"
/*This For argument i, this function computes
 * the bit-level representation of (float) i.*/
/*Floating Point Representation -> FPR */
float_bits float_i2f(int i) {
  if (i==0){   /*Returns 0 if the argument passed is 0 which is the FPR  of 0*/
    return 0;
  }
  unsigned sign_bit;
  sign_bit = (unsigned)i >> 31; /* Determines the Sign Bit in FPR */
  if (sign_bit == 1){   /* For Negative Numbers */
  i=-i;
  }
  int count = 0; /*Declaring int count that we use in loop to find the exponent*/
  unsigned exponential_bit, exponent, fractional_bit, residue,loop=(unsigned)i; 
  /*Declaring unsigned exponential_bit, fractional_bit to store exponential bit
   * and fractional bit respectively. Declaring residue to store anything 
   * beyond 23 bits in the fractional part. Defining loop as the input which 
   * help to find the count which is added to bias*/
//  unsigned fractional_bit, residue;
  while (loop != 1){
    loop = (unsigned)loop>>1;
    count++;
  }
  exponent = 127+count;
  exponential_bit = (unsigned) exponent;  /*Stores the exponential bit*/
  fractional_bit = (unsigned) i << (32-count);
  residue = fractional_bit & 0x1FF; /*Stores the residue of fractional bit*/
  fractional_bit = fractional_bit>> 9; /*Store the 23 bit fractional bits*/
  /* Checking if Roundoff is Required*/
  if(residue>0x100){
    fractional_bit=fractional_bit+1;
  }
  else if(residue == 0x100){
    if((fractional_bit & 0x1) == 1){
      fractional_bit = fractional_bit+1;
    }
  }
  if (fractional_bit == 0x800000){
    fractional_bit=0;
    exponential_bit = exponential_bit+1;
  }

  return (sign_bit<<31|exponential_bit<<23|fractional_bit);
  /* Returning the required FPR of the passed argument by making the
   * 31 bit position as sign_bit, the next 8 bit position for exponential_bit
   * and the next 23 bit position for fractional_bit */
}


