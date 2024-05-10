# DesktopCharacter

https://github.com/ueno-0921/DesktopCharacter/assets/169444519/3d8ce7f1-aff4-4e2e-95fc-db651c57f5e6

## Overview

WindowsAPIを用いて作ったデスクトップマスコットです。  
アプリ本体と操作用のインターフェイスがあります。  
趣味で作った未完成のもので想定外の操作への対策や例外対応などができていません。

## Requirement

- windows
- cl

## Usage

```bat
DesktopCharacter.exe --images sample\images\test1.png --sounds sample\sounds\test1.wav
DCInterface.exe --set_position 0 0
DCInterface.exe --set_position 200 500
DCInterface.exe --move_position 100 -100
DCInterface.exe --chara_edit 2 2 2 sample\images\test2.png sample\sounds\test2.wav
DCInterface.exe --destroy
```

## Features

### DesktopCharacter.exe

デスクトップマスコットの本体です。  
実行時に渡されたオプションをもとに起動します。  
必須なオプションはimagesのみです。

デスクトップマスコットは常にディスプレイの前面に表示されます。  
デスクトップマスコットは左クリックでドラッグできます。  
右クリックで設定した画像群からランダムな画像を表示し、同じインデックスを割り振った音声があれば再生されます。  
ホイールスクロールで画像の拡大縮小ができます。  
ホイールクリックでアプリを終了します。

主なオプション
- [--images]（必須）
  - アプリ内で使用する画像を指定します。
  - 複数の画像ファイルを指定できます。
  - 例：`DesktopCharacter.exe --images sample\images\test1.png sample\images\test2.png`
- [--images_index]
  - 画像に任意の整数インデックスを割り振れます。
  - 使用されない場合0から連番のインデックスが自動で割り振られます。
- [--default_image_index]
  - 画像のインデックスを指定することで起動時に表示される画像を指定できます。
  - 使用されない場合最初の画像が選ばれます。
- [--sounds]
  - アプリ内で使用する音声を指定します。
  - 複数の音声ファイルを指定できます。
- [--sounds_index]
  - 画像に任意の整数インデックスを割り振れます。
  - 使用されない場合0から連番のインデックスが自動で割り振られます。
- [--interrupt_index]
  - 音声が別の音声によって割り込み可能かどうかを指定できます。
  - 使用する場合--soundsと同数の「`true`」か「`false`」を引数として入力します。
  - 使用されない場合「`false`」となってすべての音声が割り込まれないようになります。
- [--click_index]
  - デスクトップマスコットを右クリック時に再生される音声及び表示される画像をインデックスで指定できます。
  - 使用されない場合画像と音声に共通して割り振られているインデックスが選ばれます。
- [--is_true_rand]
  - 「`true`」を指定した場合クリック時のランダム再生に利用する疑似乱数生成器を真正乱数で初期化します。
  - 使用されない場合真正乱数は利用されません。
- [--volume]
  - 0~100の整数で音声のボリュームを指定できます。
  - 使用されない場合100で初期化されます。

### DCInterface.exe

DesktopCharacterのインターフェイスです。  
実行時に渡されたオプションをもとに起動中のDesktopCharacterにメッセージを送信します。

主なオプション
- [--chara_operate]
  - インデックスの指定をすることで画像の表示と音声の再生ができます。
    - インデックスに負の値を指定すると無視されます。
  - 例：1の画像を表示させて2の音声を再生する場合`DCInterface.exe --chara_operate 1 2`
- [--chara_edit]
  - 画像、音声、クリック対応のインデックスの追加ができます。
    - それぞれインデックスが負の値の場合無視されます。
  - 例：インデックス3で画像を追加し、インデックス4で音声を追加する場合`--chara_edit 100 100 -1 D:\DesktopCharacter\sample\images\test1.png D:\DesktopCharacter\sample\sounds\test1.wav`
- [--set_volume]
  - 再生される音声のボリュームを0~100の整数で指定できます。
  - 例：`--set_volume 50`
- [--set_position]
  - 指定した座標に移動させます。
  - 例：`--set_position 0 0`
- [--move_position]
  - 指定した値だけ座標を移動させます。
  - 例：`--move_position 100 -100`
- [--set_size]
  - 指定したサイズに変更できます。




