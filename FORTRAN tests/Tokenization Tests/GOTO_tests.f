C     GOTO only has one valid format
      GOTO 15
C     This won't parse - it needs a positive integer
      GOTO -15
C     This won't parse - it needs to be capitalised
      goto 15
C     This won't parse - arithmetics aren't valid.
      GOTO 15 + 1
C     This won't parse - Variables aren't valid
      GOTO X
C     This won't parse - Function calls aren't valid
      GOTO SQRT(X)
C     This should parse
      GOTO 15151
C     This should warn that the line label is too long
      END