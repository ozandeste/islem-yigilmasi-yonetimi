# İşlem Yığılmasını Yönetme (Process Congestion Management)

Bu proje, işletim sistemlerinde işlem yığılmasını yönetmek amacıyla geliştirilmiştir. Projede deadlock (kilitlenme) durumlarını tespit etmek, çözmek ve güncellenmiş işlem sırasını belirlemek için Banker's Algoritması ve Wait-Die Algoritması kullanılmıştır.

## Özellikler

1. **Deadlock Tespiti**: Sistemde deadlock durumları algılanır.
2. **Durum Yazdırma**: Algılanan deadlock durumları kullanıcıya yazdırılır.
3. **Deadlock Çözme**: Algılanan kilitlenmeler çözülür.
4. **Güncel İşlem Sırası**: Deadlock çözümünden sonra güncellenmiş işlem sırası yazdırılır.

## Kullanılan Algoritmalar

### Banker's Algoritması
Banker's Algoritması, kaynak tahsisi ve deadlock önleme için kullanılan bir yöntemdir. Bu algoritma, sistemin güvenli bir durumda olup olmadığını kontrol eder ve güvenli bir kaynak tahsisi gerçekleştirir.

### Wait-Die Algoritması
Wait-Die Algoritması, deadlock önlemek için işlem önceliklerini kullanan bir algoritmadır. Daha yüksek öncelikli işlem beklerken, düşük öncelikli işlem sonlandırılır.

## Kurulum

1. **Kaynak Kodunu Klonlayın**:
   ```bash
   git clone <repo_url>
   ```
2. **Proje Dosyasını Açın**:
   ```bash
   cd islem-yigilmasi-yonetimi
   ```
3. **Derleyin**:
   ```bash
   make
   ```
4. **Çalıştırın**:
   ```build/main
   ```