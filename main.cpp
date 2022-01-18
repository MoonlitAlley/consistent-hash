#include <iostream>
#include <vector>
#include <string>
#include "consistent-hash.h"
#include "md5.h"


const int32_t HEX_MAP[256] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 2, 3, 4, 5,  6,  7,  8,  9,  0,  0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0};

int32_t md5_n_prefix(const std::string &md5, int n) {
    if (md5.size() < n) {
        return -1;
    }
    int32_t res = 0;
    for (auto i = 0u; i < n; i++) {
        res += int32_t(pow(16, n - i - 1)) * HEX_MAP[md5[i]];
    }
    return res;
}

int main() {

    /*
    std::vector<std::string> pool {
            "19.21.32.72:56534",
            "19.17.32.71:56534",
            "19.14.65.68:56534",
            "19.17.36.75:56534",
            "19.14.69.73:56568",
            "19.14.65.69:56568",
            "19.17.32.75:56568",
            "19.17.32.73:56568",
    };

    */
    std::vector<std::string> pool {
            "19.21.32.72:56534",
            "19.17.32.71:56534",
            "19.14.65.68:56534",
            "19.17.36.75:56534",
            "19.14.69.73:56568",
            "19.14.65.69:56568",
            "19.17.32.75:56568",
            "19.17.32.73:56568",
            "19.21.32.72:56534",
            "19.17.32.71:56534",
            "19.14.65.68:56534",
            "19.17.36.75:56534",
            "19.14.69.73:56568",
            "19.14.65.69:56568",
            "19.17.32.75:56568",
            "19.17.32.73:56568",
    };

    auto hash_ = shumei::utils::hash::Consistent(pool.size());

    if (!hash_.Valid()) {
        std::cout << "hash invalid" << std::endl;
        return -1;
    }

    hash_.Output();

    auto counterDimension = "organization_serviceId_class_eventId";
    auto md5ProcessKey  = MD5(counterDimension).toStr();
    auto hash = md5_n_prefix(md5ProcessKey, 2);
    auto hash_key = hash_.Hash(hash);
    std::cout << "res[ " << "hash: " << hash << "; hash_key: " << hash_key << "; target ip: " << pool[hash_key] <<  " ]" << std::endl;


    counterDimension = "n_serviceId_appId";
    md5ProcessKey  = MD5(counterDimension).toStr();
    hash = md5_n_prefix(md5ProcessKey, 2);
    hash_key = hash_.Hash(hash);
    std::cout << "res[ " << "hash: " << hash << "; hash_key: " << hash_key << "; target ip: " << pool[hash_key] <<  " ]" << std::endl;

    return 0;
}
