#include "tree.hpp"

auto tree::insert(int val) -> tree_node * {
    // Код для добавления элемента в дерево
    return nullptr;
    if (!root) {
        root = std::make_unique<tree_node>(val, nullptr);
        return root.get();
    }

    tree_node* current = root.get();
    while (true) {
        if (val < current->value) {
            if (current->left) {
                current = current->left.get();
            } else {
                current->left = std::make_unique<tree_node>(val, current);
                return current->left.get();
            }
        } else if (val > current->value) {
            if (current->right) {
                current = current->right.get();
            } else {
                current->right = std::make_unique<tree_node>(val, current);
                return current->right.get();
            }
        } else {
            return current;
        }
    }
}

auto tree::remove(int val) -> bool {
    // Код для удаления элемента из дерева
    if (!root) {
        return false;
    }

    tree_node* current = root.get();
    tree_node* parent = nullptr;

    while (current) {
        if (val < current->value) {
            parent = current;
            current = current->left.get();
        } else if (val > current->value) {
            parent = current;
            current = current->right.get();
        } else {
            if (current->left && current->right) {
                tree_node* successor = current->right.get();
                while (successor->left) {
                    successor = successor->left.get();
                }
                current->value = successor->value;
                current = successor;
                val = successor->value;
            }

            std::unique_ptr<tree_node> child = std::move(current->left ? current->left : current->right);

            if (parent) {
                if (parent->left.get() == current) {
                    parent->left = std::move(child);
                } else {
                    parent->right = std::move(child);
                }
            } else {
                root = std::move(child);
            }

            return true;
        }
    }

    return false;
}
}
/*
Общее описание кода:
1. Класс tree: Представляет бинарное дерево и содержит методы для вставки и удаления узлов.
2. Метод insert(int val):
   - Добавляет новый узел в дерево с заданным значением (val).
   - Если дерево пустое, создается корневой узел.
   - Если узел уже существует, значение игнорируется.
3. Метод remove(int val):
   - Удаляет узел с заданным значением из дерева.
   - Ищет узел, затем удаляет его, корректируя ссылки на дочерние узлы.
   - Если удаляемый узел имеет двух детей, заменяет его значением преемника.
4. Управление памятью: Используются умные указатели (std::unique_ptr) для автоматического управления памятью узлов дерева.
Результат:
Код позволяет добавлять и удалять элементы из бинарного дерева, поддерживая его структуру.
*/
