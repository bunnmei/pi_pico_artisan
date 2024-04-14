# Raspberry pi pico for Artisan

Raspberry pi pico でArtisanに温度データを送るサンプルです。
現状のコードではランダムな数値(0-255)を送っているだけです。
max31855などをつかって、温度を測定したデータに置き換える必要がある。


## Artisan側の設定

構成 > デバイス > ET/BT の中のTC4を選択
COMポートを確認し、通信速度などはデフォルトでOK

ボーレート: 115200
データ長:   8
パリティビット: N
ストップビット: 1
タイムアウト：　0.8

### 参考
[Aruduinoのシンプルな温度のみの送信例](https://github.com/FilePhil/TC4-Emulator)　<- ありがとうございます。
