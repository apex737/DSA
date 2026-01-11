class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None


# 연결리스트 관점에서...
# Queue는 Push Tail & Pop Head 이고,
# Stack은 Push Head & Pop Head 인데,
# Double Ended Queue (Deque; 덱)은 입출력 방향이 자유롭다
class Deque:
    def __init__(self):
        # 뭐가 최소한으로 필요하지?? 
        # 넣는 방향을 결정하려면 head/tail이 둘다 있어야할듯
        self.head = None
        self.tail = None
        self.cnt  = 0   # item 수를 알고싶을테니..
    
    def size(self):
        return self.cnt
    
    def push_back(self, data):
        new_node = Node(data)
        self.cnt += 1
        if self.head is None:
            self.head = self.tail = new_node
        else:
            self.tail.next = new_node
            new_node.prev = self.tail
            self.tail = new_node
            
    
    def push_head(self,data):
        new_node = Node(data)
        self.cnt += 1
        if self.head is None:
            self.head = self.tail = new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head = new_node
    
    def is_empty(self):
        return self.head is None
    
    def pop_tail(self):
        if self.is_empty():
            raise Exception("Deque is empty")
        # Pop에서의 Off-by-1 issue
        ret = self.tail.data
        if self.cnt == 1:
            self.head = self.tail = None
        else:
            self.tail = self.tail.prev
            self.tail.next = None
        
        self.cnt -= 1
        return ret
        
    def pop_head(self):
        if self.is_empty():
            raise Exception("Deque is empty")
        ret = self.head.data
        if self.cnt == 1:
            self.head = self.tail = None
        else:
            self.head = self.head.next
            self.head.prev = None
        self.cnt -= 1
        return ret
    
    def display(self):
        pos = self.head
        dspl = []
        while pos:
            dspl.append(pos.data)
            pos = pos.next
        print(dspl)

dq = Deque()

dq.push_back(1)
dq.pop_tail()

for i in range(3):
    dq.push_head(i)
for i in range(3,6):
    dq.push_back(i)
    
dq.display()
for i in range(3):
    print(f"pop_head: {dq.pop_head()} | current size: {dq.size()}")
    dq.display()

for i in range(3):
    print(f"pop_tail: {dq.pop_tail()} | current size: {dq.size()}")
    dq.display()
