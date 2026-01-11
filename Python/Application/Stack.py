class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class Stack:
    def __init__(self):
        # self.capactity = capacity; 동적할당
        self.size      = 0
        self.top       = None
        
    # def is_full(self):
    #     return (self.capactity) == self.size
    
    def is_empty(self):
        return self.top is None
    
    def push(self, data):
        new_node = Node(data)
        new_node.next = self.top
        self.top = new_node
        self.size += 1
            
    
    def pop(self):
        if self.is_empty():
            raise Exception("Stack is empty")
        # Q. pop을 하려면 prevTop 노드의 연결을 끊어야할텐데..
        # A. pop Tail은 O(N)이지만, popHead는 O(1)
        ret = self.top.data
        self.top = self.top.next
        self.size -= 1
        return ret
    
    def peek(self):
        if self.top is None:
            print("Stack is Emtpy")
            return
        return self.top.data
        
    def printAll(self):
        ret = []
        if self.size != 0:
            pos = self.top
            for _ in range(self.size):
                ret.append(pos.data)
                pos = pos.next
        print(ret)
            
        
st = Stack()
for i in range(8):
    st.push(i)

for i in range(5):
    print(f"pop: {st.pop()}")
print(st.peek())
st.printAll()