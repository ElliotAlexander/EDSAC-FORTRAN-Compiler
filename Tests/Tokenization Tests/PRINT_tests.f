C     This should parse
      PRINT 100
C     This should parse - all arithmetics are valid on the right hand side.
      PRINT 100 + X - 1
C     This wo't parse - the keyword needs to be capitalised.
      print 100
C     This will parse
      PRINT PRINT
C     The right hand side allows any arithmetic statement
C     Arithmetic statements which are invalid which will exit the compiler.
C     The following will all parse correctly, but will cause the compiler to exit.
      PRINT (X
      PRINT (X + SQRT(X)
      END