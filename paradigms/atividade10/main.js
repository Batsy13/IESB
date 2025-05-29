class Node {
  constructor(value) {
    this.value = value;
    this.next = null;
  }
}

class Stack {
  constructor(capacity = 10) {
    if (capacity <= 0) {
      throw new Error('IllegalArgumentException: Capacidade deve ser maior que 0.');
    }
    this.capacity = capacity;
    this.size = 0;
    this.header = null;
  }

  empty() {
    return this.size === 0;
  }

  peek() {
    if (this.empty()) {
      throw new Error('EmptyStackException: A pilha está vazia.');
    }
    return this.header.value;
  }

  pop() {
    if (this.empty()) {
      throw new Error('EmptyStackException: A pilha está vazia.');
    }
    const value = this.header.value;
    this.header = this.header.next;
    this.size--;
    return value;
  }

  push(value) {
    if (this.size === this.capacity) {
      throw new Error('FullStackException: A pilha está cheia.');
    }
    const newNode = new Node(value);
    newNode.next = this.header;
    this.header = newNode;
    this.size++;
  }

  getSize() {
    return this.size;
  }
}

const stack = new Stack(3);
try {
  stack.push(10);
  stack.push(20);
  stack.push(30);
  console.log('Elemento superior:', stack.peek()); 
  
  stack.push(40); // Para apresentar erro FullStackException

  console.log('Tamanho:', stack.getSize());
  
  console.log('Saindo:', stack.pop());
  
  console.log('Tamanho da pilha depois do pop:', stack.getSize());
  
  // stack.pop();
  // stack.pop(); // Para apresentar erro EmptyStackException
  // stack.pop();
} catch (error) {
  console.error('Error:', error.message);
}
