package com.syncleus.dann.neuroph;

import com.syncleus.dann.graph.AbstractDirectedEdge;
import org.neuroph.core.Connection;
import org.neuroph.core.Neuron;

public class ConnectionEdge extends AbstractDirectedEdge<Neuron> {

    public final Connection connection;

    public ConnectionEdge(Connection c, Neuron src, Neuron target) {
        super(src, target);
        this.connection = c;
    }

    @Override
    public int hashCode() {
        return super.hashCode() + connection.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        if (super.equals(obj)) {
            if (obj instanceof ConnectionEdge) {
                return ((ConnectionEdge) obj).connection == connection;
            }
        }
        return false;
    }
}
