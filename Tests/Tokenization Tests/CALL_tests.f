C     This should parse fine
      CALL PLOT(X,Y,2)
C     This should parse fine - arithmetics are valid in function arugments.
      CALL DASHP(5.0, 10, 10+5)      
C     This should also parse fine, numbers in functio names are valid.
      CALL DASHP123(5^6)
C     This shouldn't parse - function names can't start with numbers.
      CALL 123PLOT(5.0)
C     This should parse fine, negative integers and floating points are valid in function calls. 
      CALL PLOT(5.0,5.0,-3)
C     This should parse fine - negative floating points are valid in function calls.
      CALL PLOT(-5.0)
C     This should parse fine, there is no restruction (the size of a string, perhaps) on the length of a function name or it's arguments.
      CALL BIGFUNCTIONNAMEOMGANOTHERBIGFUNCTIONNAME(W,I,T,H,A,L,O,T,O,F,A,R,G,S)
C     This should parse fine - functions without arguments are valid.
      CALL NEWFUNC()
C     This won't parse, all function names are declared in upper case.
      CALL lowerCASEFUNCTION(X)
C     This won't parse, the CALL keyword needs to be uppercase. 
      call LOWERCASE(X)
C     This won't parse, the lowercase x is an invalid argument.
      CALL LOWERCASEARGUMENT(x)
      END