C     This should pass
      TESTFUNCTION(X) = A*X + B
C     This should pass
      TESTFUNCTION(X, B) = A*X + B
C     This should pass, albeit with semantic errors.
12345 TESTFUNCTION(D) = TESTFUNCTION(E)/D
C     This is a semantic error case, but should tokenize
      TESTFUNCTION(F, G) = TESTFUNCTION(F,TESTFUNCTION(G))
C     This should parse
      FIFTHF(I, A)= 30*A*I
C     This should pass
10000 SIXTHF (J) = J + K
C     This shoould fail - We are not allowed arithmetic arguments in the declaration
      TESTFUNCTION(X+X, Y) = X + Y

C     This should pass
10000 TESTFUNCTION(X) = 5 + 5
C     This should pass
      T
     &E
     SS
     TT
     FF
     UU
     NN
     CC
     TT
     II
     OO
     NN(X) = 
     XX
C     This should parse 
      TESTFUNCTIONWITHAVERYLONGNAMECOULDBEPROBLEMATIC(X) = X + Y + Z
C     This won't parse - the hypens aren't allowed
      TEST-FUNCTION-HYPHENATED(X) = X
C     This won't parse - Arithmetic expressions aren't allowed inside function declarations
      TESTFUNCTION((((((((((X)))))))))) = X
C     This is valid, and partially a test of arithmetic expression parsing.
      TESTFUNCTION(X) = (((((((((((((((((((((X)))))))))))))))))))))
      END