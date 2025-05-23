# Sosyal Ağ Analiz Sistemi

Bu proje, C dilinde geliştirilmiş graf tabanlı bir sosyal ağ analiz sistemidir. Sistem, kullanıcılar arasındaki ilişkileri temsil eden graf yapısı ve kullanıcı bilgilerini depolayan Kırmızı-Siyah ağaç veri yapısı kullanarak çeşitli sosyal ağ analizleri yapabilir.

## Özellikler

- **Belirli Mesafedeki Arkadaşları Bulma**: DFS algoritması ile kullanıcıdan belirli bir mesafedeki tüm kullanıcıları tespit eder.
- **Ortak Arkadaşları Bulma**: İki kullanıcı arasındaki ortak arkadaşları bulur.
- **Topluluk Tespiti**: Ağ içindeki bağlantılı topluluk gruplarını tespit eder.
- **Etki Alanı Hesaplama**: BFS algoritması ile bir kullanıcının etki alanını hesaplar.
- **Kullanıcı Arama**: Kırmızı-Siyah ağaç yapısı kullanarak hızlı kullanıcı araması yapar.

## Sistem Mimarisi

Proje aşağıdaki bileşenlerden oluşmaktadır:

### 1. Veri Yapıları

- **Graf Yapısı**: Komşuluk listesi kullanarak sosyal bağlantıları temsil eder.
- **Kırmızı-Siyah Ağaç**: Kullanıcı bilgilerini depolayan dengeli bir ikili arama ağacı.
- **Kullanıcı Yapısı**: Kullanıcı bilgilerini tutan basit bir yapı.

### 2. Graf İşlemleri

- Graf oluşturma
- Kenar (arkadaşlık bağı) ekleme
- Bellek temizleme

### 3. Kırmızı-Siyah Ağaç İşlemleri

- Ağaç başlatma ve düğüm oluşturma
- Dengeli ekleme ve renklendirme
- Döndürme operasyonları (sol ve sağ)
- Arama işlemi
- Bellek temizleme

### 4. Analiz Fonksiyonları

- DFS ile belirlenen mesafedeki arkadaşları bulma
- Ortak arkadaşları tespit etme
- Bağlantılı bileşenler kullanarak topluluk tespiti
- BFS ile etki alanı hesaplama

## Dosya Yapısı

- **social_graph.h**: Tüm veri yapıları ve fonksiyon prototiplerini içeren başlık dosyası.
- **graph.c**: Graf yapısı ile ilgili temel işlevleri içerir.
- **rb_tree.c**: Kırmızı-Siyah ağaç yapısı ve işlevlerini içerir.
- **analysis.c**: Sosyal ağ analiz algoritmaları ve işlevlerini içerir.
- **main.c**: Ana program akışı ve kullanıcı arayüzünü içerir.
- **veriseti.txt**: Örnek veri setini içerir.

## Kurulum ve Çalıştırma

1. Projeyi derlemek için aşağıdaki komutu kullanın:
   ```
   gcc -o social_network main.c graph.c rb_tree.c analysis.c
   ```

2. Programı çalıştırmak için:
   ```
   ./social_network
   ```

3. Programı çalıştırdıktan sonra, menüden istediğiniz analiz fonksiyonunu seçebilirsiniz.

## Veri Seti Formatı

`veriseti.txt` dosyası aşağıdaki bölümleri içerir:

1. **Kullanıcılar**: ID ve isim bilgileri
2. **Arkadaşlık İlişkileri**: Hangi kullanıcıların arkadaş olduğunu gösteren ID çiftleri
3. **Kullanıcı Özellikleri**: Yaş, konum ve meslek gibi ek kullanıcı bilgileri
4. **İlgi Alanları**: Her kullanıcının ilgi alanları listesi
5. **Etkileşimler**: Kullanıcılar arasındaki etkileşim sayıları

## Örnek Kullanım

Program başladığında, bir menü arayüzü ile karşılaşacaksınız. Seçenekler:

1. **Belirli mesafedeki arkadaşları bul**: Bir kullanıcının belirli bir mesafedeki arkadaşlarını listeler.
2. **Ortak arkadaşları bul**: İki kullanıcı arasındaki ortak arkadaşları bulur.
3. **Toplulukları tespit et**: Ağdaki farklı toplulukları tespit eder ve listeler.
4. **Kullanıcının etki alanını hesapla**: Bir kullanıcının etkisinin kaç kişiye yayıldığını hesaplar.
5. **Kullanıcı ara**: ID ile kullanıcı bilgilerini arar.
0. **Çıkış**: Programdan çıkış yapar.

## Bellek Yönetimi

Program, dinamik bellek tahsisini kullanarak veri yapılarını oluşturur. Her işlem sonrası kullanılmayan bellek temizlenir. Program çıkışında tüm bellek alanları serbest bırakılır.

## Algoritma Karmaşıklıkları

- Graf oluşturma: O(V)
- Kenar ekleme: O(1)
- Kırmızı-Siyah ağaç ekleme: O(log n)
- Kırmızı-Siyah ağaç arama: O(log n)
- DFS ile arkadaş bulma: O(V + E)
- Ortak arkadaş bulma: O(V)
- Topluluk tespiti: O(V + E)
- Etki alanı hesaplama (BFS): O(V + E)

V: Düğüm sayısı, E: Kenar sayısı, n: Kullanıcı sayısı

## Geliştirme Fırsatları

- Ağırlıklı graf yapısına geçiş yaparak etkileşim seviyelerini hesaba katma
- Daha karmaşık topluluk tespit algoritmaları (Louvain, Girvan-Newman vb.)
- Paralel işlem desteği ekleyerek büyük graf analizlerini hızlandırma
- Dosyadan otomatik veri okuma ve dışa aktarma fonksiyonları ekleme
- Görselleştirme modülü ekleme
