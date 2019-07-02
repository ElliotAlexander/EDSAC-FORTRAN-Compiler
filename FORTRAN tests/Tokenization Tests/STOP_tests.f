      STOP
C     STOP has no return values, however the following should all parse correctly.
C     The compiler will show a warning, invorming the end user that these will have no effect
C     Stop has the same format as a print statement, STOP<arithmetic>.
      STOP 1
      STOP 55
      STOP (X + 4)
      STOP ( 7 / 7 / 7 + 1)
      S
     &T
     &O
     &P      1
     &+ 4
      END