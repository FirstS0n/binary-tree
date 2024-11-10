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
