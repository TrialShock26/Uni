a) non simmetrica
b) non riflessiva
c) non transitiva
d) ok

public class Z {
    private Z other;
    private int val;

    @Override
    public boolean equals(Object o) {
        if (other != null && o.other != null) {
            return other.val == o.other.val;
        } else {return other == o.other;}
    }
}