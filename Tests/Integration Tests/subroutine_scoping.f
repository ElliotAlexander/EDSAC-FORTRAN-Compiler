      SUBROUTINE SCOPETEST(X)
      PRINT X
      RETURN
      X = 100
      PRINT X
      CALL SCOPETEST(200)
      END