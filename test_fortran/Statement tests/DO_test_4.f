C     This test is designed to test the use of DO loops inside functions
C     This includes nested do LOOPS
      SUBROUTINE NONPRIMES()
      DO 10 I=2,5
      DO 10 K=2,5
10    PRINT I*K
      RETURN
      ASSIGN I TO 10
      ASSIGN K TO 15
      CALL NONPRIMES()
      PRINT I
      PRINT K
      END