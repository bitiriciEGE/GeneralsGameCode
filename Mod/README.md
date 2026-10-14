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

- Zero Hour kurulu olmalı (Steam: *Command & Conquer The Ultimate Collection*).
- Bu depodan derlenmiş `generalszh.exe`, oyun klasörüne kurulmuş olmalı (aşağıya bak).
- İlk çalıştırmada Mod Builder kendi Python ortamını ve araçlarını (`crunch`, `gametextcompiler`,
  `generalsbigcreator`) indirir; ayrıca bir şey kurmak gerekmez.

## Motoru derleme ve kurma

"x86 Native Tools Command Prompt for VS 2022" içinde, deponun kök klasöründe:

```
cmake --workflow --preset win32
cmake --install build/win32 --config Release
```

`install`, oyunun klasörünü kayıt defterinden bulur ve `generalszh.exe` dosyasını oraya kopyalar. Klasör ilk
`cmake --preset` adımında okunur; oyunu derlemeden sonra kurduysan `build/win32` klasörünü silip yeniden derle.

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

1. Bizim derlediğimiz `generalszh.exe` (ve yanındaki DLL'ler varsa).
2. `BuildRelease.bat` çıktısındaki mod `.big` dosyaları.

Multiplayer'da herkes **aynı exe ve aynı mod sürümünü** kullanmalı; yoksa oyun eşleşmez.
EA şartları gereği mod ücretsiz dağıtılır ve tanıtımında C&C logoları kullanılmaz.
