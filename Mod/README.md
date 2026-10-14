# Zero Hour Mod (çalışma adı)

EA has not endorsed and does not support this product.

Bu klasör modun **oyun verilerini** (INI, harita, metin) tutar. Motor (C++) değişiklikleri deponun geri kalanında,
TheSuperHackers/GeneralsGameCode fork'unun içindedir.

## Klasör yapısı

| Yol | Ne var |
|---|---|
| `GameFilesEdited/Data/INI/` | Değiştirdiğimiz ya da eklediğimiz INI dosyaları. Sadece değişen dosyalar burada durur; geri kalanı oyunun kendi `.big` dosyalarından gelir. |
| `GameFilesEdited/Maps/` | Modun haritaları (ör. Crossroads). |
| `Documents/` | Tasarım ve yol haritası. |
| `Mod*.json` | Mod Builder ayarları (hangi dosya hangi `.big` içine girecek). |
| `Scripts/` | Derle / kur / çalıştır / paketle betikleri. |
| `ThirdParty/GeneralsModBuilder` | TheSuperHackers Mod Builder (git submodule, MIT). |

## Gereksinimler

- Zero Hour kurulu olmalı (Steam ya da EA App: *Command & Conquer The Ultimate Collection*).
- Bu depodan derlenmiş `generalszh.exe`, oyun klasörüne kurulmuş olmalı (aşağıya bak).
- İlk çalıştırmada Mod Builder kendi Python ortamını ve araçlarını (`crunch`, `gametextcompiler`,
  `generalsbigcreator`) indirir; ayrıca bir şey kurmak gerekmez.

## Motoru derleme ve kurma

"x86 Native Tools Command Prompt for VS 2022" içinde, deponun kök klasöründe:

```
cmake --preset win32 -DRTS_BUILD_GENERALS=OFF -DRTS_BUILD_GENERALS_TOOLS=OFF "-DRTS_INSTALL_PREFIX_ZEROHOUR=<ZH klasörü>"
cmake --build build/win32 --config Release
cmake --install build/win32 --config Release
```

- `RTS_BUILD_GENERALS=OFF`: sadece Zero Hour derlenir, süre yarıya iner.
- `RTS_INSTALL_PREFIX_ZEROHOUR`: `INIZH.big` dosyasının bulunduğu klasör. Verilmezse kayıt defterinden okunur ve ilk
  `cmake --preset` adımında önbelleğe yazılır.
- `install`, `generalszh.exe` ve `WorldBuilderZH.exe` yanında araçları ve `DebugWindow.dll` / `ParticleEditor.dll`
  dosyalarını da kopyalar. Bu iki DLL EA'nın aynı adlı dosyalarının üzerine yazar; EA'nın kopyaları
  `*.dll.ea-orijinal` olarak yedeklendi. Normal oyunda yüklenmezler, sadece `-scriptDebug` / `-particleEdit` ile.

### EA App kurulumu

EA App, Zero Hour'ı kurulum klasörünün **içindeki** `Command and Conquer Generals Zero Hour` alt klasörüne kurar
(temel Generals dosyaları onun içindeki `ZH_Generals` klasöründedir). Kayıt defterindeki `InstallPath` ise bir üst
klasörü gösterir. Bu yüzden:

- CMake'e ZH klasörü `RTS_INSTALL_PREFIX_ZEROHOUR` ile elle verilir (yukarıda).
- Mod Builder'a da elle verilir: `%LOCALAPPDATA%\TheSuperHackers\GeneralsModBuilder\UserSettings.json`

```json
{
    "userRunner": {
        "version": 1,
        "gameInstallPath": "D:/Command and Conquer Generals Zero Hour/Command and Conquer Generals Zero Hour"
    }
}
```

## Modu deneme

| Betik | Ne yapar |
|---|---|
| `Scripts\BuildInstallRun.bat` | Modu derler, oyuna kurar, oyunu açar, oyun kapanınca modu kaldırır |
| `Scripts\BuildInstall.bat` | Derler ve kurar (oyunu açmaz) |
| `Scripts\Uninstall.bat` | Modu oyun klasöründen kaldırır |
| `Scripts\BuildRelease.bat` | Arkadaşlara gönderilecek zip paketini `.Release/` içine üretir |

Betikler oyun klasörüne yazdığı için yönetici izni ister.

## Arkadaşlara gönderme

Her oyuncunun kendi Zero Hour kopyası olmalı. Gönderilecekler:

1. Bizim derlediğimiz `generalszh.exe`. ZH klasörüne (`INIZH.big` ile aynı yere) kopyalanır.
2. `BuildRelease.bat` çıktısındaki mod `.big` dosyaları.
3. Exe, Microsoft Visual C++ 2015-2022 çalışma zamanını (x86) ister (`VCRUNTIME140.dll`, `MSVCP140.dll`). Arkadaşın
   bilgisayarında yoksa Microsoft'un "Visual C++ Redistributable x86" paketini kurması gerekir.

Multiplayer'da herkes **aynı exe ve aynı mod sürümünü** kullanmalı; yoksa oyun eşleşmez.
EA şartları gereği mod ücretsiz dağıtılır ve tanıtımında C&C logoları kullanılmaz.
