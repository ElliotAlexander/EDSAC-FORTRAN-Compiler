C     Tokenization testing for ASSIGN statements.
C
C
C     Expected to pass       
      ASSIGN Y TO 5
C     Expected to pass
      ASSIGN X TO 5
C     Expcted to pass
      ASSIGN TO TO 5
C     Expected error case -  We need to pass an int into the assignment.
      ASSIGN X TO X
C     Expected Error case - assignment needs to be an integer.
      ASSIGN TO TO TO
C     Expected to fail, assignment must be an integer.
      ASSIGN TO TO 5+5
C     Not expected to pass
      ASSIGN TO TO TOTO
C     This is expected to parse as 'ASSIGN TO TO 5
      ASSIGN
     TTO
     TTO
     55
C     This won't parse, ASSIGN will catch the size of the integer and overflow.
      ASSIGN ASSIGNASSIGNASSIGNASSIGNASSIGNASSIGNASSIGNASSIGN TO 33252971317821423126254115152107205183189187255255291233424418512616313916112
C     This is expected to pass - Negative numbers are valid
      ASSIGN NEWVARIABLE TO -500
C     This shouldn't pass - we don't allow arithmetic 
      ASSIGN NEWVARIABLE TO -5-100
C     This should't parse - brackets are a disallowed symbol.
      ASSIGN NEWVARIABLE() TO 55
      END