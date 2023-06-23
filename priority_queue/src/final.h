#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

//总结：
//1.
//
//
//
//
//





namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
    template<typename T, class Compare = std::less<T>>
    class priority_queue {
    private:
        struct node {
            node *l = nullptr;
            node *r = nullptr;
            T data;
            int dis = 1;

            node() {}

            node(const node &other) : data(other.data), dis(other.dis), l(other.l), r(other.r) {}

            node(T data_, node *l_ = nullptr, node *r_ = nullptr, int dis_ = 1) : data(data_), l(l_), r(r_),
                                                                                  dis(dis_) {}
        };

        node *root = nullptr;
        int count = 0;

    public:
        priority_queue() {}

        priority_queue(const priority_queue &other) {
            this->operator=(other);
        }

        void clear(node *&t) {
            if (t == nullptr) return;
            clear(t->l);
            clear(t->r);
            delete t;
            t = nullptr;
        }


        ~priority_queue() {
            clear(root);
            count = 0;
        }


        node *copyTree(node *t) {
            if (!t) return nullptr;
            node *newLeft = nullptr, *newRight = nullptr;
            if (t->l) newLeft = copyTree(t->l);
//            else newLeft= nullptr;
            if (t->r) newRight = copyTree(t->r);
//            else newRight= nullptr;
            node *newTree = new node(t->data, newLeft, newRight, t->dis);
            return newTree;
        }


        priority_queue &operator=(const priority_queue &other) {
            if (this == &other) return *this; // ！！！by kupi
            this->~priority_queue();
            root = copyTree(other.root);
            count = other.count;
            return *this;
        }

        /**
         * get the top of the queue.
         * @return a reference of the top element.
         * throw container_is_empty if empty() returns true;
         */
        const T &top() const {
            if (empty()) throw container_is_empty{};
            return root->data;
        }

        /**
         * push new element to the priority queue.
         */

        void push(const T &e) {
            node *tmp = new node(e);
            /*
            if (empty()) {
                root = tmp;
                count = 1;
            }
            else {
                root = bing(root, tmp);
                ++count;
            }
            */
            // changed the 6 lines under.
            try {
                root = bing(root, tmp);
            } catch (...) {
                delete tmp;               //删除前面new出来的空间
                throw;                   //排除非法比较
            }
            count++;
        }

        /**
         * delete the top element.
         * throw container_is_empty if empty() returns true;
         */

        void pop() {
            if (this->empty()) throw container_is_empty();
            node *tmp = root;
            root = bing(root->l, root->r);
            delete tmp;
            count--;
        }

        /**
         * return the number of the elements.
         */
        size_t size() const {
            return count;
        }

        /**
         * check if the container has at least an element.
         * @return true if it is empty, false if it has at least an element.
         */
        bool empty() const {
            return root == nullptr;
        }

        /**
         * merge two priority_queues with at least O(logn) complexity.
         * clear the other priority_queue.
         */

        void swap(node *&x, node *&y) {
            node *tmp = x;
            x = y;
            y = tmp;
        }


        node *bing(node *x, node *y) {
            if (!x) return y;
            if (!y) return x;
            if (Compare()(x->data, y->data)) swap(x, y);
            x->r = bing(x->r, y);
            if (x->l == nullptr) {
                x->l = x->r;
                x->r = nullptr;
                x->dis = 1;
            } else {
                if (x->r->dis > x->l->dis) swap(x->r, x->l);
                x->dis = x->r->dis + 1;//左偏树性质
            }
            return x;

        }

        void merge(priority_queue &other) {
            root = bing(root, other.root);
            count += other.count;
            // changed the 3lines below.
            other.root = nullptr;
            other.count = 0;
//            clear(other.root);     //错误原因：只是将原来的树加在新树上，不可以删除这个树，只能将其指针赋成nullptr
        }
    };

}

#endif
