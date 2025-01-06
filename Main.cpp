#include "DeadlockManager.h"

int main() {
    // Rastgele oluşumlar için time parametresi ile çağrı yapılır.
    srand(time(0));

    // Sistem parametreleri
    const int NUM_PROCESSES = 5; // İşlem Adeti
    const int NUM_RESOURCES = 3; // Kaynak Adeti

    // Deadlock yöneticisini oluştur
    DeadlockManager manager(NUM_PROCESSES, NUM_RESOURCES, false);

    // Başlangıç durumunu yazdır
    manager.printSystemState("Başlangıç Sistem Durumu:");

    // Deadlock kontrolü
    if (manager.detectDeadlock()) { // Banker's Algoritması
        std::cout << "\nSistemde deadlock tespit edildi!\n";
        
        // Deadlock çözümü
        manager.resolveDeadlock(); // Wait Die Algoritması
        
        // Yeni durumu yazdır
        manager.printSystemState("Deadlock Çözümü Sonrası Sistem Durumu:");
        
        // Çözümün başarısını kontrol et
        if (manager.detectDeadlock(true)) { // true, parametresi 
            std::cout << "\nDeadlock hala devam ediyor. Daha fazla çözüm gerekli.\n";
        } else {
            std::cout << "\nDeadlock başarıyla çözüldü. Sistem güvenli durumda.\n";
        }
    } else {
        std::cout << "\nSistemde deadlock tespit edilmedi.\n";
    }

    return 0;
}