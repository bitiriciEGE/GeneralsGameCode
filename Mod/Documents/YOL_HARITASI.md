# Yol haritası

## Tasarım kuralları

- Tek kaynak: para. Yeni kaynak türü yok.
- Üç taraf (USA, China, GLA) aynı sorunu farklı kurallarla çözer; aynı sistemi üçüne birden kopyalamayız.
- Oyuncuyu üssünden çıkaran harita kontrolü, keşif ve kalıcı stratejik seçimler.
- Önce küçük bir prototip: tek 1v1 harita (Crossroads). Eğlenceli değilse büyütmeyiz.

## Kaynaklar

| Kaynak | Ne için kullanıyoruz |
|---|---|
| `upstream` = TheSuperHackers/GeneralsGameCode | Motor; güncellemeleri buradan çekeriz |
| `ea-original` etiketi | EA'nın orijinal kodu. Bir dosyanın aslını görmek için: `git diff ea-original -- <dosya>` |
| `modding` = Andreas-W/GeneralsGameCode_Modding | Hazır modlama modülleri; gerektiğinde tek tek alınır |
| TheSuperHackers/GeneralsGamePatch | INI dosyalarının metin hali, orijinal (`GameFilesOriginalZH`) ve yamalı (`GameFilesEdited`) |
| TheSuperHackers/GeneralsModBuilder | `.big` üretme, oyuna kurma, sürüm paketi |

## Özellik → motor karşılığı

Modül adlarının hepsinin kodda var olduğu doğrulandı. "C++?" sütunu tahmindir; uygulamaya geçince netleşir.

| Özellik | Kullanılacak motor parçası | C++? |
|---|---|---|
| Doctrine (kalıcı iki yollu seçim) | `Upgrade`, `CommandSetUpgrade`, UpgradeMux `ConflictsWith` | Hayır |
| Fabrika uzmanlaşması (iki modülden biri) | Aynı mekanizma + `CostModifierUpgrade` | Bina başına üretim hızı için muhtemelen evet |
| Yıkılabilir köprü / kaya / bina | `BridgeBehavior`, `RebuildHoleBehavior`, harita objeleri | Hayır |
| Enkaz toplama | `CreateCrateDie`, `SalvageCrateCollide`, `MoneyCrateCollide` | Toplayıcıyı Dozer/Worker ile sınırlamak için belki |
| Radar Relay (içinde piyade varken bölgeyi açar) | `GarrisonContain` + görüş | Muhtemelen küçük bir modül |
| Yeni birimler | `Object`, `Weapon`, `CommandSet` INI'leri; mevcut modeller | Hayır |
| Birim kartında "güçlü / zayıf" bilgisi | Tooltip metinleri | Hayır |

## Fazlar

### Faz 0: Altyapı
- [x] Fork: `bitiriciEGE/GeneralsGameCode`
- [x] Mod Builder entegrasyonu (`Mod/`)
- [x] Visual Studio 2022 + ilk temiz derleme (`generalszh.exe`)
- [x] Oyun kurulumu (EA App), exe'nin oyun klasörüne kurulması, açılış testi (30 sn, pencere modu)
- [ ] Bir skirmish maçının baştan sona oynanması
- [x] Temel INI seti seçimi: orijinal 1.04 (oyunun kendi `INIZH.big` dosyası)
- [x] Mod Builder ile boş bir modun derlenmesi
- [x] Mod Builder ile modun oyuna kurulup oyunla açılması

### Faz 1: Sadece INI
- [ ] Doctrine: USA (Network Warfare / Rapid Deployment), China (Combined Arms / Siege Warfare),
      GLA (Guerrilla Network / Salvage Economy). v0.1 yazıldı, oyunda test bekliyor: [DOCTRINE.md](DOCTRINE.md)
- [ ] Fabrika uzmanlaşması: USA War Factory için Logistics / Advanced Systems. v0.1 yazıldı (bina başına üretim
      hızı için küçük bir C++ modülüyle), oyunda test bekliyor: [FABRIKA.md](FABRIKA.md)
- [ ] Taraf başına bir keşif/destek birimi (USA Forward Observer, China Mobile Surveillance Vehicle, GLA Spotter).
      v0.1 yazıldı, oyunda test bekliyor: [KESIF_BIRIMLERI.md](KESIF_BIRIMLERI.md)
- [x] Birim kartlarına güçlü/zayıf bilgisi: orijinal oyunda zaten var ("Strong vs. / Weak vs." tooltip satırları);
      yeni birimlerin açıklamalarına da eklendi

### Faz 2: Crossroads haritası (WorldBuilder)
- [ ] Ortada Radar Relay (geçici olarak mevcut bir tech binasıyla)
- [ ] Kanatlarda kayalarla kapalı kısa yollar ve petrol kuleleri
- [ ] Yıkılabilir köprü

### Faz 3: Küçük C++ eklemeleri
- [ ] Radar Relay görüş modülü
- [ ] Enkaz toplama. Plan (2026-10-15, kod yazılmadı):
      - C++: `GameData`'ya `ModWreckCrateData` alanı. `Object::onDie` (Object.cpp ~4729, die modüllerinden sonra)
        `VEHICLE` olan, `AIRCRAFT`/`DRONE` olmayan, yarım inşaat olmayan ve müttefikçe öldürülmemiş nesneler için bu
        sandığı bıraksın. Sandığı yerleştirme kodu `CreateCrateDie::createCrate`'ten statik bir yardımcıya taşınıp
        ortak kullanılsın. Yeni modül olmadığı için `MemoryInit` havuzu gerekmez.
      - INI: `Data/INI/GameData/ModWreck.ini` (alan), `Data/INI/Crate/ModWreck.ini` (`CrateData ModWreckCrateData`,
        CreationChance 1.0), `Data/INI/Object/ModWreck.ini` (`ModWreckCrate`, model `PMJnkCrate`, `DeletionUpdate`
        30 sn). Üç `MoneyCrateCollide`: `RequiredKindOf = DOZER` ve `PickupScience` SCIENCE_AMERICA / CHINA / GLA
        ile $50 / $100 / $150. Worker ve Dozer'ların üçü de `DOZER`.
      - Orijinal GLA `SalvageCrateData` (sadece GLA salvager öldürünce) olduğu gibi kalır.
- [x] Bina başına üretim hızı (`ProductionSpeedUpgrade`, fabrika modülleriyle birlikte)

### Faz 4: Test ve dağıtım
- [ ] Arkadaşlarla LAN / sanal LAN testi
- [ ] `BuildRelease.bat` + exe ile sürüm paketi, GitHub Release

### Sonra
Kalan yeni birimler (Bradley, ZBD, Command Tank, Mortar Team, Scavenger Team, EW Stryker), Urban Concealment
bölgeleri, taraf bazlı görüş ağları.
