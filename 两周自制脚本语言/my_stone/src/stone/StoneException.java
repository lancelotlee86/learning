package stone;
import stone.ast.ASTree;

/**
 * Created by lance on 2016/6/23.
 */
public class StoneException extends RuntimeException {
    public StoneException(String m) {
        super(m);
    }
    public StoneException(String m, ASTree t) {
        super(m + " " + t.location());
    }
}
