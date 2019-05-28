#pragma once
#include "AABB.h"
#include <memory>
#include <vector>
#include <map>
#include <forward_list>
#include <cassert>
#include <stack>
#include "IAABB.h"

#define AABB_NULL_NODE 0xffffffff

template <class T = IAABB>
struct AABBNode
{
	AABB aabb;
	T* object;
	// tree links
	unsigned parentNodeIndex;
	unsigned leftNodeIndex;
	unsigned rightNodeIndex;
	// node linked list link
	unsigned nextNodeIndex;

	bool isLeaf() const { return leftNodeIndex == AABB_NULL_NODE; }

	AABBNode() : object(nullptr), parentNodeIndex(AABB_NULL_NODE), leftNodeIndex(AABB_NULL_NODE), rightNodeIndex(AABB_NULL_NODE), nextNodeIndex(AABB_NULL_NODE)
	{

	}
};

template <class T = IAABB>
class AABBTree
{
private:
	std::map<T*, unsigned> _objectNodeIndexMap;
	std::vector<AABBNode<T>> _nodes;
	unsigned _rootNodeIndex;
	unsigned _allocatedNodeCount;
	unsigned _nextFreeNodeIndex;
	unsigned _nodeCapacity;
	unsigned _growthSize;

	unsigned allocateNode();
	void deallocateNode(unsigned nodeIndex);
	void insertLeaf(unsigned leafNodeIndex);
	void removeLeaf(unsigned leafNodeIndex);
	void updateLeaf(unsigned leafNodeIndex, const AABB& newAaab);
	void fixUpwardsTree(unsigned treeNodeIndex);

public:
	AABBTree(unsigned initialSize = 1);
	~AABBTree();

	void insertObject(T* object);
	void removeObject(T* object);
	void updateObject(T* object);
	std::forward_list<T*> queryOverlaps(T* object) const;
};

template <class T>
AABBTree<T>::AABBTree(unsigned initialSize) : _rootNodeIndex(AABB_NULL_NODE), _allocatedNodeCount(0), _nextFreeNodeIndex(0), _nodeCapacity(initialSize), _growthSize(initialSize)
{
	_nodes.resize(initialSize);
	for (unsigned nodeIndex = 0; nodeIndex < initialSize; nodeIndex++)
	{
		AABBNode<T>& node = _nodes[nodeIndex];
		node.nextNodeIndex = nodeIndex + 1;
	}
	_nodes[initialSize - 1].nextNodeIndex = AABB_NULL_NODE;
}

template <class T>
AABBTree<T>::~AABBTree()
{
}

template <class T>
unsigned AABBTree<T>::allocateNode()
{
	// if we have no free tree nodes then grow the pool
	if (_nextFreeNodeIndex == AABB_NULL_NODE)
	{
		assert(_allocatedNodeCount == _nodeCapacity);

		_nodeCapacity += _growthSize;
		_nodes.resize(_nodeCapacity);
		for (unsigned nodeIndex = _allocatedNodeCount; nodeIndex < _nodeCapacity; nodeIndex++)
		{
			AABBNode<T>& node = _nodes[nodeIndex];
			node.nextNodeIndex = nodeIndex + 1;
		}
		_nodes[_nodeCapacity - 1].nextNodeIndex = AABB_NULL_NODE;
		_nextFreeNodeIndex = _allocatedNodeCount;
	}

	unsigned nodeIndex = _nextFreeNodeIndex;
	AABBNode<T>& allocatedNode = _nodes[nodeIndex];
	allocatedNode.parentNodeIndex = AABB_NULL_NODE;
	allocatedNode.leftNodeIndex = AABB_NULL_NODE;
	allocatedNode.rightNodeIndex = AABB_NULL_NODE;
	_nextFreeNodeIndex = allocatedNode.nextNodeIndex;
	_allocatedNodeCount++;

	return nodeIndex;
}

template <class T>
void AABBTree<T>::deallocateNode(unsigned nodeIndex)
{
	AABBNode<T>& deallocatedNode = _nodes[nodeIndex];
	deallocatedNode.nextNodeIndex = _nextFreeNodeIndex;
	_nextFreeNodeIndex = nodeIndex;
	_allocatedNodeCount--;
}

template <class T>
void AABBTree<T>::insertObject(T* object)
{
	unsigned nodeIndex = allocateNode();
	AABBNode<T>& node = _nodes[nodeIndex];

	node.aabb = object->getAABB();
	node.object = object;

	insertLeaf(nodeIndex);
	_objectNodeIndexMap[object] = nodeIndex;
}

template <class T>
void AABBTree<T>::removeObject(T* object)
{
	unsigned nodeIndex = _objectNodeIndexMap[object];
	removeLeaf(nodeIndex);
	deallocateNode(nodeIndex);
	_objectNodeIndexMap.erase(object);
}

template <class T>
void AABBTree<T>::updateObject(T* object)
{
	auto it = _objectNodeIndexMap.find(object);
	if (it != _objectNodeIndexMap.end()) {
		unsigned nodeIndex = it->second;
		updateLeaf(nodeIndex, object->getAABB());
	}	
}

template <class T>
std::forward_list<T*> AABBTree<T>::queryOverlaps(T* object) const
{
	std::forward_list<T*> overlaps;
	std::stack<unsigned> stack;
	AABB testAabb = object->getAABB();

	stack.push(_rootNodeIndex);
	while (!stack.empty())
	{
		unsigned nodeIndex = stack.top();
		stack.pop();

		if (nodeIndex == AABB_NULL_NODE) continue;

		const AABBNode<T>& node = _nodes[nodeIndex];
		if (node.aabb.overlaps(testAabb))
		{
			if (node.isLeaf() && node.object != object)
			{
				overlaps.push_front(node.object);
			}
			else
			{
				stack.push(node.leftNodeIndex);
				stack.push(node.rightNodeIndex);
			}
		}
	}

	return overlaps;
}

template <class T>
void AABBTree<T>::insertLeaf(unsigned leafNodeIndex)
{
	// make sure we're inserting a new leaf
	assert(_nodes[leafNodeIndex].parentNodeIndex == AABB_NULL_NODE);
	assert(_nodes[leafNodeIndex].leftNodeIndex == AABB_NULL_NODE);
	assert(_nodes[leafNodeIndex].rightNodeIndex == AABB_NULL_NODE);

	// if the tree is empty then we make the root the leaf
	if (_rootNodeIndex == AABB_NULL_NODE)
	{
		_rootNodeIndex = leafNodeIndex;
		return;
	}

	// search for the best place to put the new leaf in the tree
	// we use surface area and depth as search heuristics
	unsigned treeNodeIndex = _rootNodeIndex;
	AABBNode<T>& leafNode = _nodes[leafNodeIndex];
	while (!_nodes[treeNodeIndex].isLeaf())
	{
		// because of the test in the while loop above we know we are never a leaf inside it
		const AABBNode<T>& treeNode = _nodes[treeNodeIndex];
		unsigned leftNodeIndex = treeNode.leftNodeIndex;
		unsigned rightNodeIndex = treeNode.rightNodeIndex;
		const AABBNode<T>& leftNode = _nodes[leftNodeIndex];
		const AABBNode<T>& rightNode = _nodes[rightNodeIndex];

		AABB combinedAabb = treeNode.aabb.merge(leafNode.aabb);

		float newParentNodeCost = 2.0f * combinedAabb.surfaceArea;
		float minimumPushDownCost = 2.0f * (combinedAabb.surfaceArea - treeNode.aabb.surfaceArea);

		// use the costs to figure out whether to create a new parent here or descend
		float costLeft;
		float costRight;
		if (leftNode.isLeaf())
		{
			costLeft = leafNode.aabb.merge(leftNode.aabb).surfaceArea + minimumPushDownCost;
		}
		else
		{
			AABB newLeftAabb = leafNode.aabb.merge(leftNode.aabb);
			costLeft = (newLeftAabb.surfaceArea - leftNode.aabb.surfaceArea) + minimumPushDownCost;
		}
		if (rightNode.isLeaf())
		{
			costRight = leafNode.aabb.merge(rightNode.aabb).surfaceArea + minimumPushDownCost;
		}
		else
		{
			AABB newRightAabb = leafNode.aabb.merge(rightNode.aabb);
			costRight = (newRightAabb.surfaceArea - rightNode.aabb.surfaceArea) + minimumPushDownCost;
		}

		// if the cost of creating a new parent node here is less than descending in either direction then
		// we know we need to create a new parent node, errrr, here and attach the leaf to that
		if (newParentNodeCost < costLeft && newParentNodeCost < costRight)
		{
			break;
		}

		// otherwise descend in the cheapest direction
		if (costLeft < costRight)
		{
			treeNodeIndex = leftNodeIndex;
		}
		else
		{
			treeNodeIndex = rightNodeIndex;
		}
	}

	// the leafs sibling is going to be the node we found above and we are going to create a new
	// parent node and attach the leaf and this item
	unsigned leafSiblingIndex = treeNodeIndex;
	AABBNode<T>& leafSibling = _nodes[leafSiblingIndex];
	unsigned oldParentIndex = leafSibling.parentNodeIndex;
	unsigned newParentIndex = allocateNode();
	AABBNode<T>& newParent = _nodes[newParentIndex];
	newParent.parentNodeIndex = oldParentIndex;
	newParent.aabb = leafNode.aabb.merge(leafSibling.aabb); // the new parents aabb is the leaf aabb combined with it's siblings aabb
	newParent.leftNodeIndex = leafSiblingIndex;
	newParent.rightNodeIndex = leafNodeIndex;
	leafNode.parentNodeIndex = newParentIndex;
	leafSibling.parentNodeIndex = newParentIndex;

	if (oldParentIndex == AABB_NULL_NODE)
	{
		// the old parent was the root and so this is now the root
		_rootNodeIndex = newParentIndex;
	}
	else
	{
		// the old parent was not the root and so we need to patch the left or right index to
		// point to the new node
		AABBNode<T>& oldParent = _nodes[oldParentIndex];
		if (oldParent.leftNodeIndex == leafSiblingIndex)
		{
			oldParent.leftNodeIndex = newParentIndex;
		}
		else
		{
			oldParent.rightNodeIndex = newParentIndex;
		}
	}

	// finally we need to walk back up the tree fixing heights and areas
	treeNodeIndex = leafNode.parentNodeIndex;
	fixUpwardsTree(treeNodeIndex);
}

template <class T>
void AABBTree<T>::removeLeaf(unsigned leafNodeIndex)
{
	// if the leaf is the root then we can just clear the root pointer and return
	if (leafNodeIndex == _rootNodeIndex)
	{
		_rootNodeIndex = AABB_NULL_NODE;
		return;
	}

	AABBNode<T>& leafNode = _nodes[leafNodeIndex];
	unsigned parentNodeIndex = leafNode.parentNodeIndex;
	const AABBNode<T>& parentNode = _nodes[parentNodeIndex]; //			TODO crash here when update
	unsigned grandParentNodeIndex = parentNode.parentNodeIndex;
	unsigned siblingNodeIndex = parentNode.leftNodeIndex == leafNodeIndex ? parentNode.rightNodeIndex : parentNode.leftNodeIndex;
	assert(siblingNodeIndex != AABB_NULL_NODE); // we must have a sibling
	AABBNode<T>& siblingNode = _nodes[siblingNodeIndex];

	if (grandParentNodeIndex != AABB_NULL_NODE)
	{
		// if we have a grand parent (i.e. the parent is not the root) then destroy the parent and connect the sibling to the grandparent in its
		// place
		AABBNode<T>& grandParentNode = _nodes[grandParentNodeIndex];
		if (grandParentNode.leftNodeIndex == parentNodeIndex)
		{
			grandParentNode.leftNodeIndex = siblingNodeIndex;
		}
		else
		{
			grandParentNode.rightNodeIndex = siblingNodeIndex;
		}
		siblingNode.parentNodeIndex = grandParentNodeIndex;
		deallocateNode(parentNodeIndex);

		fixUpwardsTree(grandParentNodeIndex);
	}
	else
	{
		// if we have no grandparent then the parent is the root and so our sibling becomes the root and has it's parent removed
		_rootNodeIndex = siblingNodeIndex;
		siblingNode.parentNodeIndex = AABB_NULL_NODE;
		deallocateNode(parentNodeIndex);
	}

	leafNode.parentNodeIndex = AABB_NULL_NODE;
}
#include <iostream>
template <class T>
void AABBTree<T>::updateLeaf(unsigned leafNodeIndex, const AABB& newAaab)
{
	std::cout << "l=" << leafNodeIndex << std::endl;
	std::cout << "n=" << _nodes.size() << std::endl;
	AABBNode<T>& node = _nodes[leafNodeIndex];
	
	// if the node contains the new aabb then we just leave things
	// TODO: when we add velocity this check should kick in as often an update will lie within the velocity fattened initial aabb
	// to support this we might need to differentiate between velocity fattened aabb and actual aabb
	if (node.aabb.contains(newAaab)) return;

	removeLeaf(leafNodeIndex);
	std::cout << "r" << std::endl;
	node.aabb = newAaab;
	insertLeaf(leafNodeIndex);
	std::cout << "i" << std::endl;
}

template <class T>
void AABBTree<T>::fixUpwardsTree(unsigned treeNodeIndex)
{
	while (treeNodeIndex != AABB_NULL_NODE)
	{
		AABBNode<T>& treeNode = _nodes[treeNodeIndex];

		// every node should be a parent
		assert(treeNode.leftNodeIndex != AABB_NULL_NODE && treeNode.rightNodeIndex != AABB_NULL_NODE);

		// fix height and area
		const AABBNode<T>& leftNode = _nodes[treeNode.leftNodeIndex];
		const AABBNode<T>& rightNode = _nodes[treeNode.rightNodeIndex];
		treeNode.aabb = leftNode.aabb.merge(rightNode.aabb);

		treeNodeIndex = treeNode.parentNodeIndex;
	}
}