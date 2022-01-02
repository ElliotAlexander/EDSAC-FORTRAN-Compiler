C     This test is designed to show the use of subroutines alone in EDSAC compiled code.
C     One possible use of the compiler is building subroutines for other programs, where they can be used. 
C     Combined with the base offset feature of the compiler, this is a very possible idea.
      SUBROUTINE FACTORIALS(X)
      ROLLINGFACTORIAL=1
      DO 10K = 2,100
      IF(X-K) 10, 20, 10 
10    ROLLINGFACTORIAL = ROLLINGFACTORIAL * K
20    PRINT ROLLINGFACTORIAL
      RETURN
      CALL FACTORIALS(6)
      END