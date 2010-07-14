/*
 * JunctionTree.h
 *
 *   Created on: Feb 4, 2010
 *       Author: nikai
 *  Description: The junction tree
 */

#pragma once

#include <set>
#include <boost/shared_ptr.hpp>
#include "BayesTree.h"
#include "ClusterTree.h"
#include "SymbolicConditional.h"

namespace gtsam {

	/**
	 * A junction tree (or clique-tree) is a cluster-tree where each node k represents a
	 * clique (maximal fully connected subset) of an associated chordal graph, such as a
	 * chordal Bayes net resulting from elimination. In GTSAM the BayesTree is used to
	 * represent the clique tree associated with a Bayes net, and the JunctionTree is
	 * used to collect the factors associated with each clique during the elimination process.
	 */
	template <class FG>
	class JunctionTree : public ClusterTree<FG> {

	public:

		/**
		 * In a junction tree each cluster is associated with a clique
		 */
		typedef typename ClusterTree<FG>::Cluster Clique;
		typedef typename Clique::shared_ptr sharedClique;

	private:
		// distribute the factors along the Bayes tree
		sharedClique distributeFactors(FG& fg, const BayesTree<SymbolicConditional>::sharedClique clique);

		// utility function called by eliminate
		template <class Conditional>
		std::pair<FG, BayesTree<Conditional> > eliminateOneClique(sharedClique fg_);

	public:
		// constructor
		JunctionTree() {}

		// constructor given a factor graph and the elimination ordering
		JunctionTree(FG& fg, const Ordering& ordering);

		// eliminate the factors in the subgraphs
		template <class Conditional>
		BayesTree<Conditional> eliminate();

	}; // JunctionTree

} // namespace gtsam
