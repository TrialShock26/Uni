import java.nio.BufferOverflowException;
import java.util.Set;
import java.util.HashSet;

public class Container {
    private static final double CAPACITY = 30;
    private double liters;
    public Set<Container> connections;

    public Container() {
        liters = 0;
        connections = new HashSet<>();
    }

    public void addWater(double liters) {
        if (this.liters + liters > CAPACITY) throw new BufferOverflowException();
        this.liters += liters;
        this.level();
    }

    public double getAmount() {return liters;}

    public void connect(Container other) {
        connections.add(other);
        other.connections.add(this);
        for (Container c : connections) {
            if (c != other) {
                c.connections.add(other);
                other.connections.add(c);
                for (Container k : other.connections) {
                    if (k != this && k != c) {
                        c.connections.add(k);
                    }
                }
            }
        }
        for (Container c: other.connections) {
            if (c != this) {
                c.connections.add(this);
                connections.add(c);
                for (Container k : connections) {
                    if (k != other && k != c) {
                        c.connections.add(k);
                    }
                }
            }
        }
        this.level();
    }

    private void level() {
        double totalLiters = this.liters;
        for (Container c : this.connections) {
            totalLiters += c.getAmount();
        }
        double newLiters = totalLiters / (this.connections.size() + 1);
        this.liters = newLiters;
        for (Container c : this.connections) {
            c.setLiters(newLiters);
        }
    }

    private void setLiters(double liters) {this.liters = liters;}
}