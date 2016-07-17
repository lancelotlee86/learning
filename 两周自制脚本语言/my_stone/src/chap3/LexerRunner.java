package chap3;
import stone.*;
import java.io.File;
import java.io.IOException;

/**
 * Created by lance on 2016/6/23.
 */
public class LexerRunner {
    public static void main(String[] args) throws IOException{
        Lexer l = new Lexer(new CodeDialog());
        l.test();
        System.out.println(l.regexPat);
    }
}
