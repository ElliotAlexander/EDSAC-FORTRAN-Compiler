      TESTFUNCTION(X) = A*X + B
      TESTFUNCTION(X, B) = A*X + B
12345 TESTFUNCTION(D) = TESTFUNCTION(E)/D
      TESTFUNCTION(F, G) = TESTFUNCTION(F,TESTFUNCTION(G))
      FIFTHF(I, A)= 30*A*I
10000 SIXTHF (J) = J + K
C Expected error case - second line of continuation is blank.
100000TESTFUNCTION(X) = 5 + 5
      END