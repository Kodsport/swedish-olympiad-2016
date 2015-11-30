package parser;

enum TokenType {
    FWD, RIGHT, LEFT, FOR, CALL, RETURN, GOTO, GOTOBLOCKED, NUMBER, NAME, LABEL, LBRACE, RBRACE, EOF
}

class Token {
    TokenType type;
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

class LabelToken extends NameToken {
    public LabelToken(String name, int line) {
        super(name, line);
        type = TokenType.LABEL;
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
