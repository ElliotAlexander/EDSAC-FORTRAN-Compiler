C     This test is designed to test how GOTO handles a non-existant line label
C     Ideally the user should get an error message, and the compiler should remain optimistic (i.e. still compile)
      GOTO 1000
      END