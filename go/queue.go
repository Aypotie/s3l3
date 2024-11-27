package main

import (
	"errors"
	"fmt"
)

// Определение структуры для узла в двусвязном списке
type DListNode struct {
	value interface{} // private, доступно только в этом пакете
	next  *DListNode
	prev  *DListNode
}

// Структура для двусвязного списка
type DList struct {
	head *DListNode // private
	tail *DListNode // private
	size int        // private
}

// Конструктор для создания нового двусвязного списка
func NewDList() *DList {
	return &DList{}
}

// Экспортируемый метод для добавления элемента в конец списка
func (d *DList) PushBack(val interface{}) {
	node := &DListNode{value: val}

	if d.tail != nil {
		d.tail.next = node
		node.prev = d.tail
	} else {
		d.head = node
	}
	d.tail = node
	d.size++
}

// Экспортируемый метод для удаления элемента с начала списка
func (d *DList) RemoveForward() {
	if d.size == 0 {
		return
	}

	d.head = d.head.next
	if d.head != nil {
		d.head.prev = nil
	} else {
		d.tail = nil
	}
	d.size--
}

// Экспортируемый метод для получения размера списка
func (d *DList) Size() int {
	return d.size
}

// Неэкспортируемый метод для получения головы списка (private)
func (d *DList) getHead() *DListNode {
	return d.head
}

// Структура для очереди
type Queue struct {
	list *DList // private
}

// Экспортируемый конструктор для создания новой очереди
func NewQueue() *Queue {
	return &Queue{
		list: NewDList(),
	}
}

// Экспортируемый метод для добавления элемента в очередь
func (q *Queue) Enqueue(val interface{}) {
	q.list.PushBack(val)
}

// Экспортируемый метод для извлечения элемента из очереди
func (q *Queue) Dequeue() (interface{}, error) {
	if q.Size() == 0 {
		return nil, errors.New("queue is empty")
	}

	dequeued := q.list.getHead().value
	q.list.RemoveForward()

	return dequeued, nil
}

// Экспортируемый метод для получения размера очереди
func (q *Queue) Size() int {
	return q.list.Size()
}

// Экспортируемый метод для вывода содержимого очереди
func (q *Queue) String() string {
	var result string
	node := q.list.getHead()
	for node != nil {
		result += fmt.Sprintf("%v ", node.value)
		node = node.next
	}
	return result
}
