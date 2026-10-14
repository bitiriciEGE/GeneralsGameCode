# Keşif birimleri (v0.1)

Her tarafa bir keşif/destek birimi. Hepsi orijinal bir birimden türetildi; model, ses ve ölüm efektleri orijinal
birimin. Değişen satırlar `; MOD` ile işaretli.

| Taraf | Birim | Nereden | Fiyat | Temel aldığı birim |
|---|---|---|---|---|
| USA | Forward Observer | Barracks, slot 5 | $300 / 6 sn | Pathfinder |
| China | Mobile Surveillance Vehicle | War Factory, slot 12 | $900 / 15 sn | Listening Outpost |
| GLA | Spotter | Barracks, slot 9 | $200 / 5 sn | Rebel |

## USA Forward Observer

- Lazer işaretleyici (300 menzil). İşaretlenen hedefe ateş eden **herkes** %50 daha hızlı ateş eder; işaret, lazer
  kesildikten sonra 10 saniye sürer. Avenger'ın orijinal `FAERIE_FIRE` mekanizması.
- Dururken görünmez, işaretlerken görünür. Kendiliğinden hedef seçmez; görünmez kalması için işaretlemeyi oyuncu
  başlatır.
- Pathfinder'dan farkı: tüfek yok, görünmez birimleri göremez, general promosyonu gerekmez, yarı fiyat.

## China Mobile Surveillance Vehicle

- **Surveillance Sweep:** haritada seçilen bir alanı kısa süre açar (GLA Radar Van taramasının aynısı, yükseltme
  gerekmez, 45 sn bekleme).
- Kırılgan (180 can), görünmez değil, piyade taşımaz.
- War Factory'de Land Mines / Neutron Mines butonlarının yerini aldı. Mayınlar hâlâ Propaganda Center'dan
  araştırılabilir.

## GLA Spotter

- Silahsız, 450 görüş. Dururken görünmez, hareket ederken görünür.
- SCUD Launcher'ın menzili (350) kendi görüşünden (300) uzun; Spotter'ın gördüğü hedeflere tam menzilden ateş
  edebilir. Rocket Buggy'de menzil ile görüş eşit (300), orada fark yok.

## Dosyalar

| Dosya | İçerik |
|---|---|
| `Data/INI/Object/ModScoutUnits.ini` | Üç birim |
| `Data/INI/Weapon/ModScoutUnits.ini` | Forward Observer işaretleyicisi |
| `Data/INI/SpecialPower/ModScoutUnits.ini` | Surveillance Sweep |
| `Data/INI/CommandButton/ModScoutUnits.ini` | 3 üretim butonu + Sweep butonu |
| `Data/INI/CommandSet/ModScoutUnits.ini` | Birim ve bina buton setleri |
| `Data/INI/Object/FactionBuilding.ini` | Barracks / War Factory'nin buton seti adları; China War Factory'nin mayın set değişimi kaldırıldı |
| `Text/ModScoutUnits.str` | Oyun içi metinler |

## Bilinen sınırlar

- İkonlar şimdilik orijinal: Forward Observer için keskin nişancı nişangâhı, diğer ikisi temel aldıkları birimin
  ikonu.
- Tasarımdaki "konuşlanınca dev radar" yerine hedefli tarama yapıldı; konuşlanma ile görüş değişimi INI ile
  yapılamıyor.
- Alt generallerin Barracks / War Factory'leri orijinal halinde; bu birimler orada yok.
- Yapay zekâ bu birimleri üretmez.

## Test listesi

1. USA Barracks'ta Forward Observer, China War Factory'de Mobile Surveillance Vehicle, GLA Barracks'ta Spotter var.
2. Forward Observer ile bir hedefe "saldır": lazer görünmeli, gözlemci görünür olmalı; hedefe ateş eden birimler
   hızlanmalı. Lazeri kesince 10 sn daha sürmeli.
3. Surveillance Sweep ile uzak bir alanı aç; buton 45 sn beklemeli.
4. Spotter dururken görünmez olmalı (rakip için); SCUD Launcher, Spotter'ın gördüğü hedefe 350 menzilden ateş etmeli.
5. China War Factory'de mayın butonu yok; Land Mines Propaganda Center'da araştırılınca War Factory'nin çevresine de
   mayın döşenmeli.
