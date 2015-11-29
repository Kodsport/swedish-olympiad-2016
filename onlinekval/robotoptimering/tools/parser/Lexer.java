package parser;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.util.ArrayList;
import java.util.List;



public class Lexer {
    private List<Token> tokens;
    int pos = 0;

    public Lexer(Reader r) throws IOException, InvalidTokenException {
        tokens = new ArrayList<>();
        BufferedReader br = new BufferedReader(r);

        int i = 1;
        String line = br.readLine();

        while(line != null) {
            String[] words = line.split("\\s");

            for(String t : words) {
                switch(t) {
                    case "":
                        continue;
                    case "forward":
                        tokens.add(new Token(TokenType.FWD, i));
                        break;
                    case "right":
                        tokens.add(new Token(TokenType.RIGHT, i));
                        break;
                    case "left":
                        tokens.add(new Token(TokenType.LEFT, i));
                        break;
                    case "for":
                        tokens.add(new Token(TokenType.FOR, i));
                        break;
                    case "{":
                        tokens.add(new Token(TokenType.LBRACE, i));
                        break;
                    case "}":
                        tokens.add(new Token(TokenType.RBRACE, i));
                        break;
                    case "call":
                        tokens.add(new Token(TokenType.CALL, i));
                        break;
                    case "return":
                        tokens.add(new Token(TokenType.RETURN, i));
                        break;
                    case "gotoblocked":
                        tokens.add(new Token(TokenType.GOTOBLOCKED, i));
                        break;
                    default:
                        if(t.matches("^[0-9]+$")) {
                            try {
                                tokens.add(new NumberToken(Integer.parseInt(t), i));
                            } catch(NumberFormatException e) {
                                throw new InvalidTokenException(t, i);
                            }
                        } else if(t.matches("^[a-z]+$")) {
                            tokens.add(new NameToken(t, i));
                        } else if(t.matches("^[a-z]+:$")) {
                            tokens.add(new LabelToken(t.substring(0, t.length()-1), i));
                        } else {
                            throw new InvalidTokenException(t, i);
                        }
                        break;
                }
            }

            line = br.readLine();
            i++;
        }
        tokens.add(new Token(TokenType.EOF, i));
    }

    public Token peekToken() {
        if(pos < tokens.size()) {
            return tokens.get(pos);
        } else {
            return null;
        }
    }

    public Token nextToken() {
        Token t = peekToken();
        pos++;
        return t;
    }

    public void print() {
        for(Token t : tokens) {
            System.out.println(t);
        }
    }

    public static class InvalidTokenException extends Exception {
        public InvalidTokenException(String token, int line) {
            super("Invalid token on line " + line + ": " + token);
        }
    }
}
