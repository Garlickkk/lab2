#include <iostream>
#include <cassert>
#include <string>
#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "array_sequence.hpp"
#include "list_sequence.hpp"
#include "bit_sequence.hpp"
#include "map_reduce_tasks.hpp"

int passed = 0;
int failed = 0;

void runTest(void (*test)(), const std::string& name) {
    try {
        test();
        passed++;
        std::cout << "  [OK] " << name << std::endl;
    } catch (const std::exception& e) {
        failed++;
        std::cout << "  [НЕУДАЧА] " << name << ": " << e.what() << std::endl;
    }
}

// DynamicArray
void test_da() {
    int items[] = {1, 2, 3};
    DynamicArray<int> a(items, 3);
    assert(a.GetSize() == 3);
    assert(a.Get(0) == 1);
    assert(a.Get(2) == 3);

    a.Set(1, 99);
    assert(a.Get(1) == 99);

    a.Resize(5);
    assert(a.GetSize() == 5);
}

// LinkedList
void test_ll() {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    assert(list.GetLength() == 3);
    assert(list.GetFirst() == 1);
    assert(list.GetLast() == 3);

    list.Append(4);
    assert(list.GetLength() == 4);
    assert(list.GetLast() == 4);

    list.Prepend(0);
    assert(list.GetFirst() == 0);

    list.InsertAt(99, 2);
    assert(list.Get(2) == 99);
}

// MutableArraySequence
void test_mas() {
    int items[] = {1, 2, 3};
    MutableArraySequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 3);

    seq.Append(4);
    assert(seq.GetLength() == 4);
    assert(seq.GetLast() == 4);

    seq.Prepend(0);
    assert(seq.GetFirst() == 0);

    seq.InsertAt(99, 2);
    assert(seq.Get(2) == 99);
}

// ImmutableArraySequence
void test_ias() {
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);

    Sequence<int>* newSeq = seq.Append(4);
    assert(seq.GetLength() == 3);  // оригинал не изменился
    assert(newSeq->GetLength() == 4);  // копия изменилась
    assert(newSeq != &seq);

    delete newSeq;
}

// MutableListSequence
void test_mls() {
    int items[] = {1, 2, 3};
    MutableListSequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 3);

    seq.Append(4);
    assert(seq.GetLast() == 4);

    seq.Prepend(0);
    assert(seq.GetFirst() == 0);
}

//ImmutableListSequence
void test_ils() {
    int items[] = {1, 2, 3};
    ImmutableListSequence<int> seq(items, 3);
    assert(seq.GetLength() == 3);

    Sequence<int>* newSeq = seq.Append(4);
    assert(seq.GetLength() == 3);
    assert(newSeq->GetLength() == 4);

    delete newSeq;
}

//Map/Reduce
void test_map_reduce() {
    int items[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> seq(items, 5);

    // Map
    Sequence<int>* mapped = seq.Map([](int x) { return x * 2; });
    assert(mapped->Get(0) == 2);
    assert(mapped->Get(2) == 6);
    delete mapped;

    // Where
    Sequence<int>* filtered = seq.Where([](int x) { return x > 3; });
    assert(filtered->GetLength() == 2);
    assert(filtered->Get(0) == 4);
    delete filtered;

    // Reduce
    int sum = seq.Reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == 15);
}

// MutableBitSequence
void test_mutable_bit() {
    bool items[] = {true, false, true, true};
    MutableBitSequence bs(items, 4);
    assert(bs.GetLength() == 4);
    assert(bs.Get(0) == true);
    assert(bs.Get(1) == false);

    bs.Append(false);
    assert(bs.GetLength() == 5);
    assert(bs.Get(4) == false);
}

//ImmutableBitSequence
void test_immutable_bit() {
    bool items[] = {true, false, true};
    ImmutableBitSequence seq(items, 3);
    assert(seq.GetLength() == 3);

    Sequence<bool>* newSeq = seq.Append(false);
    assert(seq.GetLength() == 3);   // оригинал не изменился
    assert(newSeq->GetLength() == 4); // копия изменилась

    delete newSeq;
}

// П - задачи
void test_tasks() {
    int items[] = {3, 1, 4, 1, 5, 9};
    MutableArraySequence<int> seq(items, 6);

    // П-1
    auto result = computeMinMaxAvg(&seq);
    assert(std::get<0>(result) == 1.0);   // min
    assert(std::get<1>(result) == 9.0);   // max

    // П-2
    int items2[] = {3, 1, 4, 1, 5};
    MutableArraySequence<int> seq2(items2, 5);
    assert(computeMedian(&seq2) == 3.0);

    // П-8
    int items3[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> seq3(items3, 5);
    Sequence<int>* mirror = computeMirrorSum(&seq3);
    assert(mirror->Get(0) == 6);
    assert(mirror->Get(2) == 6);
    delete mirror;
}

void runAllTests() {
    passed = 0;
    failed = 0;

    std::cout << "\nЗапуск тестов\n" << std::endl;

    runTest(test_da, "DynamicArray");
    runTest(test_ll, "LinkedList");
    runTest(test_mas, "MutableArraySequence");
    runTest(test_ias, "ImmutableArraySequence");
    runTest(test_mls, "MutableListSequence");
    runTest(test_ils, "ImmutableListSequence");
    runTest(test_map_reduce, "Map/Reduce/Where");
    runTest(test_mutable_bit, "MutableBitSequence");
    runTest(test_immutable_bit, "ImmutableBitSequence");
    runTest(test_tasks, "П-задачи");

    std::cout << "\n--------------" << std::endl;
    std::cout << "Пройдено: " << passed << ", Не пройдено: " << failed << std::endl;
}