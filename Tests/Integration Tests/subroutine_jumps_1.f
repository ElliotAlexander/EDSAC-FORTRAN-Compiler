      FUNCTION SQUARES(X)
      X = X^2
      PRINT X
      GOTO 5
10    CONTINUE
      RETURN X
      X = 20
      PRINT X
      PRINT SQUARES(5)
      PRINT X
      STOP
5     X = 10
      GOTO 10
      END