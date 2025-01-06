#ifndef DEADLOCK_MANAGER_H
#define DEADLOCK_MANAGER_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class DeadlockManager {
private:
    struct SystemState {
        std::vector<std::vector<int>> allocation;     // Tahsis matrisi
        std::vector<std::vector<int>> need;          // İhtiyaç matrisi
        std::vector<std::vector<int>> maximum;       // Maksimum gereksinim matrisi
        std::vector<int> available;                  // Mevcut kaynak vektörü
        int processCount;                            // İşlem sayısı
        int resourceCount;                           // Kaynak sayısı
    };

    // struct SystemState;
    SystemState state;

    // Yardımcı fonksiyonlar
    void initializeState(bool notRandom);
    void initializeFixedState();
    void initializeRandomState();
    bool isProcessFinishable(int processIndex, const std::vector<int>& workingResources) const;
    void releaseResources(int processIndex);

public:
    // Kurucu
    DeadlockManager(int numProcesses, int numResources, bool notRandom);

    // Ana işlevler
    bool detectDeadlock(bool isDoneAlready = false);
    void resolveDeadlock();
    void printSystemState(const std::string& message = "") const;

    // Getter fonksiyonları
    const std::vector<std::vector<int>>& getAllocation() const { return state.allocation; }
    const std::vector<std::vector<int>>& getNeed() const { return state.need; }
    const std::vector<std::vector<int>>& getMaximum() const { return state.maximum; }
    const std::vector<int>& getAvailable() const { return state.available; }
};

#endif