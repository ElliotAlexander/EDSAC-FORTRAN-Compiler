      IF (400) 60,500, 10
C     Check that invalid parenthesis are handled correctly.
      IF (400) 500, 10, 54
      IF ((500))
      IF ((500) + 4) 10, 10, 44, 50
      IF ((500) + 4) 500+4
      I   F
     &          ((((5)))) (((((5))))), (((((((((1)))))))))
      IF(IF)5,5
      IF(IF)IF,IF,IF
      END