/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2018, The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file Mpi.h
 *
 * C++ friendly support for MPI.
 *
 ***********************************************************************/

#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <set>
#include <stdexcept>
#include <vector>

#include <mpi.h>

namespace souffle {

// TODO (lyndonhenry): should do documentation for this whole file
namespace mpi {

/* typedefs */
namespace {
using Status = std::unique_ptr<MPI_Status>;
}

/* datatype */
namespace {

template <typename T>
inline const MPI_Datatype datatype() {
    return datatype<T>();
};

template <>
inline const MPI_Datatype datatype<short>() {
    return MPI_SHORT;
}

template <>
inline const MPI_Datatype datatype<int>() {
    return MPI_INT;
}

template <>
inline const MPI_Datatype datatype<long>() {
    return MPI_LONG;
}

template <>
inline const MPI_Datatype datatype<long long>() {
    return MPI_LONG_LONG;
}

template <>
inline const MPI_Datatype datatype<unsigned char>() {
    return MPI_UNSIGNED_CHAR;
}

template <>
inline const MPI_Datatype datatype<unsigned short>() {
    return MPI_UNSIGNED_SHORT;
}

template <>
inline const MPI_Datatype datatype<unsigned>() {
    return MPI_UNSIGNED;
}

template <>
inline const MPI_Datatype datatype<unsigned long>() {
    return MPI_UNSIGNED_LONG;
}

template <>
inline const MPI_Datatype datatype<unsigned long long>() {
    return MPI_UNSIGNED_LONG_LONG;
}

template <>
inline const MPI_Datatype datatype<float>() {
    return MPI_FLOAT;
}

template <>
inline const MPI_Datatype datatype<double>() {
    return MPI_DOUBLE;
}

template <>
inline const MPI_Datatype datatype<long double>() {
    return MPI_LONG_DOUBLE;
}

template <>
inline const MPI_Datatype datatype<char>() {
    return MPI_BYTE;
}
}  // namespace

/* getCount */
namespace {

template <typename T>
inline int getCount(std::unique_ptr<MPI_Status>& status) {
    assert(status);
    int count;
    MPI_Get_count(status.get(), datatype<T>(), &count);
    return count;
}
}  // namespace

/* pack */
namespace {

template <typename T>
inline void pack(const T& oldData, std::vector<char>& newData);

template <>
inline void pack<std::vector<std::string>>(
        const std::vector<std::string>& oldData, std::vector<char>& newData) {
    std::vector<int> first = {(int)oldData.size()};
    std::vector<int> second(oldData.size());
    std::vector<char> last;
    size_t i = 0;
    for (auto it = oldData.begin(); it != oldData.end(); ++it) {
        second[i] = (int)it->size();
        last.insert(last.end(), it->begin(), it->end());
        ++i;
    }
    int firstPackSize;
    MPI_Datatype firstType = datatype<int>();
    MPI_Pack_size((int)first.size(), firstType, MPI_COMM_WORLD, &firstPackSize);
    int secondPackSize;
    MPI_Datatype secondType = datatype<int>();
    MPI_Pack_size((int)second.size(), secondType, MPI_COMM_WORLD, &secondPackSize);
    int lastPackSize;
    MPI_Datatype lastType = datatype<char>();
    MPI_Pack_size((int)last.size(), lastType, MPI_COMM_WORLD, &lastPackSize);
    newData.resize((size_t)firstPackSize + secondPackSize + lastPackSize);
    int position = 0;
    MPI_Pack(&first[0], (int)first.size(), firstType, &newData[0], (int)newData.capacity(), &position,
            MPI_COMM_WORLD);
    MPI_Pack(&second[0], (int)second.size(), secondType, &newData[0], (int)newData.capacity(), &position,
            MPI_COMM_WORLD);
    MPI_Pack(&last[0], (int)last.size(), lastType, &newData[0], (int)newData.capacity(), &position,
            MPI_COMM_WORLD);
}
}  // namespace

/* unpack */
namespace {

template <typename T>
inline void unpack(const std::vector<char>& oldData, T& newData);

template <>
inline void unpack<std::vector<std::string>>(
        const std::vector<char>& oldData, std::vector<std::string>& newData) {
    int position = 0;
    std::vector<int> first(1);
    MPI_Unpack(&oldData[0], (int)oldData.size(), &position, &first[0], (int)first.capacity(), datatype<int>(),
            MPI_COMM_WORLD);
    std::vector<int> second((size_t)first.at(0));
    MPI_Unpack(&oldData[0], (int)oldData.size(), &position, &second[0], (int)second.capacity(),
            datatype<int>(), MPI_COMM_WORLD);
    std::vector<char> last(oldData.size() - position);
    MPI_Unpack(&oldData[0], (int)oldData.size(), &position, &last[0], (int)last.capacity(), datatype<char>(),
            MPI_COMM_WORLD);
    auto from = last.begin();
    for (auto length : second) {
        auto to = from + length;
        newData.push_back(std::string(from, to));
        from = to;
    }
}
}  // namespace

/* init */
namespace {
inline int init(int argc, char* argv[]) {
    auto flag = MPI_Init(&argc, &argv);
    return flag;
}
}  // namespace

/* finalize */
namespace {

inline void finalize() {
    MPI_Finalize();
}
}  // namespace

/* commSize */
namespace {
inline int commSize() {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    return size;
}
}  // namespace

/* commRank */
namespace {
inline int commRank() {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    return rank;
}
}  // namespace

/* probe */
namespace {
inline Status probe(const int source, const int tag) {
    auto status = Status(new MPI_Status());
    MPI_Probe(source, tag, MPI_COMM_WORLD, status.get());
    assert(status);

    return status;
}

inline Status probe() {
    return probe(MPI_ANY_SOURCE, MPI_ANY_TAG);
}

inline Status probe(const Status& status) {
    return probe(status->MPI_SOURCE, status->MPI_TAG);
}
}  // namespace

/* iprobe */
namespace {

inline Status iprobe(const int source, const int tag) {
    int flag;
    auto status = Status(new MPI_Status());
    MPI_Iprobe(source, tag, MPI_COMM_WORLD, &flag, status.get());
    return status;
}

inline Status iprobe() {
    return iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG);
}

inline Status iprobe(const Status& status) {
    return iprobe(status->MPI_SOURCE, status->MPI_TAG);
}
}  // namespace

/* send */
namespace {
inline void send(const void* data, const int count, const MPI_Datatype type, const int destination,
        const int tag, const MPI_Comm comm) {
    MPI_Ssend(data, count, type, destination, tag, comm);
}

template <typename S>
inline void send(const std::vector<S>& data, const int destination, const int tag) {
    send(&data[0], (int)data.size(), datatype<S>(), destination, tag, MPI_COMM_WORLD);
}

template <>
inline void send<std::string>(const std::vector<std::string>& data, const int destination, const int tag) {
    std::vector<char> newData;
    pack(data, newData);
    send(&newData[0], (int)newData.size(), MPI_PACKED, destination, tag, MPI_COMM_WORLD);
}

template <>
inline void send<bool>(const std::vector<bool>& data, const int destination, const int tag) {
    // TODO (lyndonhenry): should pack vector of bools as a bitvector
    std::vector<int> newData(data.size());
    size_t i = 0;
    for (const auto element : data) {
        newData[i] = (element) ? 1 : 0;
        ++i;
    }
    send(newData, destination, tag);
}

template <typename S>
inline void send(const S& data, const int destination, const int tag) {
    std::vector<S> newData({data});
    send(newData, destination, tag);
}

template <typename S>
inline void send(const S& data, const Status& status) {
    send(data, status->MPI_SOURCE, status->MPI_TAG);
}

template <typename T>
inline void send(const int destination, const int tag) {
    auto data = std::vector<T>(0);
    send(data, destination, tag);
}

template <typename T>
inline void send(const Status& status) {
    send<T>(status->MPI_SOURCE, status->MPI_TAG);
}

inline void send(const int destination, const int tag) {
    send<char>(destination, tag);
}

inline void send(const Status& status) {
    send<char>(status);
}

template <typename S>
inline void send(const S& data, const std::set<int>& destinations, const int tag) {
    for (const auto destination : destinations) {
        send(data, destination, tag);
    }
}

inline void send(const std::set<int>& destinations, const int tag) {
    auto data = std::vector<char>(0);
    send(data, destinations, tag);
}

template <typename S, typename T>
inline void send(const T& data, const size_t length, const int destination, const int tag) {
    const auto destinations = std::set<int>({destination});
    send<S>(data, length, destinations, tag);
}

template <typename S, typename T>
inline void send(const T& data, const size_t length, const Status& status) {
    send<S>(data, length, status->MPI_SOURCE, status->MPI_TAG);
}
template <typename S, typename T>
inline void send(const T& data, const size_t length, const std::set<int>& destinations, const int tag) {
    assert(length >= 0);
    if (length > 0) {
        std::vector<S> buffer(data.size() * length);
        size_t i = 0;
        for (const auto& element : data) {
            for (size_t j = 0; j < length; ++j) {
                buffer[i] = element[j];
                ++i;
            }
        }
        send(buffer, destinations, tag);
    } else {
        send((!data.empty()), destinations, tag);
    }
}
}  // namespace

/* recv */
namespace {
inline void recv(void* data, const int count, const MPI_Datatype type, const int source, const int tag,
        const MPI_Comm comm, MPI_Status* status) {
    MPI_Recv(data, count, type, source, tag, comm, status);
}

template <typename R>
inline void recv(std::vector<R>& data, Status& status) {
    assert(status);
    int count = getCount<R>(status);
    data.resize((size_t)count);
    recv(&data[0], count, datatype<R>(), status->MPI_SOURCE, status->MPI_TAG, MPI_COMM_WORLD, status.get());
}

template <>
inline void recv<std::string>(std::vector<std::string>& data, Status& status) {
    assert(status);
    int count = getCount<char>(status);
    std::vector<char> newData((size_t)count);
    recv(&newData[0], count, MPI_PACKED, status->MPI_SOURCE, status->MPI_TAG, MPI_COMM_WORLD, status.get());
    unpack(newData, data);
}

template <>
inline void recv<bool>(std::vector<bool>& data, Status& status) {
    // TODO (lyndonhenry): should pack vector of bools as a bitvector
    assert(status);
    std::vector<int> newData;
    recv(newData, status);
    data.resize(newData.size());
    size_t i = 0;
    for (const auto element : newData) {
        data[i] = (element);
        ++i;
    }
}

template <typename R>
inline void recv(R& data, Status& status) {
    std::vector<R> newData;
    recv(newData, status);
    data = newData.at(0);
}

template <typename R>
inline void recv(R& data, const int source, const int tag) {
    auto status = probe(source, tag);
    recv(data, status);
}

template <typename R, typename T>
inline void recv(T& data, const size_t length, const int source, const int tag) {
    auto status = probe(source, tag);
    recv<R>(data, length, status);
}

template <typename T>
inline void recv(const int source, const int tag) {
    auto data = std::vector<T>(0);
    recv(data, source, tag);
}

template <typename T>
inline void recv(Status& status) {
    recv<T>(status->MPI_SOURCE, status->MPI_TAG);
}

inline void recv(const int source, const int tag) {
    recv<char>(source, tag);
}

inline void recv(Status& status) {
    recv<char>(status);
}

template <typename R, typename T>
inline void recv(T& data, const size_t length, Status& status) {
    assert(length >= 0);
    if (length > 0) {
        std::vector<R> newData;
        recv(newData, status);
        auto it = newData.begin();
        while (it != newData.end()) {
            auto element = std::unique_ptr<R[]>(new R[length]());
            for (size_t i = 0; i < length; ++i) {
                element[i] = *it;
                ++it;
            }
            const auto* ptr = element.get();
            data.insert(ptr);
        }
    } else {
        bool islengthotEmpty;
        recv(islengthotEmpty, status);
        if (islengthotEmpty) {
            auto element = std::unique_ptr<R[]>(new R[length]());
            const auto* ptr = element.get();
            data.insert(ptr);
        }
    }
}
}  // namespace
}  // end of namespace mpi
}  // end of namespace souffle
