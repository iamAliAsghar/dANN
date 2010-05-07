/******************************************************************************
 *                                                                             *
 *  Copyright: (c) Syncleus, Inc.                                              *
 *                                                                             *
 *  You may redistribute and modify this source code under the terms and       *
 *  conditions of the Open Source Community License - Type C version 1.0       *
 *  or any later version as published by Syncleus, Inc. at www.syncleus.com.   *
 *  There should be a copy of the license included with this file. If a copy   *
 *  of the license is not included you are granted no right to distribute or   *
 *  otherwise use this file except through a legal and valid license. You      *
 *  should also contact Syncleus, Inc. at the information below if you cannot  *
 *  find a license:                                                            *
 *                                                                             *
 *  Syncleus, Inc.                                                             *
 *  2604 South 12th Street                                                     *
 *  Philadelphia, PA 19148                                                     *
 *                                                                             *
 ******************************************************************************/
package com.syncleus.dann.graph;

import java.util.*;

public class MutableDirectedAdjacencyGraph<N, E extends DirectedEdge<N>>  extends AbstractBidirectedAdjacencyGraph<N, E> implements MutableBidirectedGraph<N,E>
{
	public MutableDirectedAdjacencyGraph()
	{
		super();
	}

	public MutableDirectedAdjacencyGraph(final Graph<N,E> copyGraph)
	{
		super(copyGraph);
	}

	public MutableDirectedAdjacencyGraph(final Set<N> nodes, final Set<E> edges)
	{
		super(nodes, edges);
	}

	public boolean add(E newEdge)
	{
		if(newEdge == null)
			throw new IllegalArgumentException("newEdge can not be null");
		if(!this.getNodes().containsAll(newEdge.getNodes()))
			throw new IllegalArgumentException("newEdge has a node as an end point that is not part of the graph");

		if(this.getInternalEdges().add(newEdge))
		{
			for(N currentNode : newEdge.getNodes())
			{
				this.getInternalAdjacencyEdges().get(currentNode).add(newEdge);

				List<N> newAdjacentNodes = new ArrayList<N>(newEdge.getNodes());
				newAdjacentNodes.remove(currentNode);
				for(N newAdjacentNode : newAdjacentNodes)
					this.getInternalAdjacencyNodes().get(currentNode).add(newAdjacentNode);
			}
			return true;
		}

		return false;
	}

	public boolean add(N newNode)
	{
		if(newNode == null)
			throw new IllegalArgumentException("newNode can not be null");

		if(this.getNodes().contains(newNode))
			return false;

		this.getInternalAdjacencyEdges().put(newNode, new HashSet<E>());
		this.getInternalAdjacencyNodes().put(newNode, new ArrayList<N>());
		return true;
	}

	public boolean remove(E edgeToRemove)
	{
		if(edgeToRemove == null)
			throw new IllegalArgumentException("removeSynapse can not be null");

		if(!this.getInternalEdges().remove(edgeToRemove))
			return false;

		for(N removeNode : edgeToRemove.getNodes())
		{
			this.getInternalAdjacencyEdges().get(removeNode).remove(edgeToRemove);

			List<N> removeAdjacentNodes = new ArrayList<N>(edgeToRemove.getNodes());
			removeAdjacentNodes.remove(removeNode);
			for(N removeAdjacentNode : removeAdjacentNodes)
				this.getInternalAdjacencyNodes().get(removeNode).remove(removeAdjacentNode);
		}
		return true;
	}

	public boolean remove(N nodeToRemove)
	{
		if(nodeToRemove == null)
			throw new IllegalArgumentException("node can not be null");

		if(!this.getNodes().contains(nodeToRemove))
			return false;

		Set<E> removeEdges = this.getInternalAdjacencyEdges().get(nodeToRemove);

		//remove all the edges
		for(E removeEdge : removeEdges)
			this.remove(removeEdge);

		//modify edges by removing the node to remove
		Set<E> newEdges = new HashSet<E>();
		for(E removeEdge : removeEdges)
		{
			E newEdge = (E) removeEdge.disconnect(nodeToRemove);
			while( (newEdge.getNodes().contains(nodeToRemove)) && (newEdge != null) )
				newEdge = (E) removeEdge.disconnect(nodeToRemove);
			if(newEdge != null)
				newEdges.add(newEdge);
		}

		//add the modified edges
		for(E newEdge : newEdges)
			this.add(newEdge);

		//remove the node itself
		this.getInternalAdjacencyEdges().remove(nodeToRemove);
		this.getInternalAdjacencyNodes().remove(nodeToRemove);

		return true;
	}

	@Override
	public MutableDirectedAdjacencyGraph<N,E> cloneAdd(E newEdge)
	{
		return (MutableDirectedAdjacencyGraph<N,E>) super.cloneAdd(newEdge);
	}

	@Override
	public MutableDirectedAdjacencyGraph<N,E> cloneAdd(N newNode)
	{
		return (MutableDirectedAdjacencyGraph<N,E>) super.cloneAdd(newNode);
	}

	@Override
	public MutableDirectedAdjacencyGraph<N,E> cloneAdd(Set<N> newNodes, Set<E> newEdges)
	{
		return (MutableDirectedAdjacencyGraph<N,E>) super.cloneAdd(newNodes, newEdges);
	}

	@Override
	public MutableDirectedAdjacencyGraph<N,E> cloneRemove(E edgeToRemove)
	{
		return (MutableDirectedAdjacencyGraph<N,E>) super.cloneRemove(edgeToRemove);
	}

	@Override
	public MutableDirectedAdjacencyGraph<N,E> cloneRemove(N nodeToRemove)
	{
		return (MutableDirectedAdjacencyGraph<N,E>) super.cloneRemove(nodeToRemove);
	}

	@Override
	public MutableDirectedAdjacencyGraph<N,E> cloneRemove(Set<N> deleteNodes, Set<E> deleteEdges)
	{
		return (MutableDirectedAdjacencyGraph<N,E>) super.cloneRemove(deleteNodes, deleteEdges);
	}

	@Override
	public MutableDirectedAdjacencyGraph<N,E> clone()
	{
		return (MutableDirectedAdjacencyGraph<N,E>) super.clone();
	}
}