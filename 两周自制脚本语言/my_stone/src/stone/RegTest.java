package stone;

/**
 * Created by lance on 2016/6/23.
 */

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RegTest {
    public static void main(String[] args) {
        Pattern patt = Pattern.compile("(\\w+)\\s(\\d+)");
        Matcher matcher = patt.matcher("Bananas 123 abv");
        matcher.lookingAt();
        System.out.println("Name: " + matcher.group(1));
        System.out.println("Number: " + matcher.group(2));
    }
}
