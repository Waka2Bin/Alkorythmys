#pragma once

#include "scopedptr.h"
#include "ptrvector.h"

#include <new> // Для исключения bad_alloc
#include <vector>

// Щупальце
class Tentacle {
public:
    explicit Tentacle(int id) noexcept
        : id_(id) {
    }

    int GetId() const noexcept {
        return id_;
    }

    Tentacle* GetLinkedTentacle() const noexcept {
        return linked_tentacle_;
    }
    void LinkTo(Tentacle& tentacle) noexcept {
        linked_tentacle_ = &tentacle;
    }
    void Unlink() noexcept {
        linked_tentacle_ = nullptr;
    }

private:
    int id_ = 0;
    Tentacle* linked_tentacle_ = nullptr;
};

// Осьминог
class Octopus {
public:
    Octopus()
        : Octopus(8) {
    }
    Tentacle& AddTentacle() {
        Tentacle* tmp = new Tentacle(tentacles_.GetItems().size() + 1);
        ScopedPtr<Tentacle> p(tmp);
        tentacles_.GetItems().push_back(p.Release());
        return *tmp;
    }
    explicit Octopus(int num_tentacles) {
        for (int i = 1; i <= num_tentacles; i++) {
            AddTentacle();
        }
    }

    void swap(Octopus& other) {
        std::swap(tentacles_, other.tentacles_);
    }

    int GetTentacleCount() const noexcept {
        return static_cast<int>(tentacles_.GetItems().size());
    }

    const Tentacle& GetTentacle(size_t index) const {
        return *tentacles_.GetItems().at(index);
    }
    Tentacle& GetTentacle(size_t index) {
        return *tentacles_.GetItems().at(index);
    }

private:
    // Вектор хранит указатели на щупальца. Сами объекты щупалец находятся в куче
    PtrVector<Tentacle> tentacles_;
};