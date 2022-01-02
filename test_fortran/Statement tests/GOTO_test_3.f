C     The following is designed to test jumping into and out of a function.
C     When the GOTO jumps out of the function, the function scoping remains.
C     This is a difficult behaviour to deal with.
C     This test still breaks, future work needs a system for detecting future line numbers, whether they're inside a function scope, and 
C     automatically exiting the function scope if they are.
      SUBROUTINE SQUARENUMBER(X)
1000  X = 1
      PRINT X
      GOTO 100
      RETURN
      CALL SQUARENUMBER(5)
100   PRINT 10
      END