C Arithmetic parser tokenization errrors
C Note that this isn't designed to test the arithmetic parser, only the tokenizer prior to arithmetic statements being handed to the parser.
      Z = 3 + 5
C     Expected error - This won't parse as the left hand side must be a variable name
      ((((((((((((Z)))))))))))) = ((((((((((((((((X))))))))))))))))
C     This should parse,
C     This should parse 
      X = X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X
C     Expected error -  The right hand side is blank, so this won't parse.
      X = 
C     Expected error - invalid symbols in the right hand side.
      X = .X.
C     Expected error - The minus symbol is a uncide 'Small Hyphe-minus', not a traditional minus sign. This won't parse
      X = 1 ﹣ X
C     This shouldn't parse, double equals isn't a valid syntax.
      X == Y
C     This should parse, but will throw an arithmetic parser error . This is unrecoverable, and will (gracefully) crash the whole compiler.
      X = X // X
C     This should also parse, but cause the arithmetic parser to exit (and hence the compiler.)
      NEWVARIABLE = FUNCTION(X)
      END