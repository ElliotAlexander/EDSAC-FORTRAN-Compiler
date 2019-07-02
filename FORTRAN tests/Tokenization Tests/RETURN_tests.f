C     This is expected to parse
      RETURN 55
C     The format for RETURN statements is tried and tested, as <statement name> <arithmetic>
C     This is expected to parse
      RETURN X + 100 / 2
C     This is expected to parse
      RETURN -1000
C     The keyword cannot be lowercase
      return 10000
C     Thee keyword must be all uppercase
      RetuRN 1000