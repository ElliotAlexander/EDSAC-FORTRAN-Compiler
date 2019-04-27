C     This should parse 
      IF (400) 60,500, 10
C     This should parse 
      IF((400)) 50, 500, 10
C     This should parse
      IF (400) 500, 10, 54
C     This won't parse - no value is provided in the parenthesis.
      IF () 500, 10, 54
C     This won't parse - arguments cannot be arithmetic
      IF(500) 10+1, 11, 254
C     This should parse - the control variable can be arithmetic.
      IF (500 + X) 10, 15,20
C     Invalid - no arguments.
      IF ((500))
C     Invalid - Too many arguments.
      IF ((500) + 4) 10, 10, 44, 50
C     This wno't parse - not enough arguments.
      IF ((500) + 4) 500+4
C     This won't parse, arithmetics (and hence brackets) aren't valid in the line arguments.
      I   F
     &          ((((5)))) (((((5))))), (((((((((1))))))))), ((((((1))))))
C     This should pass
      I   F
     &          ((((5)))) 5, 1, 10
C     This won't parse - not enough arguments.
      IF(IF)5,5
C     This should parse
      IF(IF)5,5,5
C     This should parse - albeit with semantic errors.
      IF (SQRT(X) + 10 * 10 + X + IF) 0, 0, 0
      END