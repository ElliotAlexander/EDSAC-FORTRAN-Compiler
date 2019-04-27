C     This should parse
1000  DO 10000000 HELLOWORLD=55,19
C     This won't parse - the right hand side needs to be integers only.
      DO 10 NEWVAR=55,OLDVA
C     This won't parse - the right hand side needs to be integers only
15234 DO 10 NEWVAR=55,OLDVAR,NOT434
C     This won't parse - the right hand side needs to be integers only
      DO 100 I=1,LIM1
C     This won't parse - the right hand side needs to be integers only
      DO 100 I=OLDVAR,5
C     This won't parse - loop variable must be positive
      DO-10X-10=55,55
C     This won't parse - the right hand side must be integers
      DO7I1=DO,DO
C     This won't parse - the right hand side must be integers
      DO10DO10=DO10,DO10
C     This should parse
      DO10DODODODODO=10,10
C     This won't parse - variable nanmes need to be uppercase
      DO 10 doloopvar = 10, 10
C     This won't parse - the DO statement needs to be capitalised.
      do 100 DOLOOPVAR = 10, 10
C     This won't parse - the right hand side must be positive integers.
      DO 10 DOLOOPVAR = -10, -15
C     This will parse, albeit with a semantic error. 
      DO 0 DOLOOPVAR = 10, 15
      END