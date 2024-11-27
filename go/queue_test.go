// queue_test.go
package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestQueue(t *testing.T) {
	// Создаем новую очередь
	q := NewQueue()

	// Проверяем размер очереди
	assert.Equal(t, q.Size(), 0, "Queue should be empty initially")

	// Добавляем элементы в очередь
	q.Enqueue(10)
	q.Enqueue(20)
	q.Enqueue(30)

	// Проверяем размер очереди после добавления элементов
	assert.Equal(t, q.Size(), 3, "Queue size should be 3")

	// Проверяем содержимое очереди
	assert.Equal(t, q.String(), "10 20 30 ", "Queue string representation should be '10 20 30'")

	// Извлекаем элемент из очереди
	val, err := q.Dequeue()
	assert.NoError(t, err, "Dequeue should not return an error")
	assert.Equal(t, val, 10, "Dequeued value should be 10")

	// Проверяем размер очереди после извлечения одного элемента
	assert.Equal(t, q.Size(), 2, "Queue size should be 2 after dequeue")

	// Проверяем содержимое очереди после извлечения
	assert.Equal(t, q.String(), "20 30 ", "Queue string representation should be '20 30'")

	// Извлекаем еще один элемент
	val, err = q.Dequeue()
	assert.NoError(t, err, "Dequeue should not return an error")
	assert.Equal(t, val, 20, "Dequeued value should be 20")

	// Проверяем размер очереди после второго извлечения
	assert.Equal(t, q.Size(), 1, "Queue size should be 1 after second dequeue")

	// Проверяем содержимое очереди после второго извлечения
	assert.Equal(t, q.String(), "30 ", "Queue string representation should be '30'")

	// Извлекаем последний элемент
	val, err = q.Dequeue()
	assert.NoError(t, err, "Dequeue should not return an error")
	assert.Equal(t, val, 30, "Dequeued value should be 30")

	// Проверяем размер очереди после третьего извлечения
	assert.Equal(t, q.Size(), 0, "Queue size should be 0 after dequeue all elements")

	// Проверяем, что извлечение из пустой очереди вернет ошибку
	_, err = q.Dequeue()
	assert.Error(t, err, "Dequeue should return an error when the queue is empty")
}
