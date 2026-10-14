# Doctrine sistemi (v0.1)

Her taraf, doktrin binasında iki doktrinden **birini, bir kez** seçer. Seçim kalıcıdır; seçilen doktrinin butonu
"satın alındı" olarak kalır, diğeri kaybolur.

| Taraf | Bina | Doktrin | Verdiği general gücü | İndirim |
|---|---|---|---|---|
| USA | Strategy Center | Network Warfare | Spy Drone | Uçaklar %20 ucuz |
| USA | Strategy Center | Rapid Deployment | Paradrop | Araçlar %15 ucuz |
| China | Propaganda Center | Combined Arms | Frenzy | Piyade %25 ucuz |
| China | Propaganda Center | Siege Warfare | Artillery Barrage | Araçlar %10 ucuz |
| GLA | Palace | Guerrilla Network | Rebel Ambush | Piyade %20 ucuz |
| GLA | Palace | Salvage Economy | Cash Bounty | Araçlar %15 ucuz |

Her doktrin $1500, 45 saniye. Sayılar ilk test değerleri.

## Kurallar

- **General gücü kalıcıdır.** Rütbe şartı aranmaz; doktrin, normalde 1. ya da 3. rütbede açılan gücü hemen verir.
  O güç zaten promosyon puanıyla alınmışsa doktrin ek bir şey vermez.
- **İndirim binaya bağlıdır.** Doktrin binası yıkılır ya da satılırsa indirim durur, bina yeniden kurulunca geri
  gelir. Doktrin binasını korumak bu yüzden önemlidir.
- **İki doktrin aynı anda araştırılamaz:**
  - Butonlar `NOT_QUEUEABLE`: üretim sırasında başka bir şey varken tıklanamaz.
  - China Propaganda Center ve GLA Palace artık tek kurulabilir (`MaxSimultaneousOfType = 1`); Strategy Center
    zaten öyleydi.
  - Etki modüllerinde `ConflictsWith` var: bir şekilde ikisi de tamamlanırsa ilk biten geçerli olur.

## Dosyalar

| Dosya | İçerik |
|---|---|
| `GameFilesEdited/Data/INI/Upgrade/ModDoctrine.ini` | 6 doktrin yükseltmesi (fiyat, süre, ikon) |
| `GameFilesEdited/Data/INI/CommandButton/ModDoctrine.ini` | 6 buton |
| `GameFilesEdited/Data/INI/CommandSet/ModDoctrine.ini` | 12 buton seti (seçim öncesi / sonrası) |
| `GameFilesEdited/Data/INI/Object/FactionBuilding.ini` | Üç binanın modülleri; değişiklikler `; MOD` ile işaretli |
| `GameFilesEdited/Text/ModDoctrine.str` | Oyun içi metinler (İngilizce) |

Yeni tanımlar ayrı dosyalarda durur, çünkü motor `Data\INI\Upgrade.ini` ile birlikte `Data\INI\Upgrade\` klasöründeki
dosyaları da okur (CommandButton, CommandSet ve Object için de aynısı geçerli). Var olan bir objeyi değiştirmek için
ise o objenin bulunduğu dosyanın tamamını kopyalamak gerekir.

## Bilinen sınırlar

- Sadece üç ana tarafta var. Alt generallerin (Airforce, Laser, Superweapon, Tank, Infantry, Nuke, Demo, Toxin,
  Stealth) kendi binaları ayrı INI dosyalarında; onlara sonra eklenecek.
- Skirmish yapay zekâsı doktrin seçmez.
- Düşmanın doktrin binasını ele geçiren oyuncu o tarafın doktrinini de araştırabilir (Strategy Center ve Propaganda
  Center ele geçirilebilir, Palace geçirilemez). Orijinal oyunda da düşman fabrikasını ele geçirip onun birimlerini
  üretmek mümkün; şimdilik bırakıyoruz.
- Bina başına üretim hızı, görüş menzili gibi etkiler INI ile yapılamıyor. Bunlar Faz 3'teki C++ işleri.

## Test listesi

Her taraf için bir skirmish maçında:

1. Doktrin binasını kur. İki doktrin butonu da görünmeli ve tooltip'leri okunmalı.
2. Bir doktrini başlat. Diğer butonun kilitlendiğini gör (sırada iş varken tıklanamaz).
3. Araştırma bitince diğer buton kaybolmalı, seçilen buton "satın alındı" görünmeli.
4. General güçleri çubuğunda doktrinin verdiği güç çıkmalı ve kullanılabilmeli.
5. İndirimli bir birimin fiyatı düşmüş olmalı (USA Rapid Deployment'ta Humvee $700 yerine $595).
6. Doktrin binasını sat: indirim kalkmalı. Yeniden kur: indirim ve seçili buton seti geri gelmeli.
7. China'da Land Mines ve Neutron Mines butonları doktrinden önce ve sonra doğru görünmeli.
