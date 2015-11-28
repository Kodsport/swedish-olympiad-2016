package parser;

enum TokenType {
    FWD, RIGHT, LEFT, FOR, CALL, RETURN, GOTOBLOCKED, NUMBER, COLON, NAME, LBRACE, RBRACE, EOF
}

class Token {
    final TokenType type;
    final int line;

    public Token(TokenType type, int line) {
        this.type = type;
        this.line = line;
    }

    @Override
    public String toString() {
        return type.name();
    }
}

class NameToken extends Token {
    String name;

    public NameToken(String name, int line) {
        super(TokenType.NAME, line);
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }
}

class NumberToken extends Token {
    int number;

    public NumberToken(int number, int line) {
        super(TokenType.NUMBER, line);
        this.number = number;
    }

    @Override
    public String toString() {
        return Integer.toString(number);
    }
}
