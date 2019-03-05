      X = 5+5
      Y = 10 +X
      HELLO1213ASDAS
     &=
     &WHATISTHIS
     &            
     &   +
     & 55
      TESTVAR55=5.0--5.0
C Exected error case - Cannot assign a number.
      55 = 105.5 - 10
      TESTVAR = SQRT(16)
C This works as expected, 5 - (-5)
      VERYNEGATIVENUMBER = 5--5
C This should be an error case. 
      X = X
C This should be an error case, if the rhs is not present:
C Expected failure in this case is at the tokenization level.
      X = 
C Stacking negations isn't supported in the Arithmetic Parsers.
C This will throw a syntax error from the A
      X = 5---5
      END