C     The goal of this test is to test the accessibility of the loop index while the loop is in progress.

C     Expected result here is a print from 1 - 10,
C     The index of the loop should be accessible while it's in progress
      DO 10LOOPINDEX = 1,10
10    PRINT LOOPINDEX
      END