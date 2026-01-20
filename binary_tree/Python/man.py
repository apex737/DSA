class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def preorder(node): 
    if node:
        print(node.value, end=' ')
        preorder(node.left)
        preorder(node.right)

def inorder(node):
    if node:
        inorder(node.left)
        print(node.value, end=' ')
        inorder(node.right)

def postorder(node):
    if node:
        postorder(node.left)
        postorder(node.right)
        print(node.value, end=' ')

from collections import deque

def levelorder(node):
    if not node:
        return
    # 덱에 Root Node 삽입 (큐는 pop_right만 가능하므로)
    queue = deque([node])
    
    while queue:
        # 첫 popleft의 결과는 루트 노드 자체
        
        current = queue.popleft() # 1 -> 2, [3]
                                  # 1 -> 2 -> 3, [4, 5]
                                  # 1 -> 2 -> 3 -> 4, [5, 6, 7]
        print(current.value, end=' ')
        # Current Node
        # [2, 3] -> [3, 4, 5] -> [4, 5, 6, 7]
        if current.left:
            queue.append(current.left)
        if current.right:
            queue.append(current.right)


root = Node(1)
root.left = Node(2)
root.right = Node(3)
root.left.left = Node(4)
root.left.right = Node(5)
root.right.left = Node(6)
root.right.right = Node(7)

print("Preorder:")     
preorder(root)        # 1 2 4 5 3 6 7

print("\nInorder:")    
inorder(root)         # 4 2 5 1 6 3 7

print("\nPostorder:")  
postorder(root)       # 4 5 2 6 7 3 1

print("\nLevelorder:") 
levelorder(root)      # 1 2 3 4 5 6 7
