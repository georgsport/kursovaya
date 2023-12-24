#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>

const int MAX_STACK_SIZE = 10;


class Node {
private:
    int key;
    Node* p;
public:
    int getKey() { return this->key; }
    Node* getNode() { return this->p; }
    void setNode(Node* p) { this->p = p; }

    ~Node() {
        delete p;
    }

    Node() : key{ 0 }, p{ nullptr } {}
    Node(int _key) : key{ _key }, p{ nullptr } {}
    Node(int _key, Node* _p) : key{ _key }, p{ _p } {}
};

class Stack {
private:
    int size;
    Node* head;
public:
    void pop() {
        if (this->checkUnderflow()) {
            printf("Стек пуст");
            return;
        }

        Node* buf = this->head;
        this->head = this->head->getNode();
        printf("Удалён верхний элемент стека: %i", buf->getKey());
        buf->setNode(nullptr);
        delete buf;
        this->size -= 1;
    }
    void printStack() {
        if (this->checkUnderflow()) {
            printf("Стек пуст");
            return;
        }
        printf("Верхний элемент стека слева\n");
        Node* buf = this->head;
        while (buf->getNode() != nullptr) {
            printf("%i ", buf->getKey());
            buf = buf->getNode();
        }
        printf("%i ", buf->getKey());
    }
    void push() {
        if (this->checkOverflow()) {
            printf("Стек полон!");
            return;
        }
        printf("Введите новый элемент стека: ");
        int buf;
        std::cin >> buf;
        Node* node = new Node(buf, this->head);
        this->head = node;
        this->size += 1;
    }
    void invertStack() {
        std::vector<Node*> stackCopy;
        Node* buf = this->head;
        while (buf->getNode() != nullptr) {
            stackCopy.push_back(buf);
            buf = buf->getNode();
        }
        stackCopy.push_back(buf);
        std::reverse(stackCopy.begin(), stackCopy.end());
        for (int i = 0; i < stackCopy.size() - 1; i++) {
            stackCopy[i]->setNode(stackCopy[i + 1]);
        }
        stackCopy[stackCopy.size() - 1]->setNode(nullptr);
        this->head = stackCopy.at(0);
    }
    void remove() {
        if (this->checkUnderflow()) {
            printf("Стек пуст");
            return;
        }

        delete this->head;
        this->size = 0;
    }
    void addStack() {}

    int getSize() { return this->size; }
    int getHead() { return this->head->getKey(); }

    bool checkOverflow() {
        return this->size == MAX_STACK_SIZE;
    }
    bool checkUnderflow() {
        return this->size == 0;
    }

    ~Stack() { delete head; }

    Stack() : size{ 0 }, head{ nullptr } {}
};

int main()
{
    setlocale(LC_ALL, "rus");
    Stack* stack = new Stack();
    while (true) {
        system("cls");
        printf(
            "Размер стека: %i\n"
            "Выберите операцию:\n\n"
            "1 - удалить верхний элемент стека\n"
            "2 - вывести стек на экран\n"
            "3 - Добавить элемент в стек\n"
            "4 - инвертировать стек\n"
            "5 - очистить стек\n"
            "6 - добавить стек\n"
            "0 - выход\n"
            "Введите ваш выбор: "
            , stack->getSize());
        char choice;
        std::cin >> choice;
        if (!('0' <= choice <= '6')) continue;
        printf("\n");
        int i = choice - '0';
        switch (i) {
        case 0:
            delete stack;
            return 0;
        case 1:
            stack->pop();
            break;
        case 2:
            stack->printStack();
            break;
        case 3:
            stack->push();
            break;
        case 4:
            stack->invertStack();
            break;
        case 5:
            stack->remove();
            break;
        case 6:
            stack->addStack();
            break;
        }
        printf("\nНажмите Enter, чтобы продолжить...");
        _getch();
    }
}