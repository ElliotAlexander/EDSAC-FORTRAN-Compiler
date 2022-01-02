C     The purpose of ths test it to test the compilers ability to differentiate between functions and variables of the same name
C     This is made extra interesting by using a keyword as the variable / function name
      DO(X) = X + 5
      PRINT DO(5)
      X = 50
C     Expected outcome is to print 65
      PRINT X + DO(10)
      END