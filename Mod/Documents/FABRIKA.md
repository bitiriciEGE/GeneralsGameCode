# Fabrika modülleri (v0.1, sadece USA)

StarCraft II'deki Reactor / Tech Lab seçiminin Generals hali. Her War Factory **kendi** modülünü bir kez seçer;
aynı fabrika iki modülü birden alamaz, ama iki ayrı fabrika farklı modüller alabilir.

| Modül | Fiyat / süre | Etki |
|---|---|---|
| Logistics Module | $750 / 30 sn | Bu fabrika %25 hızlı üretir (Crusader 10 sn yerine 8 sn) |
| Advanced Systems Module | $1000 / 30 sn | Tomahawk, Paladin ve Microwave Tank yalnızca bu fabrikadan çıkar |

Modülsüz fabrika Crusader, Humvee, Ambulance, Sentry Drone ve Avenger üretir; gelişmiş araçların butonları boş durur.
Tomahawk ve Microwave için Strategy Center, Paladin için general promosyonu yine gerekir.

## Kurallar

- Modül yalnızca üretim sırası boşken kurulabilir (`NOT_QUEUEABLE`); bu yüzden iki modül aynı anda araştırılamaz.
- Modül binaya aittir: fabrika ele geçirilirse modülüyle birlikte gider, yıkılırsa modül de gider.
- **Yapay zekâ:** Skirmish AI modül seçemediği için AI fabrikaları Advanced Systems'ı inşaat bitince bedava alır.
  Böylece AI gelişmiş araçları orijinal oyundaki gibi üretebilir; Logistics hızını ise almaz.

## Motor değişiklikleri (C++)

| Dosya | Değişiklik |
|---|---|
| `GameLogic/Module/ProductionSpeedUpgrade.h/.cpp` | Yeni yükseltme modülü. `SpeedBonus = 25%`: binanın üretimini hızlandırır |
| `GameLogic/Module/ProductionUpdate.h/.cpp` | Bina başına hız çarpanı; kayıt dosyasına da yazılır (xfer sürüm 2) |
| `GameLogic/Module/GrantUpgradeCreate.h/.cpp` | Yeni alan `OnlyForComputerPlayers = Yes`: yükseltmeyi sadece AI oyunculara verir |
| `Common/Thing/ModuleFactory.cpp`, `CMakeLists.txt` | Yeni modülün kaydı |

Hepsi `MOD:` yorumuyla işaretli. `ProductionSpeedUpgrade` başka binalarda da kullanılabilir (ör. China'nın üretim
zinciri).

## INI dosyaları

| Dosya | İçerik |
|---|---|
| `Data/INI/Upgrade/ModFactory.ini` | 2 modül yükseltmesi (`Type = OBJECT`) |
| `Data/INI/CommandButton/ModFactory.ini` | 2 buton |
| `Data/INI/CommandSet/ModFactory.ini` | 3 buton seti: modülsüz, Logistics, Advanced |
| `Data/INI/Object/FactionBuilding.ini` | `AmericaWarFactory` modülleri (`; MOD` ile işaretli) |
| `Text/ModFactory.str` | Oyun içi metinler |

## Bilinen sınırlar

- Sadece ana USA tarafında. Airforce, Laser ve Superweapon generallerinin War Factory'leri orijinal halinde.
- Tasarımdaki "Logistics: temel araçlar daha ucuz" kısmı yok. Fiyat oyuncu başına hesaplandığı için fabrika başına
  indirim üretim kuyruğunda daha derin bir değişiklik ister.
- China (üretim zinciri) ve GLA (hurda seviyeleri) kendi sistemlerini ileride alacak.

## Test listesi

2026-10-15 debug exe ile oyunda denendi: 1-5 çalışıyor. Logistics'li fabrika aynı Crusader'ı Advanced'li fabrikanın
yaklaşık 0,76 katı sürede üretti (beklenen 0,8). AI'nın fabrikaya modülü aldığı debug kaydında görüldü. 6 denenmedi.

1. War Factory kur. Tomahawk, Paladin, Microwave butonları yok; iki modül butonu var.
2. Sırada araç varken modül butonları kilitli olmalı. Boş sırada Logistics'i başlat: Advanced kilitlenmeli.
3. Logistics bitince Advanced butonu kaybolmalı. Crusader üretimi yaklaşık 8 saniye sürmeli.
4. İkinci bir War Factory kur ve Advanced Systems al: üç gelişmiş aracın butonu görünmeli.
5. USA AI'ya karşı oyna: AI Tomahawk / Paladin üretebiliyor olmalı.
6. Logistics'li fabrika varken oyunu kaydet ve yükle: fabrika hâlâ hızlı üretmeli.
