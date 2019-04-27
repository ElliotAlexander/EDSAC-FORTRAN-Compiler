C     This should parse. This is basically the only acceptable form of this statement.
C
      GOTO X, (5,10,15)
C     This shouldn't parse - the syntax is wrong.
      GOTO 5, (X,Y,Z)
C     This shouldn't parse - the first value should be a variable
      GOTO X  (5, 10, 15)
C     This shouldn't parse - only three values are allowed in the brackets for Assigned GOTOs.
      GOTO X (5,5,5,5,5,5,5,5,5,5)
C     This shouldn't parse - only one set of brackets is expected.
      GOTO X() (5,5,5)
C     This should't parse,  values in the brackets are required
      GOTO X ()
C     This shouldn't parse, three values are required in the brackets
      GOTO X (5,5)
C     This shouldn't parse
      GOTO 10 (10, 15, 20)
C     This should't parse- variables aren't allowed in the brackets
      GOTO X (X, 10, 15)
      END