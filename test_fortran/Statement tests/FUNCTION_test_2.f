C     This test is designed to throw an error
C     Recursive functions are not allowed
C     Intended behavior here is that the compiler will exit early.
C     The arithmetic parser cannot handle unknown functions, and will cause the compiler to exit if it cannot find them.
C     This is handled gracefully, and the user gets an informative error message, however future work may involve allowing the arithmetic
C     parser to recover gracefully.
      PRINTSUM(X) = PRINTSUM(X) + 1
      PRINT PRINTSUM(5)
      END