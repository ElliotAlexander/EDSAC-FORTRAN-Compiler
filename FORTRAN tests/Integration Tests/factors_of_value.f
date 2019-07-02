      X = 55
      DO 15 K = 2, 100
      DO 15 I = 2, 100
      IF(X - K*I) 15, 30, 15 
15    CONTINUE
      STOP 1
30    PRINT K
      PRINT I
      STOP 5
      END