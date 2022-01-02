C	This should parse
      GOTO (5,10,15), X
C     This should parse
      GOTO (5,10,15), LONGERVARIABLE
C 	This should parse
      GOTO (10, 5), X
C	This should pare
      GOTO (10), X
C 	This should not parse - we need at least one argument.
      GOTO (), X
C 	This shouldn't parse, the comparison variable canot be arithmetic
      GOTO (5,10,15), 5
C     This shouldn't parse, we can't call functions as comparison variables
      GOTO (5,10, 15), SQRT(X)
      END