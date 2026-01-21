class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        
def level_order(node):
    # 1. 항상 Null Check
    if node is None:
        return
    # root를 받아서
    from collections import deque
    q = deque([node]) # 왜 node아니고 [node]?
    
    while q:
        pos = q.popleft()
        print(pos.data, end=' ')
        # 2. 항상 Null Check
        if pos.left:
            q.append(pos.left)
        if pos.right:
            q.append(pos.right)
    print()
        

    
# 자동화 가능? (BinTree ? )
root = Node(1)
root.left = Node(2)
root.right = Node(3)
root.left.left = Node(4)
root.left.right = Node(5)
root.right.left = Node(6)
root.right.right = Node(7)

level_order(root)