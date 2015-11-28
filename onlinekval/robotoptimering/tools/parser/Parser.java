package parser;

import java.text.ParseException;

public class Parser {
    Lexer lexer;

    public Parser(Lexer lexer) {
        this.lexer = lexer;
    }

    public ParseTree Program() throws ParseException {
        ListNode node = new ListNode();
        while (lexer.peekToken().type != TokenType.EOF) {
            node.addCommand(Command());
        }
        return node;
    }

    public ListNode ForBlock() throws ParseException {
        ListNode node = new ListNode();

        Token next = lexer.nextToken();
        if (next.type != TokenType.LBRACE) {
            throw new ParseException("Expected { on line " + next.line + ", got " + next.toString() + ".", next.line);
        }

        while(true) {
            Token peeked = lexer.peekToken();

            if(peeked.type == TokenType.EOF) {
                throw new ParseException("Expected } on line " + peeked.line + ", got " + peeked.toString() + ".", peeked.line);
            } else if(peeked.type == TokenType.RBRACE) {
                lexer.nextToken();
                break;
            }

            node.addCommand(Command());
        }

        return node;
    }

    public ParseTree Command() throws ParseException {
        Token next = lexer.nextToken();
        switch(next.type) {
            case FWD:
                return new MoveNode(next.line);
            case LEFT:
                return new RotateNode(false, next.line);
            case RIGHT:
                return new RotateNode(true, next.line);
            case FOR:
                Token number = lexer.nextToken();
                if (number.type != TokenType.NUMBER) {
                    throw new ParseException("Expected number on line " + number.line + ", got " + number.toString(), number.line);
                }
                int n = ((NumberToken)number).number;
                return new ForNode(ForBlock(), n, next.line);
            default:
                throw new ParseException("Unexpected token on line " + next.line + ": " + next.toString(), next.line);
        }
    }
}
