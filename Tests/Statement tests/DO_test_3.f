C     This test is designed to test the use of seperate symbol tables, and functions inside DO loops.
C     The expected output is a list of squares upto tenß
      FUNCTION SQUARENUMBER(X)
      X = X^2
      RETURN X
      DO 10 I = 1,10
10    PRINT SQUARENUMBER(I)
      END