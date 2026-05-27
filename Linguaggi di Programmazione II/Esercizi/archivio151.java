import java.util.*;

public class WeightedSet<T> {
    private Map<T, Integer> set;
    private int p;

    public WeightedSet() {
        set = new HashMap<>();
        p = Integer.MIN_VALUE;
    }

    public void add(T t, int weight) {
        if (weight < p) throw new IllegalArgumentException();
        set.put(t, weight);
    }

    public WeightedSet<T> atLeast(int p) {
        WeightedSet<T> ans = new WeightedSet<T>();
        ans.set = this.set;
        ans.p = p;
        return ans;
    }

    @Override
    public String toString() {
        List<T> ans = new ArrayList<>();
        for (Map.Entry<T, Integer> e : set.entrySet()) {
            if (e.getValue() > p) ans.add(e.getKey());
        }
        ans.sort(new Comparator<T>() {
            public int compare(T o1, T o2) {
                return set.get(o2) - set.get(o1);
            }
        });
        return ans.toString();
    }
}