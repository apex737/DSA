class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

# Stack: Push Head, Pop Head
# Queue: Push Tail, Pop Head
class Queue:
    def __init__(self):
        self.head = None
        self.tail = None
        self.cnt  = 0
    
    def is_empty(self):
        return self.head is None
        
    def enqueue(self,data):
        # push tail
        new_node = Node(data)
        self.cnt += 1
        if self.head is None:
            self.head = self.tail = new_node
        else:
            self.tail.next = new_node
            self.tail = new_node
            
    def dequeue(self):
        # pop head
        if self.is_empty():
            raise Exception("Queue is Empty")
        ret = self.head.data
        if self.cnt == 1:
            self.tail = self.head = None
        else:
            self.head = self.head.next
        self.cnt -= 1
        return ret
    
    def size(self):
        return self.cnt

    def display(self):
        dspl = []
        pos = self.head
        for _ in range(self.cnt):
            dspl.append(pos.data)
            pos = pos.next
        print(dspl)
            
q = Queue()
for i in range(5):
    q.enqueue(i)
for i in range(5):
    print(f"dequeue: {q.dequeue()} | current size: {q.size()}")
    q.display()
        
    