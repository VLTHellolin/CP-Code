#ifndef HELLOLIN_MEMORY_POOL_HPP
#define HELLOLIN_MEMORY_POOL_HPP 1
#include <cassert>
#include <mutex>

template <unsigned long long block_size, unsigned long long block_num = 10>
class memory_pool {
private:
    class free_node_block {
    public:
        char data[block_size];
        free_node_block *nxt;
        free_node_block()
            : nxt(nullptr) {}
    };
    class memory_chunk {
    public:
        free_node_block data[block_num];
        memory_chunk *nxt;
        memory_chunk()
            : nxt(nullptr) {}
    };
    free_node_block *block_head;
    memory_chunk *chunk_head;

    std::mutex mtx, arr_mtx;

public:
    memory_pool() {
        std::lock_guard<std::mutex> lg(mtx);
    }
    ~memory_pool() {
        std::lock_guard<std::mutex> lg(mtx);

        for (memory_chunk *tmp; chunk_head; chunk_head = tmp) {
            tmp = chunk_head->nxt;
            delete chunk_head;
        }
    }
    void *alloc() {
        std::lock_guard<std::mutex> lg(mtx);

        if (!block_head) {
            memory_chunk *tmp = new memory_chunk;

            block_head = &(tmp->data[0]);

            for (unsigned long long i = 0; i < block_num - 1; ++i) {
                tmp->data[i].nxt = &(tmp->data[i + 1]);
            }
            tmp->data[block_num - 1].nxt = nullptr;

            if (chunk_head) {
                chunk_head->nxt = tmp;
            }
            chunk_head = tmp;
        }

        void *r = block_head;
        block_head = block_head->nxt;

        return r;
    }
    // TODO: fix void *alloc(unsigned long long sz)
    // void *alloc(unsigned long long sz) {
    //     std::lock_guard<std::mutex> lg(arr_mtx);

    //     unsigned long long obj = sz / block_size;
    //     assert(obj > 0);
    //     void *r = alloc();

    //     for(unsigned long long i = 1; i < obj; ++i) {
    //         alloc();
    //     }

    //     return r;
    // }
    void free(void *x) {
        std::lock_guard<std::mutex> lg(mtx);

        free_node_block *tmp = static_cast<free_node_block *>(x);
        tmp->nxt = block_head;
        block_head = tmp;
    }
};

#endif