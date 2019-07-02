C     This test is designed to test detection of overlapping DO loops
C     The user should get an error message.
      DO 100I=1,10
      PRINT I
      DO 200 K = 1,10
100   PRINT K
200   PRINT I + K
      END