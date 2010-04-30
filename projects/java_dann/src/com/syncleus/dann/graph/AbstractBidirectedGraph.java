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

import java.util.Set;

public abstract class AbstractBidirectedGraph<N, E extends BidirectedEdge<N>> extends AbstractGraph<N,E> implements BidirectedGraph<N,E>
{
	public boolean isPolytree()
	{
		return false;
	}

	@Override
	public Set<Graph<N,E>> getMaximallyConnectedComponents()
	{
		return null;
	}

	@Override
	public int getDegree(final N node)
	{
		final Set<E> adjacentEdges = this.getAdjacentEdges(node);
		int degree = 0;
		for(E adjacentEdge : adjacentEdges)
		{
			if(adjacentEdge.isLoop())
				degree += 2;
			else
				degree++;
		}
		return degree;
	}
}
