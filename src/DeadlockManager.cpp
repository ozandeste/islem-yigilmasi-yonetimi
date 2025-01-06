#include "DeadlockManager.h"

DeadlockManager::DeadlockManager(int numProcesses, int numResources, bool notRandom) {
    // notRandom argümanı = Oluşturulacak işlem rastgele mi bir değere mi bağlı olacak onu söyler.
    state.processCount = numProcesses;  // İşlem Adeti
    state.resourceCount = numResources; // Kaynak Adeti
    
    // Vektörleri boyutlandır
    state.allocation.resize(numProcesses, std::vector<int>(numResources)); // tahsis
    state.maximum.resize(numProcesses, std::vector<int>(numResources));    // maksimum
    state.need.resize(numProcesses, std::vector<int>(numResources));       // ihtiyaç
    state.available.resize(numResources);                                  // mevcutKaynaklar

    // Yeni initialize çağrısı
    initializeState(notRandom);
}

void DeadlockManager::initializeState(bool notRandom) {
    if (notRandom) {
        // Not random ise, belirli değerler ile başlat
        initializeFixedState();
    } else {
        // Random ise, rastgele değerlerle başlat
        initializeRandomState();
    }
}

// 1) Rastgele İşlem Kümesi Oluştur
void DeadlockManager::initializeRandomState() {
    for (int i = 0; i < state.processCount; i++) {
        for (int j = 0; j < state.resourceCount; j++) {
            state.allocation[i][j] = rand() % 5;
            state.maximum[i][j] = state.allocation[i][j] + rand() % 5;
            state.need[i][j] = state.maximum[i][j] - state.allocation[i][j];
        }
    }

    for (int i = 0; i < state.resourceCount; i++) {
        state.available[i] = rand() % 10;
    }
}

// 2) Verilen değerler ile İşlem Kümesi Oluştur
void DeadlockManager::initializeFixedState() {
    // Burada belirli kurallara göre özel durum tanımlayabilirsiniz.
    // Örneğin, sabit bir tahsis matrisi, maksimum ve ihtiyaç matrisleriyle başlatabilirsiniz
    state.allocation = {
        {1, 1, 0},  // İşlem 0
        {1, 0, 2},  // İşlem 1
        {0, 1, 3},  // İşlem 2
        {2, 0, 0},  // İşlem 3
        {3, 2, 1}   // İşlem 4
    };

    state.maximum = {
        {2, 2, 1},  // İşlem 0
        {3, 2, 3},  // İşlem 1
        {1, 1, 4},  // İşlem 2
        {3, 2, 2},  // İşlem 3
        {4, 3, 3}   // İşlem 4
    };
    
    // İhtiyaç matrisi otomatik olarak hesaplanabilir
    for (int i = 0; i < state.processCount; i++) {
        for (int j = 0; j < state.resourceCount; j++) {
            state.need[i][j] = state.maximum[i][j] - state.allocation[i][j];
        }
    }

    // Mevcut kaynakları belirli bir şekilde sabitleyebilirsiniz
    state.available = {0, 0, 0};  // Mevcut kaynaklar
}

bool DeadlockManager::isProcessFinishable(int processIndex, const std::vector<int>& workingResources) const {

    for (int j = 0; j < state.resourceCount; j++) {
        // std::cout << "ihtiyac[i][j]: " << state.need[processIndex][j] << "\n" << "calisanKaynaklar[j]: " << workingResources[j] << std::endl; 
        std::cout << (j == 0 ? "        " : "");
        std::cout << "need: " << state.need[processIndex][j] << ", " << "working: " << workingResources[j] << " | "; 
        std::cout << (j == 2 ? "\n" : "");

        if (state.need[processIndex][j] > workingResources[j]) {
            // İhtiyaç değeri, çalışan kaynak adetinden büyük ise diğer işlemi teste tabi tut.
            std::cout  << "Bir diğer işleme geçiliyor.\n";
            // std::cout  << "Bir diğer işleme geçiliyor.\n\n\n";
            return false;
        }
    }
    return true;
}

// Deadlock Tespiti - Banker's Algorithm
bool DeadlockManager::detectDeadlock(bool isDoneAlready) {
    std::vector<int> work = state.available;               // Çalışan kaynakları, mevcut kaynaklara eşitle.
    std::vector<bool> finished(state.processCount, false); // Process adeti kadar false değerli vektör oluştur.

    std::cout << "----------------------------------------------\n";
    std::cout << "[DEBUG] islemSayisi: " << state.processCount << ", kaynakSayisi: " << state.resourceCount << "\n";

    if(isDoneAlready) {
        std::cout << "[DEBUG] Tekrardan kontrole başlandı...\n";
    }
    else {
        std::cout << "[DEBUG] Deadlock tespit süreci başladı...\n";
    }
    std::cout << "----------------------------------------------\n";


    while (true) {
        bool progress = false;

        for (int i = 0; i < state.processCount; i++) {
            if (!finished[i]) { // Process tamamlanmadıysa buraya girilir.
                std::cout << "[DEBUG] " << i << " kontrol ediliyor." << std::endl;

                if(isProcessFinishable(i, work)) { // Process[index] eğer tamamlanabilirse (yeterli çalışan kaynak var ise) if'e girilir.
                    // Process tamamlanabilir.
                    for (int j = 0; j < state.resourceCount; j++) {
                        work[j] += state.allocation[i][j];
                    }
                    finished[i] = true; // Process, tamamlandı olarak işaretlenir.
                    progress = true;    // Süreç devam edebilmekte.
                }
            }
        }

        if (!progress) {  // Deadlock durumu burada alınır; varsa true, yoksa false.
            return std::any_of(finished.begin(), finished.end(), 
                             [](bool v) { return !v; });
        }
    }
}

// Alınan processIndex'ine göre kaynağı serbest bırakır.
void DeadlockManager::releaseResources(int processIndex) {
    for (int j = 0; j < state.resourceCount; j++) {
        state.available[j] += state.allocation[processIndex][j]; // Mevcut Kaynaklara, tahsis edilen kaynaklar eklenir.
        state.allocation[processIndex][j] = 0;                   // Tahsis değerleri sıfırlanır.
        state.need[processIndex][j] = 0;                         // İhtiyaç değerleri sıfırlanır.
    }

    std::cout << "  Kaynak serbest bırakıldı; " << std::endl;
}

// Deadlock çözümlemesi - WAIT DIE Algoritması
void DeadlockManager::resolveDeadlock() {
    std::vector<std::pair<int, int>> processPriorities;
    
    // Rastgele İşlem önceliklerini oluştur
    for (int i = 0; i < state.processCount; i++) {
        processPriorities.push_back({i, rand() % 100});
    }

    // Önceliklere göre sırala
    std::sort(processPriorities.begin(), processPriorities.end(),
              [](const auto& a, const auto& b) { return a.second < b.second; });

    // Deadlock çözümü
    for (const auto& [process, priority] : processPriorities) {
        bool needsResources = false;
        // Daha fazla kaynağa ihtiyacı olanlar işaretlenir.
        for (int j = 0; j < state.resourceCount; j++) {
            if (state.need[process][j] > state.available[j]) {
                needsResources = true;
                break;
            }
        }

        // Daha fazla kaynağa ihtiyacı var ise işlemi sonlandır, serbest bırak.
        if (needsResources) {
            std::cout << "- İşlem " << process << " sonlandırılıyor (Öncelik: " 
                      << priority << ")\n";
            releaseResources(process);
        }
    }
}

// Sistem durumunu bastırır; işlemler yığınının son durumu.
void DeadlockManager::printSystemState(const std::string& message) const {
    if (!message.empty()) {
        std::cout << "\n" << message << "\n";
    }

    std::cout << "\nMevcut Kaynaklar:\n";
    for (int val : state.available) {
        std::cout << val << " ";
    }

    std::cout << "\n\nTahsis Matrisi:\n";
    for (const auto& row : state.allocation) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nİhtiyaç Matrisi:\n";
    for (const auto& row : state.need) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}