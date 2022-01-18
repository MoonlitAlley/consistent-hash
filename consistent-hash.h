// Copyright (c) 2017 SHUMEI Inc. All rights reserved.
// Authors: Luo Ruiyang <luoruiyang@ishumei.com>.

#pragma once

#include <iostream>
#include <unordered_map>
#include <math.h>

namespace shumei {
    namespace utils {
        namespace hash {

            namespace {

                const int32_t CONSISTENT_HASH_MAX_ITER = 8;

                int32_t n_bit(int32_t n) {
                    int32_t b = 0;
                    while (n) {
                        b++;
                        n >>= 1;
                    }
                    return b;
                }

                int32_t np_bit(int32_t n, int32_t iter) {
                    n = n & 0xFF;
                    for (auto i = 0u; i < CONSISTENT_HASH_MAX_ITER - iter; i++) {
                        n >>= 1;
                    }
                    return n;
                }
            }

            class Consistent {
            public:
                Consistent(int32_t size) : size_(size) {
                    valid_ = false;
                    if (size_) {
                        hash();
                    }
                }
                ~Consistent() {}

                // -1 failed other success
                int32_t Hash(int32_t key) {
                    if (!Valid()) {
                        return -1;
                    }
                    auto iter_key = np_bit(key, iter_);
                    std::cout << "np_bit_key: " << iter_key << std::endl;
                    if (data_.find(iter_key) == data_.end()) {
                        return -1;
                    }
                    return data_[iter_key];
                }

                bool Valid() { return valid_; }

                void Output() {
                    for (auto i = 0; i < data_.size(); i++) {
                        std::cout << "data item key: " << i << "; value: " << data_[i] << std::endl;
                    }
                }

            private:
                int32_t size_;  // hash total size
                int32_t iter_;  // hash iter size
                bool valid_;
                std::unordered_map<int32_t, int32_t> data_;

                void hash() {
                    iter_ = n_bit(size_ - 1);
                    std::cout << "hash get iter_ :" << iter_ << std::endl;

                    if (iter_ > CONSISTENT_HASH_MAX_ITER) {
                        valid_ = false;
                        return;
                    }

                    int32_t size = (int32_t)pow(2, iter_);
                    int32_t keys[size] = {0};
                    int32_t l = 1;
                    for (auto i = 0u; i < iter_; i++) {
                        for (auto j = 0u; j < l; j++) {
                            keys[j] <<= 1;
                        }
                        for (auto k = l; k < l << 1 && k < size; k++) {
                            keys[k] = keys[k - l] + 1;
                        }
                        l <<= 1;
                    }
                    for (auto i = 0u; i < size; i++) {
                        data_[keys[i]] = i;
                    }

                    if (size_ < size) {
                        int32_t half = size / 2;
                        for (auto i = size_; i < size; i++) {
                            data_[keys[i]] = data_[keys[i - half]];
                        }
                    }
                    valid_ = true;
                }
            };
        }
    }
}
