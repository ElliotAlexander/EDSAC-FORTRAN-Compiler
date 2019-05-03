      FUNCTION ISPRIME(X)
      Y = 1
      DO 15 K = 2,20
      DO 15 I = 2,20
      IF(X - I*K) 15, 30, 15
C If prime, fall out the bottom of this loop
15    CONTINUE
      Y = 0
      GOTO 40
C Not prime - exit the loop
30    Y = 5
      GOTO 40
40    RETURN Y
C Program start
      DO 50 INDEX = 1, 15
      K = ISPRIME(INDEX)
      IF(K) 50, 45, 50
45    PRINT INDEX
50    CONTINUE
      END