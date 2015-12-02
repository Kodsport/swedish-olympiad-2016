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
                Token end = lexer.nextToken();
                node.setEndline(end.line);
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
            case LABEL:
                return new LabelNode(((LabelToken)next).name, next.line);
            case GOTO:
                Token name = lexer.nextToken();
                if(name.type != TokenType.NAME) {
                    throw new ParseException("Expected label name on line " + name.line + ", got " + name.toString(), name.line);
                }
                return new GotoNode(((NameToken)name).name, false, next.line);
            case GOTOBLOCKED:
                Token token = lexer.nextToken();
                if(token.type != TokenType.NAME) {
                    throw new ParseException("Expected label name on line " + token.line + ", got " + token.toString(), token.line);
                }
                return new GotoNode(((NameToken)token).name, true, next.line);
            case CALL:
                Token token2 = lexer.nextToken();
                if(token2.type != TokenType.NAME) {
                    throw new ParseException("Expected label name on line " + token2.line + ", got " + token2.toString(), token2.line);
                }
                return new CallNode(((NameToken)token2).name, next.line);
            case RETURN:
                return new ReturnNode(next.line);
            default:
                throw new ParseException("Unexpected token on line " + next.line + ": " + next.toString(), next.line);
        }
    }
}
