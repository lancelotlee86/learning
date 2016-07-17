package stone;

import java.io.IOException;
        import java.io.LineNumberReader;
        import java.io.Reader;
        import java.util.ArrayList;
        import java.util.regex.Pattern;

/**
 * Created by lance on 2016/6/23.
 */

        public class Lexer {

            public static String regexPat
                    = "\\s*((//.*)|([0-9]+)|(\"(\\\\\"|\\\\\\\\|\\\\n|[^\"])*\")"
                    + "|[A-Z_a-z][A-Z_a-z0-9]*|==|<=|>=|&&|\\|\\||\\p{Punct})?";
            private Pattern pattern = Pattern.compile(regexPat);
            private ArrayList<Token> queue = new ArrayList<Token>();
            private boolean hasMore;
            private LineNumberReader reader;


            public Lexer(Reader r) {
                hasMore = true;
                reader = new LineNumberReader(r);
            }


            public void test() throws IOException {
                System.out.println(reader.readLine());
            }

            protected String toStringLiteral(String s) {
                StringBuilder sb = new StringBuilder();
        int len = s.length() - 1;
        for (int i = 1; i < len; i++) {

        }
    }

    protected static class NumToken extends Token {
        // 数字字面量类 继承自 Token 类
        private int value;

        protected NumToken(int line, int v) {
            super(line);
            value = v;
        }
        public boolean isNumber() {
            return true;
        }
        public String getText() {
            return Integer.toString(value);
        }
        public int getNumber() {
            return value;
        }
    }

    protected static class IdToken extends Token {
        // 标识符类 继承自 Token 类
        private String text;

        protected IdToken(int line, String id) {
            super(line);
            text = id;
        }
        public boolean isIdentifier() {
            return true;
        }
        public String getText() {
            return text;
        }
    }

    protected static class StrToken extends Token {
        // 字符串字面量类 继承自 Token 类
        private String literal;

        protected StrToken(int line, String str) {
            super(line);
            literal = str;
        }
        public boolean IsString() {
            return true;
        }
        public String getText() {
            return literal;
        }
    }
}
